#include "prosystem.h"
#include "multisprite.h"

#include "example_dobkeratops_gfx.c"

const char dobkeratops_x[] = {0, 0, 6, 6, 37, 35, 37, 37, 40, 25, 0};
const char dobkeratops_y[] = {0, 16, 32, 48, 64, 80, 96, 112, 128, 144, 160};
const char dobkeratops_nbbytes[] = {37, 36, 24, 34, 16, 19, 18, 19, 17, 19, 37};
const char *dobkeratops_gfx[] = {dob1, dob2, dob3, dob4, dob5, dob6, dob7, dob8, dob9, dob10, dob11};

void draw_dobkeratops(char xpos, char ypos)
{
    char c;
    for (c = 0; c != 11; c++) {
        char x = dobkeratops_x[X = c] + xpos;
        char y = dobkeratops_y[X] + ypos;
        char *gfx = dobkeratops_gfx[X];
        char nbbytes = dobkeratops_nbbytes[X];
        if (nbbytes > 31) {
            multisprite_display_sprite_aligned(x, y, gfx, 31, 0, 1);
            x += 62;
            nbbytes -= 31;
            gfx += 31;
        }
        multisprite_display_sprite_aligned(x, y, gfx, nbbytes, 0, 1);
    }
}

void init()
{
    // Dobkeratops palette
    *P0C1 = multisprite_color(0x3c); 
    *P0C2 = multisprite_color(0x39); 
    *P0C3 = multisprite_color(0x36); 
    *P1C1 = multisprite_color(0x24); 
    *P1C2 = multisprite_color(0x22); 
    *P1C3 = 0x0e; 
    *P2C1 = 0x0a; 
    *P2C2 = 0x04; 
    *P2C3 = 0x02; 
    *P3C1 = multisprite_color(0xc9); 
    *P3C2 = multisprite_color(0xc6); 
    *P3C3 = multisprite_color(0x43); // Red (unused)
}

void main()
{
    multisprite_init();
    init();

    do {
        draw_dobkeratops(80, 16);
        multisprite_flip();
    } while(1);
}
