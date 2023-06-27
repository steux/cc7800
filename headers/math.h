/*
    math.h: A common header for the Atari 7800
    Copyleft 2023 Bruno STEUX 

    This file is distributed as a companion file to cc7800 - a subset of C compiler for the Atari 7800
*/

#ifndef __MATH_H__
#define __MATH_H__

#include "stdlib.h"
#define _tx _libc_tmp
#define _ty _libc_tmp2
#define octant _libc_tmp3
#include "atan2.asm"
inline char _atan2() { asm("jsr _atan2_8"); }
#define atan2(y, x) (_tx = (x), _ty = (y), _atan2())
#undef _tx
#undef _ty

#endif // __MATH_H__

