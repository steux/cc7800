#include "prosystem.h"
#include "stdlib.h"
#include "string.h"
#include "armyfont.h"
#define MODE_320AC
#include "multisprite_8lines.h"

unsigned char X, Y;

// Generated from sprites7800 breakout.yaml
holeydma reversed scattered(8,6) char suitcase_even[48] = {
	0x30, 0xf0, 0xf0, 0xf0, 0xf0, 0xe0, 0x71, 0xf5, 0xf5, 0xf5, 0xf5, 0xf4, 0x57, 0xbd, 0xf5, 0xf5,
	0xe5, 0xdd, 0x56, 0xb9, 0x59, 0xd6, 0x65, 0xd9, 0x53, 0xbd, 0x7a, 0xfa, 0x65, 0xdc, 0x30, 0xf0,
	0xf0, 0xf0, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
holeydma reversed scattered(8,6) char suitcase_odd[48] = {
	0x70, 0xf0, 0xf0, 0xf0, 0xf0, 0xc0, 0xf1, 0xf5, 0xf5, 0xf5, 0xf5, 0xe4, 0xb7, 0x75, 0xf5, 0xf5,
	0xd7, 0xad, 0xb6, 0x65, 0xb9, 0xa6, 0xd6, 0xa9, 0xb3, 0x65, 0xfa, 0xea, 0xd7, 0xac, 0x70, 0xf0,
	0xf0, 0xf0, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
holeydma reversed scattered(8,2) char ball_even[16] = {
	0x32, 0x88, 0x7a, 0xc8, 0xfa, 0xeb, 0xfa, 0xeb, 0xfa, 0xeb, 0x7e, 0xcc, 0x33, 0x8c, 0x00, 0x00
};
holeydma reversed scattered(8,2) char ball_odd[16] = {
	0x12, 0xc8, 0x32, 0xea, 0x7a, 0xfb, 0x7a, 0xfb, 0x7a, 0xfb, 0x32, 0xeb, 0x13, 0xcc, 0x00, 0x00
};
holeydma reversed scattered(8,2) char brick[16] = {
	0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x00, 0x00
};
holeydma reversed scattered(8,1) char side_brick[8] = {
	0xdf, 0xdf, 0xdf, 0x00, 0xfb, 0xfb, 0xfb, 0x00
};

#define LEFT_BORDER ((160 - (13 * 8)) / 2)
#define RIGHT_BORDER (160 - LEFT_BORDER) 
#define PPADDLE_BUFSIZE 4
ramchip char paddle_pos[PPADDLE_BUFSIZE], paddle_pos_idx, paddle_size;
ramchip signed char paddle_speed;
ramchip char paddle_pos_str[5], paddle_speed_str[5];
ramchip unsigned int xball, yball;
ramchip signed char sxball, syball; // Ball speed 

void interrupt dli()
{
    //*BACKGRND = 0x05;
    *VBLANK = 0x00; // Let paddle capacitors charging 
    Y = 200;
    do {
        strobe(WSYNC); // 3 cycles
        if ((*INPT0 & 0x80)) break; // 7 cycles
        Y--;
    } while (Y); // Looping 5 cycles
    X = paddle_pos_idx;
    X++;
    if (X == PPADDLE_BUFSIZE) {
        X = 0;
    }
    paddle_pos_idx = X;
    paddle_pos[X] = Y;
    // This takes 15 cycles out of 113.5. Maria should have enough 
    *VBLANK = 0x80; // Dump paddles to ground
    //*BACKGRND = 0x00;
}

void display_init()
{
    char y;

    *P0C2 = multisprite_color(0x34);
    *P1C2 = multisprite_color(0x40);
    *P2C2 = multisprite_color(0x1c);
    *P3C2 = 0x0f;
    multisprite_init();
    multisprite_set_charbase(font);
    multisprite_enable_dli(0);

    // Left and right walls
    for (y = 0; y != 25; y++) {
        char yy = y << 3;
        multisprite_display_sprite_aligned(LEFT_BORDER - 4, yy, side_brick, 1, 0, 0);
        multisprite_display_sprite_aligned_fast(RIGHT_BORDER, yy, side_brick, 1, 0);
    }

    multisprite_save();
}

void game_init()
{
    paddle_pos_idx = 0;
    for (X = 4; X >= 0; X--) paddle_pos[X] = 0;
    xball = 256 * 160;
    yball = 100 * 160;
    sxball = 50;
    syball = 50;
    paddle_size = 12;
    paddle_speed = 0;
}

const char left_shift_6bits[4] = {0, 0x40, 0x80, 0xc0};

void display_paddle()
{
    char x = paddle_pos[X = paddle_pos_idx];
    X++;
    if (X == PPADDLE_BUFSIZE) X = 0;
    paddle_speed = paddle_pos[X] - x;

    // Compute the average of the last PPADDLE_BUFSIZE positions
    unsigned int sum = paddle_pos[X = 0];
    for (X++; X != PPADDLE_BUFSIZE; X++) {
        sum += paddle_pos[X];
    }
    x = 200 - (left_shift_6bits[X = (sum >> 8)] | ((sum & 0xff) >> 2)); 
    char x2 = LEFT_BORDER + (x >> 1);
    if (x2 >= RIGHT_BORDER - paddle_size) x2 = RIGHT_BORDER - paddle_size;
    char *gfx;
    if (x & 1) {
        gfx = suitcase_even;
    } else {
        gfx = suitcase_odd;
    }
    multisprite_display_sprite_aligned(x2, 192, gfx, 6, 0, 1);
}

void main()
{
    game_init();
    display_init();

    // Main loop
    do {
        *BACKGRND = 0x0f;
        
        // Display paddle position
        multisprite_restore();
#ifdef DEBUG
        itoa(paddle_pos[X = paddle_pos_idx], paddle_pos_str, 10);
        char len = strlen(paddle_pos_str);
        multisprite_display_tiles(0, 0, paddle_pos_str, len, 3);
        itoa(paddle_speed, paddle_speed_str, 10);
        char len = strlen(paddle_speed_str);
        multisprite_display_tiles(0, 1, paddle_speed_str, len, 3);
#endif
        display_paddle();
        *BACKGRND = 0x00;

        // Wait for VBLANK to start
        while (!(*MSTAT & 0x80));
        //while (*MSTAT & 0x80); // And to end
    } while(1);
}
