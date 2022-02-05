#ifndef _MAIN_VARS_EXTERNED_H_
#define _MAIN_VARS_EXTERNED_H_

#include "main.h"

// If main.c ever sees these extern declares it will no longer use $gp for them... ever, madness but it is what is

// volatile var
extern volatile int volatileVar;

// .sdata var
extern int sDataVar;

// .sbss var
extern int sBssVar;

// .bss var
extern FatStringStructure fatControllerString;

// .data var
extern FatStringStructure str;

// .rdata
extern const int cantChangeThis;

#endif // _MAIN_VARS_EXTERNED_H_
