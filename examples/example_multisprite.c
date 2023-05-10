#include "prosystem.h"
#include "multisprite.h"

char i, xpos, ypos;

#define NB_SPRITES 32 
ramchip short sp_xpos[NB_SPRITES], sp_ypos[NB_SPRITES];
ramchip char sp_direction[NB_SPRITES];

const signed short dx[24] = {300, 289, 259, 212, 149, 77, 0, -77, -150, -212, -259, -289, -300, -289, -259, -212, -149, -77, 0, 77, 149, 212, 259, 289};
const signed short dy[24] = {0, 124, 240, 339, 415, 463, 480, 463, 415, 339, 240, 124, 0, -124, -239, -339, -415, -463, -480, -463, -415, -339, -240, -124};
const char horizontal_pingpong[24] = { 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13 };
const char vertical_pingpong[24] = { 0, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

holeydma reversed scattered(16,2) char bb_char1[32] = {
	0x01, 0x00, 0x01, 0x40, 0x0a, 0x94, 0x2a, 0x90, 0x3b, 0xa0, 0xc8, 0xe5, 0xc8, 0xe4, 0xc8, 0xd0,
	0xc8, 0xe5, 0xbb, 0x84, 0x0c, 0x20, 0x2a, 0x90, 0x0e, 0x50, 0x3f, 0x94, 0x3d, 0x68, 0x5d, 0x6a
};
reversed scattered(16,2) char tiles[32] = {
	0x5a, 0x5a, 0x69, 0x69, 0x69, 0x69, 0xa5, 0xa5, 0xa5, 0xa5, 0x96, 0x96, 0x96, 0x96, 0x5a, 0x5a,
	0x5a, 0x5a, 0x69, 0x69, 0x69, 0x69, 0xa5, 0xa5, 0xa5, 0xa5, 0x96, 0x96, 0x96, 0x96, 0x5a, 0x5a
};
const char background[20] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void main()
{
    multisprite_init();
    multisprite_set_charbase(tiles);
    
    for (i = 0; i != _MS_DLL_ARRAY_SIZE; i++) {
        // 20 characters (8 bits wide) on each line, using palette 1 (pink)
        multisprite_display_chars(0, i, background, 20, 1);
    }
    multisprite_save();

    *P0C1 = multisprite_color(0x1c); // Setup Palette 0
    *P0C2 = multisprite_color(0xc5); // Green
    *P0C3 = multisprite_color(0x0f); // White
   
    *P1C1 = multisprite_color(0x55); // Dark pink
    *P1C2 = multisprite_color(0x5B); // Light pink

    // Initialize sprites
    for (ypos = 0, xpos = 0, i = 0, X = 0; X != NB_SPRITES; xpos++, ypos++, X++) {
        sp_xpos[X] = xpos << 8;
        sp_ypos[X] = ypos << 8;
        sp_direction[X] = i++;
        if (i == 24) i = 0;
    }

    // Main loop
    do {
        multisprite_flip();
        for (i = 0; i != NB_SPRITES; i++) {
            X = i;
            Y = sp_direction[X];
            sp_xpos[X] += dx[Y];
            sp_ypos[X] += dy[Y];
            xpos = sp_xpos[X] >> 8;
            ypos = sp_ypos[X] >> 8;
            if ((xpos < 5 && (dx[Y] >> 8) < 0) || 
                (xpos >= 150 && (dx[Y] >> 8) >= 0)) {
                sp_direction[X] = horizontal_pingpong[Y];
            }
            if ((ypos < 5 && (dy[Y] >> 8) < 0) || 
                (ypos >= MS_YMAX - 20 && (dy[Y] >> 8) >= 0)) {
                sp_direction[X] = vertical_pingpong[Y];
            }
            multisprite_display_sprite(xpos, ypos, bb_char1, 2, 0); 
        }
    } while(1);
}
