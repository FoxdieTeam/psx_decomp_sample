#ifndef _MAIN_H_
#define _MAIN_H_

#define SECTION(x) __attribute__((section(x)))

typedef void (*TOverlayFunction)(void);

typedef struct OverlayEntries
{
    const char* name;
    TOverlayFunction functionPointer;
} OverlayEntries;

typedef struct FatStringStructure
{
    char someString[69];
    int length;
} FatStringStructure;

void Main_TestVarAccess();

#endif // _MAIN_H_
