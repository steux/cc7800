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
    Y = 200;
    do {
        strobe(WSYNC); // 3 cycles
        if (!(*INPT0 & 0x80)) paddle[0] = Y; // Worst case 11 cycles
        if (!(*INPT1 & 0x80)) paddle[1] = Y;
        if (!(*INPT2 & 0x80)) paddle[2] = Y;
        if (!(*INPT3 & 0x80)) paddle[3] = Y;
        Y--;
    } while (Y); // Looping 5 cycles
    // This takes 52 cycles out of 113.5. 50% should be left by Maria
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
