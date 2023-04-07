#ifndef __ATARI7800_MULTISPRITE__
#define __ATARI7800_MULTISPRITE__

#define _MS_DL_SIZE 64

// Zeropage variables
char *_ms_dlpnt;
char _ms_buffer; // Double buffer state
char _ms_tmp;

ramchip char _ms_b0_dl0[_MS_DL_SIZE], _ms_b0_dl1[_MS_DL_SIZE], _ms_b0_dl2[_MS_DL_SIZE], _ms_b0_dl3[_MS_DL_SIZE], _ms_b0_dl4[_MS_DL_SIZE], _ms_b0_dl5[_MS_DL_SIZE], _ms_b0_dl6[_MS_DL_SIZE], _ms_b0_dl7[_MS_DL_SIZE], _ms_b0_dl8[_MS_DL_SIZE], _ms_b0_dl9[_MS_DL_SIZE], _ms_b0_dl10[_MS_DL_SIZE], _ms_b0_dl11[_MS_DL_SIZE];
ramchip char _ms_b1_dl0[_MS_DL_SIZE], _ms_b1_dl1[_MS_DL_SIZE], _ms_b1_dl2[_MS_DL_SIZE], _ms_b1_dl3[_MS_DL_SIZE], _ms_b1_dl4[_MS_DL_SIZE], _ms_b1_dl5[_MS_DL_SIZE], _ms_b1_dl6[_MS_DL_SIZE], _ms_b1_dl7[_MS_DL_SIZE], _ms_b1_dl8[_MS_DL_SIZE], _ms_b1_dl9[_MS_DL_SIZE], _ms_b1_dl10[_MS_DL_SIZE], _ms_b1_dl11[_MS_DL_SIZE];
#ifdef PAL
#define _MS_DLL_ARRAY_SIZE 15 
ramchip char _ms_b0_dl12[_MS_DL_SIZE], _ms_b0_dl13[_MS_DL_SIZE], _ms_b0_dl14[_MS_DL_SIZE];
ramchip char _ms_b1_dl12[_MS_DL_SIZE], _ms_b1_dl13[_MS_DL_SIZE], _ms_b1_dl14[_MS_DL_SIZE];
const char *_ms_dls[_MS_DLL_ARRAY_SIZE * 2] = {
    _ms_b0_dl0, _ms_b0_dl1, _ms_b0_dl2, _ms_b0_dl3, _ms_b0_dl4, _ms_b0_dl5, _ms_b0_dl6, _ms_b0_dl7, _ms_b0_dl8, _ms_b0_dl9, _ms_b0_dl10, _ms_b0_dl11, _ms_b0_dl12, _ms_b0_dl13, _ms_b0_dl14,
    _ms_b1_dl0, _ms_b1_dl1, _ms_b1_dl2, _ms_b1_dl3, _ms_b1_dl4, _ms_b1_dl5, _ms_b1_dl6, _ms_b1_dl7, _ms_b1_dl8, _ms_b1_dl9, _ms_b1_dl10, _ms_b1_dl11, _ms_b1_dl12, _ms_b1_dl13, _ms_b1_dl14
};
#else
#define _MS_DLL_ARRAY_SIZE 12 
const char *_ms_dls[_MS_DLL_ARRAY_SIZE * 2] = { 
    _ms_b0_dl0, _ms_b0_dl1, _ms_b0_dl2, _ms_b0_dl3, _ms_b0_dl4, _ms_b0_dl5, _ms_b0_dl6, _ms_b0_dl7, _ms_b0_dl8, _ms_b0_dl9, _ms_b0_dl10, _ms_b0_dl11,
    _ms_b1_dl0, _ms_b1_dl1, _ms_b1_dl2, _ms_b1_dl3, _ms_b1_dl4, _ms_b1_dl5, _ms_b1_dl6, _ms_b1_dl7, _ms_b1_dl8, _ms_b1_dl9, _ms_b1_dl10, _ms_b1_dl11
};
#endif
ramchip char _ms_b0_dll[(_MS_DLL_ARRAY_SIZE + 4) * 3];
ramchip char _ms_b1_dll[(_MS_DLL_ARRAY_SIZE + 4) * 3];
ramchip char _ms_dlend[_MS_DLL_ARRAY_SIZE * 2];
ramchip char _ms_dlbudget[_MS_DLL_ARRAY_SIZE * 2];
ramchip char _ms_dlend_save[_MS_DLL_ARRAY_SIZE * 2];
ramchip char _ms_dlbuget_save[_MS_DLL_ARRAY_SIZE * 2];

void multisprite_init();
void multisprite_clear();
void multisprite_save();
void multisprite_restore();
void multisprite_flip();

ramchip char _ms_shift4[256];

#define multisprite_display_sprite(xpos,ypos,gfx,width,palette) \
\
        X = _ms_shift4[Y = (ypos & 0xfe | _ms_buffer)]; \
        _ms_dlpnt = _ms_dls[X]; \
        _ms_dlbudget[X] += (8 + width * 3 + 1) / 2; \
        if (_ms_dlbudget[X] < 228) { \
            Y = _ms_dlend[X]; \
            _ms_dlpnt[Y++] = sprite; \
            _ms_dlpnt[Y++] = -width & 0x1f | (palette << 5); \
            _ms_tmp = (ypos) & 0x0f; \
            _ms_dlpnt[Y++] = (sprite >> 8) | _ms_tmp; \
            _ms_dlpnt[Y++] = (xpos); \
            _ms_dlend[X] = Y; \
        }\
        if ((ypos) & 0x0f) { \
            X++; \
            _ms_dlpnt = _ms_dls[X];  \
            _ms_dlbudget[X] += (8 + width * 3 + 1) / 2; \
            if (_ms_dlbudget[X] < 228) { \
                Y = _ms_dlend[X]; \
                _ms_dlpnt[Y++] = sprite; \
                _ms_dlpnt[Y++] = -width & 0x1f | (palette << 5); \
                _ms_dlpnt[Y++] = ((sprite - 0x1000) >> 8) | _ms_tmp; \
                _ms_dlpnt[Y++] = (xpos); \
                _ms_dlend[X] = Y; \
            } \
        }

#endif // __ATARI7800_MULTISPRITE__
 
