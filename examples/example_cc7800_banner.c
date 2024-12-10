#include "conio.h"
#include "cc7800_banner/cc7800_banner_bitmap.c"

const char rainbow_color[8] = {
    0x32, 0x26, 0x17, 0xe9, 0xca, 0xb9, 0x96, 0x83 
};

void main()
{
    clrscr();
    char i, color;
    char counter;
    counter = 0;

    do {
        // Clear palette
        for (i = 0; i != 8; i++) {
            X = i << 2;
            P0C2[X] = 0x00;
        }
        conio_set_dl(10, cc7800_banner_0_dl);
        conio_set_dl(11, cc7800_banner_1_dl);
        conio_set_dl(12, cc7800_banner_2_dl);
        do {
            // Wait for a frame
            while (!(*MSTAT & 0x80)); // Wait for VBLANK
            while ((*MSTAT & 0x80)); // Wait for end of VBLANK
            for (i = 0; i != 8; i++) {
                if (counter >= (i << 2)) {
                    color = (counter - (i << 2)) >> 2;
                    X = i << 2;
                    if (color < 0x10) {
                        P0C2[X] = color;
                    } else if (counter >= 128) {
                        color = multisprite_color(rainbow_color[Y = i]);
                        char shade = 0x0f - ((counter - 128) >> 2);
                        if (shade >= 0 && shade >= (color & 0x0f)) {
                            color = (color & 0xf0) | shade;
                        }
                        P0C2[X] = color;
                    }
                }
            }
            counter++;
        } while (counter);
        conio_restore_dl(10);
        conio_restore_dl(11);
        conio_restore_dl(12);
    } while (1);
}
