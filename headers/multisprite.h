/*
    multisprite.h : multisprite display for the Atari 7800
    Copyleft 2023 Bruno STEUX 

    This file is distributed as a companion file to cc7800 - a subset of C compiler for the Atari 7800
    
    v0.1: First working version
    v0.2: Added DMA Masking vertical scrolling support
    v0.3: Refactored scrolling to avoid memory copy from region to region when coarse scrolling 
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
#define _MS_DMA_START_VALUE (402 / 2)

// Zeropage variables
char _ms_dmaerror;
#define _ms_tmpptr _libc_tmpptr
#define _ms_tmpptr2 _libc_tmpptr2
#define _ms_tmp _libc_tmp
#define _ms_tmp2 _libc_tmp2
signed char _ms_tmp3;
char _ms_tmp4;

#ifdef BIDIR_VERTICAL_SCROLLING
#ifndef VERTICAL_SCROLLING
#define VERTICAL_SCROLLING
#endif
#endif

#ifdef VERTICAL_SCROLLING
signed char _ms_vscroll_fine_offset;
ramchip char _ms_vscroll_coarse_offset;
char _ms_vscroll_coarse_offset_shifted;
ramchip char _ms_delayed_vscroll;
ramchip char _ms_delayed_vscroll_remove;
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

#ifndef _MS_TOP_DISPLAY
#ifdef _MS_TOP_SCROLLING_ZONE
#define _MS_TOP_DISPLAY _MS_TOP_SCROLLING_ZONE
#else
#define _MS_TOP_DISPLAY 0
#endif
#endif

ramchip char _ms_b0_dl0[_MS_DL_MALLOC(0)], _ms_b0_dl1[_MS_DL_MALLOC(1)], _ms_b0_dl2[_MS_DL_MALLOC(2)], _ms_b0_dl3[_MS_DL_MALLOC(3)], _ms_b0_dl4[_MS_DL_MALLOC(4)], _ms_b0_dl5[_MS_DL_MALLOC(5)], _ms_b0_dl6[_MS_DL_MALLOC(6)], _ms_b0_dl7[_MS_DL_MALLOC(7)], _ms_b0_dl8[_MS_DL_MALLOC(8)], _ms_b0_dl9[_MS_DL_MALLOC(9)], _ms_b0_dl10[_MS_DL_MALLOC(10)], _ms_b0_dl11[_MS_DL_MALLOC(11)], _ms_b0_dl12[_MS_DL_MALLOC(12)], _ms_b0_dl13[_MS_DL_MALLOC(13)], _ms_b0_dl14[_MS_DL_MALLOC(14)];
ramchip char _ms_b1_dl0[_MS_DL_MALLOC(0)], _ms_b1_dl1[_MS_DL_MALLOC(1)], _ms_b1_dl2[_MS_DL_MALLOC(2)], _ms_b1_dl3[_MS_DL_MALLOC(3)], _ms_b1_dl4[_MS_DL_MALLOC(4)], _ms_b1_dl5[_MS_DL_MALLOC(5)], _ms_b1_dl6[_MS_DL_MALLOC(6)], _ms_b1_dl7[_MS_DL_MALLOC(7)], _ms_b1_dl8[_MS_DL_MALLOC(8)], _ms_b1_dl9[_MS_DL_MALLOC(9)], _ms_b1_dl10[_MS_DL_MALLOC(10)], _ms_b1_dl11[_MS_DL_MALLOC(11)], _ms_b1_dl12[_MS_DL_MALLOC(12)], _ms_b1_dl13[_MS_DL_MALLOC(13)], _ms_b1_dl14[_MS_DL_MALLOC(14)];

#ifdef VERTICAL_SCROLLING
#if _MS_TOP_SCROLLING_ZONE == 0
aligned(256) const char _ms_shift3[] = {
    0, _MS_DLL_ARRAY_SIZE + 0, 0, _MS_DLL_ARRAY_SIZE + 0, 0, _MS_DLL_ARRAY_SIZE + 0, 0, _MS_DLL_ARRAY_SIZE + 0,
    1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1,
    2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2,
    3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3,
    4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4,
    5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5,
    6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6,
    7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7,
    8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8,
    9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9,
    10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10,
    11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11,
    12, _MS_DLL_ARRAY_SIZE + 12, 12, _MS_DLL_ARRAY_SIZE + 12, 12, _MS_DLL_ARRAY_SIZE + 12, 12, _MS_DLL_ARRAY_SIZE + 12,
    13, _MS_DLL_ARRAY_SIZE + 13, 13, _MS_DLL_ARRAY_SIZE + 13, 13, _MS_DLL_ARRAY_SIZE + 13, 13, _MS_DLL_ARRAY_SIZE + 13,
    14, _MS_DLL_ARRAY_SIZE + 14, 14, _MS_DLL_ARRAY_SIZE + 14, 14, _MS_DLL_ARRAY_SIZE + 14, 14, _MS_DLL_ARRAY_SIZE + 14,
    0, _MS_DLL_ARRAY_SIZE + 0, 0, _MS_DLL_ARRAY_SIZE + 0, 0, _MS_DLL_ARRAY_SIZE + 0, 0, _MS_DLL_ARRAY_SIZE + 0,
    1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1,
    2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2,
    3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3,
    4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4,
    5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5,
    6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6,
    7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7,
    8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8,
    9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9,
    10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10,
    11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11,
    12, _MS_DLL_ARRAY_SIZE + 12, 12, _MS_DLL_ARRAY_SIZE + 12, 12, _MS_DLL_ARRAY_SIZE + 12, 12, _MS_DLL_ARRAY_SIZE + 12,
    13, _MS_DLL_ARRAY_SIZE + 13, 13, _MS_DLL_ARRAY_SIZE + 13, 13, _MS_DLL_ARRAY_SIZE + 13, 13, _MS_DLL_ARRAY_SIZE + 13,
    14, _MS_DLL_ARRAY_SIZE + 14, 14, _MS_DLL_ARRAY_SIZE + 14, 14, _MS_DLL_ARRAY_SIZE + 14, 14, _MS_DLL_ARRAY_SIZE + 14,
    0, _MS_DLL_ARRAY_SIZE + 0, 0, _MS_DLL_ARRAY_SIZE + 0, 0, _MS_DLL_ARRAY_SIZE + 0, 0, _MS_DLL_ARRAY_SIZE + 0
};
#else
#if _MS_TOP_SCROLLING_ZONE == 1
aligned(256) const char _ms_shift3[] = {
    1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1,
    2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2,
    3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3,
    4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4,
    5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5,
    6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6,
    7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7,
    8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8,
    9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9,
    10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10,
    11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11,
    12, _MS_DLL_ARRAY_SIZE + 12, 12, _MS_DLL_ARRAY_SIZE + 12, 12, _MS_DLL_ARRAY_SIZE + 12, 12, _MS_DLL_ARRAY_SIZE + 12,
    13, _MS_DLL_ARRAY_SIZE + 13, 13, _MS_DLL_ARRAY_SIZE + 13, 13, _MS_DLL_ARRAY_SIZE + 13, 13, _MS_DLL_ARRAY_SIZE + 13,
    14, _MS_DLL_ARRAY_SIZE + 14, 14, _MS_DLL_ARRAY_SIZE + 14, 14, _MS_DLL_ARRAY_SIZE + 14, 14, _MS_DLL_ARRAY_SIZE + 14,
    1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1,
    2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2,
    3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3,
    4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4,
    5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5,
    6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6,
    7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7,
    8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8,
    9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9,
    10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10,
    11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11,
    12, _MS_DLL_ARRAY_SIZE + 12, 12, _MS_DLL_ARRAY_SIZE + 12, 12, _MS_DLL_ARRAY_SIZE + 12, 12, _MS_DLL_ARRAY_SIZE + 12,
    13, _MS_DLL_ARRAY_SIZE + 13, 13, _MS_DLL_ARRAY_SIZE + 13, 13, _MS_DLL_ARRAY_SIZE + 13, 13, _MS_DLL_ARRAY_SIZE + 13,
    14, _MS_DLL_ARRAY_SIZE + 14, 14, _MS_DLL_ARRAY_SIZE + 14, 14, _MS_DLL_ARRAY_SIZE + 14, 14, _MS_DLL_ARRAY_SIZE + 14,
    1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1, 1, _MS_DLL_ARRAY_SIZE + 1
};
#else
#if _MS_TOP_SCROLLING_ZONE == 2
aligned(256) const char _ms_shift3[] = {
    2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2,
    3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3,
    4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4,
    5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5,
    6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6,
    7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7,
    8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8,
    9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9,
    10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10,
    11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11,
    12, _MS_DLL_ARRAY_SIZE + 12, 12, _MS_DLL_ARRAY_SIZE + 12, 12, _MS_DLL_ARRAY_SIZE + 12, 12, _MS_DLL_ARRAY_SIZE + 12,
    13, _MS_DLL_ARRAY_SIZE + 13, 13, _MS_DLL_ARRAY_SIZE + 13, 13, _MS_DLL_ARRAY_SIZE + 13, 13, _MS_DLL_ARRAY_SIZE + 13,
    14, _MS_DLL_ARRAY_SIZE + 14, 14, _MS_DLL_ARRAY_SIZE + 14, 14, _MS_DLL_ARRAY_SIZE + 14, 14, _MS_DLL_ARRAY_SIZE + 14,
    2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2,
    3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3, 3, _MS_DLL_ARRAY_SIZE + 3,
    4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4, 4, _MS_DLL_ARRAY_SIZE + 4,
    5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5, 5, _MS_DLL_ARRAY_SIZE + 5,
    6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6, 6, _MS_DLL_ARRAY_SIZE + 6,
    7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7, 7, _MS_DLL_ARRAY_SIZE + 7,
    8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8, 8, _MS_DLL_ARRAY_SIZE + 8,
    9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9, 9, _MS_DLL_ARRAY_SIZE + 9,
    10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10, 10, _MS_DLL_ARRAY_SIZE + 10,
    11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11, 11, _MS_DLL_ARRAY_SIZE + 11,
    12, _MS_DLL_ARRAY_SIZE + 12, 12, _MS_DLL_ARRAY_SIZE + 12, 12, _MS_DLL_ARRAY_SIZE + 12, 12, _MS_DLL_ARRAY_SIZE + 12,
    13, _MS_DLL_ARRAY_SIZE + 13, 13, _MS_DLL_ARRAY_SIZE + 13, 13, _MS_DLL_ARRAY_SIZE + 13, 13, _MS_DLL_ARRAY_SIZE + 13,
    14, _MS_DLL_ARRAY_SIZE + 14, 14, _MS_DLL_ARRAY_SIZE + 14, 14, _MS_DLL_ARRAY_SIZE + 14, 14, _MS_DLL_ARRAY_SIZE + 14,
    2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2, 2, _MS_DLL_ARRAY_SIZE + 2
};
#endif
#endif
#endif
#else
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
#endif
const char *_ms_dls[_MS_DLL_ARRAY_SIZE * 2] = {
    _ms_b0_dl0, _ms_b0_dl1, _ms_b0_dl2, _ms_b0_dl3, _ms_b0_dl4, _ms_b0_dl5, _ms_b0_dl6, _ms_b0_dl7, _ms_b0_dl8, _ms_b0_dl9, _ms_b0_dl10, _ms_b0_dl11, _ms_b0_dl12, _ms_b0_dl13, _ms_b0_dl14,
    _ms_b1_dl0, _ms_b1_dl1, _ms_b1_dl2, _ms_b1_dl3, _ms_b1_dl4, _ms_b1_dl5, _ms_b1_dl6, _ms_b1_dl7, _ms_b1_dl8, _ms_b1_dl9, _ms_b1_dl10, _ms_b1_dl11, _ms_b1_dl12, _ms_b1_dl13, _ms_b1_dl14
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
ramchip char _ms_pal_frame_skip_counter;

void multisprite_init();
void multisprite_clear();
void multisprite_save();
void multisprite_restore();
void multisprite_flip();

#ifdef VERTICAL_SCROLLING
#define multisprite_display_sprite(x, y, gfx, width, palette) \
        _ms_tmp2 = (y) + _ms_vscroll_fine_offset; \
	_ms_tmp = _ms_tmp2 & 0x0f; \
        _ms_tmp3 = (((_ms_tmp2 >> 1) + _ms_vscroll_coarse_offset_shifted) & 0xfe | _ms_buffer); \
	X = _ms_shift3[Y = _ms_tmp3]; \
        _ms_dldma[X] -= (8 + width * 3 + 1) / 2; \
        if (_ms_dldma[X] < 0) { \
            _ms_dmaerror++; \
            _ms_dldma[X] += (8 + width * 3 + 1) / 2; \
        } else { \
            _ms_tmpptr = _ms_dls[X]; \
            Y = _ms_dlend[X]; \
            if (Y >= _MS_DL_SIZE - 6) { \
                _ms_dmaerror++; \
            } else { \
                _ms_tmpptr[Y++] = (gfx); \
                _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                _ms_tmpptr[Y++] = ((gfx) >> 8) | _ms_tmp; \
                _ms_tmpptr[Y++] = (x); \
                _ms_dlend[X] = Y; \
                if (_ms_tmp2 & 0x0f) { \
	            X = _ms_shift3[Y = _ms_tmp3 + 8]; \
                    _ms_dldma[X] -= (8 + width * 3 + 1) / 2; \
                    if (_ms_dldma[X] < 0) { \
                        _ms_dmaerror++; \
                        _ms_dldma[X] += (8 + width * 3 + 1) / 2; \
                    } else { \
                        _ms_tmpptr = _ms_dls[X];  \
                        Y = _ms_dlend[X]; \
                        if (Y >= _MS_DL_SIZE - 6) { \
                            _ms_dmaerror++; \
                        } else { \
                            _ms_tmpptr[Y++] = (gfx); \
                            _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                            _ms_tmpptr[Y++] = (((gfx) >> 8) - 0x10) | _ms_tmp; \
                            _ms_tmpptr[Y++] = (x); \
                            _ms_dlend[X] = Y; \
                        } \
                    } \
                }\
            }\
        }

#define multisprite_display_small_sprite(x, y, gfx, width, palette) \
        _ms_tmp2 = (y) + _ms_vscroll_fine_offset; \
	_ms_tmp = _ms_tmp2 & 0x0f; \
        _ms_tmp3 = (((_ms_tmp2 >> 1) + _ms_vscroll_coarse_offset_shifted) & 0xfe | _ms_buffer); \
	X = _ms_shift3[Y = _ms_tmp3]; \
        _ms_dldma[X] -= (8 + width * 3 + 1) / 2; \
        if (_ms_dldma[X] < 0) { \
            _ms_dmaerror++; \
            _ms_dldma[X] += (8 + width * 3 + 1) / 2; \
        } else { \
            _ms_tmpptr = _ms_dls[X]; \
            Y = _ms_dlend[X]; \
            if (Y >= _MS_DL_SIZE - 6) { \
                _ms_dmaerror++; \
            } else { \
                _ms_tmpptr[Y++] = (gfx); \
                _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                _ms_tmpptr[Y++] = ((gfx) >> 8) | _ms_tmp; \
                _ms_tmpptr[Y++] = (x); \
                _ms_dlend[X] = Y; \
                if (_ms_tmp >= 8) { \
                    X = _ms_shift3[Y = _ms_tmp3 + 8]; \
                    _ms_dldma[X] -= (8 + width * 3 + 1) / 2; \
                    if (_ms_dldma[X] < 0) { \
                        _ms_dmaerror++; \
                        _ms_dldma[X] += (8 + width * 3 + 1) / 2; \
                    } else { \
                        _ms_tmpptr = _ms_dls[X];  \
                        Y = _ms_dlend[X]; \
                        if (Y >= _MS_DL_SIZE - 6) { \
                            _ms_dmaerror++; \
                        } else { \
                            _ms_tmpptr[Y++] = (gfx); \
                            _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                            _ms_tmpptr[Y++] = ((gfx) >> 8) - 0x10 + _ms_tmp; \
                            _ms_tmpptr[Y++] = (x); \
                            _ms_dlend[X] = Y; \
                        } \
                    } \
                }\
            }\
        }

#define multisprite_display_small_sprite_ex(x, y, gfx, width, palette, mode) \
        _ms_tmp2 = (y) + _ms_vscroll_fine_offset; \
	_ms_tmp = _ms_tmp2 & 0x0f; \
        _ms_tmp3 = (((_ms_tmp2 >> 1) + _ms_vscroll_coarse_offset_shifted) & 0xfe | _ms_buffer); \
	X = _ms_shift3[Y = _ms_tmp3]; \
        _ms_dldma[X] -= (10 + width * 3 + 1) / 2; \
        if (_ms_dldma[X] < 0) { \
            _ms_dmaerror++; \
            _ms_dldma[X] += (10 + width * 3 + 1) / 2; \
        } else { \
            _ms_tmpptr = _ms_dls[X]; \
            Y = _ms_dlend[X]; \
            if (Y >= _MS_DL_SIZE - 7) { \
                _ms_dmaerror++; \
            } else { \
                _ms_tmpptr[Y++] = (gfx); \
                _ms_tmpptr[Y++] = (mode)?0xc0:0x40; \
                _ms_tmpptr[Y++] = ((gfx) >> 8) | _ms_tmp; \
                _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                _ms_tmpptr[Y++] = (x); \
                _ms_dlend[X] = Y; \
                if (_ms_tmp >= 8) { \
                    X = _ms_shift3[Y = _ms_tmp3 + 8]; \
                    _ms_dldma[X] -= (10 + width * 3 + 1) / 2; \
                    if (_ms_dldma[X] < 0) { \
                        _ms_dmaerror++; \
                        _ms_dldma[X] += (10 + width * 3 + 1) / 2; \
                    } else { \
                        _ms_tmpptr = _ms_dls[X];  \
                        Y = _ms_dlend[X]; \
                        if (Y >= _MS_DL_SIZE - 7) { \
                            _ms_dmaerror++; \
                        } else { \
                            _ms_tmpptr[Y++] = (gfx); \
                            _ms_tmpptr[Y++] = (mode)?0xc0:0x40; \
                            _ms_tmpptr[Y++] = ((gfx) >> 8) - 0x10 + _ms_tmp; \
                            _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                            _ms_tmpptr[Y++] = (x); \
                            _ms_dlend[X] = Y; \
                        } \
                    } \
                }\
            }\
        }

#define multisprite_display_big_sprite(x, y, gfx, width, palette, height, mode) \
        _ms_tmp2 = (y) + _ms_vscroll_fine_offset; \
	_ms_tmp = _ms_tmp2 & 0x0f; \
        _ms_tmp3 = (((_ms_tmp2 >> 1) + _ms_vscroll_coarse_offset_shifted) & 0xfe | _ms_buffer); \
	X = _ms_shift3[Y = _ms_tmp3]; \
        _ms_dldma[X] -= (10 + width * 3 + 1) / 2; \
        if (_ms_dldma[X] < 0) { \
            _ms_dmaerror++; \
            _ms_dldma[X] += (10 + width * 3 + 1) / 2; \
        } else { \
            _ms_tmpptr = _ms_dls[X]; \
            Y = _ms_dlend[X]; \
            if (Y >= _MS_DL_SIZE - 7) { \
                _ms_dmaerror++; \
            } else { \
                _ms_tmpptr[Y++] = (gfx); \
                _ms_tmpptr[Y++] = (mode)?0xc0:0x40; \
                _ms_tmpptr[Y++] = ((gfx) >> 8) | _ms_tmp; \
                _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                _ms_tmpptr[Y++] = (x); \
                _ms_dlend[X] = Y; \
                if (_ms_tmp2 & 0x0f) { \
                    _ms_tmpptr2 = (gfx); \
                    _ms_tmp2 = ((_ms_tmpptr2 >> 8) - 0x10) | _ms_tmp; \
                    for (_ms_tmp4 = (height) - 1; _ms_tmp4 != 0; _ms_tmp4--) { \
                        _ms_tmp3 += 8; \
                        X = _ms_shift3[Y = _ms_tmp3]; \
                        _ms_dldma[X] -= (20 + 3 + width * 3 + 1) / 2; \
                        if (_ms_dldma[X] < 0) { \
                            _ms_dmaerror++; \
                            _ms_dldma[X] += (20 + 3 + width * 3 + 1) / 2; \
                        } else { \
                            _ms_tmpptr = _ms_dls[X];  \
                            Y = _ms_dlend[X]; \
                            if (Y >= _MS_DL_SIZE - 12) { \
                                _ms_dmaerror++; \
                            } else { \
                                _ms_tmpptr[Y++] = _ms_tmpptr2; \
                                _ms_tmpptr[Y++] = (mode)?0xc0:0x40; \
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
                            } \
                        } \
                    } \
                    X = _ms_shift3[Y = _ms_tmp3 + 8]; \
                    _ms_dldma[X] -= (10 + width * 3 + 1) / 2; \
                    if (_ms_dldma[X] < 0) { \
                        _ms_dmaerror++; \
                        _ms_dldma[X] += (10 + width * 3 + 1) / 2; \
                    } else { \
                        _ms_tmpptr = _ms_dls[X];  \
                        Y = _ms_dlend[X]; \
                        if (Y >= _MS_DL_SIZE - 7) { \
                            _ms_dmaerror++; \
                        } else { \
                            _ms_tmpptr[Y++] = _ms_tmpptr2; \
                            _ms_tmpptr[Y++] = (mode)?0xc0:0x40; \
                            _ms_tmpptr[Y++] = _ms_tmp2; \
                            _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                            _ms_tmpptr[Y++] = (x); \
                            _ms_dlend[X] = Y; \
                        } \
                    } \
                } else { \
                    _ms_tmpptr2 = (gfx); \
                    _ms_tmp2 = (_ms_tmpptr2 >> 8) | _ms_tmp; \
                    for (_ms_tmp4 = (height) - 1; _ms_tmp4 != 0; _ms_tmp4--) { \
                        _ms_tmp3 += 8; \
                        X = _ms_shift3[Y = _ms_tmp3]; \
                        _ms_tmpptr2 += width; \
                        _ms_dldma[X] -= (10 + width * 3 + 1) / 2; \
                        if (_ms_dldma[X] < 0) { \
                            _ms_dmaerror++; \
                            _ms_dldma[X] += (10 + width * 3 + 1) / 2; \
                        } else { \
                            _ms_tmpptr = _ms_dls[X];  \
                            Y = _ms_dlend[X]; \
                            if (Y >= _MS_DL_SIZE - 7) { \
                                _ms_dmaerror++; \
                            } else { \
                                _ms_tmpptr[Y++] = _ms_tmpptr2; \
                                _ms_tmpptr[Y++] = (mode)?0xc0:0x40; \
                                _ms_tmpptr[Y++] = _ms_tmp2; \
                                _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                                _ms_tmpptr[Y++] = (x); \
                                _ms_dlend[X] = Y; \
                            } \
                        } \
                    } \
                } \
            } \
        }

#define multisprite_display_sprite_ex(x, y, gfx, width, palette, mode) \
        _ms_tmp2 = (y) + _ms_vscroll_fine_offset; \
	_ms_tmp = _ms_tmp2 & 0x0f; \
        _ms_tmp3 = (((_ms_tmp2 >> 1) + _ms_vscroll_coarse_offset_shifted) & 0xfe | _ms_buffer); \
	X = _ms_shift3[Y = _ms_tmp3]; \
        _ms_dldma[X] -= (8 + width * 3 + 1) / 2; \
        if (_ms_dldma[X] < 0) { \
            _ms_dmaerror++; \
            _ms_dldma[X] += (8 + width * 3 + 1) / 2; \
        } else { \
            _ms_tmpptr = _ms_dls[X]; \
            Y = _ms_dlend[X]; \
            if (Y >= _MS_DL_SIZE - 7) { \
                _ms_dmaerror++; \
            } else { \
                _ms_tmpptr[Y++] = (gfx); \
                _ms_tmpptr[Y++] = (mode)?0xc0:0x40; \
                _ms_tmpptr[Y++] = ((gfx) >> 8) | _ms_tmp; \
                _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                _ms_tmpptr[Y++] = (x); \
                _ms_dlend[X] = Y; \
                if (_ms_tmp2 & 0x0f) { \
                    X = _ms_shift3[Y = _ms_tmp3 + 8]; \
                    _ms_dldma[X] -= (8 + width * 3 + 1) / 2; \
                    if (_ms_dldma[X] < 0) { \
                        _ms_dmaerror++; \
                        _ms_dldma[X] += (8 + width * 3 + 1) / 2; \
                    } else { \
                        _ms_tmpptr = _ms_dls[X];  \
                        Y = _ms_dlend[X]; \
                        if (Y >= _MS_DL_SIZE - 7) { \
                            _ms_dmaerror++; \
                        } else { \
                            _ms_tmpptr[Y++] = (gfx); \
                            _ms_tmpptr[Y++] = (mode)?0xc0:0x40; \
                            _ms_tmpptr[Y++] = (((gfx) >> 8) - 0x10) | _ms_tmp; \
                            _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                            _ms_tmpptr[Y++] = (x); \
                            _ms_dlend[X] = Y; \
                        } \
                    } \
                }\
            }\
        }

#define multisprite_display_sprite_fast(x, y, gfx, width, palette) \
        _ms_tmp2 = (y) + _ms_vscroll_fine_offset; \
        _ms_tmp = _ms_tmp2 & 0x0f; \
        _ms_tmp3 = (((_ms_tmp2 >> 1) + _ms_vscroll_coarse_offset_shifted) & 0xfe | _ms_buffer); \
	X = _ms_shift3[Y = _ms_tmp3]; \
        _ms_dldma[X] -= (8 + width * 3 + 1) / 2; \
        _ms_tmpptr = _ms_dls[X]; \
        Y = _ms_dlend[X]; \
        _ms_tmpptr[Y++] = (gfx); \
        _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
        _ms_tmpptr[Y++] = ((gfx) >> 8) | _ms_tmp; \
        _ms_tmpptr[Y++] = (x); \
        _ms_dlend[X] = Y; \
        if (_ms_tmp2 & 0x0f) { \
	    X = _ms_shift3[Y = _ms_tmp3 + 8]; \
            _ms_dldma[X] -= (8 + width * 3 + 1) / 2; \
            _ms_tmpptr = _ms_dls[X];  \
            Y = _ms_dlend[X]; \
            _ms_tmpptr[Y++] = (gfx); \
            _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
            _ms_tmpptr[Y++] = (((gfx) >> 8) - 0x10) | _ms_tmp; \
            _ms_tmpptr[Y++] = (x); \
            _ms_dlend[X] = Y; \
        }

#define multisprite_reserve_dma(y, nb_sprites, width) \
        _ms_tmp2 = (y) + _ms_vscroll_fine_offset; \
        _ms_tmp3 = (((_ms_tmp2 >> 1) + _ms_vscroll_coarse_offset_shifted) & 0xfe | _ms_buffer); \
	X = _ms_shift3[Y = _ms_tmp3]; \
        _ms_dldma[X] -= nb_sprites * (8 + width * 3 + 1) / 2; \
        if (_ms_tmp2 & 0x0f) { \
	    X = _ms_shift3[Y = _ms_tmp3 + 8]; \
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
            _ms_tmpptr = _ms_dls[X]; \
            Y = _ms_dlend[X]; \
            if (Y >= _MS_DL_SIZE - 6) { \
                _ms_dmaerror++; \
            } else { \
                _ms_tmpptr[Y++] = (gfx); \
                _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                _ms_tmpptr[Y++] = ((gfx) >> 8) | _ms_tmp; \
                _ms_tmpptr[Y++] = (x); \
                _ms_dlend[X] = Y; \
                if ((y) & 0x0f) { \
                    X++; \
                    _ms_dldma[X] -= (8 + width * 3 + 1) / 2; \
                    if (_ms_dldma[X] < 0) { \
                        _ms_dmaerror++; \
                        _ms_dldma[X] += (8 + width * 3 + 1) / 2; \
                    } else { \
                        _ms_tmpptr = _ms_dls[X];  \
                        Y = _ms_dlend[X]; \
                        if (Y >= _MS_DL_SIZE - 6) { \
                            _ms_dmaerror++; \
                        } else { \
                            _ms_tmpptr[Y++] = (gfx); \
                            _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                            _ms_tmpptr[Y++] = (((gfx) >> 8) - 0x10) | _ms_tmp; \
                            _ms_tmpptr[Y++] = (x); \
                            _ms_dlend[X] = Y; \
                        } \
                    } \
                }\
            }\
        }

#define multisprite_display_small_sprite(x, y, gfx, width, palette) \
	_ms_tmp = (y) & 0x0f; \
	X = _ms_shift4[Y = (y & 0xfe | _ms_buffer)]; \
        _ms_dldma[X] -= (8 + width * 3 + 1) / 2; \
        if (_ms_dldma[X] < 0) { \
            _ms_dmaerror++; \
            _ms_dldma[X] += (8 + width * 3 + 1) / 2; \
        } else { \
            _ms_tmpptr = _ms_dls[X]; \
            Y = _ms_dlend[X]; \
            if (Y >= _MS_DL_SIZE - 6) { \
                _ms_dmaerror++; \
            } else { \
                _ms_tmpptr[Y++] = (gfx); \
                _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                _ms_tmpptr[Y++] = ((gfx) >> 8) | _ms_tmp; \
                _ms_tmpptr[Y++] = (x); \
                _ms_dlend[X] = Y; \
                if (_ms_tmp >= 8) { \
                    X++; \
                    _ms_dldma[X] -= (8 + width * 3 + 1) / 2; \
                    if (_ms_dldma[X] < 0) { \
                        _ms_dmaerror++; \
                        _ms_dldma[X] += (8 + width * 3 + 1) / 2; \
                    } else { \
                        _ms_tmpptr = _ms_dls[X];  \
                        Y = _ms_dlend[X]; \
                        if (Y >= _MS_DL_SIZE - 6) { \
                            _ms_dmaerror++; \
                        } else { \
                            _ms_tmpptr[Y++] = (gfx); \
                            _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                            _ms_tmpptr[Y++] = ((gfx) >> 8) - 0x10 + _ms_tmp; \
                            _ms_tmpptr[Y++] = (x); \
                            _ms_dlend[X] = Y; \
                        } \
                    } \
                }\
            }\
        }

#define multisprite_display_small_sprite_ex(x, y, gfx, width, palette, mode) \
	_ms_tmp = (y) & 0x0f; \
	X = _ms_shift4[Y = (y & 0xfe | _ms_buffer)]; \
        _ms_dldma[X] -= (10 + width * 3 + 1) / 2; \
        if (_ms_dldma[X] < 0) { \
            _ms_dmaerror++; \
            _ms_dldma[X] += (10 + width * 3 + 1) / 2; \
        } else { \
            _ms_tmpptr = _ms_dls[X]; \
            Y = _ms_dlend[X]; \
            if (Y >= _MS_DL_SIZE - 7) { \
                _ms_dmaerror++; \
            } else { \
                _ms_tmpptr[Y++] = (gfx); \
                _ms_tmpptr[Y++] = (mode)?0xc0:0x40; \
                _ms_tmpptr[Y++] = ((gfx) >> 8) | _ms_tmp; \
                _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                _ms_tmpptr[Y++] = (x); \
                _ms_dlend[X] = Y; \
                if (_ms_tmp >= 8) { \
                    X++; \
                    _ms_dldma[X] -= (10 + width * 3 + 1) / 2; \
                    if (_ms_dldma[X] < 0) { \
                        _ms_dmaerror++; \
                        _ms_dldma[X] += (10 + width * 3 + 1) / 2; \
                    } else { \
                        _ms_tmpptr = _ms_dls[X];  \
                        Y = _ms_dlend[X]; \
                        if (Y >= _MS_DL_SIZE - 7) { \
                            _ms_dmaerror++; \
                        } else { \
                            _ms_tmpptr[Y++] = (gfx); \
                            _ms_tmpptr[Y++] = (mode)?0xc0:0x40; \
                            _ms_tmpptr[Y++] = ((gfx) >> 8) - 0x10 + _ms_tmp; \
                            _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                            _ms_tmpptr[Y++] = (x); \
                            _ms_dlend[X] = Y; \
                        } \
                    } \
                }\
            }\
        }

#define multisprite_display_big_sprite(x, y, gfx, width, palette, height, mode) \
	_ms_tmp = (y) & 0x0f; \
	X = _ms_shift4[Y = (y & 0xfe | _ms_buffer)]; \
        _ms_dldma[X] -= (10 + width * 3 + 1) / 2; \
        if (_ms_dldma[X] < 0) { \
            _ms_dmaerror++; \
            _ms_dldma[X] += (10 + width * 3 + 1) / 2; \
        } else { \
            _ms_tmpptr = _ms_dls[X]; \
            Y = _ms_dlend[X]; \
            if (Y >= _MS_DL_SIZE - 7) { \
                _ms_dmaerror++; \
            } else { \
                _ms_tmpptr[Y++] = (gfx); \
                _ms_tmpptr[Y++] = (mode)?0xc0:0x40; \
                _ms_tmpptr[Y++] = ((gfx) >> 8) | _ms_tmp; \
                _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                _ms_tmpptr[Y++] = (x); \
                _ms_dlend[X] = Y; \
                if ((y) & 0x0f) { \
                    _ms_tmpptr2 = (gfx); \
                    _ms_tmp2 = ((_ms_tmpptr2 >> 8) - 0x10) | _ms_tmp; \
                    for (_ms_tmp3 = (height) - 1; _ms_tmp3 != 0; _ms_tmp3--) { \
                        X++; \
                        _ms_dldma[X] -= (20 + 3 + width * 3 + 1) / 2; \
                        if (_ms_dldma[X] < 0) { \
                            _ms_dmaerror++; \
                            _ms_dldma[X] += (20 + 3 + width * 3 + 1) / 2; \
                        } else { \
                            _ms_tmpptr = _ms_dls[X];  \
                            Y = _ms_dlend[X]; \
                            if (Y >= _MS_DL_SIZE - 12) { \
                                _ms_dmaerror++; \
                            } else { \
                                _ms_tmpptr[Y++] = _ms_tmpptr2; \
                                _ms_tmpptr[Y++] = (mode)?0xc0:0x40; \
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
                            } \
                        } \
                    } \
                    X++; \
                    _ms_dldma[X] -= (10 + width * 3 + 1) / 2; \
                    if (_ms_dldma[X] < 0) { \
                        _ms_dmaerror++; \
                        _ms_dldma[X] += (10 + width * 3 + 1) / 2; \
                    } else { \
                        _ms_tmpptr = _ms_dls[X];  \
                        Y = _ms_dlend[X]; \
                        if (Y >= _MS_DL_SIZE - 7) { \
                            _ms_dmaerror++; \
                        } else { \
                            _ms_tmpptr[Y++] = _ms_tmpptr2; \
                            _ms_tmpptr[Y++] = (mode)?0xc0:0x40; \
                            _ms_tmpptr[Y++] = _ms_tmp2; \
                            _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                            _ms_tmpptr[Y++] = (x); \
                            _ms_dlend[X] = Y; \
                        } \
                    } \
                } else { \
                    _ms_tmpptr2 = (gfx); \
                    _ms_tmp2 = (_ms_tmpptr2 >> 8) | _ms_tmp; \
                    for (_ms_tmp3 = (height) - 1; _ms_tmp3 != 0; _ms_tmp3--) { \
                        X++; \
                        _ms_tmpptr2 += width; \
                        _ms_dldma[X] -= (10 + width * 3 + 1) / 2; \
                        if (_ms_dldma[X] < 0) { \
                            _ms_dmaerror++; \
                            _ms_dldma[X] += (10 + width * 3 + 1) / 2; \
                        } else { \
                            _ms_tmpptr = _ms_dls[X];  \
                            Y = _ms_dlend[X]; \
                            if (Y >= _MS_DL_SIZE - 7) { \
                                _ms_dmaerror++; \
                            } else { \
                                _ms_tmpptr[Y++] = _ms_tmpptr2; \
                                _ms_tmpptr[Y++] = (mode)?0xc0:0x40; \
                                _ms_tmpptr[Y++] = _ms_tmp2; \
                                _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                                _ms_tmpptr[Y++] = (x); \
                                _ms_dlend[X] = Y; \
                            } \
                        } \
                    } \
                } \
            } \
        }

#define multisprite_display_sprite_ex(x, y, gfx, width, palette, mode) \
	_ms_tmp = (y) & 0x0f; \
	X = _ms_shift4[Y = (y & 0xfe | _ms_buffer)]; \
        _ms_dldma[X] -= (8 + width * 3 + 1) / 2; \
        if (_ms_dldma[X] < 0) { \
            _ms_dmaerror++; \
            _ms_dldma[X] += (8 + width * 3 + 1) / 2; \
        } else { \
            _ms_tmpptr = _ms_dls[X]; \
            Y = _ms_dlend[X]; \
            if (Y >= _MS_DL_SIZE - 7) { \
                _ms_dmaerror++; \
            } else { \
                _ms_tmpptr[Y++] = (gfx); \
                _ms_tmpptr[Y++] = (mode)?0xc0:0x40; \
                _ms_tmpptr[Y++] = ((gfx) >> 8) | _ms_tmp; \
                _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                _ms_tmpptr[Y++] = (x); \
                _ms_dlend[X] = Y; \
                if ((y) & 0x0f) { \
                    X++; \
                    _ms_dldma[X] -= (8 + width * 3 + 1) / 2; \
                    if (_ms_dldma[X] < 0) { \
                        _ms_dmaerror++; \
                        _ms_dldma[X] += (8 + width * 3 + 1) / 2; \
                    } else { \
                        _ms_tmpptr = _ms_dls[X];  \
                        Y = _ms_dlend[X]; \
                        if (Y >= _MS_DL_SIZE - 7) { \
                            _ms_dmaerror++; \
                        } else { \
                            _ms_tmpptr[Y++] = (gfx); \
                            _ms_tmpptr[Y++] = (mode)?0xc0:0x40; \
                            _ms_tmpptr[Y++] = (((gfx) >> 8) - 0x10) | _ms_tmp; \
                            _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
                            _ms_tmpptr[Y++] = (x); \
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
        _ms_tmpptr = _ms_dls[X]; \
        Y = _ms_dlend[X]; \
        _ms_tmpptr[Y++] = (gfx); \
        _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
        _ms_tmpptr[Y++] = ((gfx) >> 8) | _ms_tmp; \
        _ms_tmpptr[Y++] = (x); \
        _ms_dlend[X] = Y; \
        if ((y) & 0x0f) { \
            X++; \
            _ms_dldma[X] -= (8 + width * 3 + 1) / 2; \
            _ms_tmpptr = _ms_dls[X];  \
            Y = _ms_dlend[X]; \
            _ms_tmpptr[Y++] = (gfx); \
            _ms_tmpptr[Y++] = -width & 0x1f | (palette << 5); \
            _ms_tmpptr[Y++] = (((gfx) >> 8) - 0x10) | _ms_tmp;  \
            _ms_tmpptr[Y++] = (x); \
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
        _ms_tmpptr = _ms_dls[X]; \
        Y = _ms_dlend[X]; \
        if (Y >= _MS_DL_SIZE - 7) { \
            _ms_dmaerror++; \
         } else { \
            _ms_tmpptr[Y++] = (tiles); \
            _ms_tmpptr[Y++] = 0x60; \
            _ms_tmpptr[Y++] = (tiles) >> 8; \
            _ms_tmpptr[Y++] = -size & 0x1f | (palette << 5); \
            _ms_tmpptr[Y++] = (x); \
            _ms_dlend[X] = Y; \
        } \
    }

#define multisprite_display_tiles_fast(x, y, tiles, size, palette) \
    X = (y); \
    if (_ms_buffer) X += _MS_DLL_ARRAY_SIZE; \
    _ms_dldma[X] -= (10 + 3 + size * 9 + 1) / 2; \
    _ms_tmpptr = _ms_dls[X]; \
    Y = _ms_dlend[X]; \
    _ms_tmpptr[Y++] = (tiles); \
    _ms_tmpptr[Y++] = 0x60; \
    _ms_tmpptr[Y++] = (tiles) >> 8; \
    _ms_tmpptr[Y++] = -size & 0x1f | (palette << 5); \
    _ms_tmpptr[Y++] = (x); \
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

void multisprite_init()
{
    *BACKGRND = 0x0;
    
    multisprite_get_tv();
    multisprite_clear();
    multisprite_save();

    _ms_tmpptr = _ms_b0_dll;
    for (X = 0, _ms_tmp = 0; _ms_tmp <= 1; _ms_tmp++) {
        // Build DLL
        // 69 blank lines for PAL
        // 19 blank lines for NTSC
        if (_ms_pal_detected) {
            // 16 blank lines
            _ms_tmpptr[Y = 0] = 0x4f;  // 16 lines
            _ms_tmpptr[++Y] = _ms_set_wm_dl >> 8;
            _ms_tmpptr[++Y] = _ms_set_wm_dl;
            // 16 blank lines
            _ms_tmpptr[++Y] = 0x4f;  // 16 lines
            _ms_tmpptr[++Y] = _ms_blank_dl >> 8;
            _ms_tmpptr[++Y] = _ms_blank_dl;
        } else {
            _ms_tmpptr[Y = 0] = 0x41; // 2 lines
            _ms_tmpptr[++Y] = _ms_set_wm_dl >> 8;
            _ms_tmpptr[++Y] = _ms_set_wm_dl;
        }
        // 16 pixel high regions
        for (_ms_tmp2 = 0; _ms_tmp2 != _MS_DLL_ARRAY_SIZE - 1; X++, _ms_tmp2++) {
            _ms_tmpptr[++Y] = (_ms_tmp2 < _MS_TOP_DISPLAY)?0x0f:0x4f; // 16 lines
            _ms_tmpptr[++Y] = _ms_dls[X] >> 8; // High address
            _ms_tmpptr[++Y] = _ms_dls[X]; // Low address
        }
        // 1 pixel high region for the last display list (for vertical scrolling)
        _ms_tmpptr[++Y] = 0x40; // 1 line
        _ms_tmpptr[++Y] = _ms_blank_dl >> 8;
        _ms_tmpptr[++Y] = _ms_blank_dl;
        X++;
        if (_ms_pal_detected) {
            // 15 blank lines
            _ms_tmpptr[++Y] = 0x4f;  // 16 lines
            _ms_tmpptr[++Y] = _ms_blank_dl >> 8;
            _ms_tmpptr[++Y] = _ms_blank_dl;
            // 16 blank lines
            _ms_tmpptr[++Y] = 0x4e;  // 15 lines
            _ms_tmpptr[++Y] = _ms_blank_dl >> 8;
            _ms_tmpptr[++Y] = _ms_blank_dl;
            // 5 blank lines
            _ms_tmpptr[++Y] = 0x44;  // 5 lines
            _ms_tmpptr[++Y] = _ms_blank_dl >> 8;
            _ms_tmpptr[++Y] = _ms_blank_dl;
        } else {
            _ms_tmpptr[++Y] = 0x4f; // 16 lines
            _ms_tmpptr[++Y] = _ms_blank_dl >> 8;
            _ms_tmpptr[++Y] = _ms_blank_dl;
        }
        _ms_tmpptr = _ms_b1_dll;
    }

#ifdef VERTICAL_SCROLLING
    _ms_vscroll_fine_offset = 0;
    _ms_vscroll_coarse_offset = 0;
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
#endif   
 
#ifdef HORIZONTAL_SCROLLING
    _ms_delayed_hscroll = 0;
#endif

    _ms_buffer = 0; // 0 is the current write buffer
    _ms_dmaerror = 0;
    *DPPH = _ms_b1_dll >> 8; // 1 the current displayed buffer
    *DPPL = _ms_b1_dll;
#ifdef MODE_320AC
    *CTRL = 0x53;
#else
#ifdef MODE_320BD
    *CTRL = 0x52;
#else
    *CTRL = 0x50; // DMA on, 160A/B mode, Two (2) byte characters mode
#endif
#endif
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
    while (!(*MSTAT & 0x80)); // Wait for VBLANK
    if (_ms_buffer) {
        for (Y = _MS_DLL_ARRAY_SIZE * 2 - 1, X = _MS_DLL_ARRAY_SIZE - 1; X >= 0; Y--, X--) {
            _ms_dlend_save[X] = _ms_dlend[Y];
            _ms_dldma_save[X] = _ms_dldma[Y];
        }
        // Copy the DLs from current write buffer to all buffers
        for (_ms_tmp = _MS_DLL_ARRAY_SIZE - 1; _ms_tmp >= 0; _ms_tmp--) {
            _ms_tmpptr = _ms_dls[X = _ms_tmp + _MS_DLL_ARRAY_SIZE];
            _ms_tmpptr2 = _ms_dls[X = _ms_tmp];
            for (Y = _ms_dlend[X] - 1; Y >= 0; Y--) {
                _ms_tmpptr2[Y] = _ms_tmpptr[Y];
            } 
        }
    } else {
        for (X = _MS_DLL_ARRAY_SIZE - 1; X >= 0; X--) {
            _ms_dlend_save[X] = _ms_dlend[X];
            _ms_dldma_save[X] = _ms_dldma[X];
        }
        // Copy the DLs from current write buffer to all buffers
        for (_ms_tmp = _MS_DLL_ARRAY_SIZE - 1; _ms_tmp >= 0; _ms_tmp--) {
            _ms_tmpptr = _ms_dls[X = _ms_tmp + _MS_DLL_ARRAY_SIZE];
            _ms_tmpptr2 = _ms_dls[X = _ms_tmp];
            for (Y = _ms_dlend[X] - 1; Y >= 0; Y--) {
                _ms_tmpptr[Y] = _ms_tmpptr2[Y];
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
    _ms_top_sbuffer_dma -= (10 + 3 + 21 * 9 + 1) / 2; \
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
    _ms_bottom_sbuffer_dma -= (10 + 3 + 21 * 9 + 1) / 2; \
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

char *_ms_vscroll_sparse_tiles_ptr_high, *_ms_vscroll_sparse_tiles_ptr_low;
#define multisprite_vscroll_init_sparse_tiles(ptr) \
    _ms_vscroll_sparse_tiles_ptr_high = ptr[Y = 0];\
    _ms_vscroll_sparse_tiles_ptr_low = ptr[Y = 1];

void multisprite_vscroll_buffer_sparse_tiles(char c)
{
    char *stiles, tmp;
    Y = c;
    stiles = _ms_vscroll_sparse_tiles_ptr_low[Y] | (_ms_vscroll_sparse_tiles_ptr_high[Y] << 8);   
    Y = 1;
    tmp = stiles[Y];
    X = _ms_sbuffer_size;
    while (tmp != 0xff) {
        _ms_sbuffer[X++] = stiles[++Y];
        _ms_sbuffer[X++] = stiles[++Y];
        _ms_sbuffer[X++] = stiles[++Y];
        _ms_sbuffer[X++] = stiles[++Y];
        _ms_sbuffer[X++] = tmp << 3;
        _ms_sbuffer_dma -= stiles[++Y];
        ++Y;
        tmp = stiles[++Y];
    }
    if (!X) X = 128; // To mark sbuffer_size != 0
    _ms_sbuffer_size = X;
}

#ifdef MULTISPRITE_USE_VIDEO_MEMORY
ramchip char _ms_vscroll_sparse_step;
ramchip char _ms_vscroll_sparse_vmem_ptr_low, _ms_vscroll_sparse_vmem_ptr_high, _ms_vscroll_charbase;
char *_ms_sbuffer_sparse_tilemap_ptr;

bank1 char multisprite_vmem[8192]; // Video memory in RAM
bank1 const char multisprite_vscroll_init_sparse_tiles_vmem_use_rom[] = {1};

#define multisprite_vscroll_init_sparse_tiles_vmem(ptr, tiles_ptr) \
{ \
    _ms_vscroll_sparse_tiles_ptr_high = ptr[Y = 0]; \
    _ms_vscroll_sparse_tiles_ptr_low = ptr[Y = 1]; \
    _ms_vscroll_charbase = (tiles_ptr) >> 8; \
    _ms_vscroll_sparse_vmem_ptr_low = 0x00; \
    _ms_vscroll_sparse_vmem_ptr_high = 0x40; \
    _ms_vscroll_sparse_step = 255; \
    _ms_sbuffer_size = 128; \
} \

void multisprite_vscroll_buffer_sparse_tiles_vmem(char c)
{
    char len, len2, tmp, low, tmp2, tmp3, high, first = 1;
    low = _ms_vscroll_sparse_vmem_ptr_low;
    high = _ms_vscroll_sparse_vmem_ptr_high;
    Y = c;
    _ms_sbuffer_sparse_tilemap_ptr = _ms_vscroll_sparse_tiles_ptr_low[Y] | (_ms_vscroll_sparse_tiles_ptr_high[Y] << 8);   
    Y = 0;
    len = _ms_sbuffer_sparse_tilemap_ptr[Y++];
    tmp = _ms_sbuffer_sparse_tilemap_ptr[Y];
    X = _ms_sbuffer_size;
    while (tmp != 0xff) {
        len2 = len - tmp + 1;
        len = len2 << 1;
        tmp2 = low - len;
        if (tmp2 < 0) {
            low = -len;
            //high ^= 16;
            high += 16;
            if (high == 0x70) high = 0x40;
        } else low = tmp2;
        Y++; Y++; Y++; Y++;
        tmp3 = _ms_sbuffer_sparse_tilemap_ptr[Y] & 0xe0;
        tmp2 = ((-len) & 0x1f) | tmp3;
        if (first) {
            _ms_sbuffer[X++] = low;
            _ms_sbuffer[X++] = 0x40;
            _ms_sbuffer[X++] = high;
            _ms_sbuffer[X++] = tmp2;
            _ms_sbuffer_dma -= 5 + len + len2;
            first = 0;
        } else {
            _ms_sbuffer[X++] = low;
            _ms_sbuffer[X++] = tmp2;
            _ms_sbuffer[X++] = high;
            _ms_sbuffer_dma -= 4 + len + len2;
        }
        Y++;
        _ms_sbuffer[X++] = tmp << 3;
        len = _ms_sbuffer_sparse_tilemap_ptr[++Y];
        tmp = _ms_sbuffer_sparse_tilemap_ptr[++Y];
    }
    if (!X) X = 128; // To mark sbuffer_size != 0
    _ms_sbuffer_size = X;
    _ms_vscroll_sparse_step = 15;
}

char multisprite_vscroll_buffer_sparse_tiles_vmem_step()
{
    char len, len2, tmp, low, tmp2, high, chlow, chhigh, *chptr, *tilesptr, *vmemptr, byte1;
    if (_ms_vscroll_sparse_step == 255) return 0;
    tmp = _ms_vscroll_charbase + _ms_vscroll_sparse_step;
    tilesptr = tmp << 8;
    low = _ms_vscroll_sparse_vmem_ptr_low;
    high = _ms_vscroll_sparse_vmem_ptr_high + _ms_vscroll_sparse_step;
    Y = 0;
    len = _ms_sbuffer_sparse_tilemap_ptr[Y++];
    tmp = _ms_sbuffer_sparse_tilemap_ptr[Y];
    while (tmp != 0xff) {
        len2 = len - tmp + 1; // in chars
        len = len2 << 1; // in bytes
        tmp2 = low - len;
        if (tmp2 < 0) {
            low = -len;
            //high ^= 16;
            high += 16;
            if (high >= 0x70) high = 0x40 + _ms_vscroll_sparse_step;
        } else low = tmp2;
        vmemptr = low | (high << 8);
        chlow = _ms_sbuffer_sparse_tilemap_ptr[++Y];
        ++Y;
        chhigh = _ms_sbuffer_sparse_tilemap_ptr[++Y];
        ++Y; ++Y;

        _save_y = Y;
        // Copy the row of chars for current step
        chptr = chlow | (chhigh << 8);
        for (Y = 0; Y != len2; Y++) {
            tmp2 = Y;
            Y = chptr[Y];
            byte1 = tilesptr[Y++];
            X = tilesptr[Y];
            Y = tmp2 << 1;
            vmemptr[Y++] = byte1;
            vmemptr[Y] = X;
            Y = tmp2;
        }
        Y = _save_y;
        
        len = _ms_sbuffer_sparse_tilemap_ptr[++Y];
        tmp = _ms_sbuffer_sparse_tilemap_ptr[++Y];
    }
    _ms_vscroll_sparse_step--;
    if (_ms_vscroll_sparse_step == 255) {
        _ms_vscroll_sparse_vmem_ptr_low = low;
        _ms_vscroll_sparse_vmem_ptr_high = high;
        return 0;
    }
    return 1;
}

#endif
#endif

void _ms_move_dlls_down()
{
    if (_ms_pal_detected) {
        Y = 6 + (_MS_TOP_SCROLLING_ZONE * 3);
    } else {
        Y = 3 + (_MS_TOP_SCROLLING_ZONE * 3);
    }
    if (_ms_buffer) {
        _ms_tmpptr = _ms_b1_dll;
        X = _MS_TOP_SCROLLING_ZONE + _ms_vscroll_coarse_offset + _MS_DLL_ARRAY_SIZE;
        // 16 pixel high regions
        for (_ms_tmp2 = _MS_TOP_SCROLLING_ZONE; _ms_tmp2 != _MS_DLL_ARRAY_SIZE; _ms_tmp2++) {
            Y++;
            _ms_tmpptr[Y++] = _ms_dls[X] >> 8; // High address
            _ms_tmpptr[Y++] = _ms_dls[X]; // Low address
            X++;
            if (X == 2 *_MS_DLL_ARRAY_SIZE) X = _MS_DLL_ARRAY_SIZE + _MS_TOP_SCROLLING_ZONE;
        }
        // Copy the scroll buffer to the first zone 
        X = _MS_TOP_SCROLLING_ZONE + _ms_vscroll_coarse_offset + _MS_DLL_ARRAY_SIZE;
    } else {
        _ms_tmpptr = _ms_b0_dll;
        X = _MS_TOP_SCROLLING_ZONE + _ms_vscroll_coarse_offset;
        // 16 pixel high regions
        for (_ms_tmp2 = _MS_TOP_SCROLLING_ZONE; _ms_tmp2 != _MS_DLL_ARRAY_SIZE; _ms_tmp2++) {
            Y++;
            _ms_tmpptr[Y++] = _ms_dls[X] >> 8; // High address
            _ms_tmpptr[Y++] = _ms_dls[X]; // Low address
            X++;
            if (X == _MS_DLL_ARRAY_SIZE) X = _MS_TOP_SCROLLING_ZONE;
        }
        // Copy the scroll buffer to the first zone 
        X = _MS_TOP_SCROLLING_ZONE + _ms_vscroll_coarse_offset;
    }
    _ms_tmpptr = _ms_dls[X];
#ifdef BIDIR_VERTICAL_SCROLLING
    Y = _ms_top_sbuffer_size;
#else
    Y = _ms_sbuffer_size & 0x7f;
#endif
    _ms_dlend[X] = Y;
    for (Y--; Y >= 0; Y--) { 
#ifdef BIDIR_VERTICAL_SCROLLING
        _ms_tmpptr[Y] = _ms_top_sbuffer[Y];
#else
        _ms_tmpptr[Y] = _ms_sbuffer[Y];
#endif
    }
}

void _ms_move_save_down()
{
    X = _MS_TOP_SCROLLING_ZONE + _ms_vscroll_coarse_offset;

#ifdef BIDIR_VERTICAL_SCROLLING
    _ms_dlend_save[X] = _ms_top_sbuffer_size;
    _ms_dldma_save[X] = _ms_top_sbuffer_dma;
    _ms_bottom_sbuffer_size = 0;
    _ms_bottom_sbuffer_dma = _MS_DMA_START_VALUE;
    _ms_top_sbuffer_size = 0;
    _ms_top_sbuffer_dma = _MS_DMA_START_VALUE;
    _ms_scroll_buffers_refill = MS_SCROLL_UP;
#else
    _ms_dlend_save[X] = _ms_sbuffer_size & 0x7f;
    _ms_dldma_save[X] = _ms_sbuffer_dma;
    _ms_sbuffer_size = 0;
    _ms_sbuffer_dma = _MS_DMA_START_VALUE;
#endif
}

void _ms_move_dlls_up()
{
    // Move the DLLs
    if (_ms_pal_detected) {
        Y = 6 + (_MS_TOP_SCROLLING_ZONE * 3);
    } else {
        Y = 3 + (_MS_TOP_SCROLLING_ZONE * 3);
    }
    if (_ms_buffer) {
        _ms_tmpptr = _ms_b1_dll;
        X = _MS_TOP_SCROLLING_ZONE + _ms_vscroll_coarse_offset + _MS_DLL_ARRAY_SIZE;
        // 16 pixel high regions
        for (_ms_tmp2 = _MS_TOP_SCROLLING_ZONE; _ms_tmp2 != _MS_DLL_ARRAY_SIZE; _ms_tmp2++) {
            Y++;
            _ms_tmpptr[Y++] = _ms_dls[X] >> 8; // High address
            _ms_tmpptr[Y++] = _ms_dls[X]; // Low address
            X++;
            if (X == 2 *_MS_DLL_ARRAY_SIZE) X = _MS_DLL_ARRAY_SIZE + _MS_TOP_SCROLLING_ZONE;
        }
        // Copy the scroll buffer to the last zone 
        if (_ms_vscroll_coarse_offset == 0) {
            X = _MS_DLL_ARRAY_SIZE * 2 - 1;
        } else {
            X = _MS_TOP_SCROLLING_ZONE - 1 + _ms_vscroll_coarse_offset + _MS_DLL_ARRAY_SIZE;
        }
    } else {
        _ms_tmpptr = _ms_b0_dll;
        X = _MS_TOP_SCROLLING_ZONE + _ms_vscroll_coarse_offset;
        // 16 pixel high regions
        for (_ms_tmp2 = _MS_TOP_SCROLLING_ZONE; _ms_tmp2 != _MS_DLL_ARRAY_SIZE; _ms_tmp2++) {
            Y++;
            _ms_tmpptr[Y++] = _ms_dls[X] >> 8; // High address
            _ms_tmpptr[Y++] = _ms_dls[X]; // Low address
            X++;
            if (X == _MS_DLL_ARRAY_SIZE) X = _MS_TOP_SCROLLING_ZONE;
        }
        if (_ms_vscroll_coarse_offset == 0) {
            X = _MS_DLL_ARRAY_SIZE - 1;
        } else {
            X = _MS_TOP_SCROLLING_ZONE - 1 + _ms_vscroll_coarse_offset;
        }
    }
    // Copy the scroll buffer to the last zone 
    _ms_tmpptr = _ms_dls[X];
#ifdef BIDIR_VERTICAL_SCROLLING
    Y = _ms_bottom_sbuffer_size;
#else
    Y = _ms_sbuffer_size & 0x7f;
#endif
    _ms_dlend[X] = Y;
    for (Y--; Y >= 0; Y--) { 
#ifdef BIDIR_VERTICAL_SCROLLING
        _ms_tmpptr[Y] = _ms_bottom_sbuffer[Y];
#else
        _ms_tmpptr[Y] = _ms_sbuffer[Y];
#endif
    }
}

void _ms_move_save_up()
{
    if (_ms_vscroll_coarse_offset == 0) {
        X = _MS_DLL_ARRAY_SIZE - 1;
    } else {
        X = _MS_TOP_SCROLLING_ZONE + _ms_vscroll_coarse_offset - 1;
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
    _ms_dlend_save[X] = _ms_sbuffer_size & 0x7f;
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
    // Insert DMA masking objects 
    if (_ms_vscroll_fine_offset) {
        if (_ms_buffer) {
            if (_ms_vscroll_coarse_offset == 0) {
                X = _MS_DLL_ARRAY_SIZE * 2 - 1;
            } else {
                X = _MS_TOP_SCROLLING_ZONE + _ms_vscroll_coarse_offset - 1 + _MS_DLL_ARRAY_SIZE;
            }
        } else {
            if (_ms_vscroll_coarse_offset == 0) {
                X = _MS_DLL_ARRAY_SIZE - 1;
            } else {
                X = _MS_TOP_SCROLLING_ZONE + _ms_vscroll_coarse_offset - 1;
            }
        } 
        _ms_tmpptr = _ms_dls[X];
        if (_ms_dlend[X] == 0 || _ms_tmpptr[Y = 4] != 161) {
            // Insert the object
            Y = _ms_dlend[X];
            // First, move all objects on this line 17 bytes on the right
            _ms_tmpptr2 = _ms_tmpptr + 17;
            for (Y--; Y >= 0; Y--) { 
                _ms_tmpptr2[Y] = _ms_tmpptr[Y];
            }
            Y = 0;
            _ms_tmpptr[Y++] = 0; 
            _ms_tmpptr[Y++] = 0xc0; // WM = 1, Direct mode
            _ms_tmpptr[Y++] = 0xa0 | _ms_vscroll_fine_offset;
            _ms_tmpptr[Y++] = 0;
            _ms_tmpptr[Y++] = 161; 
            for (_ms_tmp = 0; _ms_tmp != 3; _ms_tmp++) {
                _ms_tmpptr[Y++] = 0; 
                _ms_tmpptr[Y++] = 0xe1;
                _ms_tmpptr[Y++] = 0xa0 | _ms_vscroll_fine_offset;
                _ms_tmpptr[Y++] = 161; 
            }
            _ms_dlend[X] += 17;
        } else {
            _ms_tmpptr[Y = 2] = 0xa0 | _ms_vscroll_fine_offset;
            for (Y = 7, _ms_tmp = 0; _ms_tmp != 3; Y += 4, _ms_tmp++) {
                _ms_tmpptr[Y] = 0xa0 | _ms_vscroll_fine_offset;
            }
        }
    }
#endif
    if (_ms_buffer) {
        // Add DL end entry on each DL
        for (X = _MS_DLL_ARRAY_SIZE * 2 - 1; X >= _MS_DLL_ARRAY_SIZE; X--) {
            _ms_tmpptr = _ms_dls[X];
            Y = _ms_dlend[X];
            _ms_tmpptr[++Y] = 0; 
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
                _ms_tmpptr = _ms_dls[X = _ms_delayed_vscroll_remove];
                if (_ms_dlend[X] >= 17 && _ms_tmpptr[Y = 4] == 161) {
                    // Remove the DMA masking objects 
                    // First, move all objects on this line 17 bytes to the left 
                    _ms_tmpptr2 = _ms_tmpptr + 17;
                    for (Y = 0; Y != _ms_dlend[X]; Y++) { 
                        _ms_tmpptr[Y] = _ms_tmpptr2[Y];
                    }
                    _ms_dlend[X] -= 17;
                }
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
        if (_ms_vscroll_coarse_offset == 0) {
            X = _MS_DLL_ARRAY_SIZE - 1;
        } else {
            X = _MS_TOP_SCROLLING_ZONE + _ms_vscroll_coarse_offset - 1;
        }
#endif
    } else {
        // Add DL end entry on each DL
        for (X = _MS_DLL_ARRAY_SIZE - 1; X >= 0; X--) {
            _ms_tmpptr = _ms_dls[X];
            Y = _ms_dlend[X];
            _ms_tmpptr[++Y] = 0; 
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
                _ms_tmpptr = _ms_dls[X = _ms_delayed_vscroll_remove];
                if (_ms_dlend[X] >= 17 && _ms_tmpptr[Y = 4] == 161) {
                    // Remove the DMA masking objects 
                    // First, move all objects on this line 17 bytes to the left 
                    _ms_tmpptr2 = _ms_tmpptr + 17;
                    for (Y = 0; Y != _ms_dlend[X]; Y++) { 
                        _ms_tmpptr[Y] = _ms_tmpptr2[Y];
                    }
                    _ms_dlend[X] -= 17;
                }
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
        if (_ms_vscroll_coarse_offset == 0) {
            X = _MS_DLL_ARRAY_SIZE * 2 - 1;
        } else {
            X = _MS_TOP_SCROLLING_ZONE + _ms_vscroll_coarse_offset - 1 + _MS_DLL_ARRAY_SIZE;
        }
#endif
    }
#ifdef VERTICAL_SCROLLING
    // Insert DMA masking objects 
    if (_ms_vscroll_fine_offset) {
        _ms_tmpptr = _ms_dls[X];
        _ms_dldma[X] -= (13 * 4) / 2;
        if (_ms_dlend[X] == 0 || _ms_tmpptr[Y = 4] != 161) {
            // Insert the object
            Y = _ms_dlend[X];
            // First, move all objects on this line 17 bytes on the right
            _ms_tmpptr2 = _ms_tmpptr + 17;
            for (Y--; Y >= 0; Y--) { 
                _ms_tmpptr2[Y] = _ms_tmpptr[Y];
            }
            Y = 0;
            _ms_tmpptr[Y++] = 0; 
            _ms_tmpptr[Y++] = 0xc0; // WM = 1, Direct mode
            _ms_tmpptr[Y++] = 0xa0 | _ms_vscroll_fine_offset;
            _ms_tmpptr[Y++] = 0;
            _ms_tmpptr[Y++] = 161; 
            for (_ms_tmp = 0; _ms_tmp != 3; _ms_tmp++) {
                _ms_tmpptr[Y++] = 0; 
                _ms_tmpptr[Y++] = 0xe1;
                _ms_tmpptr[Y++] = 0xa0 | _ms_vscroll_fine_offset;
                _ms_tmpptr[Y++] = 161; 
            }
        } else {
            _ms_tmpptr[Y = 2] = 0xa0 | _ms_vscroll_fine_offset;
            for (Y = 7, _ms_tmp = 0; _ms_tmp != 3; Y += 4, _ms_tmp++) {
                _ms_tmpptr[Y] = 0xa0 | _ms_vscroll_fine_offset;
            }
        }
        _ms_dlend[X] += 17;
    }
#endif
}

#ifdef VERTICAL_SCROLLING

// Vertical scrolling
#define multisprite_vertical_scrolling(x) { _ms_tmp = (x); _ms_vertical_scrolling(); }

void _ms_vertical_scrolling_adjust_bottom_of_screen()
{
    if (_ms_buffer) {
        _ms_tmpptr = _ms_b1_dll;
        if (_ms_vscroll_coarse_offset == 0) {
            X = _MS_DLL_ARRAY_SIZE * 2 - 1;
        } else {
            X = _MS_TOP_SCROLLING_ZONE + _ms_vscroll_coarse_offset - 1 + _MS_DLL_ARRAY_SIZE;
        }
    } else {
        _ms_tmpptr = _ms_b0_dll;
        if (_ms_vscroll_coarse_offset == 0) {
            X = _MS_DLL_ARRAY_SIZE - 1;
        } else {
            X = _MS_TOP_SCROLLING_ZONE + _ms_vscroll_coarse_offset - 1;
        }
    }
    if (_ms_pal_detected) { Y = 6 + 3 * _MS_TOP_SCROLLING_ZONE; } else { Y = 3 + 3 * _MS_TOP_SCROLLING_ZONE; }
    _ms_tmpptr[Y] = (_ms_tmpptr[Y] & 0xf0) | (15 - _ms_vscroll_fine_offset); // 16 - _ms_vscroll_fine_offset lines
    Y +=  3 * (_MS_DLL_ARRAY_SIZE - 1 - _MS_TOP_SCROLLING_ZONE);
    if (_ms_vscroll_fine_offset) {
        _ms_tmpptr[Y] = 0x4f; // 16 lines
        _ms_tmpptr[++Y] = _ms_dls[X] >> 8;
        _ms_tmpptr[++Y] = _ms_dls[X];
        _ms_tmpptr[++Y] = _ms_vscroll_fine_offset | 0x40;  // _ms_vscroll_fine_offset + 1 lines
    } else {
        _ms_tmpptr[Y] = 0x40; // 1 line
        _ms_tmpptr[++Y] = _ms_blank_dl >> 8;
        _ms_tmpptr[++Y] = _ms_blank_dl;
        _ms_tmpptr[++Y] = 0x4f;  // 16 lines
    }
}

void _ms_vertical_scrolling()
{
    _ms_vscroll_fine_offset -= _ms_tmp;
    if (_ms_vscroll_fine_offset < 0) {
        _ms_vscroll_coarse_offset--; 
        if (_ms_vscroll_coarse_offset == 255)
            _ms_vscroll_coarse_offset = _MS_DLL_ARRAY_SIZE - _MS_TOP_SCROLLING_ZONE - 1;
        _ms_vscroll_coarse_offset_shifted = _ms_vscroll_coarse_offset << 3; 
        _ms_move_dlls_down();
        _ms_vscroll_fine_offset += 16;
        _ms_delayed_vscroll = 1;
    } else if (_ms_vscroll_fine_offset >= 16) {
        
        // Check the current last zone and remove the DMA masking object
        if (_ms_buffer) {
            if (_ms_vscroll_coarse_offset == 0) {
                X = _MS_DLL_ARRAY_SIZE * 2 - 1;
            } else {
                X = _MS_TOP_SCROLLING_ZONE + _ms_vscroll_coarse_offset - 1 + _MS_DLL_ARRAY_SIZE;
            }
            _ms_delayed_vscroll_remove = X - _MS_DLL_ARRAY_SIZE;
        } else {
            if (_ms_vscroll_coarse_offset == 0) {
                X = _MS_DLL_ARRAY_SIZE - 1;
            } else {
                X = _MS_TOP_SCROLLING_ZONE + _ms_vscroll_coarse_offset - 1;
            }
            _ms_delayed_vscroll_remove = X + _MS_DLL_ARRAY_SIZE;
        } 
        _ms_tmpptr = _ms_dls[X];
        if (_ms_dlend[X] >= 17 && _ms_tmpptr[Y = 4] == 161) {
            // Remove the object
            // First, move all objects on this line 17 bytes to the left 
            _ms_tmpptr2 = _ms_tmpptr + 17;
            for (Y = 0; Y != _ms_dlend[X]; Y++) { 
                _ms_tmpptr[Y] = _ms_tmpptr2[Y];
            }
            _ms_dlend[X] -= 17;
        }

        _ms_vscroll_coarse_offset++; 
        if (_ms_vscroll_coarse_offset == _MS_DLL_ARRAY_SIZE - _MS_TOP_SCROLLING_ZONE)
            _ms_vscroll_coarse_offset = 0;
        _ms_vscroll_coarse_offset_shifted = _ms_vscroll_coarse_offset << 3; 
        _ms_move_dlls_up();
        _ms_vscroll_fine_offset -= 16;
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
    _ms_tmpptr = _ms_dls[X]; \
    Y = (offset) + 4; \
    _ms_horizontal_tiles_scrolling()

void _ms_horizontal_tiles_scrolling()
{
    _ms_tmp = _ms_tmpptr[Y] - _ms_hscroll; // X position
    if (_ms_hscroll > 0) {
        if (_ms_tmp > 160 && _ms_tmp < 256 - 8) {
            // We have reached the left border of the screen
            // Advance the pointer
            _ms_tmpptr[Y] = _ms_tmp + 8;
#ifdef TILES_CHECK_BOUNDARIES
            Y -= 4;
            _ms_tmpptr2 = _ms_tmpptr[Y];
            Y++; Y++;
            _ms_tmpptr2 |= (_ms_tmpptr[Y] << 8);
            Y++;
            // Get the width of this tileset
            _ms_tmp = Y;
            Y = -(_ms_tmpptr[Y] | 0xe0);
            if (_ms_tmpptr2[Y] == 0xff) { // This is a boundary
                // Reduce the width of this string
                X = --Y;
                Y = _ms_tmp;
                X = (-X) & 0x1f;
                _ms_tmpptr[Y] = _ms_tmpptr[Y] & 0xe0 | X; 
            }
            Y = _ms_tmp;
            _ms_tmpptr2++;
            _ms_tmpptr[--Y] = _ms_tmpptr2 >> 8;
            Y--; Y--;
            _ms_tmpptr[Y] = _ms_tmpptr2;
#else 
            Y -= 4;
            _ms_tmpptr[Y]++;
            if (_ms_tmpptr[Y] == 0) {
                // Crossing page boundary
                Y++; Y++;
                _ms_tmpptr[Y]++;
            }
#endif
        } else {
            _ms_tmpptr[Y] = _ms_tmp;
#ifdef TILES_CHECK_BOUNDARIES
            // TODO : Check if we we should expand the width of the tileset
            // If it touches the right border of the screen
#endif
        }
    } else {
        _ms_tmpptr[Y] = _ms_tmp;
        if (_ms_tmp >= 0) {
#ifdef TILES_CHECK_BOUNDARIES
            // TODO: If the tileset touches the right side of the screen, reduce its width...
            // TODO: Do below only if one touches the left border of the screen
            X = _ms_tmp;
            Y -= 4;
            _ms_tmpptr2 = _ms_tmpptr[Y];
            Y++; Y++;
            _ms_tmpptr2 |= (_ms_tmpptr[Y] << 8);
            _ms_tmpptr2--;
            _ms_tmp = Y;
            if (_ms_tmpptr2[Y = 0] == 0xff) { // This is a boundary
                _ms_tmpptr2++; // Go back to previous pointer
            } else {
                // Extend the width up to 21
                Y = _ms_tmp;
                Y++; Y++;
                _ms_tmpptr[Y] = X - 8;
                Y--;
                X = -(_ms_tmpptr[Y] | 0xe0);
                if (X < 21) {
                    X++;
                    X = (-X) & 0x1f;
                    _ms_tmpptr[Y] = _ms_tmpptr[Y] & 0xe0 | X; 
                }
            }
            Y = _ms_tmp;
            _ms_tmpptr[Y] = _ms_tmpptr2 >> 8;
            Y--; Y--;
            _ms_tmpptr[Y] = _ms_tmpptr2;
#else
            _ms_tmpptr[Y] = _ms_tmp - 8;
            Y -= 4;
            _ms_tmpptr[Y]--;
            if (_ms_tmpptr[Y] == 0xff) {
                // Crossing page boundary
                Y++; Y++;
                _ms_tmpptr[Y]--;
            }
#endif
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
    _ms_tmpptr = _ms_top_sbuffer;
    Y = 4; 
    _ms_horizontal_tiles_scrolling();
    _ms_tmpptr = _ms_bottom_sbuffer;
    Y = 4; 
    _ms_horizontal_tiles_scrolling();
#endif
}

#endif

// _ms_tmp : display list entry to apply DLI flag
void _multisprite_enable_dli()
{
    _ms_tmp = (_ms_tmp << 2) - _ms_tmp + 3; // _ms_tmp = _ms_tmp * 3 + 3
    if (_ms_pal_detected) _ms_tmp += 3;
    _ms_b0_dll[X = _ms_tmp] |= 0x80;
    _ms_b1_dll[X] |= 0x80;
}

// _ms_tmp : display list entry to apply DLI flag
void _multisprite_disable_dli()
{
    _ms_tmp = (_ms_tmp << 2) - _ms_tmp + 3; // _ms_tmp = _ms_tmp * 3 + 3
    if (_ms_pal_detected) _ms_tmp += 3;
    _ms_b0_dll[X = _ms_tmp] &= 0x7f;
    _ms_b1_dll[X] &= 0x7f;
}

char _ms_bit_extract[8] = {128, 64, 32, 16, 8, 4, 2, 1};

// ~100 cycles max pixel accurate collision detection (60us)
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

#endif // __ATARI7800_MULTISPRITE__
 
