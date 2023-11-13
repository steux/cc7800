#include "string.h"
#define HORIZONTAL_SCROLLING
#define _MS_BOTTOM_SCROLLING_ZONE 1
#include "sparse_tiling.h"
#include "joystick.h"

// Generated from sprites7800 RType_tiles.yaml
#include "example_RType_tiles.c"

// Generated from tiles7800 --sparse RType_tiles.yaml --varname tilemap_level1 RType_level1.tmx 
#include "example_RType_level1.c"

// Generated from sprites7800 RType_font.yaml
#include "example_RType_font.c"

ramchip char save_acc, save_x, save_y;

void interrupt dli()
{
    store(save_acc);
    save_x = X;
    save_y = Y;
    multisprite_set_charbase(alphabet);
    *CTRL = 0x43; // DMA on, 320A/C mode, One (1) byte characters mode
    X = save_x;
    Y = save_y;
    load(save_acc);
}

// Background scrolling
char scroll_background_counter;

void scroll_background()
{
    char c;
    signed char pos1, pos2, pos3, pos4;
    pos1 = -scroll_background_counter;
    pos2 = pos1 + 80;
    pos3 = pos1 - 8;
    if (pos3 < -16) pos3 += 16;
    pos4 = pos3 + 80;
    if (_ms_buffer) {
        X = _MS_DLL_ARRAY_SIZE + 1;
        scroll_background_counter++;
        if (scroll_background_counter == 16) scroll_background_counter = 0;
    } else X = 1;
    _ms_tmpptr = _ms_dls[X];
    for (c = 0; c != 3; c++) {
        // Modify bytes 4 and 8 of the DLL entries (x position of background sprites=
        _ms_tmpptr[Y = 4] = pos1;
        _ms_tmpptr[Y = 8] = pos2;
        _ms_tmpptr = _ms_dls[++X];
        _ms_tmpptr[Y = 4] = pos1;
        _ms_tmpptr[Y = 8] = pos2;
        _ms_tmpptr = _ms_dls[++X];
        _ms_tmpptr[Y = 4] = pos3;
        _ms_tmpptr[Y = 8] = pos4;
        _ms_tmpptr = _ms_dls[++X];
        _ms_tmpptr[Y = 4] = pos3;
        _ms_tmpptr[Y = 8] = pos4;
        _ms_tmpptr = _ms_dls[++X];
    }
}

ramchip int score;
ramchip char update_score;
ramchip char display_score_str[5];

void display_score_update()
{
    char display_score_ascii[6];
    itoa(score, display_score_ascii, 10);
    Y = strlen(display_score_ascii); 
    for (X = 0; X != 5 - Y; X++) {
        display_score_str[X] = 26; // '0'
    }
    X = 4;
    do {
        display_score_str[X--] = 26 + (display_score_ascii[--Y] - '0');
    } while (Y);
}

void rtype_init()
{
    *BACKGRND = 0x0;
    
    multisprite_get_tv();
    multisprite_clear();
    multisprite_save();

    _ms_tmpptr = _ms_b0_dll;
    for (X = 0, _ms_tmp = 0; _ms_tmp <= 1; _ms_tmp++) {
        // Build DLL
        // 69 blank lines for PAL
        // 19 blank lines for NTSC
        if (_ms_pal_detected) {
            // 16 blank lines
            _ms_tmpptr[Y = 0] = 0x0f;  // 16 lines
            _ms_tmpptr[++Y] = _ms_set_wm_dl >> 8;
            _ms_tmpptr[++Y] = _ms_set_wm_dl;
            // 16 blank lines
            _ms_tmpptr[++Y] = 0x0f;  // 16 lines
            _ms_tmpptr[++Y] = _ms_blank_dl >> 8;
            _ms_tmpptr[++Y] = _ms_blank_dl;
        } else {
            _ms_tmpptr[Y = 0] = 0x08; // 9 lines
            _ms_tmpptr[++Y] = _ms_set_wm_dl >> 8;
            _ms_tmpptr[++Y] = _ms_set_wm_dl;
        }
        // 16 pixel high regions
        for (_ms_tmp2 = 0; _ms_tmp2 != _MS_DLL_ARRAY_SIZE - 2; X++, _ms_tmp2++) {
            _ms_tmpptr[++Y] = 0x4f; // 16 lines
            _ms_tmpptr[++Y] = _ms_dls[X] >> 8; // High address
            _ms_tmpptr[++Y] = _ms_dls[X]; // Low address
        }
        // 1 pixel high region to separate from 320A scoreboard. This gives some little room for the DLI to execute
        _ms_tmpptr[++Y] = 0x00; // 1 line
        _ms_tmpptr[++Y] = _ms_blank_dl >> 8;
        _ms_tmpptr[++Y] = _ms_blank_dl;
        // 8 pixel high regions (320A)
        for (_ms_tmp2 = 0; _ms_tmp2 != 2; X++, _ms_tmp2++) {
            _ms_tmpptr[++Y] = 0x07; // 8 lines
            _ms_tmpptr[++Y] = _ms_dls[X] >> 8; // High address
            _ms_tmpptr[++Y] = _ms_dls[X]; // Low address
        }
        if (_ms_pal_detected) {
            // 16 blank lines
            _ms_tmpptr[++Y] = 0x0f;  // 16 lines
            _ms_tmpptr[++Y] = _ms_blank_dl >> 8;
            _ms_tmpptr[++Y] = _ms_blank_dl;
            // 16 blank lines
            _ms_tmpptr[++Y] = 0x0f;  // 16 lines
            _ms_tmpptr[++Y] = _ms_blank_dl >> 8;
            _ms_tmpptr[++Y] = _ms_blank_dl;
            // 4 blank lines
            _ms_tmpptr[++Y] = 0x03;  // 4 lines
            _ms_tmpptr[++Y] = _ms_blank_dl >> 8;
            _ms_tmpptr[++Y] = _ms_blank_dl;
        } else {
            _ms_tmpptr[++Y] = 0x08; // 9 lines
            _ms_tmpptr[++Y] = _ms_blank_dl >> 8;
            _ms_tmpptr[++Y] = _ms_blank_dl;
        }
        _ms_tmpptr = _ms_b1_dll;
    }
    multisprite_start();
}

const char oneup[3] = {27, 'U' - 'A', 'P' - 'A'};
const char high[4] = {'H' - 'A', 'I' - 'A', 'G' - 'A', 'H' - 'A'};
const char beam[4] = {'B' - 'A', 'E' - 'A', 'A' - 'A', 'M' - 'A'};
const char gauge_out[17] = {45, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 47};
const char gauge_in[15] = { 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48};

void main()
{
    char button_pressed = 0;
    scroll_background_counter = 0;

    joystick_init();
    rtype_init();
    sparse_tiling_init(tilemap_level1_data_ptrs);
    multisprite_set_charbase(brown_tiles1);
   
    // Green (background) color 
    *P3C1 = multisprite_color(0xd0); 
    *P3C2 = multisprite_color(0xd2); 
    *P3C3 = multisprite_color(0xd1); 
    
    // Beige palette
    *P4C1 = multisprite_color(0x12); 
    *P4C2 = multisprite_color(0x14); 
    *P4C3 = multisprite_color(0x16); 
    
    // Blue palette
    *P5C1 = multisprite_color(0x84); // Dark blue 
    *P5C2 = multisprite_color(0x87); // Light blue
    *P5C3 = multisprite_color(0xac); // Turquoise 

    // Rose palette
    *P6C1 = multisprite_color(0x34); // Dark Rose
    *P6C2 = multisprite_color(0x38); // Rose 
    *P6C3 = multisprite_color(0x3c); // Light Rose 

    // Grey palette 
    *P7C1 = 0x04; // Dark gray
    *P7C2 = 0x08; // Medium gray
    *P7C3 = 0x0c; // Dark gray

    multisprite_display_tiles(3 * 4, 14, oneup, 3, 5);
    multisprite_display_tiles(7 * 4, 14, display_score_str, 5, 7);
    multisprite_display_tiles(16 * 4, 14, high, 4, 5);
    multisprite_display_tiles(21 * 4, 14, display_score_str, 5, 7);
    multisprite_display_tiles(8 * 4, 13, beam, 4, 5);
    multisprite_display_tiles(13 * 4, 13, gauge_out, 17, 7);
    multisprite_display_tiles(14 * 4, 13, gauge_in, 1, 5);
   
    // Background display
    char c, y = 0;
    for (c = 0; c != 3; c++) {
        y += 16;
        multisprite_display_sprite_ex(0, y, background_level1, 20, 3, 0);
        multisprite_display_sprite_fast(80, y, background_level1, 24, 3);
        y += 16;
        multisprite_display_sprite_ex(0, y, background_level1_1, 20, 3, 0);
        multisprite_display_sprite_fast(80, y, background_level1_1, 24, 3);
        y += 16;
        multisprite_display_sprite_ex(-8, y, background_level1, 20, 3, 0);
        multisprite_display_sprite_fast(72, y, background_level1, 24, 3);
        y += 16;
        multisprite_display_sprite_ex(-8, y, background_level1_1, 20, 3, 0);
        multisprite_display_sprite_fast(72, y, background_level1_1, 24, 3);
    }

    // Save it
    multisprite_save();

    multisprite_enable_dli(13);
    
    sparse_tiling_display();
    multisprite_flip();
    sparse_tiling_scroll(1); // Offset of 1 compared to previous screen
    sparse_tiling_display();
    multisprite_flip();

    do {
        scroll_background();
        sparse_tiling_scroll(2); // Offset of 2 compared to previous same buffer (1 pixel scrolling due to double buffering)
        char x = _tiling_xpos[0]; 
        score = x;
        display_score_update();

        multisprite_flip();
        multisprite_set_charbase(brown_tiles1);
        *CTRL = 0x50; // DMA on, 160A/B mode, Two (2) byte characters mode
    } while (1);
}
