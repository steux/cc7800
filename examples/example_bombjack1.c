#include "prosystem.h"
#include "multisprite.h"

// Generated by sprites7800 bombjack_tiles.yaml 
#include "bombjack/bombjack_tiles.c"

// Generated by sprites7800 bombjack_sprites.yaml 
#include "bombjack/bombjack_sprites.c"

// Generated by tiles7800 --sparse bombjack_tiles.yaml --varname tilemap_sphinx bombjack_sphinx.tmx
#include "bombjack/bombjack_sphinx.c"

// Generated by tiles7800 --sparse bombjack_tiles.yaml --varname tilemap_arrangement_A bombjack_arrangement_A.tmx
#include "bombjack/bombjack_arrangement_A.c"

const char topborder[15] = {26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28};
const char topborder_dl[] = { topborder, 0x60, topborder >> 8, (3 << 5) | (-15 & 0x1f), 0, 0, 0};

const char bottomborder[15] = {30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32};
const char bottomborder_dl[] = { bottomborder, 0x60, bottomborder >> 8, (3 << 5) | (-15 & 0x1f), 0, 0, 0};

// Arrangements - x, y of first bomb, nb bombs, direction (0 to 3).
const char arrangement_A[] = { 
    6 + 6 * 8, 3 * 16 - 8, 4, 0, 
    4 + 13 * 8, 8 + 4 * 16, 4, 3, 4, 
    5 * 16, 4, 3, 
    4 + 2 * 8, 0, 3, 0,
    4 + 11 * 8, 11 * 16, 3, 2, 
    5 * 8, 13 * 16, 3, 2, 
    4 + 13 * 8, 0, 3, 2}; 
const char arrangements_nb_series[] = { 7 };
const char *arrangements[] = { arrangement_A }; 
const signed char arrangement_dx[4] = { 12, 0, -12, 0 };
const signed char arrangement_dy[4] = { 0, -24, 0, 24 };

void display_arrangement(char a)
{
    char *arrangement = arrangements[X = a];
    char i, j, nb_series = arrangements_nb_series[X];
    for (Y = 0, i = 0; i != nb_series; i++) {
        char x = arrangement[Y++];
        char y = arrangement[Y++];
        char nb_bombs = arrangement[Y++];
        char direction = arrangement[Y++];
        _save_y = Y;
        for (j = 0; j != nb_bombs; j++) {
            multisprite_display_sprite_fast(x, y, bomb, 2, 2);
            x += arrangement_dx[X = direction]; 
            y += arrangement_dy[X]; 
        }
        Y = _save_y;
    }
}

void main()
{
    char y;
    multisprite_init(0);
    multisprite_set_charbase(platform);
    // Top border in overscan
    if (_ms_pal_detected) {
        X = 4;
    } else {
        X = 1;
    }
    _ms_b0_dll[X] = topborder_dl >> 8;  
    _ms_b1_dll[X] = topborder_dl >> 8;
    _ms_b0_dll[++X] = topborder_dl;  
    _ms_b1_dll[X] = topborder_dl;
    // Bottom border in overscan
    X += 14 * 3 + 1;
    _ms_b0_dll[X] = 0x08; // 9 lines  
    _ms_b1_dll[X] = 0x08; // 9 lines 
    _ms_b0_dll[++X] = bottomborder_dl >> 8;  
    _ms_b1_dll[X] = bottomborder_dl >> 8;
    _ms_b0_dll[++X] = bottomborder_dl;  
    _ms_b1_dll[X] = bottomborder_dl;
    // Adjust the bottom of screen to fit the screen size
    X += 4;
    if (_ms_pal_detected) {
        _ms_b0_dll[X] = 0x07; // 8 lines  
        _ms_b1_dll[X] = 0x07; // 8 lines  
    } else {
        _ms_b0_dll[X] = 0x00; // 1 line  
        _ms_b1_dll[X] = 0x00; // 1 line  
    }
    // Left and right borders
    for (y = 0; y < 224; y += 16) {
        multisprite_display_sprite_fast(0, y, border, 1, 3);
        multisprite_display_sprite_fast(116, y, border, 1, 3);
    }
    // Display the sphinx and platforms
    multisprite_sparse_tiling(tilemap_sphinx_data_ptrs, 0, 0, 4, 14);
    multisprite_sparse_tiling(tilemap_arrangement_A_data_ptrs, 0, 0, 4, 14);

    multisprite_save();
    
    *P1C2 = multisprite_color(0x3c); // Rose 

    // Bomb palette
    *P2C1 = multisprite_color(0x34); // Red
    *P2C2 = multisprite_color(0x1c); // Yellow 
    *P2C3 = 0x0f; 

    // Fire palette
    *P3C1 = multisprite_color(0x24); // Red
    *P3C2 = multisprite_color(0x28); // Orange
    *P3C3 = multisprite_color(0x1c); // Yellow 

    // Blue palette
    *P4C1 = multisprite_color(0x84); // Dark blue 
    *P4C2 = multisprite_color(0x87); // Light blue
    *P4C3 = multisprite_color(0xac); // Turquoise 
    
    // Sphinx palette
    *P5C1 = multisprite_color(0x12); // Red
    *P5C2 = multisprite_color(0x15); // Orange
    *P5C3 = multisprite_color(0x18); // Yellow 

    // Main loop
    do {
        // Display the first arrangement
        display_arrangement(0);

        multisprite_flip();
    } while(1);
}
