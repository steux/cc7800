#include "prosystem.h"
#include "armyfont.h"
#define MODE_320AC
#include "multisprite_8lines.h"

unsigned char X, Y;

screencode const char helloworld[] = "HELLO WORLD!";

void main()
{
    *P0C2 = 0x07; // Grey
    *P1C2 = multisprite_color(0x87); // Blue
    *P2C2 = multisprite_color(0xDA); // Green
    *P3C2 = multisprite_color(0x9C); // Cyran
    *P4C2 = multisprite_color(0x32); // Red
    *P5C2 = multisprite_color(0x36); // Brown
    *P6C2 = multisprite_color(0x1D); // Yellow
    *P7C2 = 0x0f; // White

    multisprite_init();
    multisprite_set_charbase(font);
    multisprite_display_tiles(0, 0, helloworld, 12, 0);

    // Main loop
    do {

        while (!(*MSTAT & 0x80)); // Wait for VBLANK

        // Wait for VBLANK to end
        while (*MSTAT & 0x80);
    } while(1);
}
