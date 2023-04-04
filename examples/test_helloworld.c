#include "prosystem.h"
#include "armyfont.h"

char i;
unsigned char X, Y;
char *dlpnt;

ramchip char dl0[32], dl1[32], dl2[32], dl3[32], dl4[32], dl5[32], dl6[32], dl7[32], dl8[32], dl9[32];
ramchip char dl10[32], dl11[32], dl12[32], dl13[32], dl14[32], dl15[32], dl16[32], dl17[32], dl18[32], dl19[32];
ramchip char dl20[32], dl21[32], dl22[32], dl23[32];

#ifdef PAL
#define DLL_ARRAY_SIZE 30 
ramchip char dl24[32], dl25[32], dl26[32], dl27[32], dl28[32], dl29[32];
const char *dls[DLL_ARRAY_SIZE] = { 
    dl0, dl1, dl2, dl3, dl4, dl5, dl6, dl7, dl8, dl9, 
    dl10, dl11, dl12, dl13, dl14, dl15, dl16, dl17, dl18, dl19, 
    dl20, dl21, dl22, dl23, dl24, dl25, dl26, dl27, dl28, dl29 
};
#else
#define DLL_ARRAY_SIZE 24 
const char *dls[DLL_ARRAY_SIZE] = { 
    dl0, dl1, dl2, dl3, dl4, dl5, dl6, dl7, dl8, dl9, 
    dl10, dl11, dl12, dl13, dl14, dl15, dl16, dl17, dl18, dl19, 
    dl20, dl21, dl22, dl23 
};
#define YMAX (192 - 16)
#endif
ramchip char dll[(DLL_ARRAY_SIZE + 4) * 3];
char dlend[DLL_ARRAY_SIZE];

screencode char helloworld[] = "HELLO WORLD!";

void main()
{
    // Build DLL
    // 25 blank lines
    dll[X = 0] = 0x0f;  // 16 lines
    dll[++X] = 0x21; // 0x2100 = Blank DL
    dll[++X] = 0x00;
    dll[++X] = 0x08; // 9 lines
    dll[++X] = 0x21; // 0x2100 = Blank DL
    dll[++X] = 0x00;
    for (Y = 0; Y != DLL_ARRAY_SIZE; Y++) {
        dll[++X] = 0x07; // 8 lines
        dll[++X] = dls[Y] >> 8; // High address
        dll[++X] = dls[Y]; // Low address
    }
    // 26 blank lines
    dll[++X] = 0x0f; // 16 lines
    dll[++X] = 0x21; // 0x2100 = Blank DL
    dll[++X] = 0x00;
    dll[++X] = 0x09; // 10 lines
    dll[++X] = 0x21; // 0x2100 = Blank DL
    dll[++X] = 0x00;

    // Setup Maria registers
    *CHARBASE = (font >> 8);
    *DPPH = dll >> 8;
    *DPPL = dll;
    *P0C1 = 0x18; // Setup Palette 0
    *P0C2 = 0x38;
    *P0C3 = 0x58;
    *CTRL = 0x43; // Enable DMA

    // Reset DL ends
    for (X = DLL_ARRAY_SIZE - 1; X >= 0; X--) {
        dlend[X] = 0;
    }

    // Build DL entries
    dlpnt = dls[X = 0];

    // Create DL entry for upper part of sprite
    Y = dlend[X];
    dlpnt[Y++] = helloworld; // Low byte of data address
    dlpnt[Y++] = 0x60; // Mode 320x1, Indirect mode
    dlpnt[Y++] = (helloworld >> 8);
    dlpnt[Y++] = (-12 & 0x1f); // Palette 0, 32 characters to display
    dlpnt[Y++] = 0; // Horizontal position
    dlend[X] = Y;

    // Add DL end entry on each DL
    for (X = DLL_ARRAY_SIZE - 1; X >= 0; X--) {
        dlpnt = dls[X];
        Y = dlend[X];
        dlpnt[++Y] = 0; 
    }

    // Main loop
    do {

        while (!(*MSTAT & 0x80)); // Wait for VBLANK

        // Wait for VBLANK to end
        while (*MSTAT & 0x80);
    } while(1);
}
