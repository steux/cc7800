#include "prosystem.h"
#include "multisprite.h"
#include "joystick.h"

const signed short dx[24] = {300, 289, 259, 212, 149, 77, 0, -77, -150, -212, -259, -289, -300, -289, -259, -212, -149, -77, 0, 77, 149, 212, 259, 289};
const signed short dy[24] = {0, 124, 240, 339, 415, 463, 480, 463, 415, 339, 240, 124, 0, -124, -239, -339, -415, -463, -480, -463, -415, -339, -240, -124};
const char horizontal_pingpong[24] = { 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13 };
const char vertical_pingpong[24] = { 0, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

// Generated by sprites7800 shmup.yaml

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
holeydma reversed scattered(16,1) char bullet[16] = {
	0x18, 0x96, 0x7a, 0x7e, 0x7e, 0x6e, 0x9a, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
holeydma reversed scattered(16,6) char spaceship[96] = {
	0x00, 0x00, 0x30, 0x80, 0x00, 0x00, 0x00, 0x00, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00, 0x30, 0x80,
	0x00, 0x00, 0x00, 0x00, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00, 0x30, 0x80, 0x00, 0x00, 0x00, 0x00,
	0xe1, 0x94, 0x00, 0x00, 0x00, 0x00, 0xa1, 0x94, 0x00, 0x00, 0x00, 0x00, 0xf1, 0x94, 0x00, 0x00,
	0x00, 0x00, 0xb9, 0xd6, 0x00, 0x00, 0x10, 0x00, 0xba, 0xd6, 0x00, 0x40, 0x13, 0x30, 0xba, 0xd6,
	0x80, 0x4c, 0x20, 0x30, 0xa9, 0x96, 0x80, 0x80, 0x20, 0xd2, 0xa9, 0x96, 0x68, 0x80, 0x20, 0xd2,
	0xa9, 0x96, 0x68, 0x80, 0x00, 0x5a, 0xaa, 0x5a, 0x5a, 0x00, 0x32, 0x5a, 0xaa, 0x5a, 0x5a, 0x80
};
holeydma reversed scattered(16,6) char spaceship_1[96] = {
	0xda, 0x5a, 0x66, 0x59, 0x5a, 0x68, 0xda, 0x9e, 0x6a, 0x5a, 0x6b, 0x68, 0xda, 0x9a, 0x68, 0x52,
	0x6a, 0x68, 0xda, 0x9a, 0xa0, 0x50, 0x6a, 0x68, 0xfb, 0x98, 0xe0, 0x60, 0x62, 0xec, 0x00, 0x98,
	0x30, 0x80, 0x62, 0x00, 0x00, 0x98, 0x20, 0x40, 0x62, 0x00, 0x00, 0x48, 0x20, 0x40, 0x12, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
holeydma reversed scattered(16,1) char exhaust1[16] = {
	0x3c, 0xbe, 0xaa, 0xaa, 0x98, 0x24, 0x18, 0x10, 0x18, 0x14, 0x04, 0x24, 0x14, 0x10, 0x14, 0x04
};
holeydma reversed scattered(16,1) char exhaust2[16] = {
	0x3c, 0xbe, 0xaa, 0xaa, 0x1a, 0x24, 0x08, 0x24, 0x18, 0x10, 0x18, 0x14, 0x04, 0x24, 0x14, 0x10
};
holeydma reversed scattered(16,1) char exhaust3[16] = {
	0x3c, 0xbe, 0xaa, 0xaa, 0x9a, 0x20, 0x18, 0x24, 0x08, 0x24, 0x18, 0x10, 0x18, 0x14, 0x04, 0x24
};
holeydma reversed scattered(16,2) char exhauststart[32] = {
	0x03, 0xc0, 0x3f, 0xfc, 0xae, 0xee, 0x26, 0x64, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const char collision_bullet_spaceship[78] = {0x03, 0x80, 0x07, 0xc0, 0x07, 0xc0, 0x07, 0xc0, 0x07, 0xc0, 0x07, 0xc0, 0x0f, 0xe0, 0x0f, 0xe0, 0x0f, 0xe0, 0x3f, 0xf8, 0x7f, 0xfc, 0x7f, 0xfc, 0x7f, 0xfc, 0x7f, 0xfc, 0x7f, 0xfc, 0x7f, 0xfc, 0x7f, 0xfc, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0x7f, 0xfc, 0x3f, 0xf8, 0x3f, 0xf8, 0x1b, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

#define NB_SMALL_SPRITES 32 
ramchip short sp_xpos[NB_SMALL_SPRITES], sp_ypos[NB_SMALL_SPRITES];
ramchip char sp_direction[NB_SMALL_SPRITES];
ramchip char exhaust_state;
ramchip char spaceship_x, spaceship_y, spaceship_state, spaceship_state_counter; 

void main()
{
    char i;
    multisprite_init();
    
    // Grey palette
    *P0C1 = 0x04;
    *P0C2 = 0x08;
    *P0C3 = 0x0b;

    // Blue palette
    *P1C1 = multisprite_color(0x84); // Dark blue 
    *P1C2 = multisprite_color(0x87); // Light blue
    *P1C3 = multisprite_color(0xac); // Turquoise 

    // Green palette
    *P2C1 = multisprite_color(0xd4); // Dark green 
    *P2C2 = multisprite_color(0xd8); // Light green
    *P2C3 = 0x0f; 
    
    // Fire palette
    *P3C1 = multisprite_color(0x1c); // Yellow 
    *P3C2 = multisprite_color(0x37); // Orange
    *P3C3 = multisprite_color(0x43); // Red

    // Initialize spaceship state
    spaceship_x = 80 - 6;
    spaceship_y = 180;
    exhaust_state = 0;
    spaceship_state = 0;
     
    // Initialize small sprites
    { 
        char xpos, ypos; 
        for (ypos = 0, xpos = 0, i = 0, X = 0; X != NB_SMALL_SPRITES; xpos++, ypos++, X++) {
            sp_xpos[X] = xpos << 8;
            sp_ypos[X] = ypos << 8;
            sp_direction[X] = i++;
            if (i == 24) i = 0;
        }
    }

    // Main loop
    do {
        multisprite_flip();
       
        joystick_update();
        if (spaceship_state < 2) {
            if (joystick[0] & JOYSTICK_LEFT) {
                if (spaceship_x) spaceship_x--;
            } else if (joystick[0] & JOYSTICK_RIGHT) {
                if (spaceship_x < 160 - 13) spaceship_x++;
            }
            if (joystick[0] & JOYSTICK_UP) {
                if (spaceship_y) spaceship_y--;
                exhaust_state++;
                if (exhaust_state == 13) exhaust_state = 10; 
            } else {
                exhaust_state = 0;
                if (joystick[0] & JOYSTICK_DOWN) {
                    if (spaceship_y < 224 - 33) spaceship_y++;
                }
            }
        }

        char draw_spaceship;
        if (spaceship_state == 0) {
            draw_spaceship = 1;
        } else if (spaceship_state == 1) {
            // Blinking returning spaceship
            draw_spaceship = spaceship_state_counter & 8;
            spaceship_state_counter--;
            if (spaceship_state_counter == 0) {
                spaceship_state = 0;
            }
        } else if (spaceship_state == 2) {
            char *gfx, x, y;
            if (spaceship_state_counter >= 16) {
                gfx = explosion1;
            } else if (spaceship_state_counter >= 12) {
                gfx = explosion2;
            } else if (spaceship_state_counter >= 8) {
                gfx = explosion3;
            } else if (spaceship_state_counter >= 4) {
                gfx = explosion4;
            } else gfx = explosion5;

            x = spaceship_x - 6;
            y = spaceship_y - 12;
            if (y < 0) y = 0; else if (y >= 224 - 48) y = 224 - 49;
            multisprite_display_big_sprite(x, y, gfx, 6, 3, 3, 0);
            spaceship_state_counter--;
            if (spaceship_state_counter == 0) {
                spaceship_state = 1;
                spaceship_state_counter = 100;
            }
            draw_spaceship = 0;
        }
        
        if (draw_spaceship) {
            multisprite_display_big_sprite(spaceship_x, spaceship_y, spaceship, 6, 0, 2, 1);
            // Draw exhaust
            if (exhaust_state > 0 && spaceship_y < 224 - 25 - 16) {
                char x, y;
                y = spaceship_y + 24;
                if (exhaust_state < 10) {
                    x = spaceship_x + 2;
                    multisprite_display_small_sprite_ex(x, y, exhauststart, 2, 3, 0);
                } else {
                    char *gfxptr;
                    i = exhaust_state - 10;
                    gfxptr = exhaust1 + i;
                    x = spaceship_x + 4;
                    multisprite_display_sprite_ex(x, y, gfxptr, 1, 3, 0);
                }
            }
        }

        for (i = 0; i != NB_SMALL_SPRITES; i++) {
            char xbullet, ybullet;
            X = i;
            Y = sp_direction[X];
            sp_xpos[X] += dx[Y];
            sp_ypos[X] += dy[Y];
            xbullet = sp_xpos[X] >> 8;
            ybullet = sp_ypos[X] >> 8;
            if ((xbullet < 5 && (dx[Y] >> 8) < 0) || 
                (xbullet >= 150 && (dx[Y] >> 8) >= 0)) {
                sp_direction[X] = horizontal_pingpong[Y];
            }
            if ((ybullet < 5 && (dy[Y] >> 8) < 0) || 
                (ybullet >= MS_YMAX - 20 && (dy[Y] >> 8) >= 0)) {
                sp_direction[X] = vertical_pingpong[Y];
            }
            multisprite_display_small_sprite_ex(xbullet, ybullet, bullet, 1, 3, 0); 
   
            if (spaceship_state == 0) {
                multisprite_compute_collision(xbullet, ybullet, 4, 8, spaceship_x, spaceship_y, 12, 24, collision_bullet_spaceship);
                if (multisprite_collision_detected) {
                    // Explosion
                    spaceship_state = 2;
                    spaceship_state_counter = 20;
                }
            } 
        }
    } while(1);
}