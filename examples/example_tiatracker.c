#include "prosystem.h"
#define TIA_TRACKER_INDIRECT_REGISTERS
unsigned char * const XAUDC0    = 0x15;     // Audio Control Channel   0                    write-only
unsigned char * const XAUDC1    = 0x16;     // Audio Control Channel   1                    write-only
unsigned char * const XAUDF0    = 0x17;     // Audio Frequency Channel 0                    write-only
unsigned char * const XAUDF1    = 0x18;     // Audio Frequency Channel 1                    write-only
unsigned char XAUDV0, XAUDV1;

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
        l = 17 - (((i == 0)?XAUDV0:XAUDV1) & 0x0f);
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
        *AUDV0 = XAUDV0;
        *AUDV1 = XAUDV1;
    } while(1);
}
