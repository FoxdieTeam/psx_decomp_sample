#include "main.h"
#include "another_tu.h"
#include <stdio.h>

void Overlay1_Function1();

const OverlayEntries gOverlay1Functions[] = 
{
    { "Overlay1_Function1",  Overlay1_Function1 },
    { 0, 0}
};

// volatile var
volatile int overlayvolatileVar = 7722;

// .sdata var
int overlaysDataVar = 3232;

// .sbss var
int overlaysBssVar;

// .bss var
FatStringStructure overlayfatControllerString;

// .data var
FatStringStructure overlaystr = { { 'b', 'o', 'o', 'm', 0, }, 4 };

// .rdata
const int overlaycantChangeThis = 997711;

void Overlay1_SetVolatileVar(int value)
{
    printf("Set .sdata volatile var (not) via gp to %d\n", value);
    overlayvolatileVar = value;
}

void Overlay1_SetSDataVar(int value)
{
    printf("Set .sdata var (not) via gp to %d\n", value);
    overlaysDataVar = value;
}

void Overlay1_SetSbssVar(int value)
{
    printf("Set .sbss var (not) via gp to %d\n", value);
    overlaysBssVar = value;
}

void Overlay1_SetBssVar(int value)
{
    printf("Set .bss var to %d\n", value);
    overlayfatControllerString.length = value;
}

void Overlay1_SetDataVar(int value)
{
    printf("Set .data var to %d\n", value);
    overlaystr.length = value;
}

void Overlay1_Function1()
{
    printf("Overlay1_Function1\n");
    Overlay1_SetVolatileVar(11);
    Overlay1_SetSDataVar(22);
    Overlay1_SetSbssVar(33);
    Overlay1_SetBssVar(44);
    Overlay1_SetDataVar(55);
}
