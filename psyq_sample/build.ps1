param([String]$psyq_path)

$ErrorActionPreference = "Stop"

Push-Location $PSScriptRoot

$oldPathEnv = $Env:path 

Function psyq_setup($psyq_path)
{
    # Setup PSYQ env vars
    $Env:path = $oldPathEnv + ";" + $psyq_path
    $Env:PSYQ_PATH = $psyq_path
    
    # Setup PSYQ ini
    $psyq_path_without_bin = $psyq_path
    if ($psyq_path_without_bin.EndsWith("\bin\", "CurrentCultureIgnoreCase"))
    {
        $psyq_path_without_bin = $psyq_path_without_bin.Substring(0, $psyq_path_without_bin.Length - 5)
    }
    elseif ($psyq_path_without_bin.EndsWith("\bin", "CurrentCultureIgnoreCase"))
    {
        $psyq_path_without_bin = $psyq_path_without_bin.Substring(0, $psyq_path_without_bin.Length - 4)
    }

    $env:C_PLUS_INCLUDE_PATH = "$psyq_path_without_bin\include"
    $Env:c_include_path = "$psyq_path_without_bin\include"
    $env:PSX_PATH = $psyq_path

    (Get-Content $psyq_path\psyq.ini.template) | 
    Foreach-Object {$_ -replace '\$PSYQ_PATH',$psyq_path_without_bin} | 
    Out-File $psyq_path\psyq.ini
}

function compile_c([string] $fileName, [string] $prefixSections, $useG)
{
    # foo.c -> foo.obj
    $objName = $fileName.replace(".C", ".obj").replace(".c", ".obj")

    # invoke compiler to output obj
    if ($useG -eq $true)
    {
        ccpsx.exe "-O2 -mgpopt -g -G 8 $prefixSections -c -Wall $fileName -o$objName"
    }
    else
    {
        ccpsx.exe "-O2 -g -G 4 $prefixSections -c -Wall $fileName -o$objName"
    }

    if($LASTEXITCODE -eq 0)
    {
        Write-Host "Compiled $fileName" -ForegroundColor "green"
    }
    else
    {
        Write-Error "Compilation failed for: ccpsx.exe -O2 -g -c -Wall $fileName -o$objName"
    }
}

Write-Host "Setup psyq" -ForegroundColor "DarkMagenta" -BackgroundColor "Black"
psyq_setup($psyq_path)


Write-Host "Compile C source" -ForegroundColor "DarkMagenta" -BackgroundColor "Black"
compile_c("$PSScriptRoot\main.c", "", $true)
compile_c("$PSScriptRoot\another_tu.c", "", $true)
# Stupid undocumented assembler command to prefix all sections with a name
# so we can export the whole group to a file for overlays
compile_c("$PSScriptRoot\overlay1.c", "-Wa,sover1", $false)
compile_c("$PSScriptRoot\overlay2.c", "-Wa,sover2", $true)

asmpsx.exe /l /q $PSScriptRoot\gOverlayFunctions.s,$PSScriptRoot\gOverlayFunctions.obj

# Run the linker
Write-Host "link" -ForegroundColor "DarkMagenta" -BackgroundColor "Black"
psylink.exe /n 512 /c /m /gp .sdata "@$PSScriptRoot\linker_command_file.txt",$PSScriptRoot\output.cpe,$PSScriptRoot\output.sym,$PSScriptRoot\output.map
if($LASTEXITCODE -eq 0)
{
    Write-Host "Linked output.cpe" -ForegroundColor "yellow"
} 
else 
{
    Write-Error "Linking failed $LASTEXITCODE"
}

# Convert CPE to an EXE
Write-Host "cpe2exe" -ForegroundColor "DarkMagenta" -BackgroundColor "Black"
cpe2exe.exe /CJ output.cpe | out-null

if($LASTEXITCODE -eq 0)
{
    Write-Host "output.cpe -> output.exe" -ForegroundColor "yellow"
} 
else 
{
    Write-Error "Converting CPE to EXE failed"
}
