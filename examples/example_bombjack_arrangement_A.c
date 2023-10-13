const char tilemap_arrangement_A_0_data[] = {96, 0xff};
const char tilemap_arrangement_A_2_0[4] = {0, 2, 2, 4};
const char tilemap_arrangement_A_2_data[] = {10, 7, tilemap_arrangement_A_2_0, 0x60, tilemap_arrangement_A_2_0 >> 8, (3 << 5) | ((-4) & 0x1f), 24, 96, 0xff};
const char tilemap_arrangement_A_5_0[2] = {0, 4};
const char tilemap_arrangement_A_5_data[] = {4, 3, tilemap_arrangement_A_5_0, 0x60, tilemap_arrangement_A_5_0 >> 8, (3 << 5) | ((-2) & 0x1f), 15, 96, 0xff};
const char tilemap_arrangement_A_9_0[3] = {0, 2, 4};
const char tilemap_arrangement_A_9_data[] = {8, 6, tilemap_arrangement_A_9_0, 0x60, tilemap_arrangement_A_9_0 >> 8, (3 << 5) | ((-3) & 0x1f), 20, 96, 0xff};
const char tilemap_arrangement_A_10_data[] = {2, 1, tilemap_arrangement_A_5_0, 0x60, tilemap_arrangement_A_5_0 >> 8, (3 << 5) | ((-2) & 0x1f), 15, 96, 0xff};
const char tilemap_arrangement_A_12_0[5] = {0, 2, 2, 2, 4};
const char tilemap_arrangement_A_12_data[] = {12, 8, tilemap_arrangement_A_12_0, 0x60, tilemap_arrangement_A_12_0 >> 8, (3 << 5) | ((-5) & 0x1f), 29, 96, 0xff};

const char tilemap_arrangement_A_data_ptrs_high[14] = {tilemap_arrangement_A_0_data >> 8, tilemap_arrangement_A_0_data >> 8, tilemap_arrangement_A_2_data >> 8, tilemap_arrangement_A_0_data >> 8, tilemap_arrangement_A_0_data >> 8, tilemap_arrangement_A_5_data >> 8, tilemap_arrangement_A_0_data >> 8, tilemap_arrangement_A_0_data >> 8, tilemap_arrangement_A_0_data >> 8, tilemap_arrangement_A_9_data >> 8, tilemap_arrangement_A_10_data >> 8, tilemap_arrangement_A_0_data >> 8, tilemap_arrangement_A_12_data >> 8, tilemap_arrangement_A_0_data >> 8};

const char tilemap_arrangement_A_data_ptrs_low[14] = {tilemap_arrangement_A_0_data & 0xff, tilemap_arrangement_A_0_data & 0xff, tilemap_arrangement_A_2_data & 0xff, tilemap_arrangement_A_0_data & 0xff, tilemap_arrangement_A_0_data & 0xff, tilemap_arrangement_A_5_data & 0xff, tilemap_arrangement_A_0_data & 0xff, tilemap_arrangement_A_0_data & 0xff, tilemap_arrangement_A_0_data & 0xff, tilemap_arrangement_A_9_data & 0xff, tilemap_arrangement_A_10_data & 0xff, tilemap_arrangement_A_0_data & 0xff, tilemap_arrangement_A_12_data & 0xff, tilemap_arrangement_A_0_data & 0xff};

const char *tilemap_arrangement_A_data_ptrs[2] = {tilemap_arrangement_A_data_ptrs_high, tilemap_arrangement_A_data_ptrs_low};

/*
#define TILING_HEIGHT 14
#define TILING_WIDTH 14
#include "sparse_tiling.h"
*/

