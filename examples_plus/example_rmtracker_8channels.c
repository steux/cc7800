#include "prosystem.h"
#define POKEY_STEREO
#include "rmtplayer.h"
#include "conio.h"

#include "atari_goes_on.c"

char interrupt_flag;

//const char SHORT_INTERRUPT = 1;
void interrupt dli()
{
    interrupt_flag = 1;
}

void main()
{
    char i, j, k, l;
    *OFFSET = 0x03; // Activate Pokey1 + Pokey2 
    clrscr();
    gotoxy(6, 0);
    textcolor(2);
    cputs("Raster Music Tracker Player");

    for (i = 0; i != 8; i++) {
        gotoxy(14 + (i << 1), 19);
        putch('1' + i);
    }

    pokey_init(RMTSTART);

    textcolor(1);

    i = 0;

    interrupt_flag = 0;
    conio_enable_dli(12);

    do {
        // Display the volume for each channel
        k = 14 + (i << 1);
        l = 17 - (trackn_audc[Y = i] & 0x0f);
        for (j = 2; j < l; j++) {
            gotoxy(k, j);
            putch(' ');
        }
        for (; j < 18; j++) {
            gotoxy(k, j);
            putch(127);
        }
        i++;
        if (i == 8) i = 0;
        
        *BACKGRND = 0x00;
        while (!interrupt_flag);
        *BACKGRND = 0x0f;
        interrupt_flag = 0;
        pokey_play();
        *BACKGRND = 0x00;

        while (*MSTAT & 0x80); // Wait for end of VBLANK
        while (!(*MSTAT & 0x80)); // Wait for VBLANK
        *BACKGRND = 0x0f;
        interrupt_flag = 0;
        pokey_play();
    } while(1);
}
