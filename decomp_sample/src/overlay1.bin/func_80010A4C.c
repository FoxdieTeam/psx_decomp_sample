
extern int func_8001079C(const char* format, ...); // printf

extern const char D_8001094C[]; // Set .data var to %d
extern int D_80010B18;

void func_80010A4C(int value) // Overlay1_SetDataVar
{
    func_8001079C(D_8001094C, value);
    D_80010B18 = value;
}
