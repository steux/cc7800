#include "prosystem.h"
#define VERTICAL_SCROLLING
#include "multisprite.h"

// Generated by sprites7800 shmup_tiles.png
#include "example_shmup_tiles.c"

// Generated by tiles7800 --sparse shmup_tiles.yaml shump.tmx
#include "example_shmup_tilesets.c"

void main()
{
    char counter = 255;
    char done = 0;

    multisprite_init();
    multisprite_set_charbase(blue_objects1);
    multisprite_vscroll_init_sparse_tiles(tilemap_data_ptrs);

    // Grey palette
    *P0C1 = 0x04;
    *P0C2 = 0x08;
    *P0C3 = 0x0c;

    // Blue palette
    *P1C1 = multisprite_color(0x84); // Dark blue 
    *P1C2 = multisprite_color(0x88); // Light blue
    *P1C3 = multisprite_color(0xac); // Turquoise 

    // Main loop
    do {
        // Prepare scrolling data
        if (multisprite_vscroll_buffer_empty()) {
            if (!done) {
                multisprite_vscroll_buffer_sparse_tiles(counter);
                if (counter) counter--; else done = 1; 
            } else if (done == 1) {
                multisprite_vscroll_buffer_sparse_tiles(255);
                done = 2;
            } else done = 3;
        }

        while (*MSTAT & 0x80); 
        multisprite_flip();
        if (done != 3) multisprite_vertical_scrolling(1);

    } while(1);
}
