// This file defines hardware registers and memory mapping for the
// Atari 7800 ProSystem. It is distributed as a companion to cc7800.

#ifndef __MARIA_PLUS_H__
#define __MARIA_PLUS_H__

// ****** 120-13F ********* MARIA REGISTERS ***************

unsigned char * const MP1_P0C1     = 0x121;     // Palette 0 - Color 1                          write-only
unsigned char * const MP1_P0C2     = 0x122;     // Palette 0 - Color 2                          write-only
unsigned char * const MP1_P0C3     = 0x123;     // Palette 0 - Color 3                          write-only
unsigned char * const MP1_P1C1     = 0x125;     // Palette 1 - Color 1                          write-only
unsigned char * const MP1_P1C2     = 0x126;     // Palette 1 - Color 2                          write-only
unsigned char * const MP1_P1C3     = 0x127;     // Palette 1 - Color 3                          write-only
unsigned char * const MP1_P2C1     = 0x129;     // Palette 2 - Color 1                          write-only
unsigned char * const MP1_P2C2     = 0x12A;     // Palette 2 - Color 2                          write-only
unsigned char * const MP1_P2C3     = 0x12B;     // Palette 2 - Color 3                          write-only
unsigned char * const MP1_DPPH     = 0x12C;     // Display List List Pointer High               write-only
unsigned char * const MP1_P3C1     = 0x12D;     // Palette 3 - Color 1                          write-only
unsigned char * const MP1_P3C2     = 0x12E;     // Palette 3 - Color 2                          write-only
unsigned char * const MP1_P3C3     = 0x12F;     // Palette 3 - Color 3                          write-only
unsigned char * const MP1_DPPL     = 0x130;     // Display List List Pointer Low                write-only
unsigned char * const MP1_P4C1     = 0x131;     // Palette 4 - Color 1                          write-only
unsigned char * const MP1_P4C2     = 0x132;     // Palette 4 - Color 2                          write-only
unsigned char * const MP1_P4C3     = 0x133;     // Palette 4 - Color 3                          write-only
unsigned char * const MP1_CHARBASE = 0x134;     // Character Base Address                       write-only
unsigned char * const MP1_CHBASE   = 0x134;     // Character Base Address                       write-only
unsigned char * const MP1_P5C1     = 0x135;     // Palette 5 - Color 1                          write-only
unsigned char * const MP1_P5C2     = 0x136;     // Palette 5 - Color 2                          write-only
unsigned char * const MP1_P5C3     = 0x137;     // Palette 5 - Color 3                          write-only
unsigned char * const MP1_P6C1     = 0x139;     // Palette 6 - Color 1                          write-only
unsigned char * const MP1_P6C2     = 0x13A;     // Palette 6 - Color 2                          write-only
unsigned char * const MP1_P6C3     = 0x13B;     // Palette 6 - Color 3                          write-only
unsigned char * const MP1_CTRL     = 0x13C;     // Maria Control Register                       write-only
unsigned char * const MP1_P7C1     = 0x13D;     // Palette 7 - Color 1                          write-only
unsigned char * const MP1_P7C2     = 0x13E;     // Palette 7 - Color 2                          write-only
unsigned char * const MP1_P7C3     = 0x13F;     // Palette 7 - Color 3                          write-only

unsigned char * const MP2_P0C1     = 0x221;     // Palette 0 - Color 1                          write-only
unsigned char * const MP2_P0C2     = 0x222;     // Palette 0 - Color 2                          write-only
unsigned char * const MP2_P0C3     = 0x223;     // Palette 0 - Color 3                          write-only
unsigned char * const MP2_P1C1     = 0x225;     // Palette 1 - Color 1                          write-only
unsigned char * const MP2_P1C2     = 0x226;     // Palette 1 - Color 2                          write-only
unsigned char * const MP2_P1C3     = 0x227;     // Palette 1 - Color 3                          write-only
unsigned char * const MP2_P2C1     = 0x229;     // Palette 2 - Color 1                          write-only
unsigned char * const MP2_P2C2     = 0x22A;     // Palette 2 - Color 2                          write-only
unsigned char * const MP2_P2C3     = 0x22B;     // Palette 2 - Color 3                          write-only
unsigned char * const MP2_DPPH     = 0x22C;     // Display List List Pointer High               write-only
unsigned char * const MP2_P3C1     = 0x22D;     // Palette 3 - Color 1                          write-only
unsigned char * const MP2_P3C2     = 0x22E;     // Palette 3 - Color 2                          write-only
unsigned char * const MP2_P3C3     = 0x22F;     // Palette 3 - Color 3                          write-only
unsigned char * const MP2_DPPL     = 0x230;     // Display List List Pointer Low                write-only
unsigned char * const MP2_P4C1     = 0x231;     // Palette 4 - Color 1                          write-only
unsigned char * const MP2_P4C2     = 0x232;     // Palette 4 - Color 2                          write-only
unsigned char * const MP2_P4C3     = 0x233;     // Palette 4 - Color 3                          write-only
unsigned char * const MP2_CHARBASE = 0x234;     // Character Base Address                       write-only
unsigned char * const MP2_CHBASE   = 0x234;     // Character Base Address                       write-only
unsigned char * const MP2_P5C1     = 0x235;     // Palette 5 - Color 1                          write-only
unsigned char * const MP2_P5C2     = 0x236;     // Palette 5 - Color 2                          write-only
unsigned char * const MP2_P5C3     = 0x237;     // Palette 5 - Color 3                          write-only
unsigned char * const MP2_P6C1     = 0x239;     // Palette 6 - Color 1                          write-only
unsigned char * const MP2_P6C2     = 0x23A;     // Palette 6 - Color 2                          write-only
unsigned char * const MP2_P6C3     = 0x23B;     // Palette 6 - Color 3                          write-only
unsigned char * const MP2_CTRL     = 0x23C;     // Maria Control Register                       write-only
unsigned char * const MP2_P7C1     = 0x23D;     // Palette 7 - Color 1                          write-only
unsigned char * const MP2_P7C2     = 0x23E;     // Palette 7 - Color 2                          write-only
unsigned char * const MP2_P7C3     = 0x23F;     // Palette 7 - Color 3                          write-only

unsigned char * const MP3_P0C1     = 0x321;     // Palette 0 - Color 1                          write-only
unsigned char * const MP3_P0C2     = 0x322;     // Palette 0 - Color 2                          write-only
unsigned char * const MP3_P0C3     = 0x323;     // Palette 0 - Color 3                          write-only
unsigned char * const MP3_P1C1     = 0x325;     // Palette 1 - Color 1                          write-only
unsigned char * const MP3_P1C2     = 0x326;     // Palette 1 - Color 2                          write-only
unsigned char * const MP3_P1C3     = 0x327;     // Palette 1 - Color 3                          write-only
unsigned char * const MP3_P2C1     = 0x329;     // Palette 2 - Color 1                          write-only
unsigned char * const MP3_P2C2     = 0x32A;     // Palette 2 - Color 2                          write-only
unsigned char * const MP3_P2C3     = 0x32B;     // Palette 2 - Color 3                          write-only
unsigned char * const MP3_DPPH     = 0x32C;     // Display List List Pointer High               write-only
unsigned char * const MP3_P3C1     = 0x32D;     // Palette 3 - Color 1                          write-only
unsigned char * const MP3_P3C2     = 0x32E;     // Palette 3 - Color 2                          write-only
unsigned char * const MP3_P3C3     = 0x32F;     // Palette 3 - Color 3                          write-only
unsigned char * const MP3_DPPL     = 0x330;     // Display List List Pointer Low                write-only
unsigned char * const MP3_P4C1     = 0x331;     // Palette 4 - Color 1                          write-only
unsigned char * const MP3_P4C2     = 0x332;     // Palette 4 - Color 2                          write-only
unsigned char * const MP3_P4C3     = 0x333;     // Palette 4 - Color 3                          write-only
unsigned char * const MP3_CHARBASE = 0x334;     // Character Base Address                       write-only
unsigned char * const MP3_CHBASE   = 0x334;     // Character Base Address                       write-only
unsigned char * const MP3_P5C1     = 0x335;     // Palette 5 - Color 1                          write-only
unsigned char * const MP3_P5C2     = 0x336;     // Palette 5 - Color 2                          write-only
unsigned char * const MP3_P5C3     = 0x337;     // Palette 5 - Color 3                          write-only
unsigned char * const MP3_P6C1     = 0x339;     // Palette 6 - Color 1                          write-only
unsigned char * const MP3_P6C2     = 0x33A;     // Palette 6 - Color 2                          write-only
unsigned char * const MP3_P6C3     = 0x33B;     // Palette 6 - Color 3                          write-only
unsigned char * const MP3_CTRL     = 0x33C;     // Maria Control Register                       write-only
unsigned char * const MP3_P7C1     = 0x33D;     // Palette 7 - Color 1                          write-only
unsigned char * const MP3_P7C2     = 0x33E;     // Palette 7 - Color 2                          write-only
unsigned char * const MP3_P7C3     = 0x33F;     // Palette 7 - Color 3                          write-only

#endif // __MARIA_PLUS_H__
