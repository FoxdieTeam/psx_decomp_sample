#include "main_vars_externed.h"
#include "another_tu.h"
#include <stdio.h>

void Overlay2_Function1();
void Overlay2_Function2();

const OverlayEntries gOverlay2Functions[] = 
{
    { "Overlay2_Function1",  Overlay2_Function1 },
    { "Overlay2_Function1",  Overlay2_Function2 },
    { 0, 0}
};

void Overlay2_SetVolatileVar(int value)
{
    printf("Set .sdata volatile var (not) via gp to %d\n", value);
    volatileVar = value;
}

void Overlay2_SetSDataVar(int value)
{
    printf("Set .sdata var (not) via gp to %d\n", value);
    sDataVar = value;
}

void Overlay2_SetSbssVar(int value)
{
    printf("Set .sbss var (not) via gp to %d\n", value);
    sBssVar = value;
}

void Overlay2_SetBssVar(int value)
{
    printf("Set .bss var to %d\n", value);
    fatControllerString.length = value;
}

void Overlay2_SetDataVar(int value)
{
    printf("Set .data var to %d\n", value);
    str.length = value;
}

void Overlay2_UseRDataVar(int value)
{
    printf("Simple maths with .rdata var %d\n", value * cantChangeThis);
}

void Overlay2_Function1()
{
    Overlay2_SetVolatileVar(12);
    Overlay2_SetSDataVar(13);
    Overlay2_SetSbssVar(14);
    Overlay2_SetBssVar(15);
    Overlay2_SetDataVar(16);
    Overlay2_UseRDataVar(17);
}

const int overlay2rDataVar = 1998;

void Overlay2_Function2()
{
    printf("Over2 .rdata var = %d\n", overlay2rDataVar);

    // Call function that lives in the main executable
    Main_TestVarAccess();
}
