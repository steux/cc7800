// This file defines hardware registers and memory mapping for the
// Atari 7800 ProSystem. It is distributed as a companion to cc7800.

#ifndef __PROSYSTEM_H__
#define __PROSYSTEM_H__

//  ******************** 7800 Hardware Addresses ***************************
// 
//        MEMORY MAP USAGE OF THE 7800
// 
// 	  00 -   1F	TIA REGISTERS
// 	  20 -   3F	MARIA REGISTERS
// 	  40 -   FF	RAM block 0 (zero page)
// 	 100 -  11F	TIA   (mirror of 0000-001f)
// 	 120 -  13F	MARIA (mirror of 0020-003f)
// 	 140 -  1FF	RAM block 1 (stack)
// 	 200 -  21F	TIA   (mirror of 0000-001f)
// 	 220 -  23F	MARIA (mirror of 0020-003f)
// 	 240 -  27F	???
// 	 280 -  2FF	RIOT I/O ports and timers
// 	 300 -  31F	TIA   (mirror of 0000-001f)
// 	 320 -  33F	MARIA (mirror of 0020-003f)
// 	 340 -  3FF	???
// 	 400 -  47F	unused address space
// 	 480 -  4FF	RIOT RAM
// 	 500 -  57F	unused address space
// 	 580 -  5FF	RIOT RAM (mirror of 0480-04ff)
// 	 600 - 17FF	unused address space
// 	1800 - 203F	RAM
// 	2040 - 20FF	RAM block 0 (mirror of 0000-001f)
// 	2100 - 213F	RAM
// 	2140 - 21FF	RAM block 1 (mirror of 0140-01ff)
// 	2200 - 27FF	RAM
// 	2800 - 2FFF	unavailable to external devices (bios bus-conflict)
// 	3000 - 3FFF	unused address space
// 	4000 - FF7F	potential cartridge address space
// 	FF80 - FFF9	RESERVED FOR ENCRYPTION
// 	FFFA - FFFF 	6502 VECTORS


// ****** 00-1F ********* TIA REGISTERS ******************

unsigned char * const INPTCTRL = 0x01;     // Input control. In same address space as TIA. write-only
unsigned char * const VBLANK   = 0x01;     // VBLANK. D7=1:dump paddle caps to ground.     write-only
unsigned char * const _WSYNC   = 0x02;     // Wait for HSync                               write-only
unsigned char * const _RSYNC   = 0x03;     // Reset HSync                                  write-only
unsigned char * const INPT0    = 0x08;     // Paddle Control Input 0                       read-only
unsigned char * const INPT1    = 0x09;     // Paddle Control Input 1                       read-only
unsigned char * const INPT2    = 0x0A;     // Paddle Control Input 2                       read-only
unsigned char * const INPT3    = 0x0B;     // Paddle Control Input 3                       read-only

//  ** some common alternate names for INPT0/1/2/3
unsigned char * const INPT4B   = 0x08;     // Joystick 0 Fire 1                            read-only
unsigned char * const INPT4A   = 0x09;     // Joystick 0 Fire 1                            read-only
unsigned char * const INPT5B   = 0x0A;     // Joystick 1 Fire 0                            read-only
unsigned char * const INPT5A   = 0x0B;     // Joystick 1 Fire 1                            read-only
unsigned char * const INPT4R   = 0x08;     // Joystick 0 Fire 1                            read-only
unsigned char * const INPT4L   = 0x09;     // Joystick 0 Fire 1                            read-only
unsigned char * const INPT5R   = 0x0A;     // Joystick 1 Fire 0                            read-only
unsigned char * const INPT5L   = 0x0B;     // Joystick 1 Fire 1                            read-only

unsigned char * const INPT4    = 0x0C;     // Player 0 Fire Button Input                   read-only
unsigned char * const INPT5    = 0x0D;     // Player 1 Fire Button Input                   read-only

unsigned char * const AUDC0    = 0x15;     // Audio Control Channel   0                    write-only
unsigned char * const AUDC1    = 0x16;     // Audio Control Channel   1                    write-only
unsigned char * const AUDF0    = 0x17;     // Audio Frequency Channel 0                    write-only
unsigned char * const AUDF1    = 0x18;     // Audio Frequency Channel 1                    write-only
unsigned char * const AUDV0    = 0x19;     // Audio Volume Channel    0                    write-only
unsigned char * const AUDV1    = 0x1A;     // Audio Volume Channel    1                    write-only

// ****** 20-3F ********* MARIA REGISTERS ***************

unsigned char * const BACKGRND = 0x20;     // Background Color                             write-only
unsigned char * const P0C1     = 0x21;     // Palette 0 - Color 1                          write-only
unsigned char * const P0C2     = 0x22;     // Palette 0 - Color 2                          write-only
unsigned char * const P0C3     = 0x23;     // Palette 0 - Color 3                          write-only
unsigned char * const WSYNC    = 0x24;     // Wait For Sync                                write-only
unsigned char * const P1C1     = 0x25;     // Palette 1 - Color 1                          write-only
unsigned char * const P1C2     = 0x26;     // Palette 1 - Color 2                          write-only
unsigned char * const P1C3     = 0x27;     // Palette 1 - Color 3                          write-only
unsigned char * const MSTAT    = 0x28;     // Maria Status                                 read-only
unsigned char * const P2C1     = 0x29;     // Palette 2 - Color 1                          write-only
unsigned char * const P2C2     = 0x2A;     // Palette 2 - Color 2                          write-only
unsigned char * const P2C3     = 0x2B;     // Palette 2 - Color 3                          write-only
unsigned char * const DPPH     = 0x2C;     // Display List List Pointer High               write-only
unsigned char * const P3C1     = 0x2D;     // Palette 3 - Color 1                          write-only
unsigned char * const P3C2     = 0x2E;     // Palette 3 - Color 2                          write-only
unsigned char * const P3C3     = 0x2F;     // Palette 3 - Color 3                          write-only
unsigned char * const DPPL     = 0x30;     // Display List List Pointer Low                write-only
unsigned char * const P4C1     = 0x31;     // Palette 4 - Color 1                          write-only
unsigned char * const P4C2     = 0x32;     // Palette 4 - Color 2                          write-only
unsigned char * const P4C3     = 0x33;     // Palette 4 - Color 3                          write-only
unsigned char * const CHARBASE = 0x34;     // Character Base Address                       write-only
unsigned char * const CHBASE   = 0x34;     // Character Base Address                       write-only
unsigned char * const P5C1     = 0x35;     // Palette 5 - Color 1                          write-only
unsigned char * const P5C2     = 0x36;     // Palette 5 - Color 2                          write-only
unsigned char * const P5C3     = 0x37;     // Palette 5 - Color 3                          write-only
unsigned char * const OFFSET   = 0x38;     // Unused - Store zero here                     write-only
unsigned char * const P6C1     = 0x39;     // Palette 6 - Color 1                          write-only
unsigned char * const P6C2     = 0x3A;     // Palette 6 - Color 2                          write-only
unsigned char * const P6C3     = 0x3B;     // Palette 6 - Color 3                          write-only
unsigned char * const CTRL     = 0x3C;     // Maria Control Register                       write-only
unsigned char * const P7C1     = 0x3D;     // Palette 7 - Color 1                          write-only
unsigned char * const P7C2     = 0x3E;     // Palette 7 - Color 2                          write-only
unsigned char * const P7C3     = 0x3F;     // Palette 7 - Color 3                          write-only


// ****** 280-2FF ******* PIA PORTS AND TIMERS ************

unsigned char * const SWCHA    = 0x280;    // P0+P1 Joystick Directional Input             read-write
unsigned char * const CTLSWA   = 0x281;    // I/O Control for SCHWA                        read-write
unsigned char * const SWACNT   = 0x281;    // VCS name for above                           read-write
unsigned char * const SWCHB    = 0x282;    // Console Switches                             read-write
unsigned char * const CTLSWB   = 0x283;    // I/O Control for SCHWB                        read-write
unsigned char * const SWBCNT   = 0x283;    // VCS name for above                           read-write

unsigned char * const INTIM    = 0x284;    // Interval Timer Read                          read-only
unsigned char * const TIM1T    = 0x294;    // Set 1    CLK Interval (838   nsec/interval)  write-only
unsigned char * const TIMINT   = 0x295;    // Interval Timer Interrupt                     read-only
unsigned char * const TIM8T    = 0x295;    // Set 8    CLK Interval (6.7   usec/interval)  write-only
unsigned char * const TIM64T   = 0x296;    // Set 64   CLK Interval (63.6  usec/interval)  write-only
unsigned char * const T1024T   = 0x297;    // Set 1024 CLK Interval (858.2 usec/interval)  write-only
unsigned char * const TIM64TI  = 0x29E;    // Interrupt timer 64T                          write-only

// XM
unsigned char * const XCTRL    = 0x470;    // 7=YM2151 6=RAM@6k 5=RAM@4k 4=pokey@450 3=hsc 2=cart 1=RoF_bank1 0=RoF_bank2
unsigned char * const XCTRL1   = 0x470;
unsigned char * const XCTRL2   = 0x478;
unsigned char * const XCTRL3   = 0x47c;
unsigned char * const XCTRL4   = 0x471;
unsigned char * const XCTRL5   = 0x472;

//  Pokey register relative locations, since its base may be different
//  depending on the hardware.
const unsigned char PAUDF0   = 0x0;    // Eextra audio channels and frequencies
const unsigned char PAUDC0   = 0x1;
const unsigned char PAUDF1   = 0x2;
const unsigned char PAUDC1   = 0x3;
const unsigned char PAUDF2   = 0x4;
const unsigned char PAUDC2   = 0x5;
const unsigned char PAUDF3   = 0x6;
const unsigned char PAUDC3   = 0x7;
const unsigned char PAUDCTL  = 0x8;    // Audio Control
const unsigned char PSTIMER  = 0x9;
const unsigned char PRANDOM  = 0xA;    // 17 bit polycounter pseudo random
const unsigned char PSKCTL   = 0xF;    // Serial Port control

#endif // __PROSYSTEM_H__
