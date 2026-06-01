// This routine converts a 24 bit binary number
// to 8 digit bcd format.
// This is needed for showing previous high scores
// saved in the high-score-cart.

ramchip unsigned char BCD0; // Least significant
ramchip unsigned char BCD1;
ramchip unsigned char BCD2;
ramchip unsigned char BCD3;

ramchip unsigned char BIN0; // Least significant
ramchip unsigned char BIN1;
ramchip unsigned char BIN2;

#include "bin2bcd.asm"

void bin2bcd() {
    asm("JSR _bin2bcd", 3);
}

