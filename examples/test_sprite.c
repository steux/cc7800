#include "prosystem.h"

char i;
unsigned char X, Y;
unsigned char xpos, ypos;
char dlend[12];
char *dlpnt;

holeydma scattered(16, 1) char sprite[16] = { 0x3c, 0x3c, 0x42, 0x42, 0x99, 0x99, 0xa5, 0xa5, 0x81, 0x81, 0xa5, 0xa5, 0x42, 0x42, 0x3c, 0x3c };
ramchip char dll[16 * 3];
ramchip char dl0[64];
ramchip char dl1[64], dl2[64], dl3[64], dl4[64], dl5[64], dl6[64], dl7[64], dl8[64], dl9[64], dl10[64], dl11[64];
ramchip char *dls[12] = { dl0, dl1, dl2, dl3, dl4, dl5, dl6, dl7, dl8, dl9, dl10, dl11 };

void main()
{
    // Build DLL
    // 20 blank lines
    dll[X = 0] = 0x4f;  // 16 lines
    dll[++X] = 0x21; // 0x2100 = Blank DL
    dll[++X] = 0x00;
    dll[++X] = 0x44; // 4 lines
    dll[++X] = 0x21; // 0x2100 = Blank DL
    dll[++X] = 0x00;
    // 192 lines divided into 12 regions
    for (Y = 0; Y != 12; Y++) {
        dll[++X] = 0x4f; // 16 lines
        dll[++X] = dls[Y] >> 8; // High address
        dll[++X] = dls[Y]; // Low address
    }
    // 26 blank lines
    dll[++X] = 0x4f; // 16 lines
    dll[++X] = 0x21; // 0x2100 = Blank DL
    dll[++X] = 0x00;
    dll[++X] = 0x4a; // 10 lines
    dll[++X] = 0x21; // 0x2100 = Blank DL
    dll[++X] = 0x00;

    // Setup Maria registers
    *DPPH = dll >> 8;
    *DPPL = dll;
    *P0C1 = 0x18; // Setup Palette 0
    *P0C2 = 0x38;
    *P0C3 = 0x58;
    *CTRL = 0x43; // Enable DMA
    *CTLSWA = 0; // Setup ports to read mode
    *CTLSWB = 0;

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
            if (ypos != 176) ypos++;
        }
        if (!(*SWCHA & 0x10)) { // Pushed up ?
            if (ypos != 0) ypos--;
        }

        // Reset DL ends
        for (X = 11; X >= 0; X--) {
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
            i ^= 0x0f;
            dlpnt[Y++] = (sprite >> 8) - i;
            dlpnt[Y++] = 0x1f; // Palette 0, 1 byte wide  
            dlpnt[Y++] = xpos; // Horizontal position
            dlend[X] = Y;
        }

        // Add DL end entry on each DL
        for (X = 11; X >= 0; X--) {
            dlpnt = dls[X];
            Y = dlend[X];
            dlpnt[++Y] = 0; 
        }

        // Wait for VBLANK to end
        while (*MSTAT & 0x80);
    } while(1);
}
