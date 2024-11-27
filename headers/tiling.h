/*
    tiling.h: tiling display for the Atari 7800
    Copyleft 2023 Bruno STEUX 

    This file is distributed as a companion file to cc7800 - a subset of C compiler for the Atari 7800
*/

#ifndef __ATARI7800_TILING__
#define __ATARI7800_TILING__

#define VERTICAL_SCROLLING
#include "multisprite.h"

ramchip char *_tiling_tilemap_ptr, _tiling_width, _tiling_height;

void tiling_init(char *ptr, char width, char height, int x, int y, char palette)
{
    char *_tiling_ptr, *tmpptr2;
    signed char i;
    char j, k;
    signed char xpos, ypos, xoffset, yoffset;
    _tiling_tilemap_ptr = (ptr);
    _tiling_width = (width);
    _tiling_height = (height);
    j = x;
    xpos = (((x) >> 8) << 5) | (j >> 3);
    xoffset = (x) & 7;
    j = y;
    ypos = ((((y) >> 8)) << 4) | (j >> 4);
    yoffset = (y) & 0xf;
    k = palette;
    _tiling_ptr = _tiling_tilemap_ptr;
    for (i = 0; i < ypos; i++) {
       _tiling_ptr += _tiling_width;
    }
    _tiling_ptr += xpos;
    i = -xoffset;
    for (tmpptr2 = _tiling_ptr, j = 0; j != _MS_NB_SCROLLING_ZONES + 1; j++) {
        multisprite_display_tiles_fast(i, j, tmpptr2, 21, k);
        tmpptr2 += _tiling_width;
    }
    _ms_vscroll_fine_offset = yoffset;
    _ms_vertical_scrolling_adjust_bottom_of_screen();
}

void tiling_goto(int x, int y)
{
    char *_tiling_ptr, *tmpptr, *tmpptr2;
    signed char i;
    char j, k;
    char palette_and_width;
    char bottom;
    signed char xpos, ypos, xoffset, yoffset;

    j = x;
    xpos = (((x) >> 8) << 5) | (j >> 3);
    xoffset = (x) & 7;
    j = y;
    ypos = ((((y) >> 8)) << 4) | (j >> 4);
    yoffset = (y) & 0xf;
    _tiling_ptr = _tiling_tilemap_ptr;

    for (i = 0; i < ypos; i++) {
       _tiling_ptr += _tiling_width;
    }
    X = 0; 
    if (_ms_buffer) X += _MS_DLL_ARRAY_SIZE; 
    tmpptr = _ms_dls[X]; 
    palette_and_width = tmpptr[Y = 3]; // Get the palette and width
    if (ypos < 0) {
        // Fill with blank
        k = -ypos;
        for (j = 0; j < k; j++) {
            tmpptr = _ms_dls[X++]; 
            Y = 3; 
            tmpptr[Y++] = palette_and_width | 0x1f; 
            tmpptr[Y] = 160; // Out of screen 
        }
    } else {
        j = 0;
    }
    if (xpos + 21 >= _tiling_width) {
        palette_and_width = palette_and_width & 0xe0 | ((xpos - _tiling_width) & 0x1f);
    } else {
        palette_and_width = palette_and_width & 0xe0 | (-21 & 0x1f);
    }
    i = -xoffset;
    if (xpos > 0) {
        _tiling_ptr += xpos;
    } else {
        i -= (xpos << 3);
    }
    if (ypos + (_MS_NB_SCROLLING_ZONES + 1) >= _tiling_height) {
        bottom = _tiling_height - ypos;
    } else {
        bottom = _MS_NB_SCROLLING_ZONES + 1;
    }
    for (tmpptr2 = _tiling_ptr; j < bottom; j++) {
        tmpptr = _ms_dls[X++]; 
        Y = 0; 
        tmpptr[Y++] = tmpptr2; 
        Y++;
        tmpptr[Y++] = tmpptr2 >> 8; 
        tmpptr[Y++] = palette_and_width; 
        tmpptr[Y] = i; 
        tmpptr2 += _tiling_width;
    }
    for (; j < _MS_NB_SCROLLING_ZONES + 1; j++) {
        tmpptr = _ms_dls[X++]; 
        Y = 3; 
        tmpptr[Y++] = palette_and_width | 0x1f; 
        tmpptr[Y] = 160; // Out of screen 
    }

    _ms_vscroll_fine_offset = yoffset;
    _ms_vertical_scrolling_adjust_bottom_of_screen();
}

#endif


