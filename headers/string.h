/*
    string.h: A common header for the Atari 7800
    Copyleft 2023 Bruno STEUX 

    This file is distributed as a companion file to cc7800 - a subset of C compiler for the Atari 7800
*/

#ifndef __STRING_H__
#define __STRING_H__

#include "stdlib.h"

#define strlen(s) \
    (_libc_tmpptr = (s), _strlen()) \

char _strlen()
{
    _save_y = Y;
    for (Y = 0; _libc_tmpptr[Y]; Y++);
    _libc_tmp = Y;
    Y = _save_y;
    return _libc_tmp;
}

#define memcpy(dest, src, size) \
    _libc_tmpptr = dest; \
    _libc_tmpptr2 = src; \
    _save_y = Y; \
    Y = size; Y--; \
    _memcpy()

void _memcpy()
{
    for (; Y >= 0; Y--) {
        _libc_tmpptr[Y] = _libc_tmpptr2[Y];
    } 
    Y = _save_y;
}

#endif // __STRING_H__

