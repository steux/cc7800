/*
    multisprite_8lines.h : multisprite display for the Atari 7800, 8 lines display zones based, no double buffer
    Copyleft 2023-2024 Bruno STEUX 

    This file is distributed as a companion file to cc7800 - a subset of C compiler for the Atari 7800
    
    v0.1: First working version
*/

#ifndef __ATARI7800_MULTISPRITE_8LINES__
#define __ATARI7800_MULTISPRITE_8LINES__

#include "prosystem.h"
#include "stdlib.h"
#include "assert.h"

#ifndef INIT_BANK
#define INIT_BANK
#endif

#define MS_YMAX 224
#define _MS_DLL_ARRAY_SIZE 28 
#define _MS_DMA_START_VALUE (402 / 2)

#ifndef _MS_DL_SIZE
#define _MS_DL_SIZE 64
#endif
#ifndef _MS_DL_MALLOC
#define _MS_DL_MALLOC(y) _MS_DL_SIZE
#define _MS_DL_LIMIT (_MS_DL_SIZE - 7)
#else
const char _ms_dl_limits[_MS_DLL_ARRAY_SIZE] = {
    _MS_DL_MALLOC(0) - 7, _MS_DL_MALLOC(1) - 7, _MS_DL_MALLOC(2) - 7, _MS_DL_MALLOC(3) - 7, _MS_DL_MALLOC(4) - 7, _MS_DL_MALLOC(5) - 7, _MS_DL_MALLOC(6) - 7, _MS_DL_MALLOC(7) - 7, _MS_DL_MALLOC(8) - 7, _MS_DL_MALLOC(9) - 7, _MS_DL_MALLOC(10) - 7, _MS_DL_MALLOC(11) - 7, _MS_DL_MALLOC(12) - 7, _MS_DL_MALLOC(13) - 7, _MS_DL_MALLOC(14) - 7,
    _MS_DL_MALLOC(15) - 7, _MS_DL_MALLOC(16) - 7, _MS_DL_MALLOC(17) - 7, _MS_DL_MALLOC(18) - 7, _MS_DL_MALLOC(19) - 7, _MS_DL_MALLOC(20) - 7, _MS_DL_MALLOC(21) - 7, _MS_DL_MALLOC(22) - 7, _MS_DL_MALLOC(23) - 7, _MS_DL_MALLOC(24) - 7, _MS_DL_MALLOC(25) - 7, _MS_DL_MALLOC(26) - 7, _MS_DL_MALLOC(27) - 7
};
#define _MS_DL_LIMIT _ms_dl_limits[X] 
#endif

// Zeropage variables
char _ms_dmaerror;
#define _ms_tmpptr _libc_tmpptr
#define _ms_tmpptr2 _libc_tmpptr2
#define _ms_tmp _libc_tmp
#define _ms_tmp2 _libc_tmp2
signed char _ms_tmp3;
ramchip char _ms_tmp4;
char *_ms_sparse_tiles_ptr_high, *_ms_sparse_tiles_ptr_low;

ramchip char _ms_dl0[_MS_DL_MALLOC(0)], _ms_dl1[_MS_DL_MALLOC(1)], _ms_dl2[_MS_DL_MALLOC(2)], _ms_dl3[_MS_DL_MALLOC(3)], _ms_dl4[_MS_DL_MALLOC(4)], _ms_dl5[_MS_DL_MALLOC(5)], _ms_dl6[_MS_DL_MALLOC(6)], _ms_dl7[_MS_DL_MALLOC(7)], _ms_dl8[_MS_DL_MALLOC(8)], _ms_dl9[_MS_DL_MALLOC(9)], _ms_dl10[_MS_DL_MALLOC(10)], _ms_dl11[_MS_DL_MALLOC(11)], _ms_dl12[_MS_DL_MALLOC(12)], _ms_dl13[_MS_DL_MALLOC(13)], _ms_dl14[_MS_DL_MALLOC(14)], _ms_dl15[_MS_DL_MALLOC(15)], _ms_dl16[_MS_DL_MALLOC(16)], _ms_dl17[_MS_DL_MALLOC(17)], _ms_dl18[_MS_DL_MALLOC(18)], _ms_dl19[_MS_DL_MALLOC(19)], _ms_dl20[_MS_DL_MALLOC(20)], _ms_dl21[_MS_DL_MALLOC(21)], _ms_dl22[_MS_DL_MALLOC(22)], _ms_dl23[_MS_DL_MALLOC(23)], _ms_dl24[_MS_DL_MALLOC(24)], _ms_dl25[_MS_DL_MALLOC(25)], _ms_dl26[_MS_DL_MALLOC(26)], _ms_dl27[_MS_DL_MALLOC(27)], _ms_dl_rubbish[_MS_DL_MALLOC(28)];

const char *_ms_dls[32] = {
    _ms_dl0, _ms_dl1, _ms_dl2, _ms_dl3, _ms_dl4, _ms_dl5, _ms_dl6, _ms_dl7, _ms_dl8, _ms_dl9, _ms_dl10, _ms_dl11, _ms_dl12, _ms_dl13, _ms_dl14, _ms_dl15, _ms_dl16, _ms_dl17, _ms_dl18, _ms_dl19, _ms_dl20, _ms_dl21, _ms_dl22, _ms_dl23, _ms_dl24, _ms_dl25, _ms_dl26, _ms_dl27,
    _ms_dl_rubbish, _ms_dl_rubbish, _ms_dl_rubbish, _ms_dl_rubbish 
};

const char _ms_set_wm_dl[7] = {0, 0x40, 0x21, 0xff, 160, 0, 0}; // Write mode 0
const char _ms_blank_dl[2] = {0, 0};

ramchip char _ms_dll[(_MS_DLL_ARRAY_SIZE + 6) * 3];
ramchip char _ms_dlend[32];
ramchip char _ms_dlend_save[_MS_DLL_ARRAY_SIZE];
#ifdef MULTISPRITE_OVERLAY
ramchip char _ms_dlend_save_overlay[_MS_DLL_ARRAY_SIZE];
#endif

ramchip char _ms_pal_detected;
ramchip char _ms_pal_frame_skip_counter;

INIT_BANK void multisprite_init();
INIT_BANK void multisprite_clear();
INIT_BANK void multisprite_save();
void multisprite_restore();

#ifdef DMA_CHECK
ramchip char _ms_dldma[_MS_DLL_ARRAY_SIZE];
ramchip char _ms_dldma_save[_MS_DLL_ARRAY_SIZE];
#define _MS_DMA_CHECK(x) \
        _ms_dldma[X] -= (x); \
        if (_ms_dldma[X] < 0) { \
            _ms_dmaerror++; \
            _ms_dldma[X] += (x); \
        } else  
#define _MS_DMA_SUB(x) _ms_dldma[X] -= (x)
#else
#define _MS_DMA_SUB(x)
#define _MS_DMA_CHECK(x) 
#endif 

#define multisprite_display_sprite(x, y, gfx, width, palette) \
	_ms_tmp = (y) & 0x07; \
	X = (y) >> 3; \
        _MS_DMA_CHECK((8 + width * 3 + 1) / 2) { \
            _ms_tmpptr = _ms_dls[X]; \
            Y = _ms_dlend[X]; \
            if (Y >= _MS_DL_LIMIT) { \
                _ms_dmaerror++; \
            } else { \
                _ms_tmpptr[Y++] = (gfx); \
                _ms_tmp2 = Y++; \
                _ms_tmpptr[Y++] = ((gfx) >> 8) | _ms_tmp; \
                _ms_tmpptr[Y++] = (x); \
                _ms_dlend[X] = Y; \
                _ms_tmpptr[++Y] = 0; \
                _ms_tmpptr[Y = _ms_tmp2] = -width & 0x1f | (palette << 5); \
                if (_ms_tmp) { \
                    X++; \
                    _MS_DMA_CHECK((8 + width * 3 + 1) / 2) { \
                        _ms_tmpptr = _ms_dls[X];  \
                        Y = _ms_dlend[X]; \
                        if (Y >= _MS_DL_LIMIT) { \
                            _ms_dmaerror++; \
                        } else { \
                            _ms_tmpptr[Y++] = (gfx); \
                            _ms_tmp2 = Y++; \
                            _ms_tmpptr[Y++] = (((gfx) >> 8) - 0x08) | _ms_tmp; \
                            _ms_tmpptr[Y++] = (x); \
                            _ms_dlend[X] = Y; \
                            _ms_tmpptr[++Y] = 0; \
                            _ms_tmpptr[Y = _ms_tmp2] = -width & 0x1f | (palette << 5); \
                        } \
                    } \
                }\
            }\
        }

#define multisprite_display_double_sprite(x, y, gfx, width, palette, mode) \
	_ms_tmp = (y) & 0x07; \
	X = (y) >> 3; \
        _MS_DMA_CHECK((10 + width * 3 + 1) / 2) { \
            _ms_tmpptr = _ms_dls[X]; \
            Y = _ms_dlend[X]; \
            if (Y >= _MS_DL_LIMIT) { \
                _ms_dmaerror++; \
            } else { \
                _ms_tmpptr[Y++] = (gfx);\
                _ms_tmp4 = Y++; \
                _ms_tmpptr[Y++] = ((gfx) >> 8) | _ms_tmp; \
                _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                _ms_tmpptr[Y++] = (x); \
                _ms_dlend[X] = Y; \
                _ms_tmpptr[++Y] = 0; \
                _ms_tmpptr[Y = _ms_tmp4] = (mode)?0xc0:0x40; \
                if (_ms_tmp) { \
                    _ms_tmp3 = (gfx); \
                    _ms_tmp2 = (((gfx) >> 8) - 0x08) | _ms_tmp; \
                        X++; \
                        _MS_DMA_CHECK((20 + 3 * width * 3 + 1) / 2) { \
                            _ms_tmpptr = _ms_dls[X];  \
                            Y = _ms_dlend[X]; \
                            if (Y >= _MS_DL_LIMIT - 5) { \
                                _ms_dmaerror++; \
                            } else { \
                                _ms_tmpptr[Y++] = _ms_tmp3; \
                                _ms_tmp4 = Y++; \
                                _ms_tmpptr[Y++] = _ms_tmp2; \
                                _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                                _ms_tmpptr[Y++] = (x); \
                                _ms_tmp3 += width; \
                                _ms_tmpptr[Y++] = _ms_tmp3; \
                                _ms_tmpptr[Y++] = (mode)?0xc0:0x40; \
                                _ms_tmpptr[Y++] = ((gfx) >> 8) | _ms_tmp; \
                                _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                                _ms_tmpptr[Y++] = (x); \
                                _ms_dlend[X] = Y; \
                                _ms_tmpptr[++Y] = 0; \
                                _ms_tmpptr[Y = _ms_tmp4] = (mode)?0xc0:0x40; \
                            } \
                        } \
                    X++; \
                    _MS_DMA_CHECK((10 + width * 3 + 1) / 2) { \
                        _ms_tmpptr = _ms_dls[X];  \
                        Y = _ms_dlend[X]; \
                        if (Y >= _MS_DL_LIMIT) { \
                            _ms_dmaerror++; \
                        } else { \
                            _ms_tmpptr[Y++] = _ms_tmp3; \
                            _ms_tmp4 = Y++; \
                            _ms_tmpptr[Y++] = _ms_tmp2; \
                            _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                            _ms_tmpptr[Y++] = (x); \
                            _ms_dlend[X] = Y; \
                            _ms_tmpptr[++Y] = 0; \
                            _ms_tmpptr[Y = _ms_tmp4] = (mode)?0xc0:0x40; \
                        } \
                    } \
                } else { \
                    _ms_tmpptr2 = (gfx); \
                    _ms_tmp2 = (_ms_tmpptr2 >> 8) | _ms_tmp; \
                        X++; \
                        _ms_tmpptr2 += width; \
                        _MS_DMA_CHECK((10 + width * 3 + 1) / 2) { \
                            _ms_tmpptr = _ms_dls[X];  \
                            Y = _ms_dlend[X]; \
                            if (Y >= _MS_DL_LIMIT) { \
                                _ms_dmaerror++; \
                            } else { \
                                _ms_tmpptr[Y++] = _ms_tmpptr2; \
                                _ms_tmp = Y++; \
                                _ms_tmpptr[Y++] = _ms_tmp2; \
                                _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                                _ms_tmpptr[Y++] = (x); \
                                _ms_dlend[X] = Y; \
                                _ms_tmpptr[++Y] = 0; \
                                _ms_tmpptr[Y = _ms_tmp] = (mode)?0xc0:0x40; \
                            } \
                        } \
                } \
            } \
        }

#define multisprite_display_big_sprite(x, y, gfx, width, palette, height, mode) \
	_ms_tmp = (y) & 0x07; \
	X = (y) >> 3; \
        _MS_DMA_CHECK((10 + width * 3 + 1) / 2) { \
            _ms_tmpptr = _ms_dls[X]; \
            Y = _ms_dlend[X]; \
            if (Y >= _MS_DL_LIMIT) { \
                _ms_dmaerror++; \
            } else { \
                _ms_tmpptr[Y++] = (gfx);\
                _ms_tmp4 = Y++; \
                _ms_tmpptr[Y++] = ((gfx) >> 8) | _ms_tmp; \
                _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                _ms_tmpptr[Y++] = (x); \
                _ms_dlend[X] = Y; \
                _ms_tmpptr[++Y] = 0; \
                _ms_tmpptr[Y = _ms_tmp4] = (mode)?0xc0:0x40; \
                if (_ms_tmp) { \
                    _ms_tmpptr2 = (gfx); \
                    _ms_tmp2 = ((_ms_tmpptr2 >> 8) - 0x08) | _ms_tmp; \
                    for (_ms_tmp3 = (height) - 1; _ms_tmp3 != 0; _ms_tmp3--) { \
                        X++; \
                        _MS_DMA_CHECK((20 + 3 * width * 3 + 1) / 2) { \
                            _ms_tmpptr = _ms_dls[X];  \
                            Y = _ms_dlend[X]; \
                            if (Y >= _MS_DL_LIMIT - 5) { \
                                _ms_dmaerror++; \
                            } else { \
                                _ms_tmpptr[Y++] = _ms_tmpptr2; \
                                _ms_tmp4 = Y++; \
                                _ms_tmpptr[Y++] = _ms_tmp2; \
                                _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                                _ms_tmpptr[Y++] = (x); \
                                _ms_tmpptr2 += width; \
                                _ms_tmpptr[Y++] = _ms_tmpptr2; \
                                _ms_tmpptr[Y++] = (mode)?0xc0:0x40; \
                                _ms_tmpptr[Y++] = (_ms_tmpptr2 >> 8) | _ms_tmp; \
                                _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                                _ms_tmpptr[Y++] = (x); \
                                _ms_dlend[X] = Y; \
                                _ms_tmpptr[++Y] = 0; \
                                _ms_tmpptr[Y = _ms_tmp4] = (mode)?0xc0:0x40; \
                            } \
                        } \
                    } \
                    X++; \
                    _MS_DMA_CHECK((10 + width * 3 + 1) / 2) { \
                        _ms_tmpptr = _ms_dls[X];  \
                        Y = _ms_dlend[X]; \
                        if (Y >= _MS_DL_LIMIT) { \
                            _ms_dmaerror++; \
                        } else { \
                            _ms_tmpptr[Y++] = _ms_tmpptr2; \
                            _ms_tmp4 = Y++; \
                            _ms_tmpptr[Y++] = _ms_tmp2; \
                            _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                            _ms_tmpptr[Y++] = (x); \
                            _ms_dlend[X] = Y; \
                            _ms_tmpptr[++Y] = 0; \
                            _ms_tmpptr[Y = _ms_tmp4] = (mode)?0xc0:0x40; \
                        } \
                    } \
                } else { \
                    _ms_tmpptr2 = (gfx); \
                    _ms_tmp2 = (_ms_tmpptr2 >> 8) | _ms_tmp; \
                    for (_ms_tmp3 = (height) - 1; _ms_tmp3 != 0; _ms_tmp3--) { \
                        X++; \
                        _ms_tmpptr2 += width; \
                        _MS_DMA_CHECK((10 + width * 3 + 1) / 2) { \
                            _ms_tmpptr = _ms_dls[X];  \
                            Y = _ms_dlend[X]; \
                            if (Y >= _MS_DL_LIMIT) { \
                                _ms_dmaerror++; \
                            } else { \
                                _ms_tmpptr[Y++] = _ms_tmpptr2; \
                                _ms_tmp = Y++; \
                                _ms_tmpptr[Y++] = _ms_tmp2; \
                                _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                                _ms_tmpptr[Y++] = (x); \
                                _ms_dlend[X] = Y; \
                                _ms_tmpptr[++Y] = 0; \
                                _ms_tmpptr[Y = _ms_tmp] = (mode)?0xc0:0x40; \
                            } \
                        } \
                    } \
                } \
            } \
        }

#define multisprite_display_sprite_ex(x, y, gfx, width, palette, mode) \
	_ms_tmp = (y) & 0x07; \
	X = (y) >> 3; \
        _MS_DMA_CHECK((8 + width * 3 + 1) / 2) { \
            _ms_tmpptr = _ms_dls[X]; \
            Y = _ms_dlend[X]; \
            if (Y >= _MS_DL_LIMIT) { \
                _ms_dmaerror++; \
            } else { \
                _ms_tmpptr[Y++] = (gfx); \
                _ms_tmp2 = Y++; \
                _ms_tmpptr[Y++] = ((gfx) >> 8) | _ms_tmp; \
                _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                _ms_tmpptr[Y++] = (x); \
                _ms_dlend[X] = Y; \
                _ms_tmpptr[++Y] = 0; \
                _ms_tmpptr[Y = _ms_tmp2] = (mode)?0xc0:0x40; \
                if (_ms_tmp) { \
                    X++; \
                    _MS_DMA_CHECK((8 + width * 3 + 1) / 2) { \
                        _ms_tmpptr = _ms_dls[X];  \
                        Y = _ms_dlend[X]; \
                        if (Y >= _MS_DL_LIMIT) { \
                            _ms_dmaerror++; \
                        } else { \
                            _ms_tmpptr[Y++] = (gfx); \
                            _ms_tmp2 = Y++; \
                            _ms_tmpptr[Y++] = (((gfx) >> 8) - 0x08) | _ms_tmp; \
                            _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                            _ms_tmpptr[Y++] = (x); \
                            _ms_dlend[X] = Y; \
                            _ms_tmpptr[++Y] = 0; \
                            _ms_tmpptr[Y = _ms_tmp2] = (mode)?0xc0:0x40; \
                        } \
                    } \
                }\
            }\
        }

#define multisprite_display_sprite_aligned(x, y, gfx, width, palette, mode) \
	X = (y) >> 3; \
        _MS_DMA_CHECK((8 + width * 3 + 1) / 2) { \
            _ms_tmpptr = _ms_dls[X]; \
            Y = _ms_dlend[X]; \
            if (Y >= _MS_DL_LIMIT) { \
                _ms_dmaerror++; \
            } else { \
                _ms_tmpptr[Y++] = (gfx); \
                _ms_tmp = Y++; \
                _ms_tmpptr[Y++] = ((gfx) >> 8); \
                _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                _ms_tmpptr[Y++] = (x); \
                _ms_dlend[X] = Y; \
                _ms_tmpptr[++Y] = 0; \
                _ms_tmpptr[Y = _ms_tmp] = (mode)?0xc0:0x40; \
            }\
        }

#define multisprite_display_sprite_aligned_fast(x, y, gfx, width, palette) \
	X = (y) >> 3; \
        _MS_DMA_CHECK((8 + width * 3 + 1) / 2) { \
            _ms_tmpptr = _ms_dls[X]; \
            Y = _ms_dlend[X]; \
            if (Y >= _MS_DL_LIMIT) { \
                _ms_dmaerror++; \
            } else { \
                _ms_tmpptr[Y++] = (gfx); \
                _ms_tmp = Y++; \
                _ms_tmpptr[Y++] = ((gfx) >> 8); \
                _ms_tmpptr[Y++] = (x); \
                _ms_dlend[X] = Y; \
                _ms_tmpptr[++Y] = 0; \
                _ms_tmpptr[Y = _ms_tmp] = -width & 0x1f | (palette << 5); \
            }\
        }

#define multisprite_display_sprite_fast(x, y, gfx, width, palette) \
	_ms_tmp = (y) & 0x07; \
	X = (y) >> 3; \
        _MS_DMA_SUB((8 + width * 3 + 1) / 2);  \
        _ms_tmpptr = _ms_dls[X]; \
        Y = _ms_dlend[X]; \
        _ms_tmpptr[Y++] = (gfx); \
        _ms_tmp2 = Y++; \
        _ms_tmpptr[Y++] = ((gfx) >> 8) | _ms_tmp; \
        _ms_tmpptr[Y++] = (x); \
        _ms_dlend[X] = Y; \
        _ms_tmpptr[++Y] = 0; \
        _ms_tmp3 = -width & 0x1f | (palette << 5); \
        _ms_tmpptr[Y = _ms_tmp2] = _ms_tmp3; \
        if (_ms_tmp) { \
            X++; \
            _MS_DMA_SUB((8 + width * 3 + 1) / 2);  \
            _ms_tmpptr = _ms_dls[X];  \
            Y = _ms_dlend[X]; \
            _ms_tmpptr[Y++] = (gfx); \
            _ms_tmp2 = Y++; \
            _ms_tmpptr[Y++] = (((gfx) >> 8) - 0x08) | _ms_tmp;  \
            _ms_tmpptr[Y++] = (x); \
            _ms_dlend[X] = Y; \
            _ms_tmpptr[++Y] = 0; \
            _ms_tmpptr[Y = _ms_tmp2] = _ms_tmp3; \
        }

#define multisprite_reserve_dma(y, nb_sprites, width) \
	_ms_tmp = (y) & 0x07; \
	X = (y) >> 3; \
        _MS_DMA_SUB(nb_sprites * (8 + width * 3 + 1) / 2); \
        if ((y) & 0x0f) { \
            X++; \
            _MS_DMA_SUB(nb_sprites * (8 + width * 3 + 1) / 2); \
        }

#define multisprite_display_tiles(x, y, tiles, size, palette) \
    X = (y); \
    _MS_DMA_CHECK((10 + 3 + size * 9 + 1) / 2) { \
        _ms_tmpptr = _ms_dls[X]; \
        Y = _ms_dlend[X]; \
        if (Y >= _MS_DL_LIMIT) { \
            _ms_dmaerror++; \
         } else { \
            _ms_tmpptr[Y++] = (tiles); \
            _ms_tmp = Y++; \
            _ms_tmpptr[Y++] = (tiles) >> 8; \
            _ms_tmpptr[Y++] = -size & 0x1f | (palette << 5); \
            _ms_tmpptr[Y++] = (x); \
            _ms_dlend[X] = Y; \
            _ms_tmpptr[++Y] = 0; \
            _ms_tmpptr[Y = _ms_tmp] = 0x60; \
        } \
    }

#define multisprite_display_tiles_fast(x, y, tiles, size, palette) \
    X = (y); \
    _MS_DMA_SUB((10 + 3 + size * 9 + 1) / 2); \
    _ms_tmpptr = _ms_dls[X]; \
    Y = _ms_dlend[X]; \
    _ms_tmpptr[Y++] = (tiles); \
    _ms_tmp = Y++; \
    _ms_tmpptr[Y++] = (tiles) >> 8; \
    _ms_tmpptr[Y++] = -size & 0x1f | (palette << 5); \
    _ms_tmpptr[Y++] = (x); \
    _ms_dlend[X] = Y; \
    _ms_tmpptr[++Y] = 0; \
    _ms_tmpptr[Y = _ms_tmp] = 0x60;

#define multisprite_set_charbase(ptr) *CHARBASE = (ptr) >> 8;

// Macro to convert NTSC colors to PAL colors
#define multisprite_color(color) ((color >= 0xf0)?(0x10 + (color & 0x0f)):((color >= 0x10)?(color + (_ms_pal_detected & 0x10)):color))

INIT_BANK void multisprite_get_tv()
{
    while (!(*MSTAT & 0x80)); // Wait for VBLANK
    while (*MSTAT & 0x80); // Wait for end of VBLANK

    X = 0;
    do {
        strobe(WSYNC);
        strobe(WSYNC);
        X++;
    } while (!(*MSTAT & 0x80));

    if (X >= 135) _ms_pal_detected = 0xff; 
    _ms_pal_frame_skip_counter = 0;
}

char multisprite_pal_frame_skip()
{
    if (!_ms_pal_detected) return 0;
    _ms_pal_frame_skip_counter++;
    if (_ms_pal_frame_skip_counter >= 5) {
        _ms_pal_frame_skip_counter = 0;
        return 1;
    }
    return 0;
}

inline void multisprite_start()
{
    _ms_dmaerror = 0;
    *DPPH = _ms_dll >> 8;
    *DPPL = _ms_dll;
#ifdef MODE_320AC
    *CTRL = 0x43; // DMA on, 320A/C mode, One (1) byte characters mode
#else
#ifdef MODE_320BD
    *CTRL = 0x42; // DMA on, 320B/D mode, One (1) byte characters mode
#else
    *CTRL = 0x50; // DMA on, 160A/B mode, Two (2) byte characters mode
#endif
#endif
}

INIT_BANK void multisprite_init()
{
    *BACKGRND = 0x0;
    
    // This is protection for out of screen sprites
    for (X = 31; X >= _MS_DLL_ARRAY_SIZE; X--) {
        _ms_dlend[X] = 0;
    }

    multisprite_get_tv();
    multisprite_clear();
    multisprite_save();

    _ms_tmpptr = _ms_dll;
    // Build DLL
    // 69 blank lines for PAL
    // 19 blank lines for NTSC
    if (_ms_pal_detected) {
        // 16 blank lines
        _ms_tmpptr[Y = 0] = 0x0f;  // 16 lines
        _ms_tmpptr[++Y] = _ms_set_wm_dl >> 8;
        _ms_tmpptr[++Y] = _ms_set_wm_dl;
        // 16 blank lines
        _ms_tmpptr[++Y] = 0x2f;  // 16 lines.. 8 high zone Holey DMA enabled just in case...
        _ms_tmpptr[++Y] = _ms_blank_dl >> 8;
        _ms_tmpptr[++Y] = _ms_blank_dl;
    } else {
        _ms_tmpptr[Y = 0] = 0x28; // 9 lines. 8 high zone Holey DMA enabled just in case...
        _ms_tmpptr[++Y] = _ms_set_wm_dl >> 8;
        _ms_tmpptr[++Y] = _ms_set_wm_dl;
    }
    // 8 pixel high regions (28 regions = 224 pixels)
    for (X = 0; X != _MS_DLL_ARRAY_SIZE; X++) {
        _ms_tmpptr[++Y] = 0x27; // 8 lines, Holey DMA enabled
        _ms_tmpptr[++Y] = _ms_dls[X] >> 8; // High address
        _ms_tmpptr[++Y] = _ms_dls[X]; // Low address
    }
    if (_ms_pal_detected) {
        // 16 blank lines
        _ms_tmpptr[++Y] = 0x2f;  // 16 lines. 8 high zone Holey DMA enabled just in case...
        _ms_tmpptr[++Y] = _ms_blank_dl >> 8;
        _ms_tmpptr[++Y] = _ms_blank_dl;
        // 16 blank lines
        _ms_tmpptr[++Y] = 0x0f;  // 16 lines
        _ms_tmpptr[++Y] = _ms_blank_dl >> 8;
        _ms_tmpptr[++Y] = _ms_blank_dl;
        // 4 blank lines
        _ms_tmpptr[++Y] = 0x04;  // 5 lines
        _ms_tmpptr[++Y] = _ms_blank_dl >> 8;
        _ms_tmpptr[++Y] = _ms_blank_dl;
    } else {
        _ms_tmpptr[++Y] = 0x29; // 10 lines. 8 high zone Holey DMA enabled just in case...
        _ms_tmpptr[++Y] = _ms_blank_dl >> 8;
        _ms_tmpptr[++Y] = _ms_blank_dl;
    }
    
    multisprite_start();
}

INIT_BANK void multisprite_clear()
{
    char *ptr;
    Y = 1;
    for (X = _MS_DLL_ARRAY_SIZE - 1; X >= 0; X--) {
        _ms_dlend[X] = 0;
        _ms_dlend_save[X] = 0;
#ifdef DMA_CHECK
        _ms_dldma_save[X] = _MS_DMA_START_VALUE;
#endif
        ptr = _ms_dls[X];
        ptr[Y] = 0;
    }
}

INIT_BANK void multisprite_save()
{
    for (X = _MS_DLL_ARRAY_SIZE - 1; X >= 0; X--) {
        _ms_dlend_save[X] = _ms_dlend[X];
#ifdef DMA_CHECK
        _ms_dldma_save[X] = _ms_dldma[X];
#endif
    }
}

#ifdef MULTISPRITE_OVERLAY
void multisprite_save_overlay()
{
    for (X = _MS_DLL_ARRAY_SIZE - 1; X >= 0; X--) {
        _ms_dlend_save_overlay[X] = _ms_dlend[X];
    }
}

void multisprite_save_overlay_line(char line)
{
    X = line;
    _ms_dlend_save_overlay[X] = _ms_dlend[X];
}

void multisprite_clear_overlay()
{
    char *ptr;
    for (X = _MS_DLL_ARRAY_SIZE - 1; X >= 0; X--) {
        _ms_dlend_save_overlay[X] = _ms_dlend_save[X];
        _ms_dlend[X] = _ms_dlend_save[X];
        Y = _ms_dlend[X];
        ptr = _ms_dls[X];
        ptr[++Y] = 0;
    }
}

void multisprite_restore_overlay()
{
    char *ptr;
    for (X = _MS_DLL_ARRAY_SIZE - 1; X >= 0; X--) {
        _ms_dlend[X] = _ms_dlend_save_overlay[X];
        Y = _ms_dlend[X];
        ptr = _ms_dls[X];
        ptr[++Y] = 0;
    }
}
#endif

void multisprite_restore()
{
    char *ptr;
    for (X = _MS_DLL_ARRAY_SIZE - 1; X >= 0; X--) {
        _ms_dlend[X] = _ms_dlend_save[X];
#ifdef DMA_CHECK
        _ms_dldma[X] = _ms_dldma_save[X];
#endif
        Y = _ms_dlend[X];
        ptr = _ms_dls[X];
        ptr[++Y] = 0;
    }
}

void multisprite_restore_line(char line)
{
    char *ptr;
    X = line;
    _ms_dlend[X] = _ms_dlend_save[X];
#ifdef MULTISPRITE_OVERLAY
    _ms_dlend_save_overlay[X] = _ms_dlend[X];
#endif
#ifdef DMA_CHECK
    _ms_dldma[X] = _ms_dldma_save[X];
#endif
    Y = _ms_dlend[X];
    ptr = _ms_dls[X];
    ptr[++Y] = 0;
}

void multisprite_wait_for_vblank()
{
    while (!(*MSTAT & 0x80)); // Wait for VBLANK
}

// line: display list entry to apply DLI flag
void multisprite_enable_dli(char line)
{
    line = (line << 2) - line + 3; // line = line * 3 + 3
    if (_ms_pal_detected) line += 3;
    _ms_dll[X = line] |= 0x80;
}

// line : display list entry to apply DLI flag
void multisprite_disable_dli(char line)
{
    line = (line << 2) - line + 3; // line = line * 3 + 3
    if (_ms_pal_detected) line += 3;
    _ms_dll[X = line] &= 0x7f;
}

const char _ms_bit_extract[8] = {128, 64, 32, 16, 8, 4, 2, 1};

// ~100 cycles max pixel accurate collision detection (60us)
// 160 pixels mode function
#define multisprite_compute_collision(x1, y1, w1, h1, x2, y2, w2, h2, collision_map) {\
    _ms_tmp3 = 0; \
    _ms_tmp2 = (y1) + ((h1) - 1) - (y2); \
    if (_ms_tmp2 >= 0) { \
        if ((x1) <= (x2) + ((w2) - 1)) { \
            if ((y1) <= (y2) + ((h2) - 1)) { \
                _ms_tmp = (x1) + ((w1) - 1) - (x2); \
                if (_ms_tmp >= 0) { \
                    Y = _ms_tmp2 << ((w1 + w2 - 1) / 8); \
                    while (_ms_tmp >= 8) { \
                        Y++; \
                        _ms_tmp -= 8; \
                    } \
                    _ms_tmp3 = collision_map[Y] & _ms_bit_extract[X = _ms_tmp]; \
                } \
            } \
        } \
    } \
}

// 320 pixels resolution collision function
// x1 and x2 are 160 pixels resolution (always)
// w1 and w2 are 320 pixels resolution
#define multisprite_compute_collision_320(x1, y1, w1, h1, x2, y2, w2, h2, collision_map) {\
    _ms_tmp3 = 0; \
    _ms_tmp2 = (y1) + ((h1) - 1) - (y2); \
    if (_ms_tmp2 >= 0) { \
        if ((x1) <= (x2) + (((w2) >> 1) - 1)) { \
            if ((y1) <= (y2) + ((h2) - 1)) { \
                _ms_tmp = ((x1) + (((w1) >> 1) - 1) - (x2)); \
                if (_ms_tmp >= 0) { \
                    Y = _ms_tmp2 << ((w1 + w2 - 1) / 8); \
                    while (_ms_tmp >= 4) { \
                        Y++; \
                        _ms_tmp -= 4; \
                    } \
                    _ms_tmp3 = collision_map[Y] & _ms_bit_extract[X = _ms_tmp << 1]; \
                } \
            } \
        } \
    } \
}

#define multisprite_compute_box_collision(x1, y1, w1, h1, x2, y2, w2, h2) {\
    _ms_tmp3 = 0; \
    if ((y1) + ((h1) - 1) >= (y2)) { \
        if ((x1) <= (x2) + ((w2) - 1)) { \
            if ((y1) <= (y2) + ((h2) - 1)) { \
                if ((x1) + ((w1) - 1) >= (x2)) { \
                    _ms_tmp3 = 1; \
                } \
            } \
        } \
    } \
}

#define multisprite_collision_detected (_ms_tmp3)

#define multisprite_sparse_tiling(ptr, top, left, height) \
    _ms_sparse_tiles_ptr_high = ptr[Y = 0]; \
    _ms_sparse_tiles_ptr_low = ptr[Y = 1]; \
    _ms_sparse_tiling(top, left, height);

// Sparse tiling simple display
void _ms_sparse_tiling(char top, char left, char height)
{
    char *ptr, data[5], y, bottom;
    _ms_tmp2 = 0;

    bottom = top + height;

    for (X = top; X < bottom; _ms_tmp2++) {
        Y = _ms_tmp2;
        ptr = _ms_sparse_tiles_ptr_low[Y] | (_ms_sparse_tiles_ptr_high[Y] << 8);   
        _ms_tmpptr = _ms_dls[X];
        Y = 1;
        y = _ms_dlend[X];
        data[4] = ptr[Y];
        while (data[4] != 0xff) {
            data[0] = ptr[++Y];
            data[1] = ptr[++Y];
            data[2] = ptr[++Y];
            data[3] = ptr[++Y];
#ifdef DMA_CHECK 
            _ms_dldma[X] -= ptr[++Y]; // 18 cycles
#else
            ++Y;
#endif
            _save_y = Y;
            Y = y; // 6 cycles
            _ms_tmpptr[Y++] = data[0]; // 11 cycles
            _ms_tmpptr[Y++] = data[1];
            _ms_tmpptr[Y++] = data[2];
            _ms_tmpptr[Y++] = data[3];
            _ms_tmpptr[Y++] = (data[4] << 2) + left;
            y = Y; // 21 cycles
            Y = _save_y;
            Y++;
            data[4] = ptr[++Y];
        } 
        _ms_dlend[X++] = y;
    }
}

char multisprite_sparse_tiling_collision(char top, char left, char right)
{
    char *ptr, start, end, intersect = -1;
    Y = top;
    ptr = _ms_sparse_tiles_ptr_low[Y] | (_ms_sparse_tiles_ptr_high[Y] << 8);
    // Find the first possibly intersecting tileset on this line
    Y = 0;
    while (ptr[Y] < left) Y += 7;
    // This one possibly intersects
    end = ptr[Y++];
    start = ptr[Y++];
    while (right >= start) {
        char l = (left < start)?start:left;
        char r = (end < right)?end:right;
        char n = r - l;
        if (n < 0) break;
        char tmp = ptr[Y++];
        char tmp2 = ptr[Y++];
        if (!(tmp2 & 0x20)) { // Direct mode. We don't care about the content
            return 0;
        } 
        char *ptr_tiles = tmp | (ptr[Y] << 8);
        _save_y = Y;
        Y = l - start;
        if (tmp2 < 0) { // WM = 1: 2 entries per tile
            X = n << 1;
        } else {
            X = n;
        }
        for (; X >= 0; Y++, X--) {
            if (ptr_tiles[Y] < intersect) intersect = ptr_tiles[Y];    
        }
        Y = _save_y;
        Y += 3;
        end = ptr[Y++];
        start = ptr[Y++];
    }
    return intersect;
}

#endif // __ATARI7800_MULTISPRITE_8LINES__
 
