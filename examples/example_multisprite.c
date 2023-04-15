#include "prosystem.h"
#include "multisprite.h"

char xpos, ypos;
holeydma scattered(16, 1) char sprite[16] = { 0x3c, 0x3c, 0x42, 0x42, 0x99, 0x99, 0xa5, 0xa5, 0x81, 0x81, 0xa5, 0xa5, 0x42, 0x42, 0x3c, 0x3c };

void main()
{
    xpos = 100; ypos = 100;
    multisprite_init();
    *P0C1 = 0x18; // Setup Palette 0
    *P0C2 = 0x38;
    *P0C3 = 0x58;
    multisprite_display_sprite(64, 64, sprite, 1, 0); 
    multisprite_display_sprite(xpos, ypos, sprite, 1, 0); 
    while (!(*MSTAT & 0x80)); // Wait for VBLANK
    multisprite_flip();
    while (*MSTAT & 0x80);
    // Main loop
    do {
        while (!(*MSTAT & 0x80)); // Wait for VBLANK
        xpos++;
        if (xpos >= 160) xpos = 0;
        ypos++;
        if (ypos >= 200) ypos = 0;
        multisprite_display_sprite(64, 64, sprite, 1, 0); 
        multisprite_display_sprite(xpos, ypos, sprite, 1, 0); 
        multisprite_flip();
        // Wait for VBLANK to end
        while (*MSTAT & 0x80);
    } while(1);
}
