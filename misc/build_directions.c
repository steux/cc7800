#include <math.h>
#include <stdio.h>

void main()
{
    int d;
    int dx[24], dy[24];
    for (d = 0; d != 24; d++) {
        float angle = d * (M_PI / 12);
        dx[d] = cosf(angle) * 450;
        dy[d] = sinf(angle) * 450 * 1.6;
    }
    printf("const signed char dx[24] = {");
    for (d = 0; d != 23; d++) {
        printf("%d, ", (int)floor(dx[d] + 0.5));
    }
    printf("%d};\n", (int)floor(dx[d] + 0.5));
    printf("const signed short dy[24] = {");
    for (d = 0; d != 23; d++) {
        printf("%d, ", (int)floor(dy[d] + 0.5));
    }
    printf("%d};\n", (int)floor(dy[d] + 0.5));
}
