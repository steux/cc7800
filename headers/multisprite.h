/*
    multisprite.h : multisprite display for the Atari 7800
    Copyleft 2023 Bruno STEUX 

    This file is distributed as a companion file to cc7800 - a subset of C compiler for the Atari 7800
    
    v0.1: First working version
*/

#ifndef __ATARI7800_MULTISPRITE__
#define __ATARI7800_MULTISPRITE__

#include "prosystem.h"
#include "stdlib.h"

#ifndef _MS_DL_SIZE
#define _MS_DL_SIZE 64
#endif
#ifndef _MS_DL_MALLOC
#define _MS_DL_MALLOC(y) _MS_DL_SIZE
#endif

#define MS_YMAX 224
#define _MS_DLL_ARRAY_SIZE 15
#define _MS_DMA_START_VALUE ((454 - 42) / 2)

// Zeropage variables
char _ms_dmaerror;
#define _ms_dlpnt _libc_tmpptr
#define _ms_dlpnt2 _libc_tmpptr2
#define _ms_tmp _libc_tmp
#define _ms_tmp2 _libc_tmp2

#ifdef TILED_SCROLLING
#define BIDIR_VERTICAL_SCROLLING
#define HORIZONTAL_SCROLLING
#endif

#ifdef BIDIR_VERTICAL_SCROLLING
#ifndef VERTICAL_SCROLLING
#define VERTICAL_SCROLLING
#endif
#endif

#ifdef VERTICAL_SCROLLING
ramchip signed char _ms_vscroll_offset;
ramchip char _ms_delayed_vscroll;
#ifdef BIDIR_VERTICAL_SCROLLING
ramchip char _ms_top_sbuffer_size;
ramchip char _ms_top_sbuffer_dma;
ramchip char _ms_bottom_sbuffer_size;
ramchip char _ms_bottom_sbuffer_dma;
ramchip char _ms_scroll_buffers_refill;
#define MS_SCROLL_UP    1
#define MS_SCROLL_DOWN  2
#else
ramchip char _ms_sbuffer_size;
ramchip char _ms_sbuffer_dma;
#endif

#ifndef _MS_TOP_SCROLLING_ZONE
#define _MS_TOP_SCROLLING_ZONE 0
#endif

holeydma scattered(16,20) char _ms_hide_bottom[320] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff 
};
#ifdef BIDIR_VERTICAL_SCROLLING
ramchip char _ms_top_sbuffer[_MS_DL_MALLOC(-1)];
ramchip char _ms_bottom_sbuffer[_MS_DL_MALLOC(-2)];
#else
ramchip char _ms_sbuffer[_MS_DL_MALLOC(-1)];
#endif
#endif

#ifdef HORIZONTAL_SCROLLING
ramchip signed char _ms_hscroll;
ramchip signed char _ms_delayed_hscroll;
#endif

ramchip char _ms_b0_dl0[_MS_DL_MALLOC(0)], _ms_b0_dl1[_MS_DL_MALLOC(1)], _ms_b0_dl2[_MS_DL_MALLOC(2)], _ms_b0_dl3[_MS_DL_MALLOC(3)], _ms_b0_dl4[_MS_DL_MALLOC(4)], _ms_b0_dl5[_MS_DL_MALLOC(5)], _ms_b0_dl6[_MS_DL_MALLOC(6)], _ms_b0_dl7[_MS_DL_MALLOC(7)], _ms_b0_dl8[_MS_DL_MALLOC(8)], _ms_b0_dl9[_MS_DL_MALLOC(9)], _ms_b0_dl10[_MS_DL_MALLOC(10)], _ms_b0_dl11[_MS_DL_MALLOC(11)], _ms_b0_dl12[_MS_DL_MALLOC(12)], _ms_b0_dl13[_MS_DL_MALLOC(13)], _ms_b0_dl14[_MS_DL_MALLOC(14)];
ramchip char _ms_b1_dl0[_MS_DL_MALLOC(0)], _ms_b1_dl1[_MS_DL_MALLOC(1)], _ms_b1_dl2[_MS_DL_MALLOC(2)], _ms_b1_dl3[_MS_DL_MALLOC(3)], _ms_b1_dl4[_MS_DL_MALLOC(4)], _ms_b1_dl5[_MS_DL_MALLOC(5)], _ms_b1_dl6[_MS_DL_MALLOC(6)], _ms_b1_dl7[_MS_DL_MALLOC(7)], _ms_b1_dl8[_MS_DL_MALLOC(8)], _ms_b1_dl9[_MS_DL_MALLOC(9)], _ms_b1_dl10[_MS_DL_MALLOC(10)], _ms_b1_dl11[_MS_DL_MALLOC(11)], _ms_b1_dl12[_MS_DL_MALLOC(12)], _ms_b1_dl13[_MS_DL_MALLOC(13)], _ms_b1_dl14[_MS_DL_MALLOC(14)];
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
const char _ms_set_wm_dl[5] = {0, 0x40, 0x21, 0xff, 160}; // Write mode 0
const char _ms_blank_dl[2] = {0, 0};

ramchip char _ms_b0_dll[(_MS_DLL_ARRAY_SIZE + 5) * 3];
ramchip char _ms_b1_dll[(_MS_DLL_ARRAY_SIZE + 5) * 3];
ramchip char _ms_dlend[_MS_DLL_ARRAY_SIZE * 2];
ramchip char _ms_dldma[_MS_DLL_ARRAY_SIZE * 2];
ramchip char _ms_dlend_save[_MS_DLL_ARRAY_SIZE];
ramchip char _ms_dldma_save[_MS_DLL_ARRAY_SIZE];

ramchip char _ms_buffer; // Double buffer state
ramchip char _ms_pal_detected;

void multisprite_init();
void multisprite_clear();
void multisprite_save();
void multisprite_restore();
void multisprite_flip();

#ifdef VERTICAL_SCROLLING
#define multisprite_display_sprite(x, y, gfx, width, palette) \
        _ms_tmp2 = (y) + _ms_vscroll_offset; \
	_ms_tmp = _ms_tmp2 & 0x0f; \
	X = _ms_shift4[Y = (_ms_tmp2 & 0xfe | _ms_buffer)]; \
        _ms_dldma[X] -= (8 + width * 3 + 1) / 2; \
        if (_ms_dldma[X] < 0) { \
            _ms_dmaerror++; \
            _ms_dldma[X] += (8 + width * 3 + 1) / 2; \
        } else { \
            _ms_dlpnt = _ms_dls[X]; \
            Y = _ms_dlend[X]; \
            if (Y >= _MS_DL_SIZE - 6) { \
                _ms_dmaerror++; \
            } else { \
                _ms_dlpnt[Y++] = (gfx); \
                _ms_dlpnt[Y++] = -width & 0x1f | (palette << 5); \
                _ms_dlpnt[Y++] = ((gfx) >> 8) | _ms_tmp; \
                _ms_dlpnt[Y++] = (x); \
                _ms_dlend[X] = Y; \
                if (_ms_tmp2 & 0x0f) { \
                    X++; \
                    _ms_dldma[X] -= (8 + width * 3 + 1) / 2; \
                    if (_ms_dldma[X] < 0) { \
                        _ms_dmaerror++; \
                        _ms_dldma[X] += (8 + width * 3 + 1) / 2; \
                    } else { \
                        _ms_dlpnt = _ms_dls[X];  \
                        Y = _ms_dlend[X]; \
                        if (Y >= _MS_DL_SIZE - 6) { \
                            _ms_dmaerror++; \
                        } else { \
                            _ms_dlpnt[Y++] = (gfx); \
                            _ms_dlpnt[Y++] = -width & 0x1f | (palette << 5); \
                            _ms_dlpnt[Y++] = (((gfx) >> 8) - 0x10) | _ms_tmp; \
                            _ms_dlpnt[Y++] = (x); \
                            _ms_dlend[X] = Y; \
                        } \
                    } \
                }\
            }\
        }

#define multisprite_display_sprite_fast(x, y, gfx, width, palette) \
        _ms_tmp2 = (y) + _ms_vscroll_offset; \
        _ms_tmp = _ms_tmp2 & 0x0f; \
        X = _ms_shift4[Y = (_ms_tmp2 & 0xfe | _ms_buffer)]; \
        _ms_dldma[X] -= (8 + width * 3 + 1) / 2; \
        _ms_dlpnt = _ms_dls[X]; \
        Y = _ms_dlend[X]; \
        _ms_dlpnt[Y++] = (gfx); \
        _ms_dlpnt[Y++] = -width & 0x1f | (palette << 5); \
        _ms_dlpnt[Y++] = ((gfx) >> 8) | _ms_tmp; \
        _ms_dlpnt[Y++] = (x); \
        _ms_dlend[X] = Y; \
        if (_ms_tmp2 & 0x0f) { \
            X++; \
            _ms_dldma[X] -= (8 + width * 3 + 1) / 2; \
            _ms_dlpnt = _ms_dls[X];  \
            Y = _ms_dlend[X]; \
            _ms_dlpnt[Y++] = (gfx); \
            _ms_dlpnt[Y++] = -width & 0x1f | (palette << 5); \
            _ms_dlpnt[Y++] = (((gfx) >> 8) - 0x10) | _ms_tmp; \
            _ms_dlpnt[Y++] = (x); \
            _ms_dlend[X] = Y; \
        }

#define multisprite_reserve_dma(y, nb_sprites, width) \
        _ms_tmp2 = (y) + _ms_vscroll_offset; \
        X = _ms_shift4[Y = (_ms_tmp2 & 0xfe | _ms_buffer)]; \
        _ms_dldma[X] -= nb_sprites * (8 + width * 3 + 1) / 2; \
        if (_ms_tmp2 & 0x0f) { \
            X++; \
            _ms_dldma[X] -= nb_sprites * (8 + width * 3 + 1) / 2; \
        }

#else
#define multisprite_display_sprite(x, y, gfx, width, palette) \
	_ms_tmp = (y) & 0x0f; \
	X = _ms_shift4[Y = (y & 0xfe | _ms_buffer)]; \
        _ms_dldma[X] -= (8 + width * 3 + 1) / 2; \
        if (_ms_dldma[X] < 0) { \
            _ms_dmaerror++; \
            _ms_dldma[X] += (8 + width * 3 + 1) / 2; \
        } else { \
            _ms_dlpnt = _ms_dls[X]; \
            Y = _ms_dlend[X]; \
            if (Y >= _MS_DL_SIZE - 6) { \
                _ms_dmaerror++; \
            } else { \
                _ms_dlpnt[Y++] = (gfx); \
                _ms_dlpnt[Y++] = -width & 0x1f | (palette << 5); \
                _ms_dlpnt[Y++] = ((gfx) >> 8) | _ms_tmp; \
                _ms_dlpnt[Y++] = (x); \
                _ms_dlend[X] = Y; \
                if ((y) & 0x0f) { \
                    X++; \
                    _ms_dldma[X] -= (8 + width * 3 + 1) / 2; \
                    if (_ms_dldma[X] < 0) { \
                        _ms_dmaerror++; \
                        _ms_dldma[X] += (8 + width * 3 + 1) / 2; \
                    } else { \
                        _ms_dlpnt = _ms_dls[X];  \
                        Y = _ms_dlend[X]; \
                        if (Y >= _MS_DL_SIZE - 6) { \
                            _ms_dmaerror++; \
                        } else { \
                            _ms_dlpnt[Y++] = (gfx); \
                            _ms_dlpnt[Y++] = -width & 0x1f | (palette << 5); \
                            _ms_dlpnt[Y++] = (((gfx) >> 8) - 0x10) | _ms_tmp; \
                            _ms_dlpnt[Y++] = (x); \
                            _ms_dlend[X] = Y; \
                        } \
                    } \
                }\
            }\
        }

#define multisprite_display_sprite_fast(x, y, gfx, width, palette) \
        _ms_tmp = (y) & 0x0f; \
        X = _ms_shift4[Y = (y & 0xfe | _ms_buffer)]; \
        _ms_dldma[X] -= (8 + width * 3 + 1) / 2; \
        _ms_dlpnt = _ms_dls[X]; \
        Y = _ms_dlend[X]; \
        _ms_dlpnt[Y++] = (gfx); \
        _ms_dlpnt[Y++] = -width & 0x1f | (palette << 5); \
        _ms_dlpnt[Y++] = ((gfx) >> 8) | _ms_tmp; \
        _ms_dlpnt[Y++] = (x); \
        _ms_dlend[X] = Y; \
        if ((y) & 0x0f) { \
            X++; \
            _ms_dldma[X] -= (8 + width * 3 + 1) / 2; \
            _ms_dlpnt = _ms_dls[X];  \
            Y = _ms_dlend[X]; \
            _ms_dlpnt[Y++] = (gfx); \
            _ms_dlpnt[Y++] = -width & 0x1f | (palette << 5); \
            _ms_dlpnt[Y++] = (((gfx) >> 8) - 0x10) | _ms_tmp;  \
            _ms_dlpnt[Y++] = (x); \
            _ms_dlend[X] = Y; \
        }

#define multisprite_reserve_dma(y, nb_sprites, width) \
        _ms_tmp = (y) & 0x0f; \
        X = _ms_shift4[Y = (y & 0xfe | _ms_buffer)]; \
        _ms_dldma[X] -= nb_sprites * (8 + width * 3 + 1) / 2; \
        if ((y) & 0x0f) { \
            X++; \
            _ms_dldma[X] -= nb_sprites * (8 + width * 3 + 1) / 2; \
        }

#endif

#define multisprite_display_tiles(x, y, tiles, size, palette) \
    X = (y); \
    if (_ms_buffer) X += _MS_DLL_ARRAY_SIZE; \
    _ms_dldma[X] -= (10 + 3 + size * 9 + 1) / 2; \
    if (_ms_dldma[X] < 0) { \
        _ms_dmaerror++; \
        _ms_dldma[X] += (10 + 3 + size * 9 + 1) / 2; \
    } else { \
        _ms_dlpnt = _ms_dls[X]; \
        Y = _ms_dlend[X]; \
        if (Y >= _MS_DL_SIZE - 7) { \
            _ms_dmaerror++; \
         } else { \
            _ms_dlpnt[Y++] = (tiles); \
            _ms_dlpnt[Y++] = 0x60; \
            _ms_dlpnt[Y++] = (tiles) >> 8; \
            _ms_dlpnt[Y++] = -size & 0x1f | (palette << 5); \
            _ms_dlpnt[Y++] = (x); \
            _ms_dlend[X] = Y; \
        } \
    }

#define multisprite_display_tiles_fast(x, y, tiles, size, palette) \
    X = (y); \
    if (_ms_buffer) X += _MS_DLL_ARRAY_SIZE; \
    _ms_dldma[X] -= (10 + 3 + size * 9 + 1) / 2; \
    _ms_dlpnt = _ms_dls[X]; \
    Y = _ms_dlend[X]; \
    _ms_dlpnt[Y++] = (tiles); \
    _ms_dlpnt[Y++] = 0x60; \
    _ms_dlpnt[Y++] = (tiles) >> 8; \
    _ms_dlpnt[Y++] = -size & 0x1f | (palette << 5); \
    _ms_dlpnt[Y++] = (x); \
    _ms_dlend[X] = Y; 

#define multisprite_set_charbase(ptr) *CHARBASE = (ptr) >> 8;

// Macro to convert NTSC colors to PAL colors
#define multisprite_color(color) ((color >= 0xf0)?(0x10 + (color & 0x0f)):((color >= 0x10)?(color + (_ms_pal_detected & 0x10)):color))

#define multisprite_enable_dli(line) _ms_tmp = line; _multisprite_enable_dli()
#define multisprite_disable_dli(line) _ms_tmp = line; _multisprite_disable_dli()

void multisprite_get_tv()
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
}

void multisprite_init()
{
    *BACKGRND = 0x0;
    
    multisprite_get_tv();
    multisprite_clear();
    multisprite_save();

    _ms_dlpnt = _ms_b0_dll;
    for (X = 0, _ms_tmp = 0; _ms_tmp <= 1; _ms_tmp++) {
        // Build DLL
        // 69 blank lines for PAL
        // 19 blank lines for NTSC
        if (_ms_pal_detected) {
            // 16 blank lines
            _ms_dlpnt[Y = 0] = 0x4f;  // 16 lines
            _ms_dlpnt[++Y] = _ms_set_wm_dl >> 8;
            _ms_dlpnt[++Y] = _ms_set_wm_dl;
            // 16 blank lines
            _ms_dlpnt[++Y] = 0x4f;  // 16 lines
            _ms_dlpnt[++Y] = _ms_blank_dl >> 8;
            _ms_dlpnt[++Y] = _ms_blank_dl;
        } else {
            _ms_dlpnt[Y = 0] = 0x41; // 2 lines
            _ms_dlpnt[++Y] = _ms_set_wm_dl >> 8;
            _ms_dlpnt[++Y] = _ms_set_wm_dl;
        }
        // 16 pixel high regions
        for (_ms_tmp2 = 0; _ms_tmp2 != _MS_DLL_ARRAY_SIZE - 1; X++, _ms_tmp2++) {
            _ms_dlpnt[++Y] = 0x4f; // 16 lines
            _ms_dlpnt[++Y] = _ms_dls[X] >> 8; // High address
            _ms_dlpnt[++Y] = _ms_dls[X]; // Low address
        }
        // 1 pixel high region for the last display list (for vertical scrolling)
        _ms_dlpnt[++Y] = 0x40; // 1 line
        _ms_dlpnt[++Y] = _ms_blank_dl >> 8;
        _ms_dlpnt[++Y] = _ms_blank_dl;
        X++;
        if (_ms_pal_detected) {
            // 15 blank lines
            _ms_dlpnt[++Y] = 0x4f;  // 16 lines
            _ms_dlpnt[++Y] = _ms_blank_dl >> 8;
            _ms_dlpnt[++Y] = _ms_blank_dl;
            // 16 blank lines
            _ms_dlpnt[++Y] = 0x4e;  // 15 lines
            _ms_dlpnt[++Y] = _ms_blank_dl >> 8;
            _ms_dlpnt[++Y] = _ms_blank_dl;
            // 5 blank lines
            _ms_dlpnt[++Y] = 0x44;  // 5 lines
            _ms_dlpnt[++Y] = _ms_blank_dl >> 8;
            _ms_dlpnt[++Y] = _ms_blank_dl;
        } else {
            _ms_dlpnt[++Y] = 0x4f; // 16 lines
            _ms_dlpnt[++Y] = _ms_blank_dl >> 8;
            _ms_dlpnt[++Y] = _ms_blank_dl;
        }
        _ms_dlpnt = _ms_b1_dll;
    }

#ifdef VERTICAL_SCROLLING
    _ms_vscroll_offset = 0;
    _ms_delayed_vscroll = 0;
#ifdef BIDIR_VERTICAL_SCROLLING
    _ms_top_sbuffer_size = 0;
    _ms_top_sbuffer_dma = _MS_DMA_START_VALUE;
    _ms_bottom_sbuffer_size = 0;
    _ms_bottom_sbuffer_dma = _MS_DMA_START_VALUE;
    _ms_scroll_buffers_refill = 3;
#else
    _ms_sbuffer_size = 0;
    _ms_sbuffer_dma = _MS_DMA_START_VALUE;
#endif
    *P7C3 = 0; 
#endif
    
#ifdef HORIZONTAL_SCROLLING
    _ms_delayed_hscroll = 0;
#endif

    _ms_buffer = 0; // 0 is the current write buffer
    _ms_dmaerror = 0;
    *DPPH = _ms_b1_dll >> 8; // 1 the current displayed buffer
    *DPPL = _ms_b1_dll;
    *CTRL = 0x50; // DMA on, 160A/B mode, Two (2) byte characters mode
}

void multisprite_clear()
{
    // Reset DL ends for both buffers
    for (X = _MS_DLL_ARRAY_SIZE * 2 - 1; X >= 0; X--) {
        _ms_dlend[X] = 0;
        _ms_dldma[X] = _MS_DMA_START_VALUE;
    }
    for (X = _MS_DLL_ARRAY_SIZE - 1; X >= 0; X--) {
        _ms_dlend_save[X] = 0;
        _ms_dldma_save[X] = _MS_DMA_START_VALUE;
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
            _ms_dlend[Y] = _ms_dlend_save[X];
            _ms_dldma[Y] = _ms_dldma_save[X];
        }
    } else {
        for (X = _MS_DLL_ARRAY_SIZE - 1; X >= 0; X--) {
            _ms_dlend[X] = _ms_dlend_save[X];
            _ms_dldma[X] = _ms_dldma_save[X];
        }
    }
}

#ifdef VERTICAL_SCROLLING
#ifdef BIDIR_VERTICAL_SCROLLING
#define multisprite_top_vscroll_buffer_tiles(x, tiles, size, palette) \
    _ms_top_sbuffer_dma -= (10 + 3 + size * 9 + 1) / 2; \
    Y = _ms_top_sbuffer_size; \
    _ms_top_sbuffer[Y++] = (tiles); \
    _ms_top_sbuffer[Y++] = 0x60; \
    _ms_top_sbuffer[Y++] = (tiles) >> 8; \
    _ms_top_sbuffer[Y++] = -size & 0x1f | (palette << 5); \
    _ms_top_sbuffer[Y++] = (x); \
    _ms_top_sbuffer_size = Y;

#define multisprite_top_vscroll_buffer_sprite(x, gfx, width, palette) \
    _ms_top_sbuffer_dma -= (8 + width * 3 + 1) / 2; \
    Y = _ms_top_sbuffer_size; \
    _ms_top_sbuffer[Y++] = (gfx); \
    _ms_top_sbuffer[Y++] = -width & 0x1f | (palette << 5); \
    _ms_top_sbuffer[Y++] = ((gfx) >> 8); \
    _ms_top_sbuffer[Y++] = (x); \
    _ms_top_sbuffer_size = Y;

#define multisprite_bottom_vscroll_buffer_tiles(x, tiles, size, palette) \
    _ms_bottom_sbuffer_dma -= (10 + 3 + size * 9 + 1) / 2; \
    Y = _ms_bottom_sbuffer_size; \
    _ms_bottom_sbuffer[Y++] = (tiles); \
    _ms_bottom_sbuffer[Y++] = 0x60; \
    _ms_bottom_sbuffer[Y++] = (tiles) >> 8; \
    _ms_bottom_sbuffer[Y++] = -size & 0x1f | (palette << 5); \
    _ms_bottom_sbuffer[Y++] = (x); \
    _ms_bottom_sbuffer_size = Y;

#define multisprite_bottom_vscroll_buffer_sprite(x, gfx, width, palette) \
    _ms_bottom_sbuffer_dma -= (8 + width * 3 + 1) / 2; \
    Y = _ms_bottom_sbuffer_size; \
    _ms_bottom_sbuffer[Y++] = (gfx); \
    _ms_bottom_sbuffer[Y++] = -width & 0x1f | (palette << 5); \
    _ms_bottom_sbuffer[Y++] = ((gfx) >> 8); \
    _ms_bottom_sbuffer[Y++] = (x); \
    _ms_bottom_sbuffer_size = Y;

#define multisprite_vscroll_buffers_refill_status() (_ms_scroll_buffers_refill)
#define multisprite_vscroll_buffers_refilled() _ms_scroll_buffers_refill = 0

#else
#define multisprite_vscroll_buffer_tiles(x, tiles, size, palette) \
    _ms_sbuffer_dma -= (10 + 3 + size * 9 + 1) / 2; \
    Y = _ms_sbuffer_size; \
    _ms_sbuffer[Y++] = (tiles); \
    _ms_sbuffer[Y++] = 0x60; \
    _ms_sbuffer[Y++] = (tiles) >> 8; \
    _ms_sbuffer[Y++] = -size & 0x1f | (palette << 5); \
    _ms_sbuffer[Y++] = (x); \
    _ms_sbuffer_size = Y;

#define multisprite_vscroll_buffer_sprite(x, gfx, width, palette) \
    _ms_sbuffer_dma -= (8 + width * 3 + 1) / 2; \
    Y = _ms_sbuffer_size; \
    _ms_sbuffer[Y++] = (gfx); \
    _ms_sbuffer[Y++] = -width & 0x1f | (palette << 5); \
    _ms_sbuffer[Y++] = ((gfx) >> 8); \
    _ms_sbuffer[Y++] = (x); \
    _ms_sbuffer_size = Y;

#define multisprite_vscroll_buffer_empty() (!_ms_sbuffer_size)
#endif

void _ms_move_dlls_down()
{
    if (_ms_buffer) {
        for (X = _MS_DLL_ARRAY_SIZE * 2 - 1; X >= _MS_DLL_ARRAY_SIZE + 1 + _MS_TOP_SCROLLING_ZONE; X--) {
            _ms_dlpnt = _ms_dls[X];
            _ms_dlpnt2 = _ms_dls[--X];
            Y = _ms_dlend[X];
            _ms_dlend[++X] = Y;
            for (Y--; Y >= 0; Y--) { 
                _ms_dlpnt[Y] = _ms_dlpnt2[Y];
            }
        }
    } else {
        for (X = _MS_DLL_ARRAY_SIZE - 1; X >= 1 + _MS_TOP_SCROLLING_ZONE; X--) {
            _ms_dlpnt = _ms_dls[X];
            _ms_dlpnt2 = _ms_dls[--X];
            Y = _ms_dlend[X];
            _ms_dlend[++X] = Y;
            for (Y--; Y >= 0; Y--) { 
                _ms_dlpnt[Y] = _ms_dlpnt2[Y];
            }
        }
    }
    // Copy the scroll buffer to the first zone 
    _ms_dlpnt = _ms_dls[X];
#ifdef BIDIR_VERTICAL_SCROLLING
    Y = _ms_top_sbuffer_size;
#else
    Y = _ms_sbuffer_size;
#endif
    _ms_dlend[X] = Y;
    for (Y--; Y >= 0; Y--) { 
#ifdef BIDIR_VERTICAL_SCROLLING
        _ms_dlpnt[Y] = _ms_top_sbuffer[Y];
#else
        _ms_dlpnt[Y] = _ms_sbuffer[Y];
#endif
    }
}

void _ms_move_save_down()
{
    for (X = _MS_DLL_ARRAY_SIZE - 1; X >= 1 + _MS_TOP_SCROLLING_ZONE; X--) {
        Y = _ms_dldma_save[--X];
        _ms_dldma_save[++X] = Y;
        Y = _ms_dlend_save[--X];
        _ms_dlend_save[++X] = Y;
    }
#ifdef BIDIR_VERTICAL_SCROLLING
    _ms_dlend_save[X] = _ms_top_sbuffer_size;
    _ms_dldma_save[X] = _ms_top_sbuffer_dma;
    _ms_bottom_sbuffer_size = 0;
    _ms_bottom_sbuffer_dma = _MS_DMA_START_VALUE;
    _ms_top_sbuffer_size = 0;
    _ms_top_sbuffer_dma = _MS_DMA_START_VALUE;
    _ms_scroll_buffers_refill = MS_SCROLL_UP;
#else
    _ms_dlend_save[X] = _ms_sbuffer_size;
    _ms_dldma_save[X] = _ms_sbuffer_dma;
    _ms_sbuffer_size = 0;
    _ms_sbuffer_dma = _MS_DMA_START_VALUE;
#endif
}

void _ms_move_dlls_up()
{
    if (_ms_buffer) {
        for (X = _MS_DLL_ARRAY_SIZE + _MS_TOP_SCROLLING_ZONE; X < _MS_DLL_ARRAY_SIZE * 2 - 1; X++) {
            _ms_dlpnt = _ms_dls[X];
            _ms_dlpnt2 = _ms_dls[++X];
            Y = _ms_dlend[X];
            _ms_dlend[--X] = Y;
            for (Y--; Y >= 0; Y--) { 
                _ms_dlpnt[Y] = _ms_dlpnt2[Y];
            }
        }
    } else {
        for (X = _MS_TOP_SCROLLING_ZONE; X < _MS_DLL_ARRAY_SIZE - 1; X++) {
            _ms_dlpnt = _ms_dls[X];
            _ms_dlpnt2 = _ms_dls[++X];
            Y = _ms_dlend[X];
            _ms_dlend[--X] = Y;
            for (Y--; Y >= 0; Y--) { 
                _ms_dlpnt[Y] = _ms_dlpnt2[Y];
            }
        }
    }
    // Copy the scroll buffer to the first zone 
    _ms_dlpnt = _ms_dls[X];
#ifdef BIDIR_VERTICAL_SCROLLING
    Y = _ms_bottom_sbuffer_size;
#else
    Y = _ms_sbuffer_size;
#endif
    _ms_dlend[X] = Y;
    for (Y--; Y >= 0; Y--) { 
#ifdef BIDIR_VERTICAL_SCROLLING
        _ms_dlpnt[Y] = _ms_bottom_sbuffer[Y];
#else
        _ms_dlpnt[Y] = _ms_sbuffer[Y];
#endif
    }
}

void _ms_move_save_up()
{
    for (X = _MS_TOP_SCROLLING_ZONE ; X < _MS_DLL_ARRAY_SIZE - 1; X++) {
        Y = _ms_dldma_save[++X];
        _ms_dldma_save[--X] = Y;
        Y = _ms_dlend_save[++X];
        _ms_dlend_save[--X] = Y;
    }
#ifdef BIDIR_VERTICAL_SCROLLING
    _ms_dlend_save[X] = _ms_bottom_sbuffer_size;
    _ms_dldma_save[X] = _ms_bottom_sbuffer_dma;
    _ms_bottom_sbuffer_size = 0;
    _ms_bottom_sbuffer_dma = _MS_DMA_START_VALUE;
    _ms_top_sbuffer_size = 0;
    _ms_top_sbuffer_dma = _MS_DMA_START_VALUE;
    _ms_scroll_buffers_refill = MS_SCROLL_DOWN;
#else
    _ms_dlend_save[X] = _ms_sbuffer_size;
    _ms_dldma_save[X] = _ms_sbuffer_dma;
    _ms_sbuffer_size = 0;
    _ms_sbuffer_dma = _MS_DMA_START_VALUE;
#endif
}
#endif

void _ms_vertical_scrolling_adjust_bottom_of_screen();
void _ms_horizontal_scrolling_visible();

// This one should obvisouly executed during VBLANK, since it modifies the DPPL/H pointers
void multisprite_flip()
{
#ifdef VERTICAL_SCROLLING
    // Insert vertical scrolling shadowing lines
    if (_ms_vscroll_offset) {
        if (_ms_buffer) {
            X = _MS_DLL_ARRAY_SIZE - 1 + _MS_DLL_ARRAY_SIZE;
            _ms_dlpnt = _ms_b1_dl14;
        } else {
            X = _MS_DLL_ARRAY_SIZE - 1;
            _ms_dlpnt = _ms_b0_dl14;
        }
        Y = _ms_dlend[X]; 
        _ms_dlpnt[Y++] = _ms_hide_bottom; 
        _ms_dlpnt[Y++] = -20 & 0x1f | (7 << 5);
        _ms_dlpnt[Y++] = (_ms_hide_bottom >> 8) | _ms_vscroll_offset;
        _ms_dlpnt[Y++] = 0; 
        _ms_dlpnt[Y++] = _ms_hide_bottom; 
        _ms_dlpnt[Y++] = -20 & 0x1f | (7 << 5);
        _ms_dlpnt[Y++] = (_ms_hide_bottom >> 8) | _ms_vscroll_offset;
        _ms_dlpnt[Y++] = 80; 
        _ms_dlend[X] = Y;
    }
#endif
    if (_ms_buffer) {
        // Add DL end entry on each DL
        for (X = _MS_DLL_ARRAY_SIZE * 2 - 1; X >= _MS_DLL_ARRAY_SIZE; X--) {
            _ms_dlpnt = _ms_dls[X];
            Y = _ms_dlend[X];
            _ms_dlpnt[++Y] = 0; 
        }
        _ms_buffer = 0; // 0 is the current write buffer
#ifdef DEBUG
        *BACKGRND = 0x0;
#endif
        while (!(*MSTAT & 0x80)); // Wait for VBLANK
        *DPPH = _ms_b1_dll >> 8; // 1 the current displayed buffer
        *DPPL = _ms_b1_dll;
#ifdef DEBUG
        *BACKGRND = 0x0f;
#endif
#ifdef HORIZONTAL_SCROLLING
        if (_ms_delayed_hscroll) {
            _ms_horizontal_scrolling_visible();
            _ms_delayed_hscroll = 0;
        }
#endif
#ifdef VERTICAL_SCROLLING
        if (_ms_delayed_vscroll) {
            if (_ms_delayed_vscroll == 1) {
                _ms_move_dlls_down();
                _ms_move_save_down();
            } else if (_ms_delayed_vscroll == 2) {
                _ms_move_dlls_up();
                _ms_move_save_up();
            }
            _ms_vertical_scrolling_adjust_bottom_of_screen();
            _ms_delayed_vscroll = 0;
        }
#endif
        // Restore saved state 
        for (X = _MS_DLL_ARRAY_SIZE - 1; X >= 0; X--) {
            _ms_dlend[X] = _ms_dlend_save[X];
            _ms_dldma[X] = _ms_dldma_save[X];
        }
#ifdef VERTICAL_SCROLLING
        // Consider the DMA penalty for the vertical scrolling shadowing lines
        _ms_dldma[X = _MS_DLL_ARRAY_SIZE - 1] -= (8 + 20 * 3 + 1) / 2;
#endif
    } else {
        // Add DL end entry on each DL
        for (X = _MS_DLL_ARRAY_SIZE - 1; X >= 0; X--) {
            _ms_dlpnt = _ms_dls[X];
            Y = _ms_dlend[X];
            _ms_dlpnt[++Y] = 0; 
        }
        _ms_buffer = 1; // 1 is the current write buffer
#ifdef DEBUG
        *BACKGRND = 0x0;
#endif
        while (!(*MSTAT & 0x80)); // Wait for VBLANK
        *DPPH = _ms_b0_dll >> 8; // 0 the current displayed buffer
        *DPPL = _ms_b0_dll;
#ifdef DEBUG
        *BACKGRND = 0x0f;
#endif
#ifdef HORIZONTAL_SCROLLING
        if (_ms_delayed_hscroll) {
            _ms_horizontal_scrolling_visible();
            _ms_delayed_hscroll = 0;
        }
#endif
#ifdef VERTICAL_SCROLLING
        if (_ms_delayed_vscroll) {
            if (_ms_delayed_vscroll == 1) {
                _ms_move_dlls_down();
                _ms_move_save_down();
            } else if (_ms_delayed_vscroll == 2) {
                _ms_move_dlls_up();
                _ms_move_save_up();
            }
            _ms_vertical_scrolling_adjust_bottom_of_screen();
            _ms_delayed_vscroll = 0;
        }
#endif
        // Restore saved state 
        for (Y = _MS_DLL_ARRAY_SIZE * 2 - 1, X = _MS_DLL_ARRAY_SIZE - 1; X >= 0; Y--, X--) {
            _ms_dlend[Y] = _ms_dlend_save[X];
            _ms_dldma[Y] = _ms_dldma_save[X];
        }
#ifdef VERTICAL_SCROLLING
        // Consider the DMA penalty for the vertical scrolling shadowing lines
        _ms_dldma[X = _MS_DLL_ARRAY_SIZE * 2 - 1] -= (8 + 20 * 3 + 1) / 2;
#endif
    }
}

#ifdef VERTICAL_SCROLLING

// Vertical scrolling
#define multisprite_vertical_scrolling(x) _ms_tmp = (x); _ms_vertical_scrolling() 

void _ms_vertical_scrolling_adjust_bottom_of_screen()
{
    if (_ms_buffer) {
        _ms_dlpnt = _ms_b1_dll;
    } else {
        _ms_dlpnt = _ms_b0_dll;
    }
    if (_ms_pal_detected) { Y = 6 + 3 * _MS_TOP_SCROLLING_ZONE; } else { Y = 3 + 3 * _MS_TOP_SCROLLING_ZONE; }
    _ms_dlpnt[Y] = (15 - _ms_vscroll_offset) | 0x40;
    Y +=  3 * (_MS_DLL_ARRAY_SIZE - 1 - _MS_TOP_SCROLLING_ZONE);
    if (_ms_vscroll_offset) {
        _ms_dlpnt[Y] = 0x4f; // 16 lines
        if (_ms_buffer) {
            _ms_dlpnt[++Y] = _ms_b1_dl14 >> 8;
            _ms_dlpnt[++Y] = _ms_b1_dl14;
        } else {
            _ms_dlpnt[++Y] = _ms_b0_dl14 >> 8;
            _ms_dlpnt[++Y] = _ms_b0_dl14;
        }
        _ms_dlpnt[++Y] = (_ms_vscroll_offset - 1) | 0x40;  // _ms_vscroll_offset lines
    } else {
        _ms_dlpnt[Y] = 0x40; // 1 line
        _ms_dlpnt[++Y] = _ms_blank_dl >> 8;
        _ms_dlpnt[++Y] = _ms_blank_dl;
        _ms_dlpnt[++Y] = 0x4f;  // 16 lines
    }
}

void _ms_vertical_scrolling()
{
    _ms_vscroll_offset -= _ms_tmp;
    if (_ms_vscroll_offset < 0) {
        _ms_move_dlls_down();
        _ms_vscroll_offset += 16;
        _ms_delayed_vscroll = 1;
    } else if (_ms_vscroll_offset >= 16) {
        _ms_move_dlls_up();
        _ms_vscroll_offset -= 16;
        _ms_delayed_vscroll = 2;
    } else {
        _ms_delayed_vscroll = 3;
    }
    _ms_vertical_scrolling_adjust_bottom_of_screen();
}
#endif

#ifdef HORIZONTAL_SCROLLING
// Horizontal scrolling
#define multisprite_horizontal_tiles_scrolling(offset, y, value) \
    _ms_hscroll = (value); \
    X = (y); \
    if (_ms_buffer) X += _MS_DLL_ARRAY_SIZE; \
    _ms_dlpnt = _ms_dls[X]; \
    Y = (offset) + 3; \
    _ms_horizontal_tiles_scrolling()

void _ms_horizontal_tiles_scrolling()
{
    _ms_tmp = _ms_dlpnt[++Y]; // X position
    _ms_tmp -= _ms_hscroll;
    _ms_dlpnt[Y] = _ms_tmp;
    if (_ms_hscroll > 0) {
        if (_ms_tmp < -8) {
            // We have reached the left border of the screen
            // Advance the pointer
            _ms_dlpnt[Y] = _ms_tmp + 8;
#ifdef TILES_CHECK_BOUNDARIES
            Y -= 4;
            _ms_dlpnt2 = _ms_dlpnt[Y];
            Y++; Y++;
            _ms_dlpnt2 |= (_ms_dlpnt[Y] << 8);
            Y++;
            // Get the width of this tileset
            _ms_tmp = Y;
            Y = -(_ms_dlpnt[Y] | 0xe0);
            if (_ms_dlpnt2[Y] == 0xff) { // This is a boundary
                // Reduce the width of this string
                X = --Y;
                Y = _ms_tmp;
                X = (-X) & 0x1f;
                _ms_dlpnt[Y] = _ms_dlpnt[Y] & 0xe0 | X; 
            }
            Y = _ms_tmp;
            _ms_dlpnt2++;
            _ms_dlpnt[--Y] = _ms_dlpnt2 >> 8;
            Y--; Y--;
            _ms_dlpnt[Y] = _ms_dlpnt2;
#else 
            Y -= 4;
            _ms_dlpnt[Y]++;
            if (_ms_dlpnt[Y] == 0) {
                // Crossing page boundary
                Y++; Y++;
                _ms_dlpnt[Y]++;
            }
#endif
        } else {
            _ms_dlpnt[Y] = _ms_tmp;
        }
    } else {
        if (_ms_tmp >= 0) {
            _ms_dlpnt[Y] = _ms_tmp - 8;
            Y -= 4;
            _ms_dlpnt[Y]--;
            if (_ms_dlpnt[Y] == 0xff) {
                // Crossing page boundary
                Y++; Y++;
                _ms_dlpnt[Y]--;
            }
        } else {
            _ms_dlpnt[Y] = _ms_tmp;
        }
    } 
}

#define multisprite_horizontal_scrolling(x) _ms_delayed_hscroll = (x); _ms_horizontal_scrolling() 

void _ms_horizontal_scrolling_visible()
{
    for (_ms_tmp2 = _MS_TOP_SCROLLING_ZONE; _ms_tmp2 != _MS_DLL_ARRAY_SIZE; _ms_tmp2++) {
        multisprite_horizontal_tiles_scrolling(0, _ms_tmp2, _ms_delayed_hscroll);
    }
}

void _ms_horizontal_scrolling()
{
    for (_ms_tmp2 = _MS_TOP_SCROLLING_ZONE; _ms_tmp2 != _MS_DLL_ARRAY_SIZE; _ms_tmp2++) {
        multisprite_horizontal_tiles_scrolling(0, _ms_tmp2, _ms_delayed_hscroll);
    }
#ifdef BIDIR_VERTICAL_SCROLLING
    // Scroll also the preloaded scrolling bands
    _ms_dlpnt = _ms_top_sbuffer;
    Y = 3; 
    _ms_horizontal_tiles_scrolling();
    _ms_dlpnt = _ms_bottom_sbuffer;
    Y = 3; 
    _ms_horizontal_tiles_scrolling();
#endif
}

#endif

// _ms_tmp : display to list to apply DLI flag
void _multisprite_enable_dli()
{
    _ms_tmp = (_ms_tmp << 2) - _ms_tmp + 3; // _ms_tmp = _ms_tmp * 3 + 3
    if (_ms_pal_detected) _ms_tmp += 3;
    _ms_b0_dll[X = _ms_tmp] |= 0x80;
    _ms_b1_dll[X] |= 0x80;
}

// _ms_tmp : display to list to apply DLI flag
void _multisprite_disable_dli()
{
    _ms_tmp = (_ms_tmp << 2) - _ms_tmp + 3; // _ms_tmp = _ms_tmp * 3 + 3
    if (_ms_pal_detected) _ms_tmp += 3;
    _ms_b0_dll[X = _ms_tmp] &= 0x7f;
    _ms_b1_dll[X] &= 0x7f;
}

#endif // __ATARI7800_MULTISPRITE__
 
