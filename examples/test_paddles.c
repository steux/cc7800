#include "prosystem.h"
#include "stdlib.h"
#include "string.h"
#include "armyfont.h"
#define MODE_320AC
#include "multisprite_8lines.h"

unsigned char X, Y;

screencode const char helloworld[] = "HELLO WORLD!";

ramchip char paddle[4];
ramchip char str[5];

void interrupt dli()
{
    *BACKGRND = 0x05;
    do {
        X = *INTIM;
        if (!(*INPT0 & 0x80)) paddle[0] = X;
        if (!(*INPT1 & 0x80)) paddle[1] = X;
        if (!(*INPT2 & 0x80)) paddle[2] = X;
        if (!(*INPT3 & 0x80)) paddle[3] = X;
    } while (X >= 32);
    *VBLANK = 0x80; // Dump paddles to ground
    *BACKGRND = 0x00;
}

void main()
{
    *P0C2 = 0x0f; // White

    multisprite_init();
    multisprite_set_charbase(font);
    multisprite_display_tiles(0, 0, helloworld, 12, 0);
    multisprite_enable_dli(0);
    multisprite_save();

    // Main loop
    do {

        while (!(*MSTAT & 0x80)); // Wait for VBLANK
        *BACKGRND = 0x0f;
        
        do {
            *TIM64T = 255; // That should work since we are out of DMA
        } while (*INTIM != 254);
        *VBLANK = 0x00; // Let paddle capacitors charging 
        
        // Display paddle position
        multisprite_restore();
        itoa(paddle[0], str, 10);
        char len = strlen(str);
        multisprite_display_tiles(0, 1, str, len, 0);
        *BACKGRND = 0x00;

        // Wait for VBLANK to end
        while (*MSTAT & 0x80);
    } while(1);
}
