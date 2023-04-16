#include "prosystem.h"
#include "multisprite.h"

char i, xpos, ypos;

#define NB_SPRITES 64
ramchip short sp_xpos[NB_SPRITES], sp_ypos[NB_SPRITES];
ramchip char sp_direction[NB_SPRITES];

#ifdef PAL
#define YMAX 240
#else
#define YMAX 192
#endif

const signed char dx[24] = {127, 122, 109, 89, 63, 32, 0, -32, -63, -89, -109, -122, -127, -122, -109, -89, -63, -32, 0, 32, 63, 89, 109, 122};
const signed short dy[24] = {0, 66, 128, 181, 221, 247, 256, 247, 221, 181, 128, 66, 0, -66, -127, -181, -221, -247, -256, -247, -221, -181, -128, -66};
const char horizontal_pingpong[24] = { 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13 };
const char vertical_pingpong[24] = { 0, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

holeydma scattered(16, 1) char sprite[16] = { 0x3c, 0x3c, 0x42, 0x42, 0x99, 0x99, 0xa5, 0xa5, 0x81, 0x81, 0xa5, 0xa5, 0x42, 0x42, 0x3c, 0x3c };

void main()
{
    xpos = 100; ypos = 100;
    multisprite_init();
    *P0C1 = 0x18; // Setup Palette 0
    *P0C2 = 0x38;
    *P0C3 = 0x58;
    for (ypos = 0, xpos = 0, i = 0, X = 0; X != NB_SPRITES; xpos++, ypos++, X++) {
        sp_xpos[X] = xpos << 8;
        sp_ypos[X] = ypos << 8;
        sp_direction[X] = i++;
        if (i == 24) i = 0;
    }
    // Main loop
    do {
        while (!(*MSTAT & 0x80)); // Wait for VBLANK
        multisprite_flip();
        for (i = 0; i != NB_SPRITES; i++) {
            X = i;
            Y = sp_direction[X];
            sp_xpos[X] += dx[Y];
            sp_ypos[X] += dy[Y];
            xpos = sp_xpos[X] >> 8;
            ypos = sp_ypos[X] >> 8;
            if (xpos == 0 || xpos == 159) {
                sp_direction[X] = horizontal_pingpong[Y];
            }
            if (ypos == 0 || ypos == YMAX - 17) {
                sp_direction[X] = vertical_pingpong[Y];
            }
            multisprite_display_sprite(xpos, ypos, sprite, 1, 0); 
        }
    } while(1);
}
