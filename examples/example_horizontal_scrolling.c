#define HORIZONTAL_SCROLLING
#include "sparse_tiling.h"

// Generated from sprites7800 RType_tiles.yaml
#include "example_RType_tiles.c"

// Generated from tiles7800 --sparse RType_tiles.yaml --varname tilemap_level1 RType_level1.tmx 
#include "example_RType_level1.c"

void main()
{
    multisprite_init();
    multisprite_set_charbase(brown_tiles1);
    multisprite_sparse_tiling(tilemap_level1_data_ptrs, 0, 0, 13);
    multisprite_save();
    
    // Beige palette
    *P4C1 = multisprite_color(0x12); 
    *P4C2 = multisprite_color(0x15);
    *P4C3 = multisprite_color(0x18); 
    
    // Rose palette
    *P6C1 = multisprite_color(0x38); // Dark Rose
    *P6C2 = multisprite_color(0x3c); // Rose 
    *P6C3 = multisprite_color(0x3f); // Light Rose 

    // Grey palette 
    *P7C1 = 0x04; // Dark gray
    *P7C2 = 0x08; // Medium gray
    *P7C3 = 0x0c; // Dark gray

    do {
        multisprite_flip();
    } while (1);
}
