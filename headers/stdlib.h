/*
    stdlib.h: A common header for the Atari 7800
    Copyleft 2023 Bruno STEUX 

    This file is distributed as a companion file to cc7800 - a subset of C compiler for the Atari 7800
*/

#ifndef __STDLIB_H__
#define __STDLIB_H__

#define NULL 0

char _libc_tmp, _libc_tmp2;
short _libc_tmpshort;
char *_libc_tmpptr, *_libc_tmpptr2;
ramchip char _save_x, _save_y;

#define itoa(val,str,radix) \
    _libc_tmpshort = val; \
    _libc_tmpptr = str; \
    _libc_itoa(); \
    _libc_tmpptr

void _libc_itoa()
{
    _save_x = X;
    _save_y = Y;
    Y = 0;
    X = 0;
    if (_libc_tmpshort < 0) {
        _libc_tmpptr[Y++] = '-';
        _libc_tmpshort = -_libc_tmpshort;
    }
    if (_libc_tmpshort >= 10000) {
        X = '0';
        do {
            X++;
            _libc_tmpshort -= 10000;
        } while (_libc_tmpshort >= 0);
        X--;
        _libc_tmpshort += 10000;
        _libc_tmpptr[Y++] = X;
    }
    if (X || _libc_tmpshort >= 1000) {
        X = '0';
        if (_libc_tmpshort >= 1000) {
            do {
                X++;
                _libc_tmpshort -= 1000;
            } while (_libc_tmpshort >= 0);
            X--;
            _libc_tmpshort += 1000;
        }
        _libc_tmpptr[Y++] = X;
    }
    if (X || _libc_tmpshort >= 100) {
        X = '0';
        if (_libc_tmpshort >= 100) {
            do {
                X++;
                _libc_tmpshort -= 100;
            } while (_libc_tmpshort >= 0);
            X--;
            _libc_tmpshort += 100;
        }
        _libc_tmpptr[Y++] = X;
    }
    _libc_tmp = _libc_tmpshort;
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

// Uses _libc_tmpshort. Don't use it with itoa in the same code
void srand(int seed) {
    _libc_tmpshort = seed;
}

// https://codebase64.org/doku.php?id=base:16bit_xorshift_random_generator 
char rand()
{
    load(_libc_tmpshort >> 8);
    asm("LSR", 1);
    load(_libc_tmpshort);
    asm("ROR", 1);
    asm("EOR _libc_tmpshort+1", 2);
    store(_libc_tmpshort >> 8);
    asm("ROR", 1);
    asm("EOR _libc_tmpshort", 2);
    store(_libc_tmpshort);
    asm("EOR _libc_tmpshort+1", 2);
    store(_libc_tmpshort >> 8);
    return _libc_tmpshort;
}
#endif // __STDLIB_H__

