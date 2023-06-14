/*
    sfx.h : Sound effects management for the Atari 7800
    Copyleft 2023 Bruno STEUX

    This file is distributed as a companion file to cc7800 - a subset of C compiler for the Atari 7800
*/

#ifndef __SFX_H__
#define __SFX_H__

#include "stdlib.h"

char *_sfx_instrument;
ramchip char *_sfx_ptr[2];
ramchip char _sfx_frames[2];
ramchip char _sfx_priority[2];
ramchip char _sfx_tick[2];

void sfx_init()
{
    _sfx_ptr[0] = NULL;
    _sfx_ptr[1] = NULL;
}

#define sfx_schedule(ptr) \
    _sfx_instrument = (ptr); \
    _sfx_schedule();

void _sfx_schedule()
{
#define channel X 
    channel = 0;
    if (_sfx_instrument[Y = 0] == 0x10) { // TIA sound
        if (_sfx_ptr[0] == NULL) channel = 1;
        else if (_sfx_ptr[1] == NULL) channel = 2;
        else if (_sfx_instrument[++Y]) {
            if (_sfx_priority[1] < _sfx_priority[0]) {
                channel = 2;
            } else {
                channel = 1;
            }
        }
        if (channel) {
            X = channel;
            X--;
            _sfx_priority[X] = _sfx_instrument[Y = 1];
            _sfx_frames[X] = _sfx_instrument[--Y];
            _sfx_tick[X] = 0;
            _sfx_ptr[X] = _sfx_instrument + 3;
        }
    }
}
#undef channel


#endif // __SFX_H__

