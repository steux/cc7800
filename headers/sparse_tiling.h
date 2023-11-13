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

#define SPARSE_TILING_SCROLLING_ZONE (_MS_DLL_ARRAY_SIZE - _MS_BOTTOM_SCROLLING_ZONE - 1)
ramchip char *_tiling_ptr[SPARSE_TILING_SCROLLING_ZONE];
ramchip signed char _tiling_xpos[2 * SPARSE_TILING_SCROLLING_ZONE], _tiling_xoffset[2 * SPARSE_TILING_SCROLLING_ZONE];

#ifdef MULTISPRITE_USE_VIDEO_MEMORY
ramchip char _sparse_tiling_vmem_ptr_low, _sparse_tiling_vmem_ptr_high, _sparse_tiling_charbase;
#define IDATA_MAX 5
ramchip char *_st_idata[IDATA_MAX * SPARSE_TILING_SCROLLING_ZONE];
const char _st_idata_idx[_MS_DLL_ARRAY_SIZE] = { 0, IDATA_MAX, IDATA_MAX * 2, IDATA_MAX * 3, IDATA_MAX * 4, IDATA_MAX * 5, IDATA_MAX * 6, IDATA_MAX * 7, IDATA_MAX * 8, IDATA_MAX * 9, IDATA_MAX * 10, IDATA_MAX * 11, IDATA_MAX * 12, IDATA_MAX * 13, IDATA_MAX * 14 };
ramchip char _st_idata_size[SPARSE_TILING_SCROLLING_ZONE];

bank1 char multisprite_vmem[8192]; // Video memory in RAM
bank1 const char sparse_tiling_vmem_use_rom[] = {1};

#define sparse_tiling_init_vmem(ptr, tiles_ptr) \
{ \
    _ms_sparse_tiles_ptr_high = ptr[Y = 0]; \
    _ms_sparse_tiles_ptr_low = ptr[Y = 1]; \
    _sparse_tiling_charbase = (tiles_ptr) >> 8; \
    _sparse_tiling_vmem_ptr_low = 0x00; \
    _sparse_tiling_vmem_ptr_high = 0x40; \
    _sparse_tiling_init(); \
} 
#else
#define sparse_tiling_init(ptr) \
    _ms_sparse_tiles_ptr_high = ptr[Y = 0]; \
    _ms_sparse_tiles_ptr_low = ptr[Y = 1]; \
    _sparse_tiling_init()
#endif

void _sparse_tiling_init()
{
    char *ptr;
    for (Y = _MS_DLL_ARRAY_SIZE - 2 - _MS_BOTTOM_SCROLLING_ZONE; Y >= 0; Y--) {
        ptr = _ms_sparse_tiles_ptr_low[Y] | (_ms_sparse_tiles_ptr_high[Y] << 8);   
        _tiling_ptr[Y] = ptr;
    }
    for (X = 2 * (_MS_DLL_ARRAY_SIZE - _MS_BOTTOM_SCROLLING_ZONE - 1) - 1; X >= 0; X--) {
        _tiling_xpos[X] = 0;
        _tiling_xoffset[X] = 0;
    }
#ifdef MULTISPRITE_USE_VIDEO_MEMORY
    for (X = SPARSE_TILING_SCROLLING_ZONE - 1; X >= 0; X--) {
        _st_idata_size[X] = 0;     
    }
#endif
}

#ifdef MULTISPRITE_USE_VIDEO_MEMORY
void _sparse_tiling_ROM_to_RAM(char *tmpptr, char w, char mode)
{

}

void _sparse_tiling_load_line(signed char y)
{
    char *ptr, data[5];
    char *tmpptr, x, linedl, txpos, xoffset;
    signed char right, r, d;
    char st_idata_idx, st_idata_size;
    char tileset_counter = 0;
    char mode, w;
     
    if (_ms_buffer) {
        X = y + (_MS_DLL_ARRAY_SIZE - _MS_BOTTOM_SCROLLING_ZONE - 1);
        linedl = y + _MS_DLL_ARRAY_SIZE;
    } else {
        X = y;
        linedl = y;
    }
    txpos = _tiling_xpos[X]; 
    xoffset = _tiling_xoffset[X]; 
    right = txpos + 22;
    ptr = _tiling_ptr[Y = y];
    st_idata_idx = _st_idata_idx[Y];
    st_idata_size = _st_idata_size[Y];
    _ms_tmpptr = _ms_dls[X = linedl];
    // Find the first visible tileset on this line, if any
    Y = 0;
    do {
        w = ptr[Y];
        // Check if it's the last tileset
        if (w == 96) {
            if (ptr[++Y] == 0xff) {
                return;
            } else Y--;
        }
        r = w - txpos;
        if (r >= 0) break;
        // Go to next tileset
        Y += _STS_SIZE;
        // Remove it from video memory
        for (X = st_idata_idx + st_idata_size; X > st_idata_idx; X--) {
            tmpptr = _st_idata[X];
            _st_idata[--X] = tmpptr;
            X++;
        }
        if (st_idata_size) st_idata_size--;
    } while (1);
    X = y; 
    if (Y) { // Update the pointer
        _tiling_ptr[X] += Y;
    }
    Y++; // Next byte
    x = _ms_dlend_save[X];
    data[4] = ptr[Y];
    w = w - data[4] + 1;
    // First one: maybe is this too much on the left ?
    d = right - data[4];
    if (d >= 0) {
        
        signed char xpos = data[4] - txpos;
        
        // Is it already transferred to video memory ?
        if (tileset_counter < st_idata_size) {
            // Yes. Let's get the matching pointer
            _save_y = Y;
            Y = _st_idata_idx + tileset_counter;
            tmpptr = _st_idata[Y];
            Y = _save_y;
            data[0] = tmpptr; ++Y;
            data[1] = ptr[++Y] & 0xc0; // Remove immediate mode bit
            mode = data[1] & 0x80;
            data[2] = tmpptr >> 8; ++Y;
        } else {
            // Let's transfer from ROM to RAM
            data[0] = ptr[++Y]; 
            data[1] = ptr[++Y] & 0xc0; // Remove immediate mode bit
            mode = data[1] & 0x80;
            tmpptr = data[0] | (ptr[++Y] << 8);
            // Store the pointer for this tileset_counter
            _sparse_tiling_ROM_to_RAM(tmpptr, w, mode);
            data[0] = _sparse_tiling_vmem_ptr_low;
            data[2] = _sparse_tiling_vmem_ptr_high;
            _save_y = Y;
            Y = _st_idata_idx + tileset_counter;
            _st_idata[Y] = _sparse_tiling_vmem_ptr_low | (_sparse_tiling_vmem_ptr_high << 8);
            st_idata_size++;
            Y = _save_y;
        }

        if (xpos < 0) { // Reduce the length of this tileset so that is doesn't get out of screen on the left
            w += xpos;
            xpos = (mode)?(xpos << 2):(xpos << 1); 
            // Advance pointer
            if (data[0] >= xpos) data[2]++;
            data[0] -= xpos;
            xpos = 0;
        } else if (r >= 24) { // Reduce the length of this tileset so that it doesn't get out of screen on the right
            w -= (r - 24); 
        }
        data[3] = ptr[++Y];
        w = (mode)?(w << 2):(w << 1); 

        ++Y;
        _save_y = Y;
        Y = x; // 6 cycles
        _ms_tmpptr[Y++] = data[0]; // 11 cycles
        _ms_tmpptr[Y++] = data[1];
        _ms_tmpptr[Y++] = data[2];
        _ms_tmpptr[Y++] = ((-w) & 0x1f) | (data[3] & 0xe0);
        _ms_tmpptr[Y++] = (xpos << 3) - xoffset;
        x = Y; // 21 cycles
        Y = _save_y;

        r = ptr[++Y];
        data[4] = ptr[++Y];
        w = r - data[4] + 1;
        d = right - data[4];

        // TODO: Modify second part according to first
        while (d >= 0) {
            // Check termination
            if (r == 96 && data[4] == 0xff) break;
            
            tileset_counter++;
            r -= txpos;

            data[0] = ptr[++Y]; // 10 cycles
            data[1] = ptr[++Y];
            data[2] = ptr[++Y];
            data[3] = ptr[++Y];
            if (r >= 24) { // Reduce the length of this tileset so that it doesn't get out of screen on the right
                data[3] = ((data[4] - txpos - 23) & 0x1f) | (data[3] & 0xe0); 
            } 
            ++Y;
            _save_y = Y;
            Y = x; // 6 cycles
            _ms_tmpptr[Y++] = data[0]; // 11 cycles
            _ms_tmpptr[Y++] = data[1];
            _ms_tmpptr[Y++] = data[2];
            _ms_tmpptr[Y++] = data[3];
            _ms_tmpptr[Y++] = ((data[4] - txpos) << 3) - xoffset;
            x = Y; // 21 cycles
            Y = _save_y;

            r = ptr[++Y];
            data[4] = ptr[++Y];
            w = r - data[4] + 1;
            d = right - data[4];
        } 
    } 
    _ms_dlend[X = linedl] = x;
    _ms_dlend_save_overlay[X] = x;
    _st_idata_size[Y = y] = st_idata_size; // Store the updated immediate data size
}
#else
void _sparse_tiling_load_line(signed char y)
{
    char *ptr, data[5];
    char x, linedl, txpos, xoffset;
    signed char right, r, d;
 
    if (_ms_buffer) {
        X = y + (_MS_DLL_ARRAY_SIZE - _MS_BOTTOM_SCROLLING_ZONE - 1);
        linedl = y + _MS_DLL_ARRAY_SIZE;
    } else {
        X = y;
        linedl = y;
    }
    txpos = _tiling_xpos[X]; 
    xoffset = _tiling_xoffset[X]; 
    right = txpos + 22;
    ptr = _tiling_ptr[Y = y];
    _ms_tmpptr = _ms_dls[X = linedl];
    // Find the first visible tileset on this line, if any
    Y = 0;
    do {
        // Check if it's the last tileset
        if (ptr[Y] == 96) {
            if (ptr[++Y] == 0xff) {
                return;
            } else Y--;
        }
        r = ptr[Y] - txpos;
        if (r >= 0) break;
        Y += _STS_SIZE;
    } while (1);
    X = y; 
    if (Y) { // Update the pointer
        _tiling_ptr[X] += Y;
    }
    Y++; // Next byte
    x = _ms_dlend_save[X];
    data[4] = ptr[Y];
    // First one: maybe is this too much on the left ?
    d = right - data[4];

    if (d >= 0) {
        data[0] = ptr[++Y]; // 10 cycles
        data[1] = ptr[++Y];
        data[2] = ptr[++Y];
        data[3] = ptr[++Y];
        signed char xpos = data[4] - txpos;
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
        _ms_tmpptr[Y++] = (xpos << 3) - xoffset;
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
            _ms_tmpptr[Y++] = ((data[4] - txpos) << 3) - xoffset;
            x = Y; // 21 cycles
            Y = _save_y;

            r = ptr[++Y];
            data[4] = ptr[++Y];
            d = right - data[4];
        } 
    } 
    _ms_dlend[X = linedl] = x;
    _ms_dlend_save_overlay[X] = x;
}
#endif

char sparse_tiling_collision(char top, char left, char right)
{
    char *ptr, intersect = -1, start, end, txpos, xoffset;
    signed char xrc;
    char lc = left >> 3;
    char rc = right >> 3;
    char y = top >> 4;
    if (_ms_buffer) {
        X = y + (_MS_DLL_ARRAY_SIZE - _MS_BOTTOM_SCROLLING_ZONE - 1);
    } else {
        X = y;
    }
    txpos = _tiling_xpos[X]; 
    xoffset = _tiling_xoffset[X]; 
    ptr = _tiling_ptr[Y = y];
    // Find the first possibly intersecting tileset on this line
    Y = 0;
    do {
        // Check if it's the last tileset
        if (ptr[Y] == 96) {
            if (ptr[++Y] == 0xff) {
                return -1; // No intersection possible
            } else Y--;
        }
        xrc = ptr[Y] - txpos;
        if (xrc >= lc) break;
        Y += _STS_SIZE;
    } while (1);
    // This one possibly intersects
    end = (xrc << 3) - xoffset;
    Y++;
    xrc = ptr[Y++] - txpos;
    if (rc < xrc - 1) return -1;
    start = (xrc << 3) - xoffset;
    while (right >= start) {
        char l = (left < start)?start:left;
        char r = (end < right)?end:right;
        char n = r - l;
        if (n >= 0) {
            n >>= 3;
            char tmp = ptr[Y++];
            Y++;
            char *ptr_tiles = tmp | (ptr[Y] << 8);
            _save_y = Y;
            Y = (l - start) >> 3;
            for (X = n; X >= 0; Y++, X--) {
                if (ptr_tiles[Y] < intersect) intersect = ptr_tiles[Y];    
            }
            Y = _save_y;
        } else {
            Y += 2;
        }
        Y += 3;
        if (ptr[Y] == 96) {
            if (ptr[++Y] == 0xff) {
               break; 
            } else Y--;
        }
        end = ((ptr[Y++] - txpos) << 3) - xoffset;
        xrc = ptr[Y++] - txpos;
        if (rc < xrc - 1) return intersect;
        start = (xrc << 3) - xoffset;
    }
    return intersect;
}

void sparse_tiling_display()
{ 
    signed char y;    
    for (y = _MS_DLL_ARRAY_SIZE - 2 - _MS_BOTTOM_SCROLLING_ZONE; y >= 0; y--) { 
        _sparse_tiling_load_line(y); 
    } 
}

void sparse_tiling_scroll(char offset)
{
    signed char y;
    char yy, linedl;
    char lines_moved = 0;    
    /*
    if (_tiling_xoffset[X] >= 8) {
        _tiling_xoffset[X] -= 8;
        _tiling_xpos[X]++;
        multisprite_clear_overlay();
        sparse_tiling_display();
        multisprite_save_overlay();
    }
    */
    
    if (_ms_buffer) {
        yy = 2 * (_MS_DLL_ARRAY_SIZE - _MS_BOTTOM_SCROLLING_ZONE - 1) - 1;
        linedl = _MS_DLL_ARRAY_SIZE - 2 - _MS_BOTTOM_SCROLLING_ZONE + _MS_DLL_ARRAY_SIZE;
    } else {
        yy = _MS_DLL_ARRAY_SIZE - 2 - _MS_BOTTOM_SCROLLING_ZONE;
        linedl = _MS_DLL_ARRAY_SIZE - 2 - _MS_BOTTOM_SCROLLING_ZONE;
    }

    for (y = _MS_DLL_ARRAY_SIZE - 2 - _MS_BOTTOM_SCROLLING_ZONE; y >= 0; yy--, linedl--, y--) {
        X = yy;
        _tiling_xoffset[X] += offset;
        if (_tiling_xoffset[X] >= 16 && lines_moved < 3) {
            do {
                _tiling_xoffset[X] -= 16;
                _tiling_xpos[X] += 2;
            } while (_tiling_xoffset[X] >= 16);
            _sparse_tiling_load_line(y);
            lines_moved++;
        } else {
            // Apply this offset to all the tilesets in overlay
            _ms_tmpptr = _ms_dls[X = linedl];
            Y = _ms_dlend_save[X = y]; 
            X = linedl;
            while (Y < _ms_dlend[X]) {
                if ((_ms_tmpptr[++Y] & 0x1f) == 0) {
                    // This is an extended header
                    Y++;
                }
                Y++; Y++;
                _ms_tmpptr[Y] -= offset; 
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
