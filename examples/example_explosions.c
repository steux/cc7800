#include "prosystem.h"
#include "multisprite.h"

#define NB_EXPLOSIONS 5 
ramchip char xpos[NB_EXPLOSIONS], ypos[NB_EXPLOSIONS];

// Generated with sprites7800 explosion.yaml
holeydma reversed scattered(16,6) char explosion1[96] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x2a, 0xa0, 0x00, 0x00, 0x00, 0x00, 0xa5, 0x68, 0x00, 0x00, 0x00, 0x62, 0x96, 0xaa, 0xa8, 0x00,
	0x00, 0xaa, 0x5a, 0x55, 0xa9, 0x00, 0x02, 0x69, 0x59, 0x55, 0x65, 0x00, 0x02, 0x65, 0x59, 0x55,
	0x5a, 0x00, 0x02, 0x6a, 0xa5, 0x55, 0x5b, 0x00, 0x01, 0xa5, 0x59, 0x55, 0x5b, 0x00, 0x02, 0xa5,
	0x5e, 0x55, 0x58, 0x00, 0x00, 0xa5, 0x57, 0x95, 0x5c, 0x00, 0x00, 0x65, 0x55, 0xe5, 0x50, 0x00
};
holeydma reversed scattered(16,6) char explosion1_1[96] = {
	0x02, 0x55, 0x55, 0x75, 0x54, 0x00, 0x02, 0x95, 0x55, 0x59, 0x56, 0x00, 0x01, 0x95, 0x55, 0x65,
	0x5a, 0x00, 0x01, 0x95, 0x55, 0x5b, 0xfa, 0x00, 0x01, 0x95, 0x55, 0x56, 0xa6, 0x00, 0x02, 0x95,
	0x55, 0x55, 0x56, 0x00, 0x02, 0xb5, 0x55, 0x75, 0x56, 0x00, 0x02, 0xaf, 0x55, 0x65, 0x56, 0x00,
	0x01, 0x5a, 0xd5, 0xe5, 0x56, 0x00, 0x01, 0x56, 0xbf, 0xa5, 0x56, 0x00, 0x01, 0x95, 0xaa, 0xa5,
	0x56, 0x00, 0x02, 0x96, 0xaa, 0xa5, 0x67, 0x00, 0x02, 0xa6, 0x95, 0xa5, 0x67, 0x00, 0x02, 0x6a,
	0x55, 0x95, 0x64, 0x00, 0x00, 0x6a, 0x55, 0x55, 0x60, 0x00, 0x02, 0x69, 0x55, 0x7d, 0xe9, 0x00
};
holeydma reversed scattered(16,6) char explosion1_2[96] = {
	0x01, 0x59, 0x55, 0x69, 0xa5, 0xc0, 0x02, 0x96, 0x55, 0x5a, 0xa5, 0x80, 0x02, 0x55, 0x95, 0x69,
	0x95, 0x80, 0x00, 0xa5, 0x65, 0xa5, 0xa6, 0x80, 0x00, 0x65, 0x59, 0x95, 0x6a, 0x00, 0x00, 0x15,
	0x55, 0x56, 0xa9, 0x00, 0x00, 0x15, 0x55, 0x5a, 0xa0, 0x00, 0x00, 0x0a, 0x55, 0x59, 0x80, 0x00,
	0x00, 0x02, 0x95, 0x6a, 0x80, 0x00, 0x00, 0x00, 0xbd, 0x92, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
holeydma reversed scattered(16,6) char explosion2[96] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xd4,
	0x00, 0x00, 0x00, 0xa8, 0xba, 0xfe, 0x28, 0x00, 0x00, 0xeb, 0xa5, 0x6b, 0xeb, 0x00, 0x03, 0x95,
	0x56, 0xaa, 0xda, 0xc0, 0x03, 0x95, 0x5d, 0x55, 0x56, 0xb0, 0x02, 0x57, 0xff, 0xfd, 0x55, 0x70,
	0x06, 0x59, 0x75, 0x56, 0x55, 0x60, 0x0e, 0x55, 0x95, 0x56, 0x55, 0x60, 0x0e, 0x55, 0x55, 0x55,
	0xa5, 0x70, 0x0e, 0x65, 0x55, 0x55, 0x56, 0xf0, 0x0e, 0x55, 0x55, 0x55, 0x66, 0xb0, 0x0a, 0x55,
	0x55, 0x55, 0x66, 0x80, 0x0a, 0x55, 0x55, 0x55, 0x66, 0x80, 0x0e, 0x55, 0x55, 0x55, 0x56, 0xc0
};
holeydma reversed scattered(16,6) char explosion2_1[96] = {
	0x0e, 0x55, 0x55, 0x55, 0x56, 0xc0, 0x0e, 0x55, 0x55, 0x55, 0x5a, 0x90, 0x0a, 0x95, 0x55, 0x55,
	0x5a, 0xb0, 0x02, 0x95, 0x55, 0x55, 0x5a, 0xb0, 0x02, 0x95, 0x55, 0x59, 0x65, 0xb0, 0x03, 0x95,
	0x55, 0x56, 0x95, 0x70, 0x0e, 0x95, 0x55, 0x59, 0x55, 0xb0, 0x0e, 0x95, 0x55, 0x59, 0x55, 0xb0,
	0x0e, 0x75, 0x57, 0xf5, 0x55, 0xb0, 0x0e, 0x7d, 0x57, 0x75, 0x55, 0x80, 0x0d, 0x5f, 0xff, 0x75,
	0x56, 0xc0, 0x0e, 0x55, 0x5f, 0x75, 0x56, 0xc0, 0x0e, 0x55, 0x5d, 0x75, 0x56, 0x80, 0x0e, 0x55,
	0x7d, 0x59, 0x5d, 0x70, 0x02, 0x95, 0x75, 0x59, 0x5d, 0x70, 0x03, 0xd5, 0x55, 0x56, 0x5d, 0x70
};
holeydma reversed scattered(16,6) char explosion2_2[96] = {
	0x03, 0x95, 0x95, 0x56, 0x5d, 0x70, 0x0b, 0xa9, 0x95, 0x55, 0xfd, 0x60, 0x0e, 0x96, 0x95, 0x55,
	0x5d, 0x60, 0x0e, 0x56, 0x95, 0x55, 0x55, 0x68, 0x0e, 0x55, 0x95, 0x55, 0x55, 0x68, 0x02, 0x55,
	0x95, 0x55, 0x65, 0x68, 0x02, 0x95, 0x95, 0x55, 0xa5, 0xb0, 0x03, 0x95, 0x65, 0x55, 0xb5, 0xb0,
	0x03, 0x95, 0x5f, 0xd5, 0xbb, 0xc0, 0x00, 0xa5, 0x57, 0xd6, 0xeb, 0x80, 0x00, 0x7a, 0x5b, 0xeb,
	0x45, 0x00, 0x00, 0x3f, 0x6e, 0xfd, 0x00, 0x00, 0x00, 0x03, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
holeydma reversed scattered(16,6) char explosion3[96] = {
	0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x03, 0xe0, 0x0f, 0xfe, 0x00, 0x00, 0x0a, 0xb0, 0x3f, 0xfe,
	0x0a, 0xa0, 0x29, 0xa8, 0xfd, 0x5b, 0x2a, 0xa0, 0x29, 0x5b, 0xff, 0x76, 0xea, 0xa0, 0x39, 0x5a,
	0x77, 0xf5, 0x9a, 0xe8, 0x25, 0x59, 0x96, 0x75, 0x55, 0xa8, 0x25, 0x6a, 0x6f, 0xff, 0x55, 0x68,
	0xa5, 0x5a, 0x75, 0x6b, 0x55, 0xaa, 0xe5, 0x55, 0x95, 0x7d, 0xd5, 0x5a, 0xe5, 0x75, 0x55, 0x6a,
	0xd5, 0x6a, 0xa5, 0xe5, 0x55, 0x5f, 0xd5, 0xaa, 0xb7, 0x95, 0x55, 0x57, 0xf5, 0x98, 0x3e, 0x55,
	0x55, 0x5a, 0x99, 0x58, 0x3d, 0x55, 0x55, 0x5f, 0xd9, 0x68, 0x2f, 0x55, 0x55, 0x6d, 0x55, 0xa8
};
holeydma reversed scattered(16,6) char explosion3_1[96] = {
	0x2b, 0x59, 0x55, 0x7f, 0x55, 0xa8, 0x3f, 0xfd, 0x55, 0xea, 0x56, 0xb8, 0x2b, 0xa9, 0x55, 0xfd,
	0x55, 0x78, 0x3f, 0x7a, 0xd5, 0xfd, 0x55, 0x60, 0x3d, 0x9f, 0xff, 0xf7, 0xd5, 0xb0, 0x2d, 0x95,
	0xea, 0x7f, 0xd5, 0xe0, 0x3f, 0x66, 0x7b, 0x7a, 0xff, 0xfc, 0x3d, 0x55, 0x7f, 0x77, 0xf6, 0xbc,
	0x3a, 0xd5, 0x5d, 0x5e, 0x95, 0xd8, 0xbf, 0xd5, 0x5f, 0x5f, 0x55, 0x58, 0xfd, 0x95, 0x5f, 0x7a,
	0x55, 0xa8, 0xa5, 0xd5, 0x57, 0xdf, 0x55, 0xac, 0xf5, 0x95, 0x5f, 0x76, 0x55, 0xf8, 0x35, 0xd5,
	0x97, 0xf7, 0x55, 0xb8, 0x29, 0x75, 0x99, 0xf5, 0x55, 0x60, 0x2a, 0xab, 0x69, 0xd9, 0x55, 0xa8
};
holeydma reversed scattered(16,6) char explosion3_2[96] = {
	0x0a, 0xaa, 0x95, 0x69, 0x5a, 0xa8, 0x0a, 0xaa, 0x95, 0x66, 0x99, 0xa8, 0x0a, 0xa9, 0x55, 0x56,
	0xaa, 0xa8, 0x0d, 0x69, 0x55, 0x56, 0x96, 0x98, 0x29, 0x6a, 0x55, 0x55, 0x59, 0x9a, 0x29, 0x59,
	0x55, 0x55, 0x59, 0x9a, 0x39, 0x59, 0x95, 0x56, 0x6a, 0x9e, 0xa9, 0x59, 0x65, 0x55, 0xaa, 0xa8,
	0xa5, 0x56, 0xa5, 0x59, 0xaa, 0xa8, 0x29, 0x55, 0xa6, 0x95, 0xa9, 0x60, 0x39, 0x95, 0x96, 0x55,
	0xa6, 0xb0, 0x0e, 0x95, 0x5a, 0xa6, 0xaa, 0xe0, 0x0b, 0xaa, 0x9b, 0x97, 0xaa, 0x80, 0x02, 0xba,
	0xae, 0xaa, 0xba, 0x00, 0x00, 0x3f, 0xee, 0xfc, 0x30, 0x00, 0x00, 0x00, 0xa0, 0x20, 0x00, 0x00
};
holeydma reversed scattered(16,6) char explosion4[96] = {
	0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x80, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x00, 0x00, 0x01, 0x2b,
	0x00, 0x20, 0x28, 0x00, 0x01, 0x2b, 0x0f, 0xc0, 0x2a, 0x00, 0x00, 0x28, 0x0f, 0x80, 0x2a, 0x00,
	0x00, 0xe8, 0x2a, 0x80, 0x0a, 0x00, 0x00, 0xe8, 0xaa, 0x80, 0x0a, 0x00, 0x00, 0xe8, 0xaa, 0xb0,
	0x02, 0x00, 0x00, 0xec, 0xaa, 0xb0, 0x02, 0x20, 0x00, 0x00, 0x3a, 0x80, 0x00, 0x20, 0x00, 0x00,
	0x2a, 0x80, 0x00, 0x00, 0x00, 0x20, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x00
};
holeydma reversed scattered(16,6) char explosion4_1[96] = {
	0x00, 0x20, 0x00, 0x08, 0x00, 0x20, 0x03, 0x00, 0x00, 0x0a, 0x02, 0x20, 0x02, 0x00, 0x00, 0x2a,
	0x02, 0xa0, 0x0e, 0x00, 0x00, 0xea, 0x0a, 0xc0, 0x00, 0x02, 0x80, 0xea, 0x0a, 0x00, 0x00, 0x0a,
	0xb0, 0xea, 0x0a, 0x00, 0x00, 0x02, 0xa0, 0xe8, 0x0c, 0x00, 0x01, 0x02, 0xa0, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xa0, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x03, 0x00,
	0x00, 0x00, 0x02, 0xb0, 0x02, 0xa0, 0x00, 0x00, 0x02, 0xa0, 0x0a, 0xac, 0x0e, 0x00, 0x03, 0xa0,
	0x0a, 0xac, 0x0a, 0x00, 0x03, 0x00, 0x0a, 0xac, 0x2a, 0x00, 0x00, 0x00, 0x0a, 0xa8, 0xe8, 0x00
};
holeydma reversed scattered(16,6) char explosion4_2[96] = {
	0x01, 0x00, 0x02, 0xa0, 0xa0, 0x20, 0x00, 0x00, 0x02, 0xa0, 0x00, 0x20, 0x00, 0x2e, 0xc0, 0xf0,
	0x00, 0x00, 0x00, 0x2a, 0x80, 0x00, 0x32, 0x00, 0x02, 0x2a, 0x80, 0x80, 0x0a, 0x20, 0x02, 0x8a,
	0x80, 0xa8, 0x0a, 0x20, 0x00, 0x82, 0x80, 0xa8, 0x0a, 0x20, 0x00, 0x02, 0x80, 0xaf, 0x00, 0x20,
	0x00, 0x00, 0x00, 0x28, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
holeydma reversed scattered(16,6) char explosion5[96] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
	0x00, 0x00, 0x00, 0x08, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x80,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x80, 0x0f, 0x00, 0x00, 0x08, 0x03, 0x00, 0x0a, 0x00
};
holeydma reversed scattered(16,6) char explosion5_1[96] = {
	0x00, 0x4b, 0x03, 0x01, 0x02, 0x00, 0x00, 0x0e, 0x0f, 0x00, 0x02, 0x10, 0x00, 0x00, 0x08, 0x00,
	0x00, 0xa0, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x20, 0x00, 0x00, 0x00, 0x0a,
	0x0a, 0x00, 0x00, 0x00, 0x00, 0x0a, 0xca, 0xf0, 0x00, 0x00, 0x00, 0x0a, 0x83, 0x2a, 0x02, 0x00,
	0x00, 0x03, 0xc0, 0x3f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x08, 0x02, 0x00, 0x00, 0x00, 0x00, 0x30,
	0x2e, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x08, 0x20, 0x00, 0x00
};
holeydma reversed scattered(16,6) char explosion5_2[96] = {
	0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x08, 0x00, 0x08,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x80, 0x00, 0x00, 0x00, 0x00, 0x02, 0x80, 0x00, 0x00, 0x00,
	0x80, 0x00, 0x00, 0x00, 0x00, 0x40, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void main()
{
    char i, j = 0, k, l = 0, x, y;
    multisprite_init();
    
    *P0C1 = multisprite_color(0x1c); // Yellow 
    *P0C2 = multisprite_color(0x37); // Orange
    *P0C3 = multisprite_color(0x43); // Red
   
    // Initialize explosions 
    x = 0; y = 0;
    for (X = 0; X != NB_EXPLOSIONS; X++) {
        xpos[X] = x;
        ypos[X] = y;
        x += 160 / NB_EXPLOSIONS;
        y += 224 / NB_EXPLOSIONS;
    }

    // Main loop
    do {
        multisprite_flip();
        char *gfx = explosion1;
        for (X = j; X != 0; X--) gfx += 18;
        k = j;
        for (i = 0; i != NB_EXPLOSIONS; i++) {
            x = xpos[i];
            y = ypos[i];
            multisprite_display_big_sprite(x, y, gfx, 6, 0, 3, 0);
            gfx += 18;
            k++;
            if (k == NB_EXPLOSIONS) {
                k = 0;
                gfx = explosion1;
            }
        }
        l++;
        if (l == 5) {
            j++;
            if (j == NB_EXPLOSIONS) j = 0;
            l = 0;
        }
    } while(1);
}
