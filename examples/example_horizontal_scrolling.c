#define HORIZONTAL_SCROLLING
#define _MS_BOTTOM_SCROLLING_ZONE 1
#include "sparse_tiling.h"
#include "joystick.h"

// Generated from sprites7800 RType_tiles.yaml
#include "example_RType_tiles.c"

// Generated from tiles7800 --sparse RType_tiles.yaml --varname tilemap_level1 RType_level1.tmx 
#include "example_RType_level1.c"

void main()
{
    char button_pressed = 0;

    joystick_init();
    multisprite_init();
    multisprite_set_charbase(brown_tiles1);
    //multisprite_sparse_tiling(tilemap_level1_data_ptrs, 0, 0, 13);
    //multisprite_save();
    sparse_tiling_init(tilemap_level1_data_ptrs);
    
    *P3C1 = multisprite_color(0xd0); 
    *P3C3 = multisprite_color(0xd1); 
    *P3C2 = multisprite_color(0xd2); 
    
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

    _tiling_xpos[X = 0] = 13;
    _tiling_xpos[++X] = 13;

    char c, y = 0;

    for (c = 0; c != 3; c++) {
        y += 16;
        multisprite_display_sprite_ex(0, y, background_level1, 20, 3, 0);
        multisprite_display_sprite_ex(80, y, background_level1, 24, 3, 0);
        y += 16;
        multisprite_display_sprite_ex(0, y, background_level1_1, 20, 3, 0);
        multisprite_display_sprite_ex(80, y, background_level1_1, 24, 3, 0);
        y += 16;
        multisprite_display_sprite_ex(-8, y, background_level1, 20, 3, 0);
        multisprite_display_sprite_ex(72, y, background_level1, 24, 3, 0);
        y += 16;
        multisprite_display_sprite_ex(-8, y, background_level1_1, 20, 3, 0);
        multisprite_display_sprite_ex(72, y, background_level1_1, 24, 3, 0);
    }

    multisprite_save();

    sparse_tiling_display();
    multisprite_save_overlay();
    multisprite_flip();
    sparse_tiling_display();
    multisprite_save_overlay();
    do {
        joystick_update();
        //if (joystick[0] & JOYSTICK_BUTTON1) {
            if (!button_pressed) {
                button_pressed = 1;
                sparse_tiling_scroll(2);
                while (*MSTAT & 0x80); // Make sure we are out of blank 
                multisprite_flip();
                sparse_tiling_scroll(2);
            }
        //} else 
            button_pressed = 0;
        while (*MSTAT & 0x80); // Make sure we are out of blank 
        multisprite_flip();
    } while (1);
}
