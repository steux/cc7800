/*
    tiling.h: tiling display for the Atari 7800
    Copyleft 2023 Bruno STEUX 

    This file is distributed as a companion file to cc7800 - a subset of C compiler for the Atari 7800
*/

#ifndef __ATARI7800_SPARSE_TILING__
#define __ATARI7800_SPARSE_TILING__

#define VERTICAL_SCROLLING
#include "multisprite.h"

char *_tiling_ptr, _tiling_data[5], _tiling_Y, _tiling_tmp;
ramchip char *_tilemap_data_ptr;
ramchip signed char _tiling_xpos, _tiling_ypos, _tiling_xoffset, _tiling_yoffset, _tiling_left, _tiling_right;

#define tiling_init(ptr) _tilemap_data_ptr = (ptr)

#define tiling_goto(x, y) \
    _ms_tmp = x; \
    _tiling_xpos = (((x) >> 8) << 5) | (_ms_tmp >> 3); \
    _tiling_xoffset = (x) & 7; \
    _ms_tmp = y; \
    _tiling_ypos = ((((y) >> 8)) << 4) | (_ms_tmp >> 4); \
    _tiling_yoffset = (y) & 0xf; \
    _tiling_goto()

#define _STS_SIZE 7
// SPS (Sparse Tileset Struct: 
//    X end of tileset (included)
//    X beginning of tileset
//    Low Address
//    Mode byte
//    High address
//    Palette & Width
//    DMA cost

void _tiling_goto()
{
    // Skip the lines on top
    _ms_tmp = _MS_TOP_SCROLLING_ZONE;
    _ms_tmp2 = _tiling_ypos;
    if (_tiling_ypos < 0) {
        _ms_tmp -= _tiling_ypos;
        _ms_tmp2 = 0;
    }
#define bottom _ms_tmp3
    if (_tiling_ypos + (_MS_DLL_ARRAY_SIZE - _MS_TOP_SCROLLING_ZONE - TILING_HEIGHT) >= 0) {
        bottom = _MS_TOP_SCROLLING_ZONE + TILING_HEIGHT - _tiling_ypos;
    } else {
        bottom = _MS_DLL_ARRAY_SIZE;
    }
    if (_ms_buffer) {
        _ms_tmp += _MS_DLL_ARRAY_SIZE; 
        bottom += _MS_DLL_ARRAY_SIZE;
    }
    _tiling_right = _tiling_xpos + TILING_WIDTH - 2;
    for (X = _ms_tmp; X < bottom; _ms_tmp2++) {
        Y = _ms_tmp2 << 1;
        //_tiling_ptr = tilemap_data[Y++];
        //_tiling_ptr |= tilemap_data[Y] << 8;
        //_tiling_ptr = tilemap_data[Y] | (tilemap_data[++Y] << 8);
        _tiling_tmp = tilemap_data[Y++];
        _tiling_ptr = _tiling_tmp | (tilemap_data[Y] << 8);   
        _ms_tmpptr = _ms_dls[X];
        // Find the first visible tileset on this line, if any
        Y = 0;
        do {
            _tiling_left = _tiling_ptr[Y];
            if (_tiling_left >= _tiling_xpos) break;
            Y += _STS_SIZE;
        } while (1);
        Y++; // Next byte
        _tiling_Y = 0;
        _tiling_data[4] = _tiling_ptr[Y];
        while (_tiling_data[4] < _tiling_right) { // 9 cycles
            _tiling_data[0] = _tiling_ptr[++Y]; // 10 cycles
            _tiling_data[1] = _tiling_ptr[++Y];
            _tiling_data[2] = _tiling_ptr[++Y];
            _tiling_data[3] = _tiling_ptr[++Y];
            _ms_dldma[X] += _tiling_ptr[++Y]; // 18 cycles
            _save_y = Y;
            Y = _tiling_Y; // 6 cycles
            _ms_tmpptr[Y++] = _tiling_data[0]; // 11 cycles
            _ms_tmpptr[Y++] = _tiling_data[1];
            _ms_tmpptr[Y++] = _tiling_data[2];
            _ms_tmpptr[Y++] = _tiling_data[3];
            _ms_tmpptr[Y++] = ((_tiling_data[4] - _tiling_xpos) << 3) - _tiling_xoffset; // 29 cycles
            _tiling_Y = Y; // 21 cycles
            Y = _save_y;
            Y++;
            _tiling_data[4] = _tiling_ptr[++Y];
        } // 167 cycles per tileset / 113,5 = ~1,5 lines per tileset. 
        _ms_dlend[X++] = _tiling_Y;
    }

    _ms_vscroll_offset = _tiling_yoffset;
    _ms_vertical_scrolling_adjust_bottom_of_screen();
}
#undef bottom

#endif // __ATARI7800_SPARSE_TILING__
