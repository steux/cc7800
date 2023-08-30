#include "stdlib.h"
#include "string.h"
#include "prosystem.h"
#include "joystick.h"

#define MODE_320AC

// Generated from tiles7800 --sparse highres_tiles.yaml highres_sparse.tmx 
const char tilemap_0_data[] = {96, 0xff};
const char tilemap_1_data[] = {96, 0xff};
const char tilemap_2_data[] = {96, 0xff};
const char tilemap_3_data[] = {96, 0xff};
const char tilemap_4_data[] = {96, 0xff};
const char tilemap_5_0[5] = {16, 12, 6, 12, 8};
const char tilemap_5_data[] = {6, 2, tilemap_5_0, 0x60, tilemap_5_0 >> 8, (1 << 5) | ((-5) & 0x1f), 29, 96, 0xff};
const char tilemap_6_0[4] = {10, 12, 12, 14};
const char tilemap_6_data[] = {6, 3, tilemap_6_0, 0x60, tilemap_6_0 >> 8, (1 << 5) | ((-4) & 0x1f), 24, 96, 0xff};
const char tilemap_7_0[1] = {0};
const char tilemap_7_data[] = {3, 3, tilemap_7_0, 0x60, tilemap_7_0 >> 8, (1 << 5) | ((-1) & 0x1f), 11, 96, 0xff};
const char tilemap_8_0[1] = {0};
const char tilemap_8_1[1] = {20};
const char tilemap_8_data[] = {3, 3, tilemap_8_0, 0x60, tilemap_8_0 >> 8, (1 << 5) | ((-1) & 0x1f), 11, 15, 15, tilemap_8_1, 0x60, tilemap_8_1 >> 8, (2 << 5) | ((-1) & 0x1f), 11, 96, 0xff};
const char tilemap_9_0[11] = {4, 12, 12, 12, 6, 12, 12, 6, 12, 12, 8};
const char tilemap_9_1[1] = {0};
const char tilemap_9_data[] = {13, 3, tilemap_9_0, 0x60, tilemap_9_0 >> 8, (1 << 5) | ((-11) & 0x1f), 56, 15, 15, tilemap_9_1, 0x60, tilemap_9_1 >> 8, (2 << 5) | ((-1) & 0x1f), 11, 96, 0xff};
const char tilemap_10_0[6] = {28, 28, 28, 28, 28, 28};
const char tilemap_10_1[1] = {0};
const char tilemap_10_2[1] = {0};
const char tilemap_10_data[] = {11, 6, tilemap_10_0, 0x60, tilemap_10_0 >> 8, (0 << 5) | ((-6) & 0x1f), 33, 13, 13, tilemap_10_1, 0x60, tilemap_10_1 >> 8, (1 << 5) | ((-1) & 0x1f), 11, 15, 15, tilemap_10_2, 0x60, tilemap_10_2 >> 8, (2 << 5) | ((-1) & 0x1f), 11, 96, 0xff};
const char tilemap_11_0[1] = {0};
const char tilemap_11_1[1] = {0};
const char tilemap_11_data[] = {13, 13, tilemap_11_0, 0x60, tilemap_11_0 >> 8, (1 << 5) | ((-1) & 0x1f), 11, 15, 15, tilemap_11_1, 0x60, tilemap_11_1 >> 8, (2 << 5) | ((-1) & 0x1f), 11, 96, 0xff};
const char tilemap_12_0[1] = {22};
const char tilemap_12_1[1] = {22};
const char tilemap_12_data[] = {13, 13, tilemap_12_0, 0x60, tilemap_12_0 >> 8, (1 << 5) | ((-1) & 0x1f), 11, 15, 15, tilemap_12_1, 0x60, tilemap_12_1 >> 8, (2 << 5) | ((-1) & 0x1f), 11, 96, 0xff};
const char tilemap_13_data[] = {96, 0xff};
const char tilemap_14_0[1] = {24};
const char tilemap_14_data[] = {12, 12, tilemap_14_0, 0x60, tilemap_14_0 >> 8, (0 << 5) | ((-1) & 0x1f), 11, 96, 0xff};
const char tilemap_15_0[1] = {20};
const char tilemap_15_1[2] = {30, 32};
const char tilemap_15_2[2] = {30, 32};
const char tilemap_15_3[1] = {20};
const char tilemap_15_4[1] = {20};
const char tilemap_15_data[] = {4, 4, tilemap_15_0, 0x60, tilemap_15_0 >> 8, (1 << 5) | ((-1) & 0x1f), 11, 6, 6, tilemap_15_1, 0xe0, tilemap_15_1 >> 8, (0 << 5) | ((-2) & 0x1f), 15, 12, 12, tilemap_15_2, 0xe0, tilemap_15_2 >> 8, (0 << 5) | ((-2) & 0x1f), 15, 13, 13, tilemap_15_3, 0x60, tilemap_15_3 >> 8, (1 << 5) | ((-1) & 0x1f), 11, 15, 15, tilemap_15_4, 0x60, tilemap_15_4 >> 8, (2 << 5) | ((-1) & 0x1f), 11, 96, 0xff};
const char tilemap_16_0[1] = {0};
const char tilemap_16_1[2] = {30, 32};
const char tilemap_16_2[1] = {2};
const char tilemap_16_3[1] = {0};
const char tilemap_16_data[] = {4, 4, tilemap_16_0, 0x60, tilemap_16_0 >> 8, (1 << 5) | ((-1) & 0x1f), 11, 9, 9, tilemap_16_1, 0xe0, tilemap_16_1 >> 8, (0 << 5) | ((-2) & 0x1f), 15, 13, 13, tilemap_16_2, 0x60, tilemap_16_2 >> 8, (1 << 5) | ((-1) & 0x1f), 11, 15, 15, tilemap_16_3, 0x60, tilemap_16_3 >> 8, (2 << 5) | ((-1) & 0x1f), 11, 96, 0xff};
const char tilemap_17_0[1] = {20};
const char tilemap_17_1[1] = {26};
const char tilemap_17_2[1] = {0};
const char tilemap_17_3[1] = {0};
const char tilemap_17_4[1] = {2};
const char tilemap_17_data[] = {2, 2, tilemap_17_0, 0x60, tilemap_17_0 >> 8, (2 << 5) | ((-1) & 0x1f), 11, 3, 3, tilemap_17_1, 0x60, tilemap_17_1 >> 8, (0 << 5) | ((-1) & 0x1f), 11, 4, 4, tilemap_17_2, 0x60, tilemap_17_2 >> 8, (1 << 5) | ((-1) & 0x1f), 11, 13, 13, tilemap_17_3, 0x60, tilemap_17_3 >> 8, (1 << 5) | ((-1) & 0x1f), 11, 15, 15, tilemap_17_4, 0x60, tilemap_17_4 >> 8, (2 << 5) | ((-1) & 0x1f), 11, 96, 0xff};
const char tilemap_18_0[1] = {0};
const char tilemap_18_1[1] = {0};
const char tilemap_18_2[1] = {0};
const char tilemap_18_3[1] = {0};
const char tilemap_18_data[] = {2, 2, tilemap_18_0, 0x60, tilemap_18_0 >> 8, (2 << 5) | ((-1) & 0x1f), 11, 4, 4, tilemap_18_1, 0x60, tilemap_18_1 >> 8, (1 << 5) | ((-1) & 0x1f), 11, 13, 13, tilemap_18_2, 0x60, tilemap_18_2 >> 8, (1 << 5) | ((-1) & 0x1f), 11, 15, 15, tilemap_18_3, 0x60, tilemap_18_3 >> 8, (2 << 5) | ((-1) & 0x1f), 11, 96, 0xff};
const char tilemap_19_0[1] = {0};
const char tilemap_19_1[10] = {4, 12, 12, 12, 12, 12, 12, 12, 12, 14};
const char tilemap_19_2[2] = {30, 32};
const char tilemap_19_3[1] = {0};
const char tilemap_19_data[] = {2, 2, tilemap_19_0, 0x60, tilemap_19_0 >> 8, (2 << 5) | ((-1) & 0x1f), 11, 13, 4, tilemap_19_1, 0x60, tilemap_19_1 >> 8, (1 << 5) | ((-10) & 0x1f), 51, 14, 14, tilemap_19_2, 0xe0, tilemap_19_2 >> 8, (0 << 5) | ((-2) & 0x1f), 15, 15, 15, tilemap_19_3, 0x60, tilemap_19_3 >> 8, (2 << 5) | ((-1) & 0x1f), 11, 96, 0xff};
const char tilemap_20_0[12] = {4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12};
const char tilemap_20_1[2] = {12, 14};
const char tilemap_20_data[] = {13, 2, tilemap_20_0, 0x60, tilemap_20_0 >> 8, (2 << 5) | ((-12) & 0x1f), 60, 15, 14, tilemap_20_1, 0x60, tilemap_20_1 >> 8, (2 << 5) | ((-2) & 0x1f), 15, 96, 0xff};
const char tilemap_21_data[] = {96, 0xff};
const char tilemap_22_data[] = {96, 0xff};
const char tilemap_23_data[] = {96, 0xff};
const char tilemap_24_data[] = {96, 0xff};
const char tilemap_25_data[] = {96, 0xff};
const char tilemap_26_data[] = {96, 0xff};
const char tilemap_27_data[] = {96, 0xff};
const char tilemap_28_data[] = {96, 0xff};
const char tilemap_29_data[] = {96, 0xff};
const char tilemap_30_data[] = {96, 0xff};
const char tilemap_31_data[] = {96, 0xff};
const char tilemap_data[64] = {tilemap_0_data & 0xff, tilemap_0_data >> 8, tilemap_1_data & 0xff, tilemap_1_data >> 8, tilemap_2_data & 0xff, tilemap_2_data >> 8, tilemap_3_data & 0xff, tilemap_3_data >> 8, tilemap_4_data & 0xff, tilemap_4_data >> 8, tilemap_5_data & 0xff, tilemap_5_data >> 8, tilemap_6_data & 0xff, tilemap_6_data >> 8, tilemap_7_data & 0xff, tilemap_7_data >> 8, tilemap_8_data & 0xff, tilemap_8_data >> 8, tilemap_9_data & 0xff, tilemap_9_data >> 8, tilemap_10_data & 0xff, tilemap_10_data >> 8, tilemap_11_data & 0xff, tilemap_11_data >> 8, tilemap_12_data & 0xff, tilemap_12_data >> 8, tilemap_13_data & 0xff, tilemap_13_data >> 8, tilemap_14_data & 0xff, tilemap_14_data >> 8, tilemap_15_data & 0xff, tilemap_15_data >> 8, tilemap_16_data & 0xff, tilemap_16_data >> 8, tilemap_17_data & 0xff, tilemap_17_data >> 8, tilemap_18_data & 0xff, tilemap_18_data >> 8, tilemap_19_data & 0xff, tilemap_19_data >> 8, tilemap_20_data & 0xff, tilemap_20_data >> 8, tilemap_21_data & 0xff, tilemap_21_data >> 8, tilemap_22_data & 0xff, tilemap_22_data >> 8, tilemap_23_data & 0xff, tilemap_23_data >> 8, tilemap_24_data & 0xff, tilemap_24_data >> 8, tilemap_25_data & 0xff, tilemap_25_data >> 8, tilemap_26_data & 0xff, tilemap_26_data >> 8, tilemap_27_data & 0xff, tilemap_27_data >> 8, tilemap_28_data & 0xff, tilemap_28_data >> 8, tilemap_29_data & 0xff, tilemap_29_data >> 8, tilemap_30_data & 0xff, tilemap_30_data >> 8, tilemap_31_data & 0xff, tilemap_31_data >> 8};

#define TILING_HEIGHT 32
#define TILING_WIDTH 32
#include "sparse_tiling.h"

// Generated from sprites7800 highres_tiles.yaml
reversed scattered(16,24) char blue_tubes[384] = {
	0x3f, 0xfc, 0x3f, 0xfc, 0x3f, 0xfc, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfc,
	0x30, 0x00, 0x00, 0x18, 0x7f, 0xfe, 0x3f, 0xfc, 0x3f, 0xfc, 0x3f, 0xfc, 0x3f, 0xfc, 0x00, 0xc0,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfc, 0xb6, 0x00, 0x00, 0xda, 0x7f, 0xfe, 0x3f, 0xfc,
	0x3f, 0xfc, 0x3f, 0xfc, 0x3f, 0xfb, 0xfe, 0xdf, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xdf, 0xfc,
	0xb6, 0xff, 0xfe, 0xda, 0x05, 0xa0, 0x3f, 0xfc, 0x3f, 0xfc, 0x3f, 0xfc, 0x3f, 0xff, 0xf2, 0xff,
	0xff, 0xe0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x37, 0xff, 0xff, 0xd8, 0x3f, 0xfc, 0x3f, 0xfc,
	0x3f, 0xfc, 0x3f, 0xfc, 0x3f, 0xff, 0xfa, 0xdf, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xfc,
	0x36, 0xff, 0xfe, 0xd8, 0x3f, 0xfc, 0x3f, 0xfc, 0x3f, 0xfc, 0x15, 0x54, 0x3f, 0xff, 0xfe, 0xff,
	0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x37, 0xff, 0xff, 0xd8, 0x3f, 0xfc, 0x3f, 0xfc,
	0x3f, 0xfc, 0x2a, 0xa8, 0x3f, 0xff, 0xfe, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfc,
	0xb7, 0xff, 0xff, 0xda, 0x3f, 0xfc, 0x3f, 0xfc, 0x3f, 0xfc, 0x00, 0x00, 0x3f, 0xff, 0xfe, 0xff,
	0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xb7, 0xff, 0xff, 0xda, 0x3f, 0xfc, 0x3f, 0xfc,
	0x3f, 0xfc, 0x7f, 0xfe, 0x3f, 0xff, 0xfe, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc,
	0xb7, 0xff, 0xff, 0xda, 0x3f, 0xfc, 0x3f, 0xfc, 0x3f, 0xfc, 0x7f, 0xfe, 0x1f, 0xff, 0xfe, 0xff,
	0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xb7, 0xff, 0xff, 0xda, 0x3f, 0xfc, 0x3f, 0xfc,
	0x3f, 0xfc, 0x17, 0xe8, 0x15, 0x55, 0x54, 0xd5, 0x7f, 0xfc, 0x3f, 0xfd, 0x55, 0x55, 0x55, 0x58,
	0x36, 0xaa, 0xaa, 0xd8, 0x3f, 0xfc, 0x3f, 0xfc, 0x3f, 0xfc, 0x3f, 0xfc, 0x0f, 0xff, 0xfe, 0xff,
	0xff, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x37, 0xff, 0xff, 0xd8, 0x3f, 0xfc, 0x3f, 0xfc,
	0x3f, 0xfc, 0x3f, 0xfc, 0x05, 0x55, 0x54, 0xd5, 0x7f, 0xfc, 0x3f, 0xfd, 0x55, 0x55, 0x55, 0x40,
	0x36, 0xaa, 0xaa, 0xd8, 0x3f, 0xfc, 0x3f, 0xfc, 0x3f, 0xfc, 0x3f, 0xfc, 0x00, 0x55, 0x54, 0xd5,
	0x5f, 0xfc, 0x3f, 0xf9, 0x55, 0x55, 0x55, 0x00, 0xb6, 0xaa, 0xaa, 0xda, 0x3f, 0xfc, 0x05, 0xa0,
	0x3f, 0xfc, 0x3f, 0xfc, 0x00, 0x00, 0x00, 0xc0, 0x3f, 0xfc, 0x3f, 0xfc, 0x00, 0x00, 0x00, 0x00,
	0xb6, 0x00, 0x00, 0xda, 0x3f, 0xfc, 0x7f, 0xfe, 0x3f, 0xfc, 0x3f, 0xfc, 0x00, 0x00, 0x00, 0xc0,
	0x3f, 0xfc, 0x3f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x18, 0x3f, 0xfc, 0x7f, 0xfe
};
reversed scattered(16,6) char objects[96] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfc, 0x7f, 0x7f, 0x07, 0xe8, 0x5f, 0xfa,
	0x00, 0x00, 0x0e, 0x74, 0x6f, 0xf6, 0x7f, 0x7f, 0x0c, 0x34, 0x70, 0x0e, 0x7f, 0x7f, 0x0e, 0x74,
	0x77, 0xee, 0x7e, 0x7e, 0x07, 0xe8, 0x77, 0xee, 0x3e, 0x3e, 0x00, 0x00, 0x77, 0xee, 0x3e, 0x3e,
	0x01, 0xa0, 0x77, 0xee, 0x3e, 0x3e, 0x01, 0x80, 0x77, 0xee, 0x1c, 0x1c, 0x01, 0x80, 0x77, 0xee,
	0x1c, 0x1c, 0x01, 0x60, 0x70, 0x0e, 0x1c, 0x1c, 0x01, 0x80, 0x6f, 0xf6, 0x18, 0x18, 0x01, 0x60,
	0x5f, 0xfa, 0x08, 0x08, 0x01, 0x80, 0x3f, 0xfc, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
reversed scattered(16,4) char colored_cube[64] = {
	0x00, 0x00, 0x00, 0x00, 0x30, 0xf0, 0xf0, 0xc0, 0x50, 0xf0, 0xf0, 0xa2, 0x60, 0xf0, 0xf0, 0x6a,
	0x70, 0x00, 0x00, 0xea, 0x70, 0x7f, 0xef, 0xea, 0x70, 0x75, 0xe5, 0xea, 0x70, 0x7f, 0xef, 0xea,
	0x70, 0x75, 0xe5, 0xea, 0x70, 0x7f, 0xef, 0xea, 0x70, 0x75, 0xe5, 0xea, 0x70, 0x00, 0x00, 0xea,
	0x60, 0xfa, 0xfa, 0x6a, 0x52, 0xfa, 0xfa, 0xaa, 0x32, 0xfa, 0xfa, 0xc8, 0x00, 0x00, 0x00, 0x00
};

ramchip int x, y;

void main()
{
    x = 0; y = 0;

    multisprite_init();
    multisprite_set_charbase(blue_tubes);
    tiling_init(tilemap_data);
    joystick_init();
    
    tiling_goto(x, y);
    *P0C2 = 0x0f; // White
    *P1C2 = multisprite_color(0x9a); // Blue
    *P2C2 = multisprite_color(0x3a); // Orange
    *P3C2 = multisprite_color(0x33); // Red

    // Main loop
    do {
        multisprite_flip();
        joystick_update();
        if (joystick[0] & JOYSTICK_LEFT) x--; 
        else if (joystick[0] & JOYSTICK_RIGHT) x++;
        if (joystick[0] & JOYSTICK_UP) y--; 
        else if (joystick[0] & JOYSTICK_DOWN) y++;
        tiling_goto(x, y);
    } while(1);
}