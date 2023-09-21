/*
    tiling.h: tiling display for the Atari 7800
    Copyleft 2023 Bruno STEUX 

    This file is distributed as a companion file to cc7800 - a subset of C compiler for the Atari 7800
*/

#ifndef __ATARI7800_TILING__
#define __ATARI7800_TILING__

#define VERTICAL_SCROLLING
#include "multisprite.h"

char *_tiling_ptr;

ramchip signed char _tiling_xpos, _tiling_ypos, _tiling_xoffset, _tiling_yoffset;
ramchip char *_tiling_tilemap_ptr, _tiling_width, _tiling_height;
signed char _tiling_tmp;

#define tiling_init(ptr, width, height, x, y, palette) \
    _tiling_tilemap_ptr = (ptr); \
    _tiling_width = (width); \
    _tiling_height = (height); \
    _ms_tmp = x; \
    _tiling_xpos = (((x) >> 8) << 5) | (_ms_tmp >> 3); \
    _tiling_xoffset = (x) & 7; \
    _ms_tmp = y; \
    _tiling_ypos = ((((y) >> 8)) << 4) | (_ms_tmp >> 4); \
    _tiling_yoffset = (y) & 0xf; \
    _ms_tmp3 = palette; \
    _tiling_init()

void _tiling_init()
{
    _tiling_ptr = _tiling_tilemap_ptr;
    for (_tiling_tmp = 0; _tiling_tmp < _tiling_ypos; _tiling_tmp++) {
       _tiling_ptr += _tiling_width;
    }
    _tiling_ptr += _tiling_xpos;
    _tiling_tmp = -_tiling_xoffset;
    for (_ms_tmpptr2 = _tiling_ptr, _ms_tmp = _MS_TOP_SCROLLING_ZONE; _ms_tmp != _MS_DLL_ARRAY_SIZE; _ms_tmp++) {
        multisprite_display_tiles_fast(_tiling_tmp, _ms_tmp, _ms_tmpptr2, 21, _ms_tmp3);
        _ms_tmpptr2 += _tiling_width;
    }
    _ms_vscroll_fine_offset = _tiling_yoffset;
    _ms_vertical_scrolling_adjust_bottom_of_screen();
}

#define tiling_goto(x, y) \
    _ms_tmp = x; \
    _tiling_xpos = (((x) >> 8) << 5) | (_ms_tmp >> 3); \
    _tiling_xoffset = (x) & 7; \
    _ms_tmp = y; \
    _tiling_ypos = ((((y) >> 8)) << 4) | (_ms_tmp >> 4); \
    _tiling_yoffset = (y) & 0xf; \
    _tiling_goto()

void _tiling_goto()
{
    _tiling_ptr = _tiling_tilemap_ptr;
    for (_tiling_tmp = 0; _tiling_tmp < _tiling_ypos; _tiling_tmp++) {
       _tiling_ptr += _tiling_width;
    }
    X = _MS_TOP_SCROLLING_ZONE; 
    if (_ms_buffer) X += _MS_DLL_ARRAY_SIZE; 
    _ms_tmpptr = _ms_dls[X]; 
#define palette_and_width _ms_tmp2
    palette_and_width = _ms_tmpptr[Y = 3]; // Get the palette and width
    if (_tiling_ypos < 0) {
        // Fill with blank
        _ms_tmp3 = _MS_TOP_SCROLLING_ZONE - _tiling_ypos;
        for (_ms_tmp = _MS_TOP_SCROLLING_ZONE; _ms_tmp < _ms_tmp3; _ms_tmp++) {
            _ms_tmpptr = _ms_dls[X++]; 
            Y = 3; 
            _ms_tmpptr[Y++] = palette_and_width | 0x1f; 
            _ms_tmpptr[Y] = 160; // Out of screen 
        }
    } else {
        _ms_tmp = _MS_TOP_SCROLLING_ZONE;
    }
    if (_tiling_xpos + 21 >= _tiling_width) {
        palette_and_width = palette_and_width & 0xe0 | ((_tiling_xpos - _tiling_width) & 0x1f);
    } else {
        palette_and_width = palette_and_width & 0xe0 | (-21 & 0x1f);
    }
    _tiling_tmp = -_tiling_xoffset;
    if (_tiling_xpos > 0) {
        _tiling_ptr += _tiling_xpos;
    } else {
        _tiling_tmp -= (_tiling_xpos << 3);
    }
#define bottom _ms_tmp3
    if (_tiling_ypos + _MS_DLL_ARRAY_SIZE - _MS_TOP_SCROLLING_ZONE >= _tiling_height) {
        bottom = _MS_TOP_SCROLLING_ZONE + _tiling_height - _tiling_ypos;
    } else {
        bottom = _MS_DLL_ARRAY_SIZE;
    }
    for (_ms_tmpptr2 = _tiling_ptr; _ms_tmp < bottom; _ms_tmp++) {
        _ms_tmpptr = _ms_dls[X++]; 
        Y = 0; 
        _ms_tmpptr[Y++] = _ms_tmpptr2; 
        Y++;
        _ms_tmpptr[Y++] = _ms_tmpptr2 >> 8; 
        _ms_tmpptr[Y++] = palette_and_width; 
        _ms_tmpptr[Y] = _tiling_tmp; 
        _ms_tmpptr2 += _tiling_width;
    }
    for (; _ms_tmp < _MS_DLL_ARRAY_SIZE; _ms_tmp++) {
        _ms_tmpptr = _ms_dls[X++]; 
        Y = 3; 
        _ms_tmpptr[Y++] = palette_and_width | 0x1f; 
        _ms_tmpptr[Y] = 160; // Out of screen 
    }

    _ms_vscroll_fine_offset = _tiling_yoffset;
    _ms_vertical_scrolling_adjust_bottom_of_screen();
}
#undef palette_and_width
#undef bottom

#endif


