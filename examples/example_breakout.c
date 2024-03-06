#include "prosystem.h"
#include "stdlib.h"
#include "string.h"
#include "armyfont.h"
#define MODE_320AC
#define _MS_DL_SIZE 96
#define MULTISPRITE_OVERLAY
#include "multisprite_8lines.h"

unsigned char X, Y;

// Generated from sprites7800 breakout.yaml
holeydma reversed scattered(8,6) char suitcase_even[48] = {
	0x30, 0xf0, 0xf0, 0xf0, 0xf0, 0xe0, 0x60, 0xf5, 0xf5, 0xf5, 0xf5, 0xb4, 0x57, 0xbd, 0xf5, 0xf5,
	0xe5, 0xdd, 0x56, 0xb9, 0x59, 0xd6, 0x65, 0xd9, 0x53, 0xbd, 0x7a, 0xfa, 0x65, 0xdc, 0x30, 0xf0,
	0xf0, 0xf0, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
holeydma reversed scattered(8,6) char suitcase_odd[48] = {
	0x70, 0xf0, 0xf0, 0xf0, 0xf0, 0xc0, 0xd1, 0xf5, 0xf5, 0xf5, 0xf5, 0x60, 0xb7, 0x75, 0xf5, 0xf5,
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
holeydma reversed scattered(8,7) char side_brick[56] = {
	0xdf, 0xdf, 0xdf, 0xdf, 0xdf, 0xdf, 0xdf, 0xdf, 0xdf, 0xdf, 0xdf, 0xdf, 0xdf, 0xdf, 0xdf, 0xdf,
	0xdf, 0xdf, 0xdf, 0xdf, 0xdf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0xfb, 0xfb, 0xfb,
	0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb,
	0xfb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#define LEFT_BORDER ((160 - (13 * 8)) / 2)
#define RIGHT_BORDER (160 - LEFT_BORDER) 
#define BALL_SIZE 7
#define BALL_XOFFSET 16
#define PADDLE_YPOS 208
#define PPADDLE_BUFSIZE 4
ramchip char paddle_pos[PPADDLE_BUFSIZE], paddle_pos_idx, paddle_size, paddle_filtered_pos;
ramchip signed char paddle_speed;
ramchip unsigned int xball, yball;
ramchip int sxball, syball; // Ball speed 
#ifdef DEBUG
ramchip char paddle_pos_str[5], paddle_speed_str[5];
#endif

ramchip char dli_done;

ramchip char playfield[16 * 16];

const char playfield_level1[16 * 10] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1,
    1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 2, 1, 1,
    1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1
};
   
const char playfield_level1_offset[10] = {0, 0, 0, 1, 0, 1, 0, 1, 0, 1};

void interrupt dli()
{
    if (!dli_done) {
        *BACKGRND = 0x05;
        *VBLANK = 0x00; // Let paddle capacitors charging 
        Y = 200;
        do {
            strobe(WSYNC); // 3 cycles
            if ((*INPT0 & 0x80)) break; // 7 cycles
            Y--;
        } while (Y); // Looping 5 cycles
        // This takes 15 cycles out of 113.5. Maria should have enough cycles left... 
        X = paddle_pos_idx;
        X++;
        if (X == PPADDLE_BUFSIZE) {
            X = 0;
        }
        paddle_pos_idx = X;
        paddle_pos[X] = Y;
        *VBLANK = 0x80; // Dump paddles to ground
        *BACKGRND = 0x00;
        dli_done = ++Y; // To tell the main prog how much lines the DLI took
    }
}

void display_playfield()
{
    char x, y, x2, y2, tmp, v;
    char *gfx;
    for (y = 0; y != 10; y++) {
        X = y << 4;
        x2 = LEFT_BORDER;
        y2 = (y + 2) << 3;
        if (playfield_level1_offset[Y = y]) {
            v = playfield[X];
            if (v) {
                char color = v - 1;
                tmp = X;
                multisprite_display_sprite_aligned_fast(x2, y2, brick + 1, 1, color);
                X = tmp;
            }
            x2 += 4;
            X++;
        }
        for (x = 0; x != 12; X++, x++) {
            v = playfield[X];
            if (v) {
                char color = v - 1;
                tmp = X;
                multisprite_display_sprite_aligned_fast(x2, y2, brick, 2, color);
                X = tmp;
            }
            x2 += 8;
        }
        v = playfield[X];
        if (v) {
            char color = v - 1;
            tmp = (playfield_level1_offset[Y = y])?1:2;
            multisprite_display_sprite_aligned_fast(x2, y2, brick, tmp, color);
        }
    }

    multisprite_save_overlay();
}

void display_init()
{
    char x, y;

    *P0C2 = multisprite_color(0x40);
    *P1C2 = multisprite_color(0x34);
    *P2C2 = multisprite_color(0x1c);
    *P3C2 = 0x0f;
    multisprite_init();
    multisprite_set_charbase(font);
    dli_done = 0;
    multisprite_enable_dli(0);

    // Upper wall
    multisprite_display_sprite_aligned(LEFT_BORDER - 4, 8, side_brick, 7, 0, 0);
    x = LEFT_BORDER - 4;
    for (y = 0; y != 3; y++) {
        x += 56 / 2;
        multisprite_display_sprite_aligned_fast(x, 8, side_brick, 7, 0);
    }

    // Left and right walls
    for (y = 2; y != 28; y++) {
        char yy = y << 3;
        multisprite_display_sprite_aligned(LEFT_BORDER - 4, yy, side_brick, 1, 0, 0);
        multisprite_display_sprite_aligned_fast(RIGHT_BORDER, yy, side_brick, 1, 0);
    }

    multisprite_save();

    display_playfield();
}

void game_init()
{
    paddle_pos_idx = 0;
    for (X = 4; X >= 0; X--) paddle_pos[X] = 0;
    xball = 256 * ((13 * 16) / 2 + BALL_XOFFSET - (BALL_SIZE / 2));
    yball = 256 * 50;
    sxball = 200;
    syball = 400;
    paddle_size = 24;
    paddle_speed = 0;
    paddle_filtered_pos = 0;

    // Clear playfield
    for (Y = 255; Y != 0; Y--) {
        playfield[Y] = 0;
    }
    playfield[Y] = 0;

    // Copy level1
    for (X = 0; X != 16 * 10; X++) {
        playfield[X] = playfield_level1[X];
    }
}

const char left_shift_6bits[4] = {0, 0x40, 0x80, 0xc0};

void compute_paddle()
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
    sum >>= 2;
    x = 200 - (sum & 0xff); 
    if (x >= 13 * 16 - paddle_size) x = 13 * 16 - paddle_size;
    paddle_filtered_pos = x;
} 

void display_paddle()
{
    char x2 = LEFT_BORDER + (paddle_filtered_pos >> 1);
    char *gfx;
    if (paddle_filtered_pos & 1) {
        gfx = suitcase_even;
    } else {
        gfx = suitcase_odd;
    }
    multisprite_display_sprite_aligned(x2, PADDLE_YPOS, gfx, 6, 0, 1);
}

void compute_ball()
{
    xball += sxball;
    yball += syball;
    if ((yball >> 8) >= 223) {
        // Reset ball
        xball = 256 * ((13 * 16) / 2 + 16 - 3);
        yball = 256 * 50;
    }
    // Bounces on left and right walls
    if (((sxball >> 8) >= 0 && ((xball >> 8) >= (13 * 16) + BALL_XOFFSET - BALL_SIZE)) || ((sxball >> 8) < 0 && ((xball >> 8) < BALL_XOFFSET ))) {
        sxball = -sxball;
    }
    // Bounces on upper wall
    if ((syball >> 8) < 0 && (yball >> 8) < 15) {
        syball = -syball;
    }
    // Bounces on suitcase
    if ((syball >> 8) >= 0 && ((yball >> 8) >= PADDLE_YPOS - 7) && ((yball >> 8) <= PADDLE_YPOS - 3)) {
        // Are we above the suitcase ?
        char left_side = paddle_filtered_pos + BALL_XOFFSET - (BALL_SIZE / 2); // Including the 16 pixels offset of the ball - 3 pixels off the ball (round)
        if (((xball >> 8) >= left_side) && ((xball >> 8) < left_side + paddle_size)) {
            signed int speed_offset = paddle_speed;
            speed_offset <<= 3;
            syball = -syball;
            sxball += speed_offset;
        }
    }
}

void display_ball()
{
    char x = xball >> 8;
    char y = yball >> 8;
    char x2 = LEFT_BORDER + (x >> 1) - 8;
    char *gfx;
    if (x & 1) {
        gfx = ball_odd;
    } else {
        gfx = ball_even;
    }
    multisprite_display_sprite_ex(x2, y, gfx, 2, 0, 1);
}

void main()
{
    game_init();
    display_init();

    // Main loop
    do {
        while (!dli_done);
        dli_done = 0;
        *BACKGRND = 0x0f;
        compute_paddle();
        compute_ball();
#ifdef DEBUG
        itoa(paddle_pos[X = paddle_pos_idx], paddle_pos_str, 10);
        char len = strlen(paddle_pos_str);
        multisprite_display_tiles(0, 0, paddle_pos_str, len, 3);
        itoa(paddle_speed, paddle_speed_str, 10);
        char len = strlen(paddle_speed_str);
        multisprite_display_tiles(0, 1, paddle_speed_str, len, 3);
#endif

        *BACKGRND = 0x00;
        
        while (!(*MSTAT & 0x80)); // Wait for VBLANK
        *BACKGRND = 0x0f;
        // Display paddle position
        multisprite_restore_overlay();
        display_paddle();
        display_ball();
        *BACKGRND = 0x00;
    } while(1);
}
