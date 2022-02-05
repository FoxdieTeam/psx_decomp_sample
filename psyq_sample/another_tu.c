#include "another_tu.h"
#include "main_vars_externed.h"
#include <stdio.h>

void AnotherTU_SetVolatileVar(int value)
{
    printf("Set .sdata volatile var (not) via gp to %d\n", value);
    volatileVar = value;
}

void AnotherTU_SetSDataVar(int value)
{
    printf("Set .sdata var (not) via gp to %d\n", value);
    sDataVar = value;
}

void AnotherTU_SetSbssVar(int value)
{
    printf("Set .sbss var (not) via gp to %d\n", value);
    sBssVar = value;
}

void AnotherTU_SetBssVar(int value)
{
    printf("Set .bss var to %d\n", value);
    fatControllerString.length = value;
}

void AnotherTU_SetDataVar(int value)
{
    printf("Set .data var to %d\n", value);
    str.length = value;
}

void AnotherTU_UseRDataVar(int value)
{
    printf("Simple maths with .rdata var %d\n", value * cantChangeThis);
}

void AnotherTU_TestVarAccess()
{
    printf("Test var access from another_tu.c\n");

    AnotherTU_SetVolatileVar(1);
    AnotherTU_SetSDataVar(2);
    AnotherTU_SetSbssVar(3);
    AnotherTU_SetBssVar(4);
    AnotherTU_SetDataVar(5);
    AnotherTU_UseRDataVar(6);
}
