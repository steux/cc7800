/*
    joystick.h : Joystick management for the Atari 7800
    Copyleft 2023 Bruno STEUX 

    This file is distributed as a companion file to cc7800 - a subset of C compiler for the Atari 7800
*/

#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

ramchip char joystick[2];

#define JOYSTICK_UP     1
#define JOYSTICK_DOWN   2
#define JOYSTICK_LEFT   4
#define JOYSTICK_RIGHT  8
#define JOYSTICK_BUTTON1 64
#define JOYSTICK_BUTTON2 128
#define JOYSTICK_HAS_TWO_BUTTONS 32

#ifndef INIT_BANK
#define INIT_BANK
#endif

INIT_BANK void joystick_init()
{
    *CTLSWA = 0; // Port A as input
    *CTLSWB = 0x14; // Prepare for 2 buttons joystick
    *SWCHB = 0; // Output 0 on bits 2 and 4 of port B
    joystick[0] = JOYSTICK_HAS_TWO_BUTTONS;
    joystick[1] = JOYSTICK_HAS_TWO_BUTTONS;
}

void joystick_update()
{
    joystick[1] = ~*SWCHA;
    // Player 0
    joystick[0] &= JOYSTICK_HAS_TWO_BUTTONS;
    joystick[0] |= (joystick[1] >> 4);
    if (!(*INPT4 & 0x80)) {
        // This is a single button joystick.
        if (joystick[0] & JOYSTICK_HAS_TWO_BUTTONS) {
            *SWCHB |= 4; // In order to protect the console
        }
        joystick[0] = JOYSTICK_BUTTON1;
    } else if (joystick[0] & JOYSTICK_HAS_TWO_BUTTONS) {
        if (*INPT1 & 0x80) {
            joystick[0] |= JOYSTICK_BUTTON1;
        }
        if (*INPT0 & 0x80) {
            joystick[0] |= JOYSTICK_BUTTON2;
        }
    }
    // Player 1
    joystick[1] &= JOYSTICK_HAS_TWO_BUTTONS | 0x0f;
    if (!(*INPT5 & 0x80)) {
        // This is a single button joystick.
        if (joystick[1] & JOYSTICK_HAS_TWO_BUTTONS) {
            *SWCHB |= 0x10; // In order to protect the console
        }
        joystick[1] = JOYSTICK_BUTTON1;
    } else if (joystick[1] & JOYSTICK_HAS_TWO_BUTTONS) {
        if (*INPT3 & 0x80) {
            joystick[1] |= JOYSTICK_BUTTON1;
        }
        if (*INPT2 & 0x80) {
            joystick[1] |= JOYSTICK_BUTTON2;
        }
    }
}

#endif
