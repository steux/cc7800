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

holeydma reversed scattered(16,2) char bb_char1[32] = {
	0x01, 0x00, 0x01, 0x40, 0x0a, 0x94, 0x2a, 0x90, 0x3b, 0xa0, 0xc8, 0xe5, 0xc8, 0xe4, 0xc8, 0xd0,
	0xc8, 0xe5, 0xbb, 0x84, 0x0c, 0x20, 0x2a, 0x90, 0x0e, 0x50, 0x3f, 0x94, 0x3d, 0x68, 0x5d, 0x6a
};

void main()
{
    xpos = 100; ypos = 100;
    multisprite_init();
    *P0C1 = 0x1c; // Setup Palette 0
    *P0C2 = 0xd5; // Green
    *P0C3 = 0x0f; // White
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
            if (xpos == 0 || xpos == 151) {
                sp_direction[X] = horizontal_pingpong[Y];
            }
            if (ypos == 0 || ypos == YMAX - 17) {
                sp_direction[X] = vertical_pingpong[Y];
            }
            multisprite_display_sprite(xpos, ypos, bb_char1, 2, 0); 
        }
    } while(1);
}
