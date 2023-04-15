#ifndef __ATARI7800_MULTISPRITE__
#define __ATARI7800_MULTISPRITE__

#ifndef _MS_DL_SIZE
#define _MS_DL_SIZE 64
#endif

// Zeropage variables
char _ms_buffer; // Double buffer state
char _ms_dmaerror;
char *_ms_dlpnt, *_ms_dlpnt2;
char _ms_tmp, _ms_tmp2;

ramchip char _ms_b0_dl0[_MS_DL_SIZE], _ms_b0_dl1[_MS_DL_SIZE], _ms_b0_dl2[_MS_DL_SIZE], _ms_b0_dl3[_MS_DL_SIZE], _ms_b0_dl4[_MS_DL_SIZE], _ms_b0_dl5[_MS_DL_SIZE], _ms_b0_dl6[_MS_DL_SIZE], _ms_b0_dl7[_MS_DL_SIZE], _ms_b0_dl8[_MS_DL_SIZE], _ms_b0_dl9[_MS_DL_SIZE], _ms_b0_dl10[_MS_DL_SIZE], _ms_b0_dl11[_MS_DL_SIZE];
ramchip char _ms_b1_dl0[_MS_DL_SIZE], _ms_b1_dl1[_MS_DL_SIZE], _ms_b1_dl2[_MS_DL_SIZE], _ms_b1_dl3[_MS_DL_SIZE], _ms_b1_dl4[_MS_DL_SIZE], _ms_b1_dl5[_MS_DL_SIZE], _ms_b1_dl6[_MS_DL_SIZE], _ms_b1_dl7[_MS_DL_SIZE], _ms_b1_dl8[_MS_DL_SIZE], _ms_b1_dl9[_MS_DL_SIZE], _ms_b1_dl10[_MS_DL_SIZE], _ms_b1_dl11[_MS_DL_SIZE];
#ifdef PAL
#define _MS_DLL_ARRAY_SIZE 15 
ramchip char _ms_b0_dl12[_MS_DL_SIZE], _ms_b0_dl13[_MS_DL_SIZE], _ms_b0_dl14[_MS_DL_SIZE];
ramchip char _ms_b1_dl12[_MS_DL_SIZE], _ms_b1_dl13[_MS_DL_SIZE], _ms_b1_dl14[_MS_DL_SIZE];
const char *_ms_dls[_MS_DLL_ARRAY_SIZE * 2] = {
    _ms_b0_dl0, _ms_b0_dl1, _ms_b0_dl2, _ms_b0_dl3, _ms_b0_dl4, _ms_b0_dl5, _ms_b0_dl6, _ms_b0_dl7, _ms_b0_dl8, _ms_b0_dl9, _ms_b0_dl10, _ms_b0_dl11, _ms_b0_dl12, _ms_b0_dl13, _ms_b0_dl14,
    _ms_b1_dl0, _ms_b1_dl1, _ms_b1_dl2, _ms_b1_dl3, _ms_b1_dl4, _ms_b1_dl5, _ms_b1_dl6, _ms_b1_dl7, _ms_b1_dl8, _ms_b1_dl9, _ms_b1_dl10, _ms_b1_dl11, _ms_b1_dl12, _ms_b1_dl13, _ms_b1_dl14
};
const char _ms_shift4[16 * _MS_DLL_ARRAY_SIZE] = {
    0, _MS_DLL_ARRAY_SIZE + 0, 0, _MS_DLL_ARRAY_SIZE + 0, 0, _MS_DLL_ARRAY_SIZE + 0, 0, _MS_DLL_ARRAY_SIZE + 0, 0, _MS_DLL_ARRAY_SIZE + 0, 0, _MS_DLL_ARRAY_SIZE + 0, 0, _MS_DLL_ARRAY_SIZE + 0, 0, _MS_DLL_ARRAY_SIZE + 0,
    1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1,
    2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2,
    3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3,
    4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4,
    5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5,
    6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6,
    7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7,
    8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8,
    9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9,
    10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10,
    11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11,
    12, _MS_DLL_ARRAY_SIZE + 12, 12, _MS_DLL_ARRAY_SIZE + 12, 12, _MS_DLL_ARRAY_SIZE + 12, 12, _MS_DLL_ARRAY_SIZE + 12, 12, _MS_DLL_ARRAY_SIZE + 12, 12, _MS_DLL_ARRAY_SIZE + 12, 12, _MS_DLL_ARRAY_SIZE + 12, 12, _MS_DLL_ARRAY_SIZE + 12,
    13, _MS_DLL_ARRAY_SIZE + 13, 13, _MS_DLL_ARRAY_SIZE + 13, 13, _MS_DLL_ARRAY_SIZE + 13, 13, _MS_DLL_ARRAY_SIZE + 13, 13, _MS_DLL_ARRAY_SIZE + 13, 13, _MS_DLL_ARRAY_SIZE + 13, 13, _MS_DLL_ARRAY_SIZE + 13, 13, _MS_DLL_ARRAY_SIZE + 13,
    14, _MS_DLL_ARRAY_SIZE + 14, 14, _MS_DLL_ARRAY_SIZE + 14, 14, _MS_DLL_ARRAY_SIZE + 14, 14, _MS_DLL_ARRAY_SIZE + 14, 14, _MS_DLL_ARRAY_SIZE + 14, 14, _MS_DLL_ARRAY_SIZE + 14, 14, _MS_DLL_ARRAY_SIZE + 14, 14, _MS_DLL_ARRAY_SIZE + 14
};

#else
#define _MS_DLL_ARRAY_SIZE 12 
const char *_ms_dls[_MS_DLL_ARRAY_SIZE * 2] = { 
    _ms_b0_dl0, _ms_b0_dl1, _ms_b0_dl2, _ms_b0_dl3, _ms_b0_dl4, _ms_b0_dl5, _ms_b0_dl6, _ms_b0_dl7, _ms_b0_dl8, _ms_b0_dl9, _ms_b0_dl10, _ms_b0_dl11,
    _ms_b1_dl0, _ms_b1_dl1, _ms_b1_dl2, _ms_b1_dl3, _ms_b1_dl4, _ms_b1_dl5, _ms_b1_dl6, _ms_b1_dl7, _ms_b1_dl8, _ms_b1_dl9, _ms_b1_dl10, _ms_b1_dl11
};
const char _ms_shift4[16 * _MS_DLL_ARRAY_SIZE] = {
    0, _MS_DLL_ARRAY_SIZE + 0, 0, _MS_DLL_ARRAY_SIZE + 0, 0, _MS_DLL_ARRAY_SIZE + 0, 0, _MS_DLL_ARRAY_SIZE + 0, 0, _MS_DLL_ARRAY_SIZE + 0, 0, _MS_DLL_ARRAY_SIZE + 0, 0, _MS_DLL_ARRAY_SIZE + 0, 0, _MS_DLL_ARRAY_SIZE + 0,
    1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1,
    2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2,
    3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3,
    4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4,
    5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5,
    6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6,
    7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7,
    8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8,
    9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9,
    10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10,
    11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11
};

#endif
ramchip char _ms_b0_dll[(_MS_DLL_ARRAY_SIZE + 4) * 3];
ramchip char _ms_b1_dll[(_MS_DLL_ARRAY_SIZE + 4) * 3];
ramchip char _ms_dlend[_MS_DLL_ARRAY_SIZE * 2];
ramchip char _ms_dldma[_MS_DLL_ARRAY_SIZE * 2];
ramchip char _ms_dlend_save[_MS_DLL_ARRAY_SIZE];
ramchip char _ms_dldma_save[_MS_DLL_ARRAY_SIZE];

void multisprite_init();
void multisprite_clear();
void multisprite_save();
void multisprite_restore();
void multisprite_flip();

#define multisprite_display_sprite(x, y, gfx, width, palette) \
        _ms_tmp = (y) & 0x0f; \
        X = _ms_shift4[Y = (y & 0xfe | _ms_buffer)]; \
        _ms_dldma[X] -= (8 + width * 3 + 1) / 2; \
        if (_ms_dldma[X] < 0) { \
            _ms_dmaerror = 1; \
            _ms_dldma[X] += (8 + width * 3 + 1) / 2; \
        } else { \
            _ms_dlpnt = _ms_dls[X]; \
            Y = _ms_dlend[X]; \
            _ms_dlpnt[Y++] = sprite; \
            _ms_dlpnt[Y++] = -width & 0x1f | (palette << 5); \
            _ms_dlpnt[Y++] = (sprite >> 8) | _ms_tmp; \
            _ms_dlpnt[Y++] = (x); \
            _ms_dlend[X] = Y; \
            if ((y) & 0x0f) { \
                X++; \
                _ms_dldma[X] -= (8 + width * 3 + 1) / 2; \
                if (_ms_dldma[X] < 0) { \
                    _ms_dmaerror = 1; \
                    _ms_dldma[X] += (8 + width * 3 + 1) / 2; \
                } else { \
                    _ms_dlpnt = _ms_dls[X];  \
                    Y = _ms_dlend[X]; \
                   _ms_dlpnt[Y++] = sprite; \
                   _ms_dlpnt[Y++] = -width & 0x1f | (palette << 5); \
                   _ms_dlpnt[Y++] = ((sprite - 0x1000) >> 8) | _ms_tmp; \
                   _ms_dlpnt[Y++] = (x); \
                   _ms_dlend[X] = Y; \
                } \
            }\
        }

#define multisprite_display_sprite_fast(x, y, gfx, width, palette) \
        _ms_tmp = (y) & 0x0f; \
        X = _ms_shift4[Y = (y & 0xfe | _ms_buffer)]; \
        _ms_dldma[X] -= (8 + width * 3 + 1) / 2; \
        _ms_dlpnt = _ms_dls[X]; \
        Y = _ms_dlend[X]; \
        _ms_dlpnt[Y++] = sprite; \
        _ms_dlpnt[Y++] = -width & 0x1f | (palette << 5); \
        _ms_dlpnt[Y++] = (sprite >> 8) | _ms_tmp; \
        _ms_dlpnt[Y++] = (x); \
        _ms_dlend[X] = Y; \
        if ((y) & 0x0f) { \
            X++; \
            _ms_dldma[X] -= (8 + width * 3 + 1) / 2; \
            _ms_dlpnt = _ms_dls[X];  \
            Y = _ms_dlend[X]; \
            _ms_dlpnt[Y++] = sprite; \
            _ms_dlpnt[Y++] = -width & 0x1f | (palette << 5); \
            _ms_dlpnt[Y++] = ((sprite - 0x1000) >> 8) | _ms_tmp; \
            _ms_dlpnt[Y++] = (x); \
            _ms_dlend[X] = Y; \
        }

void multisprite_init()
{
    multisprite_clear();
    multisprite_save();
    _ms_dlpnt = _ms_b0_dll;
    for (X = 0, _ms_tmp = 0; _ms_tmp <= 1; _ms_tmp++) {
        // Build DLL
        // 25 blank lines
        _ms_dlpnt[Y = 0] = 0x4f;  // 16 lines
        _ms_dlpnt[++Y] = 0x21; // 0x2100 = Blank DL
        _ms_dlpnt[++Y] = 0x00;
        _ms_dlpnt[++Y] = 0x48; // 9 lines
        _ms_dlpnt[++Y] = 0x21; // 0x2100 = Blank DL
        _ms_dlpnt[++Y] = 0x00;
        // 16 pixel high regions
        for (_ms_tmp2 = 0; _ms_tmp2 != _MS_DLL_ARRAY_SIZE; X++, _ms_tmp2++) {
            _ms_dlpnt[++Y] = 0x4f; // 16 lines
            _ms_dlpnt[++Y] = _ms_dls[X] >> 8; // High address
            _ms_dlpnt[++Y] = _ms_dls[X]; // Low address
        }
        // 26 blank lines
        _ms_dlpnt[++Y] = 0x4f; // 16 lines
        _ms_dlpnt[++Y] = 0x21; // 0x2100 = Blank DL
        _ms_dlpnt[++Y] = 0x00;
        _ms_dlpnt[++Y] = 0x49; // 10 lines
        _ms_dlpnt[++Y] = 0x21; // 0x2100 = Blank DL
        _ms_dlpnt[++Y] = 0x00;
        _ms_dlpnt = _ms_b1_dll;
    }
    _ms_buffer = 0; // 0 is the current write buffer
    *DPPH = _ms_b1_dll >> 8; // 1 the current displayed buffer
    *DPPL = _ms_b1_dll;
    *CTRL = 0x40; // DMA on, Black background, 160A/B mode
}

void multisprite_clear()
{
    // Reset DL ends for both buffers
    for (X = _MS_DLL_ARRAY_SIZE * 2 - 1; X >= 0; X--) {
        _ms_dlend[X] = 0;
        _ms_dldma[X] = (454 - 23 - 7) / 2;
    }
    for (X = _MS_DLL_ARRAY_SIZE - 1; X >= 0; X--) {
        _ms_dlend_save[X] = 0;
        _ms_dldma_save[X] = (454 - 23 - 7) / 2;
    }
}

// This one should be done during VBLANK, since we are copying from write buffer to currently displayed buffer
void multisprite_save()
{
    if (_ms_buffer) {
        for (Y = _MS_DLL_ARRAY_SIZE * 2 - 1, X = _MS_DLL_ARRAY_SIZE - 1; X >= 0; Y--, X--) {
            _ms_dlend_save[X] = _ms_dlend[Y];
            _ms_dldma_save[X] = _ms_dldma[Y];
        }
        // Copy the DLs from current write buffer to all buffers
        for (_ms_tmp = _MS_DLL_ARRAY_SIZE - 1; _ms_tmp >= 0; _ms_tmp--) {
            _ms_dlpnt = _ms_dls[X = _ms_tmp + _MS_DLL_ARRAY_SIZE];
            _ms_dlpnt2 = _ms_dls[X = _ms_tmp];
            for (Y = _ms_dlend[X] - 1; Y >= 0; Y--) {
                _ms_dlpnt2[Y] = _ms_dlpnt[Y];
            } 
        }
    } else {
        for (X = _MS_DLL_ARRAY_SIZE - 1; X >= 0; X--) {
            _ms_dlend_save[X] = _ms_dlend[X];
            _ms_dldma_save[X] = _ms_dldma[X];
        }
        // Copy the DLs from current write buffer to all buffers
        for (_ms_tmp = _MS_DLL_ARRAY_SIZE - 1; _ms_tmp >= 0; _ms_tmp--) {
            _ms_dlpnt = _ms_dls[X = _ms_tmp + _MS_DLL_ARRAY_SIZE];
            _ms_dlpnt2 = _ms_dls[X = _ms_tmp];
            for (Y = _ms_dlend[X] - 1; Y >= 0; Y--) {
                _ms_dlpnt[Y] = _ms_dlpnt2[Y];
            } 
        }
    }
}

void multisprite_restore()
{
    if (_ms_buffer) {
        for (Y = _MS_DLL_ARRAY_SIZE * 2 - 1, X = _MS_DLL_ARRAY_SIZE - 1; X >= 0; Y--, X--) {
            _ms_dlend[X] = _ms_dlend_save[Y];
            _ms_dldma[X] = _ms_dldma_save[Y];
        }
    } else {
        for (X = _MS_DLL_ARRAY_SIZE - 1; X >= 0; X--) {
            _ms_dlend[X] = _ms_dlend_save[X];
            _ms_dldma[X] = _ms_dldma_save[X];
        }
    }
}

// This one should obvisouly executed during VBLANK, since it modifies the DPPL/H pointers
void multisprite_flip()
{
    if (_ms_buffer) {
        // Add DL end entry on each DL
        for (X = _MS_DLL_ARRAY_SIZE * 2 - 1; X >= _MS_DLL_ARRAY_SIZE; X--) {
            _ms_dlpnt = _ms_dls[X];
            Y = _ms_dlend[X];
            _ms_dlpnt[++Y] = 0; 
        }
        // Restore saved state 
        for (Y = _MS_DLL_ARRAY_SIZE * 2 - 1, X = _MS_DLL_ARRAY_SIZE - 1; X >= 0; Y--, X--) {
            _ms_dlend[Y] = _ms_dlend_save[X];
            _ms_dldma[Y] = _ms_dldma_save[X];
        }
        _ms_buffer = 0; // 0 is the current write buffer
        *DPPH = _ms_b1_dll >> 8; // 1 the current displayed buffer
        *DPPL = _ms_b1_dll;
    } else {
        // Add DL end entry on each DL
        // Restore saved state 
        for (X = _MS_DLL_ARRAY_SIZE - 1; X >= 0; X--) {
            _ms_dlpnt = _ms_dls[X];
            Y = _ms_dlend[X];
            _ms_dlpnt[++Y] = 0; 
            _ms_dlend[X] = _ms_dlend_save[X];
            _ms_dldma[X] = _ms_dldma_save[X];
        }
        _ms_buffer = 1; // 1 is the current write buffer
        *DPPH = _ms_b0_dll >> 8; // 0 the current displayed buffer
        *DPPL = _ms_b0_dll;
    }
}

#endif // __ATARI7800_MULTISPRITE__
 
