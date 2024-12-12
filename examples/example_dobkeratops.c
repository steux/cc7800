#include "prosystem.h"
#define _MS_DL_SIZE 96
#include "multisprite.h"

// Generated by sprites7800 dobkeratops.yaml
#include "RType/dobkeratops_gfx.c"

const char dobkeratops_x[] = {0, 0, 6, 6, 37, 35, 37, 37, 40, 25, 0};
const char dobkeratops_y[] = {0, 16, 32, 48, 64, 80, 96, 112, 128, 144, 160};
const char dobkeratops_nbbytes[] = {32, 32, 24, 32, 16, 19, 18, 19, 17, 19, 28};
const char *dobkeratops_gfx[] = {dob1, dob2, dob3, dob4, dob5, dob6, dob7, dob8, dob9, dob10, dob11};

// Generated by 
// rustc misc/dobkeratops_tail.rs -o dokeratops_tail
// ./dobkeratops_tail > examples/RType/dobkeratops_tail.c
#include "RType/dobkeratops_tail.c"

void draw_dobkeratops(char xpos, char ypos, char anim)
{
    char x, y, c, *gfx;
    char *tailx = dobkeratops_tail_x[X = anim];
    char *taily = dobkeratops_tail_y[X];
    char margin = 16 - 12;
    // Draw tail
    gfx = tail1;
    for (c = 0; c != 17; c++) {
        x = tailx[Y = c] + xpos - 46;
        y = taily[Y] + ypos;
        if (c == 6) {
            gfx = tail2;
            margin = 16 - 10;
        } else if (c == 12) gfx = tail3;
        multisprite_display_small_sprite_ex(x, y, gfx, 2, 0, margin, 0);
    }
    x = tailx[Y = c] + xpos - 46;
    y = taily[Y] + ypos;
    multisprite_display_sprite_ex(x, y, tail4, 4, 0, 1);
    // Draw ugly alien body
    for (c = 0; c != 11; c++) {
        x = dobkeratops_x[X = c] + xpos;
        y = dobkeratops_y[X] + ypos;
        gfx = dobkeratops_gfx[X];
        char nbbytes = dobkeratops_nbbytes[X];
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
    char counter_tail = 0;
    char counter_move1 = 0, counter_move2 = 0;

    signed char tx = 0;
    multisprite_init();
    init();

    do {
        char x = 80 + tx;
        draw_dobkeratops(x, 16, counter_tail);
        counter_tail++;
        if (counter_tail == 60) counter_tail = 0;
        counter_move1++;
        if (counter_move1 == 5) {
            counter_move1 = 0;
            counter_move2++;
            if (counter_move2 < 30) {
               tx++;
            } else {
               tx--;
               if (counter_move2 > 60) counter_move2 = 0;
            }
        }
    
        multisprite_flip();
    } while(1);
}
