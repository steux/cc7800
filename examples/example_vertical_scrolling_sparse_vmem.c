#include "prosystem.h"
#define VERTICAL_SCROLLING
#define MULTISPRITE_USE_VIDEO_MEMORY
#include "multisprite.h"

// Generated by sprites7800 shmup_tiles.yaml
#include "shmup/shmup_tiles.c"

// Generated by tiles7800 --sparse shmup_tiles.yaml shump.tmx
#include "shmup/shmup_tilesets.c"

void main()
{
    char counter = 255;
    char done = 0;

    multisprite_init();
    multisprite_vscroll_init_sparse_tiles_vmem(tilemap_data_ptrs, blue_objects1);

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
        multisprite_vscroll_buffer_sparse_tiles_vmem_step();
        multisprite_vscroll_buffer_sparse_tiles_vmem_step();
        // Prepare scrolling data
        if (multisprite_vscroll_buffer_empty()) {
            if (!done) {
                multisprite_vscroll_buffer_sparse_tiles_vmem(counter);
                if (counter) counter--; else done = 1; 
            } else if (done == 1) {
                multisprite_vscroll_buffer_sparse_tiles_vmem(255);
                done = 2;
            } else done = 3;
        }

        while (*MSTAT & 0x80); 
        multisprite_flip();
        if (done != 3) multisprite_vertical_scrolling(2);

    } while(1);
}
