#include <stdio.h>

void main()
{
    unsigned char array[2048];
    int i, size = 0;
    while (!feof(stdin) && size < 2048) {
        array[size++] = getchar();
    }
/*  // Uncomment to skip the first 2kb (for 4kb fonts with small caps in the second part)
    size = 0;
    while (!feof(stdin) && size < 2048) {
        array[size++] = getchar();
    }
*/
    printf("reversed scattered(8,1) char font[%d]={\n\t", size);
    for (i = 0; i != size; i++) {
        printf("0x%02x", (int)array[i]);
        if (i != size - 1) {
            printf(", ");
            if (!((i + 1) % 16)) printf("\n\t");
        }
    }
    printf("\n};\n");
}

