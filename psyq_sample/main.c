#include "main.h"
#include "another_tu.h"
#include <stdio.h>

// volatile var
volatile int volatileVar = 77;

// .sdata var
int sDataVar = 99;

// .sbss var
int sBssVar;

// .bss var
FatStringStructure fatControllerString;

// .data var
FatStringStructure str = { { 'l', 'o', 'l', 0, }, 3 };

// .rdata
const int cantChangeThis = 1234;

extern const OverlayEntries gOverlayFunctions[];

int haha;

void Main_SetVolatileVar(int value)
{
    printf("Set .sdata volatile var via gp to %d\n", value);
    volatileVar = value;

    haha = value;
}

void Main_SetSDataVar(int value)
{
    printf("Set .sdata var via gp to %d\n", value);
    sDataVar = value;
}

void Main_SetSbssVar(int value)
{
    printf("Set .sbss var via gp to %d\n", value);
    sBssVar = value;
}

void Main_SetBssVar(int value)
{
    printf("Set .bss var to %d\n", value);
    fatControllerString.length = value;
}

void Main_SetDataVar(int value)
{
    printf("Set .data var to %d\n", value);
    str.length = value;
}

void Main_UseRDataVar(int value)
{
    printf("Simple maths with .rdata var %d\n", value * cantChangeThis);
}

void Main_TestVarAccess()
{
    printf("Test var access from main.c\n");

    Main_SetVolatileVar(1);
    Main_SetSDataVar(2);
    Main_SetSbssVar(3);
    Main_SetBssVar(4);
    Main_SetDataVar(5);
    Main_UseRDataVar(6);
}

void ExecuteOverlayFunctions()
{
    const OverlayEntries* pIter = &gOverlayFunctions[0];
    while (pIter->name)
    {
        printf("Calling overlay function with name %s\n", pIter->name);
        pIter->functionPointer();
        pIter++;
    }
}

int main()
{
    printf("Main goes pog pog\n");

    Main_TestVarAccess();
    AnotherTU_TestVarAccess();

    // Note: We don't actually load the overlay, this sample is just about codegen, actually loading the overlay bin
    // file from the CD to gOverlayFunctions doesn't really add anything.
    for (;;)
    {
        ExecuteOverlayFunctions();
    }

    printf("Never gonna give you up, never gonna run this code, or exit\n");
}
