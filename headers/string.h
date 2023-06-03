/*
    string.h: A common header for the Atari 7800
    Copyleft 2023 Bruno STEUX 

    This file is distributed as a companion file to cc7800 - a subset of C compiler for the Atari 7800
*/

#ifndef __STRING_H__
#define __STRING_H__

#include "stdlib.h"

#define strlen(s) \
    _libc_tmpptr = (s), _strlen() \

char _strlen()
{
    for (Y = 0; _libc_tmpptr[Y]; Y++);
    _libc_tmp = Y;
    return _libc_tmp;
}

#endif // __STRING_H__

