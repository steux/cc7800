; Routine for packing a 3 byte binary field to a 8 digit BCD format.
; This 3 byte binary high-score is used by the HSC cart.

; The routine will destroy the input during the conversion.

; 24-bit binary to 8-digit packed BCD
;
; Input:
;   BIN0 = LSB
;   BIN1
;   BIN2 = MSB
;
; Output:
;   BCD0 = least significant 2 digits
;   BCD1
;   BCD2
;   BCD3 = most significant 2 digits
;

_bin2bcd
        lda #0
        sta BCD0
        sta BCD1
        sta BCD2
        sta BCD3

        ldx #24

bin2bcdloop
        asl BIN0 ; Shift leftmost bit to carry
        rol BIN1
        rol BIN2

        sed

        lda BCD0 ; Multiply by 2
        adc BCD0 ; and add carry
        sta BCD0

        lda BCD1 ; Same to higher digits
        adc BCD1
        sta BCD1

        lda BCD2
        adc BCD2
        sta BCD2

        lda BCD3
        adc BCD3
        sta BCD3

        cld

        dex
        bne bin2bcdloop

        rts

