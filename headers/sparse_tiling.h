/*
    sparse_tiling.h: tiling display for the Atari 7800
    Copyleft 2023 Bruno STEUX 

    This file is distributed as a companion file to cc7800 - a subset of C compiler for the Atari 7800
*/

#ifndef __ATARI7800_SPARSE_TILING__
#define __ATARI7800_SPARSE_TILING__

#define _STS_SIZE 7
// SPS (Sparse Tileset Struct: 
//    X end of tileset (included)
//    X beginning of tileset
//    Low Address
//    Mode byte
//    High address
//    Palette & Width
//    DMA cost

#ifdef HORIZONTAL_SCROLLING
#define MULTISPRITE_OVERLAY
#include "multisprite.h"

#ifndef _MS_BOTTOM_SCROLLING_ZONE
#define _MS_BOTTOM_SCROLLING_ZONE 0
#endif

ramchip char *_tiling_ptr[_MS_DLL_ARRAY_SIZE - _MS_BOTTOM_SCROLLING_ZONE - 1];
ramchip signed char _tiling_xpos[2], _tiling_xoffset[2];

#define sparse_tiling_init(ptr) \
    _ms_sparse_tiles_ptr_high = ptr[Y = 0]; \
    _ms_sparse_tiles_ptr_low = ptr[Y = 1]; \
    _sparse_tiling_init()

void _sparse_tiling_init()
{
    char *ptr;
    for (Y = _MS_DLL_ARRAY_SIZE - 2 - _MS_BOTTOM_SCROLLING_ZONE; Y >= 0; Y--) {
        ptr = _ms_sparse_tiles_ptr_low[Y] | (_ms_sparse_tiles_ptr_high[Y] << 8);   
        _tiling_ptr[Y] = ptr;
    }
    _tiling_xpos[X = 0] = 0;
    _tiling_xoffset[X] = 0;
    _tiling_xoffset[++X] = 0;
    _tiling_xpos[X] = 0;
}

void sparse_tiling_display()
{
    char *ptr, data[5];
    signed char y, right;
    char x, linedb, txpos = _tiling_xpos[X = _ms_buffer];

    right = txpos + 22;
    for (y = _MS_DLL_ARRAY_SIZE - 2 - _MS_BOTTOM_SCROLLING_ZONE; y >= 0; y--) {
        signed char r, d;
        char skip = 0;
        ptr = _tiling_ptr[Y = y];
        linedb = (_ms_buffer)?(y + _MS_DLL_ARRAY_SIZE):y;
        _ms_tmpptr = _ms_dls[X = linedb];
        // Find the first visible tileset on this line, if any
        Y = 0;
        do {
            // Check if it's the last tileset
            if (ptr[Y] == 96) {
                if (ptr[++Y] == 0xff) {
                    skip = 1;
                    break;
                } else Y--;
            }
            r = ptr[Y] - txpos;
            if (r >= 0) break;
            Y += _STS_SIZE;
        } while (1);
        if (skip) continue;
        if (Y) { // Update the pointer
            x = Y;
            _tiling_ptr[X = y] += x;
        }
        Y++; // Next byte
        x = _ms_dlend[X = linedb];
        data[4] = ptr[Y];
        // First one: maybe is this too much on the left ?
        d = right - data[4];
        
        if (d >= 0) {
            char off;
            data[0] = ptr[++Y]; // 10 cycles
            data[1] = ptr[++Y];
            data[2] = ptr[++Y];
            data[3] = ptr[++Y];
            char xpos = data[4] - txpos;
            if (xpos < 0) { // Reduce the length of this tileset so that is doesn't get out of screen on the left
                data[3] = (((data[3] | 0xe0) - xpos) & 0x1f) | (data[3] & 0xe0); 
                // Advance pointer
                if (data[0] >= xpos) data[2]++;
                data[0] -= xpos;
                xpos = 0;
            }
            if (r >= 24) { // Reduce the length of this tileset so that it doesn't get out of screen on the right
                data[3] = ((xpos - 23) & 0x1f) | (data[3] & 0xe0); 
            } 
#ifdef DMA_CHECK 
            _ms_dldma[X] -= ptr[++Y]; // 18 cycles
#else
            ++Y;
#endif
            _save_y = Y;
            Y = x; // 6 cycles
            _ms_tmpptr[Y++] = data[0]; // 11 cycles
            _ms_tmpptr[Y++] = data[1];
            _ms_tmpptr[Y++] = data[2];
            _ms_tmpptr[Y++] = data[3];
            _ms_tmpptr[Y++] = xpos << 3;
            x = Y; // 21 cycles
            Y = _save_y;
            
            r = ptr[++Y];
            data[4] = ptr[++Y];
            d = right - data[4];
            
            while (d >= 0) {
                // Check termination
                if (r == 96 && data[4] == 0xff) break;
                r -= txpos;

                data[0] = ptr[++Y]; // 10 cycles
                data[1] = ptr[++Y];
                data[2] = ptr[++Y];
                data[3] = ptr[++Y];
                if (r >= 24) { // Reduce the length of this tileset so that it doesn't get out of screen on the right
                    data[3] = ((data[4] - txpos - 23) & 0x1f) | (data[3] & 0xe0); 
                    //data[3] = (((data[3] | 0xe0) + (21 - r)) & 0x1f) | (data[3] & 0xe0); 
                } 
#ifdef DMA_CHECK 
                _ms_dldma[X] -= ptr[++Y]; // 18 cycles
#else
                ++Y;
#endif
                _save_y = Y;
                Y = x; // 6 cycles
                _ms_tmpptr[Y++] = data[0]; // 11 cycles
                _ms_tmpptr[Y++] = data[1];
                _ms_tmpptr[Y++] = data[2];
                _ms_tmpptr[Y++] = data[3];
                _ms_tmpptr[Y++] = ((data[4] - txpos) << 3);
                x = Y; // 21 cycles
                Y = _save_y;
            
                r = ptr[++Y];
                data[4] = ptr[++Y];
                d = right - data[4];
            } 
        } 
        _ms_dlend[X = linedb] = x;
    }
}

void sparse_tiling_scroll(char offset)
{
    signed char y;
    _tiling_xoffset[X = _ms_buffer] += offset;
    if (_tiling_xoffset[X] >= 8) {
        _tiling_xoffset[X] -= 8;
        _tiling_xpos[X]++;
        multisprite_clear_overlay();
        sparse_tiling_display();
        multisprite_save_overlay();
    }
    if (_tiling_xoffset[X]) {
        char xoffset = _tiling_xoffset[X];
        // Apply this offset to all the tilesets in overlay
        for (y = _MS_DLL_ARRAY_SIZE - 2 - _MS_BOTTOM_SCROLLING_ZONE; y >= 0; y--) {
            if (_ms_buffer) {
                _ms_tmpptr = _ms_dls[X = y + _MS_DLL_ARRAY_SIZE];
            } else {
                _ms_tmpptr = _ms_dls[X = y];
            }
            Y = _ms_dlend_save[X = y]; 
            while (Y < _ms_dlend[X]) {
                if ((_ms_tmpptr[++Y] & 0x1f) == 0) {
                    // This is an extended header
                    Y++;
                }
                Y++; Y++;
                _ms_tmpptr[Y] = ((_ms_tmpptr[Y] + 7) & 0xf8) - xoffset; 
                Y++;
            }
        }
    }
}

#else
#define VERTICAL_SCROLLING
#include "multisprite.h"

#define sparse_tiling_init(ptr) \
    _ms_sparse_tiles_ptr_high = ptr[Y = 0]; \
    _ms_sparse_tiles_ptr_low = ptr[Y = 1];

ramchip signed char _tiling_xpos, _tiling_ypos, _tiling_xoffset, _tiling_yoffset, _tiling_left, _tiling_right;

#define sparse_tiling_goto(x, y) \
    _ms_tmp = x; \
    _tiling_xpos = (((x) >> 8) << 5) | (_ms_tmp >> 3); \
    _tiling_xoffset = (x) & 7; \
    _ms_tmp = y; \
    _tiling_ypos = ((((y) >> 8)) << 4) | (_ms_tmp >> 4); \
    _tiling_yoffset = (y) & 0xf; \
    _sparse_tiling_goto()

void _sparse_tiling_goto()
{
    char *ptr, data[5], y, tmp, bottom;

    // Skip the lines on top
    _ms_tmp = _MS_TOP_SCROLLING_ZONE;
    _ms_tmp2 = _tiling_ypos;
    if (_tiling_ypos < 0) {
        _ms_tmp -= _tiling_ypos;
        _ms_tmp2 = 0;
    }
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
        Y = _ms_tmp2;
        tmp = _ms_sparse_tiles_ptr_low[Y];
        ptr = tmp | (_ms_sparse_tiles_ptr_high[Y] << 8);   
        _ms_tmpptr = _ms_dls[X];
        // Find the first visible tileset on this line, if any
        Y = 0;
        do {
            _tiling_left = ptr[Y];
            if (_tiling_left >= _tiling_xpos) break;
            Y += _STS_SIZE;
        } while (1);
        Y++; // Next byte
        y = _ms_dlend[X];
        data[4] = ptr[Y];
        while (data[4] < _tiling_right) { // 9 cycles
            data[0] = ptr[++Y]; // 10 cycles
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
            _ms_tmpptr[Y++] = ((data[4] - _tiling_xpos) << 3) - _tiling_xoffset; // 29 cycles
            y = Y; // 21 cycles
            Y = _save_y;
            Y++;
            data[4] = ptr[++Y];
        } // 167 cycles per tileset / 113,5 = ~1,5 lines per tileset. 
        _ms_dlend[X++] = y;
    }

    _ms_vscroll_fine_offset = _tiling_yoffset;
    _ms_vertical_scrolling_adjust_bottom_of_screen();
}
#endif // HORIZONTAL_SCROLLING
#endif // __ATARI7800_SPARSE_TILING__
