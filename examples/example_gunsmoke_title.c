#include "prosystem.h"
#define MODE_320AC
#include "multisprite.h"

// Generated from bitmap7800 gunsmoke_title.yaml > title_bitmap.c
#include "gunsmoke/title_bitmap.c"

void main()
{
    multisprite_init();
    title_set_palette();
    multisprite_disable_holeydma();
    multisprite_display_bitmap(title_data_ptrs, 20, 4, 4);
    multisprite_flip();
    while(1);
}
