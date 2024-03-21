/*
    stdlib.h: A common header for the Atari 7800
    Copyleft 2023 Bruno STEUX 

    This file is distributed as a companion file to cc7800 - a subset of C compiler for the Atari 7800
*/

#ifndef __STDLIB_H__
#define __STDLIB_H__

#define NULL 0

char _libc_tmp, _libc_tmp2;
char *_libc_tmpptr, *_libc_tmpptr2;
ramchip char _save_x, _save_y;

#define itoa(val,str,radix) \
    _libc_tmpptr = str; \
    _libc_itoa(val); \
    _libc_tmpptr

void _libc_itoa(short val)
{
    _save_x = X;
    _save_y = Y;
    Y = 0;
    X = 0;
    if (val < 0) {
        _libc_tmpptr[Y++] = '-';
        val = -val;
    }
    if (val >= 10000) {
        X = '0';
        do {
            X++;
            val -= 10000;
        } while (val >= 0);
        X--;
        val += 10000;
        _libc_tmpptr[Y++] = X;
    }
    if (X || val >= 1000) {
        X = '0';
        if (val >= 1000) {
            do {
                X++;
                val -= 1000;
            } while (val >= 0);
            X--;
            val += 1000;
        }
        _libc_tmpptr[Y++] = X;
    }
    if (X || val >= 100) {
        X = '0';
        if (val >= 100) {
            do {
                X++;
                val -= 100;
            } while (val >= 0);
            X--;
            val += 100;
        }
        _libc_tmpptr[Y++] = X;
    }
    _libc_tmp = val;
    if (X || _libc_tmp >= 10) {
        X = '0';
        if (_libc_tmp >= 10) {
            do {
                X++;
                _libc_tmp -= 10;
            } while (_libc_tmp >= 0);
            X--;
            _libc_tmp += 10;
        }
        _libc_tmpptr[Y++] = X;
    }
    _libc_tmpptr[Y++] = '0' + _libc_tmp;
    _libc_tmpptr[Y] = 0;
    X = _save_x;
    Y = _save_y;
}

short _libc_rand;

void srand(int seed) {
    _libc_rand = seed;
}

// https://codebase64.org/doku.php?id=base:16bit_xorshift_random_generator 
char rand()
{
    load(_libc_rand >> 8);
    asm("LSR", 1);
    load(_libc_rand);
    asm("ROR", 1);
    asm("EOR _libc_rand+1", 2);
    store(_libc_rand >> 8);
    asm("ROR", 1);
    asm("EOR _libc_rand", 2);
    store(_libc_rand);
    asm("EOR _libc_rand+1", 2);
    store(_libc_rand >> 8);
    return _libc_rand;
}
#endif // __STDLIB_H__

