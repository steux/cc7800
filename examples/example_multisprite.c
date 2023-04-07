#include "prosystem.h"
#include "multisprite.h"

char xpos, ypos;
holeydma scattered(16, 1) char sprite[16] = { 0x3c, 0x3c, 0x42, 0x42, 0x99, 0x99, 0xa5, 0xa5, 0x81, 0x81, 0xa5, 0xa5, 0x42, 0x42, 0x3c, 0x3c };

void main()
{
    xpos = 64; ypos = 64;
    multisprite_display_sprite(xpos, ypos, sprite, 1, 0); 
    multisprite_display_sprite(64, 64, sprite, 1, 0); 
}
