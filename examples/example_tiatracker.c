#include "prosystem.h"
#include "miniblast_tiatracker.h"
#include "miniblast_trackdata.h"
#include "conio.h"

char i, j, k, l;

void main()
{
    tia_tracker_init();

    clrscr();
    gotoxy(12, 0);
    textcolor(2);
    cputs("TIA Tracker Player");

    for (i = 0; i != 2; i++) {
        gotoxy(18 + (i << 2), 19);
        putch('1' + i);
    }

    textcolor(1);

    i = 0;

    do {
        // Display the volume for each channel
        k = 18 + (i << 2);
        l = 17 - (AUDV0[Y = i] & 0x0f);
        for (j = 2; j < l; j++) {
            gotoxy(k, j);
            putch(' ');
        }
        for (; j < 18; j++) {
            gotoxy(k, j);
            putch(127);
        }
        i++;
        if (i == 2) i = 0;

        *BACKGRND = 0x00;
        while (*MSTAT & 0x80); // Wait for end of VBLANK
        while (!(*MSTAT & 0x80)); // Wait for VBLANK
        *BACKGRND = 0x0f;
        
        tia_tracker_play();
    } while(1);
}
