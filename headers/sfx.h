/*
    sfx.h : Sound effects management for the Atari 7800
    Copyleft 2023 Bruno STEUX

    This file is distributed as a companion file to cc7800 - a subset of C compiler for the Atari 7800
*/

#ifndef __SFX_H__
#define __SFX_H__

#include "prosystem.h"
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
        if (!(_sfx_ptr[0] >> 8)) channel = 1;
        else if (!(_sfx_ptr[1] >> 8)) channel = 2;
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
            _sfx_frames[X] = _sfx_instrument[++Y];
            _sfx_tick[X] = 0;
            _sfx_ptr[X] = _sfx_instrument + 3;
        }
    }
}
#undef channel

void sfx_mute()
{
    _sfx_ptr[0] = NULL;
    _sfx_ptr[1] = NULL;
     for (X = 3; X >= 0; X--)
         AUDF0[X] = 0;
}

// Must be called every frame, regularly (for instance in NMI or at VBLANK)
void sfx_play()
{
    for (X = 0; X != 2; X++) {
        if (_sfx_ptr[X] >> 8) {
            if (!_sfx_tick[X]) {
                // This chunk is over. Load the next one
                _sfx_tick[X] = _sfx_frames[X];
                // Play the sound
                _libc_tmpptr = _sfx_ptr[X];
                AUDF0[X] = _libc_tmp = _libc_tmpptr[Y = 0];
                AUDC0[X] = _libc_tmp2 = _libc_tmpptr[++Y];
                AUDV0[X] = _libc_tmpptr[++Y];
                if (!_libc_tmp && !_libc_tmp2 && !_libc_tmpptr[Y]) {
                    _sfx_ptr[X] = 0;
                } else {
                    _sfx_ptr[X] += 3;
                }
            } else {
                _sfx_tick[X]--;
            }
        }
    }
}

#endif // __SFX_H__

