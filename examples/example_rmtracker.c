#include "prosystem.h"
#include "rmtplayer.h"
#include "examples/RMT_Alien3.asm"

void main()
{
    asm("LDX #<RMTSTART");
    asm("LDY #>RMTSTART");
    load(0);
    asm("JSR rmt_init");

    do {
        // Wait for vblank
        *BACKGRND = 0x00;
        while (!(*MSTAT & 0x80));
        *BACKGRND = 0x0f;
        asm("JSR rmt_play");
        while (*MSTAT & 0x80); // Wait for end of VBLANK
    } while(1);
}
