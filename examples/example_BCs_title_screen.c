#include "prosystem.h"
#include "multisprite.h"

// Generated from bitmap7800 BC's.yaml > example_BCs_title_screen_bitmap.c
#define BITMAP_TABLE_BANK bank0 
#include "example_BCs_title_screen_bitmap.c"

void main()
{
    multisprite_init();
    title_screen_set_palette();
    multisprite_disable_holeydma();
    multisprite_display_bitmap(title_screen_data_ptrs, 0, 1, 12);
    multisprite_flip();
    while(1);
}
