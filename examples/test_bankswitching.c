#include "prosystem.h"

char i;
unsigned char X, Y;
unsigned char xpos, ypos;
char *dlpnt;

holeydma scattered(16,1) char sprite[16] = { 0x3c, 0x3c, 0x42, 0x42, 0x99, 0x99, 0xa5, 0xa5, 0x81, 0x81, 0xa5, 0xa5, 0x42, 0x42, 0x3c, 0x3c };
ramchip char dl0[64], dl1[64], dl2[64], dl3[64], dl4[64], dl5[64], dl6[64], dl7[64], dl8[64], dl9[64], dl10[64], dl11[64];
#ifdef PAL
#define DLL_ARRAY_SIZE 15 
#define YMAX (240 - 16)
ramchip char dl12[64], dl13[64], dl14[64];
const char *dls[DLL_ARRAY_SIZE] = { dl0, dl1, dl2, dl3, dl4, dl5, dl6, dl7, dl8, dl9, dl10, dl11, dl12, dl13, dl14 };
#else
#define DLL_ARRAY_SIZE 12 
#define YMAX (192 - 16)
const char *dls[DLL_ARRAY_SIZE] = { dl0, dl1, dl2, dl3, dl4, dl5, dl6, dl7, dl8, dl9, dl10, dl11 };
#endif
ramchip char dll[(DLL_ARRAY_SIZE + 4) * 3];
char dlend[DLL_ARRAY_SIZE];

bank2 void init()
{
    *BACKGRND = 0xff;

    // Build DLL
    // 25 blank lines
    dll[X = 0] = 0x4f;  // 16 lines
    dll[++X] = 0x21; // 0x2100 = Blank DL
    dll[++X] = 0x00;
    dll[++X] = 0x48; // 9 lines
    dll[++X] = 0x21; // 0x2100 = Blank DL
    dll[++X] = 0x00;
    // 192 lines divided into 12 regions
    for (Y = 0; Y != DLL_ARRAY_SIZE; Y++) {
        dll[++X] = 0x4f; // 16 lines
        dll[++X] = dls[Y] >> 8; // High address
        dll[++X] = dls[Y]; // Low address
    }
    // 26 blank lines
    dll[++X] = 0x4f; // 16 lines
    dll[++X] = 0x21; // 0x2100 = Blank DL
    dll[++X] = 0x00;
    dll[++X] = 0x49; // 10 lines
    dll[++X] = 0x21; // 0x2100 = Blank DL
    dll[++X] = 0x00;

    // Setup Maria registers
    *DPPH = dll >> 8;
    *DPPL = dll;
    *P0C1 = 0x18; // Setup Palette 0
    *P0C2 = 0x38;
    *P0C3 = 0x58;
    *CTRL = 0x4b; // Enable DMA
    *CTLSWA = 0; // Setup ports to read mode
    *CTLSWB = 0;
}

void main()
{
    init();

    xpos = 64;
    ypos = 64;

    // Main loop
    do {

        while (!(*MSTAT & 0x80)); // Wait for VBLANK

        if (!(*SWCHA & 0x80)) { // Pushed right ?
            xpos++; // Move right
        }
        if (!(*SWCHA & 0x40)) { // Pushed left ?
            xpos--;
        }
        if (!(*SWCHA & 0x20)) { // Pushed down ?
            if (ypos != YMAX) ypos++;
        }
        if (!(*SWCHA & 0x10)) { // Pushed up ?
            if (ypos != 0) ypos--;
        }

        // Reset DL ends
        for (X = DLL_ARRAY_SIZE - 1; X >= 0; X--) {
            dlend[X] = 0;
        }

        // Build DL entries
        X = ypos >> 4;
        dlpnt = dls[X];

        // Create DL entry for upper part of sprite
        Y = dlend[X];
        dlpnt[Y++] = sprite; // Low byte of data address
        dlpnt[Y++] = 0x40; // Mode 320x1
        i = ypos & 0x0f;
        dlpnt[Y++] = (sprite >> 8) | i;
        dlpnt[Y++] = 0x1f; // Palette 0, 1 byte wide  
        dlpnt[Y++] = xpos; // Horizontal position
        dlend[X] = Y;

        if (ypos & 0x0f) { // Is the sprite lying on another region ?
            X++;
            dlpnt = dls[X]; // Point to the next region
            Y = dlend[X];
            dlpnt[Y++] = sprite; // Low byte of data address
            dlpnt[Y++] = 0x40; // Mode 320x1
            dlpnt[Y++] = ((sprite - 0x1000) >> 8) | i;
            dlpnt[Y++] = 0x1f; // Palette 0, 1 byte wide  
            dlpnt[Y++] = xpos; // Horizontal position
            dlend[X] = Y;
        }

        // Add DL end entry on each DL
        for (X = DLL_ARRAY_SIZE - 1; X >= 0; X--) {
            dlpnt = dls[X];
            Y = dlend[X];
            dlpnt[++Y] = 0; 
        }

        // Wait for VBLANK to end
        while (*MSTAT & 0x80);
    } while(1);
}
