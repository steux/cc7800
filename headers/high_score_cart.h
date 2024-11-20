/*
    high_score_cart.h : High Score Cart support for cc7800
    Copyleft 2024 Bruno STEUX

    This file is distributed as a companion file to cc7800 - a subset of C compiler for the Atari 7800
*/
    
// To test HSC:
// ./a7800 a7800 -cart xm -cart2 /media/steux/Bruno/git/TigerHeli7800/a.out

unsigned char *const HSC_MAGIC1 = 0x3900;
unsigned char *const HSC_MAGIC2 = 0x3904;
unsigned char *const HSC_START = 0x1000;
unsigned char *const HSC_GAME_ID1 = 0x1029;
unsigned char *const HSC_GAME_ID2 = 0x106e;
unsigned char *const HSC_GAME_DIFFICULTY  = 0x10b3;
unsigned char *const HSC_GAME_INDEX = 0x10f8;

ramchip unsigned char *hsc_data;

char hsc_detect()
{
    const char hsc_header[0x29] = {          
    0x00,0x00,0x68,0x83,0xAA,0x55,0x9C,0xFF,0x07,0x12,0x02,0x1F,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03};

    *XCTRL1 = 0x0c; // Switch on HSC with XM
                    
    if (*HSC_MAGIC1 != 0xc6 || *HSC_MAGIC2 != 0xfe) return 0;
    // Check if it's initialized
    // If all 0xff, not initalized
    for (X = 0, Y = 255; Y != 0; Y--) {
        if (HSC_START[Y] != 0xff) {
            X = 1;
            break;
        }
    }
    // If all 0x00, not inialized
    if (X) {
        for (X = 0, Y = 255; Y != 0; Y--) {
            if (HSC_START[Y] != 0x00) {
                X = 1;
                break;
            }
        }
    }
    if (!X) { // It's not initialized
        // Do minimal initialization
        for (Y = 0x28; Y >= 0; Y--) {
            HSC_START[Y] = hsc_header[Y];
        } 
        for (Y = 0; Y < 69 * 2; Y++) {
           HSC_GAME_DIFFICULTY[Y] = 0x7f;
        }
    }
    return 1;
}

// returns -1 on error
// 1 when the table was already recorded (to be decoded through hsc_data pointer)
// 0 when the table is not initialized (to be initialized through hsc_data pointer)
char hsc_init(char game_id1, char game_id2, char game_difficulty)
{
    for (Y = 68; Y >= 0; Y--) {
        if (HSC_GAME_DIFFICULTY[Y] == 0x7f) break;
        if (HSC_GAME_ID1[Y] == game_id1 && HSC_GAME_ID2[Y] == game_id2 && HSC_GAME_DIFFICULTY[Y] == game_difficulty) break;
    }
    if (Y != -1) {
        char slot = Y;
        hsc_data = 0x17fa;
        do {
            hsc_data -= 25;
            Y++;
        } while (Y != 69);
        Y = slot;
        if (HSC_GAME_DIFFICULTY[Y] != game_difficulty) {
            // Init table entry
            HSC_GAME_ID1[Y] = game_id1;
            HSC_GAME_ID2[Y] = game_id2;
            HSC_GAME_DIFFICULTY[Y] = game_difficulty;
            // Fix game index entries
            X = 0;
            for (; Y != 69; Y++) {
                HSC_GAME_INDEX[Y] = ++X;
            }
            return 0; // Not initialized table
        }
        return 1; // Initialized table to be read
    }
    return Y; // Error
}



