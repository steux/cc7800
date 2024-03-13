#include <stdio.h>

char conv2dot[16] = {0x00, 0x01, 0x04, 0x05, 0x10, 0x11, 0x14, 0x15, 0x40, 0x41, 0x44, 0x45, 0x50, 0x51, 0x54, 0x55}; 

void main()
{
    unsigned char array[2048];
    int i, j, size = 0;
    while (!feof(stdin) && size < 2048) {
        array[size++] = getchar();
    }
    for (j = 0; j != 64; j++) {
        printf("holeydma reversed scattered(8,2) char dot_letter%d_0[16]={", j);
        for (i = 0; i != 4; i++) {
            printf("0x%02x, 0x%02x, 0, 0", conv2dot[array[j * 8 + i] >> 4], conv2dot[array[j * 8 + i] & 0x0f]);
            if (i != 3) {
                printf(", ");
            }
        }
        printf("};\n");
        printf("holeydma reversed scattered(8,2) char dot_letter%d_1[16]={", j);
        for (; i != 8; i++) {
            printf("0x%02x, 0x%02x, 0, 0", conv2dot[array[j * 8 + i] >> 4], conv2dot[array[j * 8 + i] & 0x0f]);
            if (i != 7) {
                printf(", ");
            }
        }
        printf("};\n");
    }
}

