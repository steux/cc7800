#include "string.h"
#define INIT_BANK bank7
#define _MS_DL_MALLOC(line) ((line < 13)?96:32) 
#define HORIZONTAL_SCROLLING
#define _MS_BOTTOM_SCROLLING_ZONE 1
#define MULTISPRITE_USE_VIDEO_MEMORY
#include "sparse_tiling.h"
#include "joystick.h"
bank7 {
#include "sfx.h"
#ifdef POKEY_MUSIC
#define POKEY_AT_450
#include "rmtplayer.h"
#include "RMT_RType.c"
#endif
}

// Generated from sprites7800 RType_tiles.yaml
#include "example_RType_tiles_mirror.c"

// Generated from sprites7800 RType_sprites.yaml
#include "example_RType_sprites.c"

// Generated from tiles7800 --sparse RType_tiles.yaml --varname tilemap_level1 RType_level1.tmx 
#include "example_RType_level1_mirror.c"

const signed short dx[48] = {300, 289, 259, 212, 149, 77, 0, -77, -150, -212, -259, -289, -300, -289, -259, -212, -149, -77, 0, 77, 149, 212, 259, 289, 450, 434, 389, 318, 224, 116, 0, -116, -225, -318, -389, -434, -450, -434, -389, -318, -224, -116, 0, 116, 224, 318, 389, 434};
const signed short dy[48] = {0, 124, 240, 339, 415, 463, 480, 463, 415, 339, 240, 124, 0, -124, -239, -339, -415, -463, -480, -463, -415, -339, -240, -124, 0, 186, 360, 509, 623, 695, 720, 695, 623, 509, 360, 186, 0, -186, -359, -509, -623, -695, -720, -695, -623, -509, -360, -186};

bank7 {
// Generated from sprites7800 RType_font.yaml
#include "example_RType_font.c"

const char sfx_pewpew[66] = {
	0x10, 0, 0x00, 0x1c, 0x04, 0x0f, 0x1c, 0x04, 0x0f, 0x09, 0x04, 0x0b, 0x03, 0x0c, 0x0a, 0x04,
	0x0c, 0x0e, 0x12, 0x04, 0x0c, 0x19, 0x04, 0x0f, 0x1c, 0x04, 0x0f, 0x07, 0x04, 0x05, 0x09, 0x04,
	0x05, 0x0d, 0x04, 0x06, 0x0c, 0x04, 0x05, 0x18, 0x04, 0x06, 0x1c, 0x04, 0x05, 0x1e, 0x04, 0x03,
	0x07, 0x04, 0x03, 0x09, 0x04, 0x03, 0x0c, 0x04, 0x02, 0x04, 0x0c, 0x02, 0x06, 0x0c, 0x01, 0x00,
	0x00, 0x00
};

const char sfx_bigboom[261] = {
	0x10, 1, 0x00, 0x1d, 0x07, 0x0f, 0x1e, 0x06, 0x0f, 0x00, 0x06, 0x0f, 0x14, 0x07, 0x0f, 0x13,
	0x0f, 0x0f, 0x1b, 0x07, 0x0f, 0x0e, 0x07, 0x0f, 0x1b, 0x07, 0x0f, 0x0f, 0x07, 0x0f, 0x10, 0x07,
	0x0f, 0x10, 0x06, 0x0f, 0x16, 0x07, 0x0f, 0x0d, 0x0f, 0x0f, 0x1e, 0x0c, 0x0f, 0x16, 0x01, 0x0f,
	0x17, 0x01, 0x0f, 0x10, 0x07, 0x0f, 0x10, 0x0f, 0x0f, 0x15, 0x07, 0x0d, 0x1a, 0x07, 0x0f, 0x1a,
	0x01, 0x0f, 0x1a, 0x07, 0x0f, 0x14, 0x0f, 0x0f, 0x16, 0x07, 0x0f, 0x16, 0x07, 0x0f, 0x15, 0x07,
	0x0f, 0x17, 0x07, 0x0f, 0x13, 0x0f, 0x0f, 0x13, 0x0f, 0x0f, 0x19, 0x0f, 0x0f, 0x18, 0x07, 0x0c,
	0x0b, 0x06, 0x0c, 0x1e, 0x01, 0x0d, 0x10, 0x01, 0x0d, 0x14, 0x07, 0x0f, 0x16, 0x06, 0x0c, 0x17,
	0x07, 0x0c, 0x1a, 0x01, 0x0c, 0x12, 0x06, 0x0d, 0x17, 0x07, 0x0c, 0x0b, 0x0f, 0x0c, 0x19, 0x07,
	0x09, 0x19, 0x07, 0x0b, 0x0b, 0x0f, 0x09, 0x0d, 0x0e, 0x0b, 0x0d, 0x0e, 0x0b, 0x19, 0x0f, 0x09,
	0x0e, 0x0f, 0x06, 0x1b, 0x0c, 0x08, 0x18, 0x0f, 0x08, 0x13, 0x07, 0x05, 0x1a, 0x01, 0x05, 0x17,
	0x0f, 0x08, 0x16, 0x06, 0x08, 0x0c, 0x06, 0x05, 0x1c, 0x0f, 0x06, 0x16, 0x06, 0x08, 0x0b, 0x06,
	0x06, 0x12, 0x06, 0x04, 0x0f, 0x0f, 0x05, 0x11, 0x07, 0x06, 0x09, 0x06, 0x05, 0x10, 0x06, 0x05,
	0x10, 0x06, 0x05, 0x10, 0x06, 0x05, 0x11, 0x0f, 0x04, 0x15, 0x0f, 0x04, 0x1e, 0x07, 0x05, 0x16,
	0x01, 0x04, 0x16, 0x01, 0x04, 0x1a, 0x0f, 0x04, 0x19, 0x0f, 0x02, 0x1e, 0x0f, 0x02, 0x1b, 0x0f,
	0x02, 0x1e, 0x0f, 0x02, 0x1c, 0x0f, 0x02, 0x0d, 0x0f, 0x01, 0x0f, 0x06, 0x02, 0x0e, 0x06, 0x01,
	0x18, 0x0f, 0x01, 0x0b, 0x06, 0x02, 0x16, 0x0f, 0x01, 0x17, 0x0f, 0x01, 0x13, 0x06, 0x01, 0x0f,
	0x0e, 0x01, 0x00, 0x00, 0x00
};

const char sfx_eek2[63] = {
	0x10, 1, 0x00, 0x1e, 0x06, 0x01, 0x0a, 0x04, 0x0a, 0x0a, 0x04, 0x0f, 0x09, 0x04, 0x0f, 0x13,
	0x04, 0x0e, 0x09, 0x04, 0x0f, 0x09, 0x04, 0x0f, 0x09, 0x04, 0x0f, 0x09, 0x04, 0x0a, 0x09, 0x04,
	0x0f, 0x09, 0x04, 0x0c, 0x09, 0x04, 0x0f, 0x0a, 0x04, 0x0f, 0x0a, 0x04, 0x0c, 0x03, 0x0c, 0x0f,
	0x0c, 0x04, 0x0a, 0x0d, 0x04, 0x05, 0x09, 0x04, 0x02, 0x03, 0x0c, 0x01, 0x00, 0x00, 0x00
};

const char sfx_plainlaser[48] = {
	0x10, 0, 0x00, 0x10, 0x04, 0x06, 0x13, 0x04, 0x08, 0x16, 0x04, 0x08, 0x16, 0x04, 0x07, 0x1c,
	0x04, 0x09, 0x0b, 0x0c, 0x0f, 0x0d, 0x0c, 0x0f, 0x0e, 0x0c, 0x0f, 0x0e, 0x0c, 0x0f, 0x12, 0x0c,
	0x0f, 0x03, 0x06, 0x0d, 0x1e, 0x0c, 0x0a, 0x1e, 0x0c, 0x0c, 0x0a, 0x06, 0x04, 0x00, 0x00, 0x00
};

const char sfx_powerup[165] = {
	0x10, 2, 0x00, 0x1e, 0x06, 0x0f, 0x1c, 0x04, 0x0f, 0x0c, 0x0c, 0x0f, 0x0c, 0x0c, 0x0f, 0x0c,
	0x0c, 0x0f, 0x1c, 0x04, 0x0f, 0x1b, 0x04, 0x0a, 0x16, 0x04, 0x09, 0x12, 0x04, 0x07, 0x12, 0x04,
	0x0e, 0x12, 0x04, 0x08, 0x0d, 0x04, 0x03, 0x12, 0x04, 0x08, 0x12, 0x04, 0x0f, 0x0b, 0x0c, 0x0f,
	0x0b, 0x0c, 0x0f, 0x0b, 0x0c, 0x0c, 0x1c, 0x04, 0x06, 0x1c, 0x04, 0x0c, 0x07, 0x0c, 0x0f, 0x07,
	0x0c, 0x09, 0x05, 0x0c, 0x0a, 0x18, 0x04, 0x07, 0x07, 0x0c, 0x0f, 0x07, 0x0c, 0x0a, 0x05, 0x0c,
	0x0c, 0x05, 0x0c, 0x05, 0x1e, 0x06, 0x03, 0x03, 0x0c, 0x04, 0x03, 0x0c, 0x04, 0x03, 0x0c, 0x04,
	0x02, 0x0c, 0x08, 0x03, 0x0c, 0x04, 0x1e, 0x06, 0x02, 0x0a, 0x0c, 0x0e, 0x0a, 0x0c, 0x0f, 0x1e,
	0x04, 0x0d, 0x19, 0x04, 0x08, 0x15, 0x04, 0x0b, 0x15, 0x04, 0x0f, 0x15, 0x04, 0x08, 0x0f, 0x04,
	0x07, 0x15, 0x04, 0x07, 0x15, 0x04, 0x0c, 0x06, 0x0c, 0x07, 0x0f, 0x04, 0x02, 0x00, 0x06, 0x04,
	0x01, 0x0c, 0x00, 0x0a, 0x04, 0x04, 0x0a, 0x04, 0x08, 0x0a, 0x04, 0x03, 0x07, 0x04, 0x03, 0x0a,
	0x04, 0x03, 0x00, 0x00, 0x00
};

}

// Game state management
#define MISSILES_SPEED 4 
#define MISSILES_NB_MAX 5
ramchip char missile_xpos[MISSILES_NB_MAX], missile_ypos[MISSILES_NB_MAX], missile_type[MISSILES_NB_MAX];
ramchip char nb_missiles, missile_first;

#define CIRCLES_NB_MAX 5
ramchip char circle_xpos[MISSILES_NB_MAX], circle_ypos[MISSILES_NB_MAX], circle_state[MISSILES_NB_MAX];
ramchip char nb_circles, circle_first;

#define ENEMY_NB_MAX 10
ramchip char enemy_xpos[ENEMY_NB_MAX], enemy_ypos[ENEMY_NB_MAX], enemy_type[ENEMY_NB_MAX], enemy_state[ENEMY_NB_MAX], enemy_lives[ENEMY_NB_MAX], enemy_counter1[ENEMY_NB_MAX], enemy_counter2[ENEMY_NB_MAX];
ramchip char nb_enemies, enemy_first;

#define BULLETS_NB_MAX 32 
ramchip short bullet_xpos[BULLETS_NB_MAX], bullet_ypos[BULLETS_NB_MAX];
ramchip char bullet_direction[BULLETS_NB_MAX];
ramchip char nb_bullets, bullet_first;

#define BIG_EXPLOSIONS_NB_MAX 4
ramchip char big_explosion_xpos[BIG_EXPLOSIONS_NB_MAX], big_explosion_ypos[BIG_EXPLOSIONS_NB_MAX];
ramchip char big_explosion_counter[BIG_EXPLOSIONS_NB_MAX];
ramchip char nb_big_explosions, big_explosion_first;

#define EXPLOSIONS_NB_MAX 4
ramchip char explosion_xpos[EXPLOSIONS_NB_MAX], explosion_ypos[EXPLOSIONS_NB_MAX];
ramchip char explosion_counter[EXPLOSIONS_NB_MAX];
ramchip char nb_explosions, explosion_first;

ramchip char button_pressed;
ramchip char R9_xpos, R9_ypos, R9_state, R9_state_counter; 
ramchip char R9_shield_xpos, R9_shield_counter1, R9_shield_counter2, R9_shield_state;
ramchip char R9_shield_bonus_accumulator;
ramchip char R9_charging_counter, R9_charging_counter2;
const char *R9_shield_sequence[] = {satellite1, satellite2, satellite3, satellite4};
const char *R9_charging_sequence[] = {beam1, beam2, beam3};

#define R9_CIRCLE_FIRE  4
#define R9_CHARGING     8

ramchip char nb_lives;
ramchip unsigned int score, high_score;
ramchip char update_score;
ramchip char display_score_str[5];
ramchip char display_high_score_str[5];
ramchip char level_progress_low, level_progress_high;
ramchip char counter_tail;

ramchip char game_state;
#define STATE_RUNNING  0
#define STATE_GAMEOVER 1

ramchip char *sfx_to_play;

// Input: X = missile index
void destroy_missile()
{
    missile_xpos[X] = -1; // Removed
    if (X == missile_first) {
        do {
            nb_missiles--;
            X++;
            if (X == MISSILES_NB_MAX) X = 0;
        } while (nb_missiles && missile_xpos[X] == -1);
        missile_first = X;
    }
}

// Input: X = circle index
void destroy_circle()
{
    circle_xpos[X] = -1; // Removed
    if (X == circle_first) {
        do {
            nb_circles--;
            X++;
            if (X == CIRCLES_NB_MAX) X = 0;
        } while (nb_circles && circle_xpos[X] == -1);
        circle_first = X;
    }
}

void lose_one_life();

// Put the dobkeratops code in Bank 1 & gfx in Bank 2
#include "example_dobkeratops_banked.c"

void game_init()
{
    nb_lives = 3;
    score = 0;
    high_score = 0;
    update_score = 1;
    level_progress_high = 0;
    level_progress_low = 0;

    // Init game state variables
    nb_missiles = 0;
    missile_first = 0;
    nb_circles = 0;
    circle_first = 0;
    nb_enemies = 0;
    enemy_first = 0;
    nb_bullets = 0;
    bullet_first = 0;
    nb_big_explosions = 0;
    big_explosion_first = 0;
    nb_explosions = 0;
    explosion_first = 0;

    // Initialize R9 state
    R9_xpos = 20;
    R9_ypos = 80;
    R9_state = 1;
    R9_state_counter = 100;
    R9_shield_state = 0;
    R9_shield_bonus_accumulator = 0;
    R9_charging_counter = 0;
    R9_charging_counter2 = 0;

    // Initialize boss
    counter_tail = 0;

    game_state = STATE_RUNNING;
}

void draw_gameover()
{
    char i, x, xx = (R9_state_counter << 1), *ptr;
    x = xx - 36;
    ptr = game;
    for (i = 0; i != 2; i++) {
        multisprite_display_sprite_ex(x, ((224 - 16 - 16) / 2), ptr, 9, 1, 0);
        ptr = over;
        x = 160 - xx;
    }
    R9_state_counter++;
    if (R9_state_counter == 41) {
        R9_state_counter = 40;
        game_state = STATE_GAMEOVER;
    }
}

void big_explosion(char x, char y)
{
    char last;
    sfx_to_play = sfx_bigboom;
    char xp = x - 12;
    char yp = y - 24;
    if (yp < 0) yp = 0; else if (yp >= 224 - 16 - 49) yp = 224 - 16 - 50;
    if (nb_big_explosions != BIG_EXPLOSIONS_NB_MAX) {
        last = big_explosion_first + nb_big_explosions++;
        if (last >= BIG_EXPLOSIONS_NB_MAX) last -= BIG_EXPLOSIONS_NB_MAX; 
        big_explosion_xpos[X = last] = xp;
        big_explosion_ypos[X] = yp;
        big_explosion_counter[X] = 20;
    }
}

void explosion(char x, char y)
{
    char last;
    sfx_to_play = sfx_eek2;
    if (y < 0) y = 0; else if (y >= 224 - 16 - 17) y = 224 - 16 - 18;
    if (nb_explosions != EXPLOSIONS_NB_MAX) {
        last = explosion_first + nb_explosions++;
        if (last >= EXPLOSIONS_NB_MAX) last -= EXPLOSIONS_NB_MAX; 
        explosion_xpos[X = last] = x;
        explosion_ypos[X] = y;
        explosion_counter[X] = 20;
    }
}

void lose_one_life()
{
    // Explosion
    nb_lives--;
    big_explosion(R9_xpos + 8, R9_ypos + 6);
    if (nb_lives) {
        R9_state = 1;
        R9_state_counter = 100;
    } else {
        nb_lives = 3;
        R9_state = 3; // Gameover
    }
    R9_shield_state = 0;
    Y = (-(nb_lives << 1)) & 0x1f;
    _ms_b0_dl13[X = 8] = Y; // 13th zone
    _ms_b1_dl13[X] = Y; // on the second buffer
}

const signed char sin[120] = {0, 2, 3, 5, 6, 8, 9, 11, 12, 14, 15, 16, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 27, 28, 29, 29, 29, 30, 30, 30, 30, 30, 30, 30, 29, 29, 29, 28, 27, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 16, 15, 14, 12, 11, 9, 8, 6, 5, 3, 2, 0, -2, -3, -5, -6, -8, -9, -11, -12, -14, -15, -16, -18, -19, -20, -21, -22, -23, -24, -25, -26, -27, -27, -28, -29, -29, -29, -30, -30, -30, -30, -30, -30, -30, -29, -29, -29, -28, -27, -27, -26, -25, -24, -23, -22, -21, -20, -19, -18, -16, -15, -14, -12, -11, -9, -8, -6, -5, -3, -2};
const char *patapata_sprites[4] = {patapata1, patapata2, patapata3, patapata2};

void spawn_papapatas()
{
    char c, last, i = 0;
    for (c = 0; c != 8; i += 3, c++) {
        if (nb_enemies != ENEMY_NB_MAX) {
            last = enemy_first + nb_enemies++;
            if (last >= ENEMY_NB_MAX) last -= ENEMY_NB_MAX; 
            enemy_xpos[X = last] = 160;
            enemy_ypos[X] = 100;
            enemy_type[X] = 0;
            enemy_state[X] = 0;
            enemy_lives[X] = i;
            enemy_counter1[X] = 0;
            enemy_counter2[X] = 0;
        }
    }
}

char check_enemy_collision(char xe, char ye)
{
    char i, c, x, y, collision = 0; 
    for (i = missile_first, c = nb_missiles; c != 0; i++, c--) {
        if (i == MISSILES_NB_MAX) {
            i = 0;
        }
        if (missile_xpos[X = i] != -1) {
            y = missile_ypos[X = i];
            x = missile_xpos[X];
            if (missile_type[X]) { // Big missile
                multisprite_compute_box_collision(xe, ye, 8, 12, x, y, 32, 16);
            } else {
                multisprite_compute_box_collision(xe, ye, 8, 12, x, y, 8, 4);
            }
            if (multisprite_collision_detected) {
                collision = 1;
                if (!missile_type[X]) {
                    // It's a small missile. Destroy it
                    destroy_missile();  
                }
            }
        }
    }
    
    // Check collisions with circles
    for (i = circle_first, c = nb_circles; c != 0; i++, c--) {
        if (i == CIRCLES_NB_MAX) {
            i = 0;
        }
        if (circle_xpos[X = i] != -1) {
            y = circle_ypos[X = i];
            x = circle_xpos[X];
            multisprite_compute_box_collision(xe, ye, 8, 12, x, y, 16, 32);
            if (multisprite_collision_detected) {
                collision = 1;
            }
        }
    }

    return collision;
}

void draw_enemies()
{
    char i, c, x, y, destroyed, display_it;
    char *gfx;
    for (i = enemy_first, c = nb_enemies; c != 0 ; i++, c--) {
        if (i == ENEMY_NB_MAX) {
            i = 0;
        }
        X = i;
        if (enemy_type[X] != -1) {
            destroyed = 0;
            display_it = 0;
            if (enemy_type[X] == 0) {
                // This is a Pata-pata
                enemy_counter1[X]++;
                if (enemy_counter1[X] == 5) {
                    if (enemy_lives[X]) {
                        enemy_lives[X]--;
                    } else {
                        enemy_state[X]++;
                        if (enemy_state[X] == 4) enemy_state[X] = 0;
                    }
                    enemy_counter1[X] = 0;
                }
                if (!enemy_lives[X]) {
                    x = enemy_xpos[X];
                    if (x == 255 - 16) {
                        R9_shield_bonus_accumulator = 0;
                        destroyed = 1; // Out of screen
                    }
                    enemy_xpos[X]--;
                    y = enemy_ypos[X] + (sin[Y = enemy_counter2[X]] >> 1);
                    enemy_counter2[X]++;
                    if (enemy_counter2[X] == 120) {
                        enemy_counter2[X] = 0;
                    }
                    // Check collisions with circles or missiles
                    if (check_enemy_collision(x, y + 2)) {
                        destroyed = 1;
                        explosion(x, y);
                        score += 10;
                        update_score = 1;
                        R9_shield_bonus_accumulator++;
                    } else {
                        display_it = 1;
                    }
                    X = i; // Restore X register destroyed by check_enemy_collision function
                    // Check collision with R9
                    if ((R9_state & 1) == 0) {
                        multisprite_compute_box_collision(x, y + 2, 8, 12, R9_xpos, R9_ypos, 16, 14);
                        if (multisprite_collision_detected) {
                            lose_one_life();
                        }
                    }
                }
            }
            if (destroyed) {
                enemy_type[X] = -1; // Removed
                if (X == enemy_first) {
                    do {
                        nb_enemies--;
                        X++;
                        if (X == ENEMY_NB_MAX) X = 0;
                    } while (nb_enemies && enemy_type[X] == -1);
                    enemy_first = X;
                }
            } else if (display_it) {
                gfx = patapata_sprites[Y = enemy_state[X]];
                multisprite_display_sprite_ex(x, y, gfx, 2, 1, 0);
            }
        }
    }
}

void step()
{
    char x, y, i, j, c, state;
    char *gfx;
    char draw_R9;
   
    if (R9_shield_bonus_accumulator >= 8) {
        R9_shield_bonus_accumulator = 0;
        score += 100;
        update_score = 1;
        // If the shield is not there
        if (R9_shield_state == 0) {
            sfx_to_play = sfx_powerup;
            R9_shield_state = 1;
            R9_shield_xpos = 200;
            R9_shield_counter1 = 0;
            R9_shield_counter2 = 0;
        }
    }

    // Draw R9
    if ((R9_state & 1) == 0) {
        draw_R9 = 1;
        // Check collision with background
        char c = sparse_tiling_collision(R9_ypos + 6, R9_xpos, R9_xpos + 15);
        if (c != -1) {
            lose_one_life();
        }
    } else if (R9_state == 1) {
        // Blinking returning R9
        draw_R9 = R9_state_counter & 8;
        R9_state_counter--;
        if (R9_state_counter == 0) {
            R9_state = 0;
        }
    } else if (R9_state == 3) {
        draw_R9 = 0;
    }

    if (draw_R9) {
        char display_shield = 0;
        multisprite_display_small_sprite_ex(R9_xpos, R9_ypos, R9, 8, 0, 4, 1);
        if (R9_state & R9_CIRCLE_FIRE) {
            x = R9_xpos + 17;
            y = R9_ypos - 1;
            display_shield = 1;
        } else if (R9_shield_state == 1) {
            x = 160 - R9_xpos;
            if (R9_shield_xpos != x && (R9_shield_counter2 & 1)) {
                if (R9_shield_xpos >= x) R9_shield_xpos--;
                else R9_shield_xpos++;
            }
            if (R9_shield_xpos == R9_xpos + 12) {
                // Attach shield
                R9_state |= R9_CIRCLE_FIRE;
            }
            x = R9_shield_xpos;
            y = R9_ypos;
            display_shield = 1;
        }
        if (display_shield) {
            R9_shield_counter2++;
            if (R9_shield_counter2 == 5) {
                R9_shield_counter2 = 0;
                R9_shield_counter1++;
                if (R9_shield_counter1 == 4) R9_shield_counter1 = 0;
            }
            gfx = R9_shield_sequence[X = R9_shield_counter1];
            multisprite_display_sprite_ex(x, y, gfx, 4, 0, 1);
        }
        if ((R9_state & R9_CHARGING) && R9_charging_counter >= 10) {
            gfx = R9_charging_sequence[X = (R9_charging_counter2 >> 2)];
            if (R9_state & R9_CIRCLE_FIRE) {
                x = R9_xpos + 17 + 8;
            } else {
                x = R9_xpos + 16;
            }
            y = R9_ypos + 1;
            multisprite_display_small_sprite_ex(x, y, gfx, 2, 0, 5, 0);
            R9_charging_counter2++;
            if (R9_charging_counter2 == 12) {
                R9_charging_counter2 = 0;
            }
        }
    }
    
    // Draw enemies
    draw_enemies();

    // Draw missiles
    for (i = missile_first, c = nb_missiles; c != 0; i++, c--) {
        if (i == MISSILES_NB_MAX) {
            i = 0;
        }
        if (missile_xpos[X = i] != -1) {
            y = missile_ypos[X];
            x = missile_xpos[X] + MISSILES_SPEED;
            if (x >= 160 || sparse_tiling_collision(y + 1, x, x + 7) != -1 ) {
                // Out of screen or collided with background
                X = i;
                destroy_missile();
            } else {
                missile_xpos[X = i] = x;
                // Draw missile
                if (missile_type[X = i] == 1) {
                    multisprite_display_sprite_ex(x, y, big_fire, 8, 1, 0);
                } else {
                    multisprite_display_small_sprite_ex(x, y, missile, 2, 0, 12, 0);
                }
            }
        }
    }
    
    // Display big explosions
    for (i = big_explosion_first, c = nb_big_explosions; c != 0; i++, c--) {
        char xbig_explosion, ybig_explosion;
        if (i == BIG_EXPLOSIONS_NB_MAX) {
            i = 0;
        }
        X = i;
        if (big_explosion_counter[X]) {
            char *gfx;
            xbig_explosion = big_explosion_xpos[X];
            ybig_explosion = big_explosion_ypos[X];
            big_explosion_counter[X]--;
            if (big_explosion_counter[X] >= 16) {
                gfx = big_explosion1;
            } else if (big_explosion_counter[X] >= 12) {
                gfx = big_explosion2;
            } else if (big_explosion_counter[X] >= 8) {
                gfx = big_explosion3;
            } else if (big_explosion_counter[X] >= 4) {
                gfx = big_explosion4;
            } else gfx = big_explosion5;
            multisprite_display_big_sprite(xbig_explosion, ybig_explosion, gfx, 6, 0, 3, 0);
        } else {
            if (X == big_explosion_first) {
                do {
                    nb_big_explosions--;
                    X++;
                    if (X == BIG_EXPLOSIONS_NB_MAX) X = 0;
                } while (nb_big_explosions && big_explosion_counter[X] == 0);
                big_explosion_first = X;
            }
        }
    }
    
    // Display explosions
    for (i = explosion_first, c = nb_explosions; c != 0; i++, c--) {
        char xexplosion, yexplosion;
        if (i == EXPLOSIONS_NB_MAX) {
            i = 0;
        }
        X = i;
        if (explosion_counter[X]) {
            char *gfx;
            xexplosion = explosion_xpos[X];
            yexplosion = explosion_ypos[X];
            explosion_counter[X]--;
            if (explosion_counter[X] >= 15) {
                gfx = explosion1;
            } else if (explosion_counter[X] >= 10) {
                gfx = explosion2;
            } else if (explosion_counter[X] >= 5) {
                gfx = explosion3;
            } else gfx = explosion4;
            multisprite_display_sprite_ex(xexplosion, yexplosion, gfx, 2, 0, 0);
        } else {
            if (X == explosion_first) {
                do {
                    nb_explosions--;
                    X++;
                    if (X == EXPLOSIONS_NB_MAX) X = 0;
                } while (nb_explosions && explosion_counter[X] == 0);
                explosion_first = X;
            }
        }
    }
    
    if (R9_state != 3) { // If it's not gameover
        // Draw bullets (last, so if there is a DMA issue, it doesn't prevent R9s to be displayed)
        for (i = bullet_first, c = nb_bullets; c != 0; i++, c--) {
            char xbullet, ybullet;
            if (i == BULLETS_NB_MAX) {
                i = 0;
            }
            X = i;
            Y = bullet_direction[X];
            if (Y != 255) {
                bullet_xpos[X] += dx[Y];
                bullet_ypos[X] += dy[Y];
                xbullet = bullet_xpos[X] >> 8;
                ybullet = bullet_ypos[X] >> 8;
                if (xbullet < 5 || xbullet >= 156 || ybullet < 5 || ybullet >= MS_YMAX - 20 - 16) {
                    bullet_direction[X] = 255; // Removed
                    if (X == bullet_first) {
                        do {
                            nb_bullets--;
                            X++;
                            if (X == BULLETS_NB_MAX) X = 0;
                        } while (nb_bullets && bullet_direction[X] == 255);
                        bullet_first = X;
                    }
                } else {
                    multisprite_display_small_sprite_ex(xbullet, ybullet, bullet1, 1, 3, 8, 0); 
                    if (R9_state == 0) {
                        multisprite_compute_collision(xbullet, ybullet, 4, 8, R9_xpos, R9_ypos, 16, 14, collision_bullet1_R9);
                        if (multisprite_collision_detected) {
                            lose_one_life();
                        }
                    } 
                }
            }
        }
    
        // Draw circles
        for (i = circle_first, j = nb_circles; j != 0; i++, j--) {
            if (i == CIRCLES_NB_MAX) {
                i = 0;
            }
            if (circle_xpos[X = i] != -1) {
                y = circle_ypos[X = i];
                x = circle_xpos[X];
                state = circle_state[X];
                if (x >= 160) { // Out of screen or collided with background
                    circle_xpos[X = i] = -1; // Removed
                    if (X == circle_first) {
                        do {
                            nb_circles--;
                            X++;
                            if (X == CIRCLES_NB_MAX) X = 0;
                        } while (nb_circles && circle_xpos[X] == -1);
                        circle_first = X;
                    }
                } else {
                    char w, xp, yp;
                    // Draw circle
                    if (state < 11) {
                        for (c = 0; c != 2; c++) {
                            if (c == 0) {
                                gfx = big_circle_top;
                                yp = y - 8;
                            } else {
                                gfx = big_circle_bottom;
                                yp = y + 24;
                            }
                            if (state < 6) {
                                w = state + 1;
                            } else {
                                w = state - 5;
                                gfx += w;
                                w = 11 - state;
                            }
                            multisprite_display_sprite_ex(x, yp, gfx, w, 1, 0);
                        }   
                    }
                    if (state >= 5) {
                        c = state - 5;
                        if (c < 6) w = c + 1;
                        else w = 7;
                        if (state < 11) {
                            gfx = circles_top;
                            xp = x + 20 - (c << 2);
                        } else {
                            c = state - 10;
                            gfx = circles_top + c; 
                            xp = x;
                        }
                        multisprite_display_sprite_ex(xp, y, gfx, w, 1, 0);
                        if (state < 11) {
                            gfx = circles_bottom;
                        } else {
                            gfx = circles_bottom + c;
                            if (state >= 17) state -= 7;
                        }
                        yp = y + 16;
                        multisprite_display_sprite_ex(xp, yp, gfx, w, 1, 0);
                    }
                    if (state >= 5) {
                        x += 4;
                        circle_xpos[X = i] = x;
                        if (state == 10) x += 20;
                    }
                    state++;
                    circle_state[X = i] = state;
                }
            }
        }
    } else draw_gameover();
}

void fire()
{
    char last;
    if (R9_state & R9_CIRCLE_FIRE) {
        if (nb_circles != CIRCLES_NB_MAX) {
            sfx_to_play = sfx_pewpew;
            last = circle_first + nb_circles++;
            if (last >= CIRCLES_NB_MAX) last -= CIRCLES_NB_MAX; 
            circle_xpos[X = last] = R9_xpos + 20;
            circle_ypos[X] = R9_ypos - 10;
            circle_state[X] = 0;
        }
    } else {
        if (nb_missiles != MISSILES_NB_MAX) {
            sfx_to_play = sfx_plainlaser;
            last = missile_first + nb_missiles++;
            if (last >= MISSILES_NB_MAX) last -= MISSILES_NB_MAX; 
            missile_xpos[X = last] = R9_xpos + 8;
            if (R9_charging_counter >= 16) {
                missile_ypos[X] = R9_ypos;
                missile_type[X] = 1;
            } else {
                missile_ypos[X] = R9_ypos + 6;
                missile_type[X] = 0;
            }
        }
    }
}

void beam_meter_update();

void joystick_input()
{
    joystick_update();
    if (joystick[0] & JOYSTICK_LEFT) {
        if (R9_xpos) R9_xpos--;
    } else if (joystick[0] & JOYSTICK_RIGHT) {
        if (R9_xpos < 160 - 16) R9_xpos++;
    }
    if (joystick[0] & JOYSTICK_UP) {
        if (R9_ypos > 2) R9_ypos -= 2;
    } else {
        if (joystick[0] & JOYSTICK_DOWN) {
            if (R9_ypos < 208 - 14) R9_ypos += 2;
        }
    }
    if (joystick[0] & JOYSTICK_BUTTON1) {
        if (button_pressed) {
            if (R9_charging_counter != 32) {
                R9_charging_counter++;
                beam_meter_update();
            }
        } else {
            button_pressed = 1;
            if ((R9_state & 1) == 0) {
                R9_state |= R9_CHARGING;
            }
        }
    } else {
        button_pressed = 0;
        R9_state &= ~R9_CHARGING;
        if (R9_charging_counter != 0 && R9_state != 3) {
            fire();
            R9_charging_counter = 0;
            beam_meter_update();
        }
    }
}

// Background scrolling
ramchip char scroll_background_counter1, scroll_background_counter2;

void scroll_stars(char speed)
{
    char c;
    char pos1, pos2;
    scroll_background_counter1++;
    if (scroll_background_counter1 == speed) {
        scroll_background_counter1 = 0;
        scroll_background_counter2--;
    }
    pos1 = scroll_background_counter2;
    pos2 = scroll_background_counter2 << 1;
    if (_ms_buffer) {
        X = _MS_DLL_ARRAY_SIZE + 1;
    } else X = 1;
    
    _ms_tmpptr = _ms_dls[X];
    for (c = 0; c != 3; c++) {
        // Modify bytes 4 and 8 of the DLL entries (x position of background sprites=
        _ms_tmpptr[Y = 4] = pos1;
        pos1 += 100;
        _ms_tmpptr = _ms_dls[++X];
        _ms_tmpptr[Y = 4] = pos2;
        pos2 += 200;
        _ms_tmpptr = _ms_dls[++X];
        _ms_tmpptr[Y = 4] = pos1;
        pos1 += 100;
        _ms_tmpptr = _ms_dls[++X];
        _ms_tmpptr[Y = 4] = pos2;
        pos2 += 100;
        _ms_tmpptr = _ms_dls[++X];
    }
}

INIT_BANK void my_multisprite_init()
{
    *BACKGRND = 0x0;
    
    multisprite_get_tv();
    multisprite_clear();
    multisprite_save();

    _ms_tmpptr = _ms_b0_dll;
    for (X = 0, _ms_tmp = 0; _ms_tmp <= 1; _ms_tmp++) {
        // Build DLL
        // 69 blank lines for PAL
        // 19 blank lines for NTSC
        if (_ms_pal_detected) {
            // 16 blank lines
            _ms_tmpptr[Y = 0] = 0x0f;  // 16 lines
            _ms_tmpptr[++Y] = _ms_set_wm_dl >> 8;
            _ms_tmpptr[++Y] = _ms_set_wm_dl;
            // 16 blank lines
            _ms_tmpptr[++Y] = 0x0f;  // 16 lines
            _ms_tmpptr[++Y] = _ms_blank_dl >> 8;
            _ms_tmpptr[++Y] = _ms_blank_dl;
        } else {
            _ms_tmpptr[Y = 0] = 0x08; // 9 lines
            _ms_tmpptr[++Y] = _ms_set_wm_dl >> 8;
            _ms_tmpptr[++Y] = _ms_set_wm_dl;
        }
        // 16 pixel high regions (208 pixels = 13 regions)
        for (_ms_tmp2 = 0; _ms_tmp2 != 13; X++, _ms_tmp2++) {
            _ms_tmpptr[++Y] = 0x4f; // 16 lines
            _ms_tmpptr[++Y] = _ms_dls[X] >> 8; // High address
            _ms_tmpptr[++Y] = _ms_dls[X]; // Low address
        }
        // 1 pixel high region to separate from 320A scoreboard. This gives some little room for the DLI to execute
        _ms_tmpptr[++Y] = 0x00; // 1 line
        _ms_tmpptr[++Y] = _ms_blank_dl >> 8;
        _ms_tmpptr[++Y] = _ms_blank_dl;
        // 8 pixel high regions (320A)
        for (_ms_tmp2 = 0; _ms_tmp2 != 2; X++, _ms_tmp2++) {
            _ms_tmpptr[++Y] = 0x07; // 8 lines
            _ms_tmpptr[++Y] = _ms_dls[X] >> 8; // High address
            _ms_tmpptr[++Y] = _ms_dls[X]; // Low address
        }
        X++;
        if (_ms_pal_detected) {
            // 16 blank lines
            _ms_tmpptr[++Y] = 0x0f;  // 16 lines
            _ms_tmpptr[++Y] = _ms_blank_dl >> 8;
            _ms_tmpptr[++Y] = _ms_blank_dl;
            // 16 blank lines
            _ms_tmpptr[++Y] = 0x0f;  // 16 lines
            _ms_tmpptr[++Y] = _ms_blank_dl >> 8;
            _ms_tmpptr[++Y] = _ms_blank_dl;
            // 4 blank lines
            _ms_tmpptr[++Y] = 0x03;  // 4 lines
            _ms_tmpptr[++Y] = _ms_blank_dl >> 8;
            _ms_tmpptr[++Y] = _ms_blank_dl;
        } else {
            _ms_tmpptr[++Y] = 0x08; // 9 lines
            _ms_tmpptr[++Y] = _ms_blank_dl >> 8;
            _ms_tmpptr[++Y] = _ms_blank_dl;
        }
        _ms_tmpptr = _ms_b1_dll;
    }
    multisprite_start();
    multisprite_set_charbase(alphabet);
}

bank1 void rtype_level1_palette()
{
    // Beige palette
    *P4C1 = multisprite_color(0x12); 
    *P4C2 = multisprite_color(0x14); 
    *P4C3 = multisprite_color(0x16); 
    
    // Blue palette
    *P5C1 = multisprite_color(0x84); // Dark blue 
    *P5C2 = multisprite_color(0x87); // Light blue
    *P5C3 = multisprite_color(0xac); // Turquoise 

    // Rose palette
    *P6C1 = multisprite_color(0x34); // Dark Rose
    *P6C2 = multisprite_color(0x38); // Rose 
    *P6C3 = multisprite_color(0x3c); // Light Rose 

    // Grey palette 
    *P7C1 = 0x04; // Dark gray
    *P7C2 = 0x08; // Medium gray
    *P7C3 = 0x0c; // Dark gray
}

// Scoreboard display functions
const char oneup[3] = {27, 'U' - 'A', 'P' - 'A'};
const char high[4] = {'H' - 'A', 'I' - 'A', 'G' - 'A', 'H' - 'A'};
const char beam[4] = {'B' - 'A', 'E' - 'A', 'A' - 'A', 'M' - 'A'};
    
INIT_BANK void scoreboard_display()
{
    multisprite_display_sprite_aligned(13 * 4, 13 * 16, beam_meter_in, 1, 1, 0);
    multisprite_display_sprite_aligned(0, 13 * 16, lives, 6, 0, 1);
    multisprite_display_sprite_aligned(13 * 4, 13 * 16, beam_meter_out, 18, 2, 0);
    multisprite_display_tiles(3 * 4, 14, oneup, 3, 2);
    multisprite_display_tiles(7 * 4, 14, display_score_str, 5, 0);
    multisprite_display_tiles(16 * 4, 14, high, 4, 2);
    multisprite_display_tiles(21 * 4, 14, display_high_score_str, 5, 0);
    multisprite_display_tiles(8 * 4, 13, beam, 4, 2);
}

void beam_meter_update()
{
    char i = (-((R9_charging_counter >> 1) + 1) & 0x1f) | (1 << 5);
    _ms_b0_dl13[X = 3] = i; // 13th zone
    _ms_b1_dl13[X] = i; // on the second buffer
}

void display_score_update(char *score_str)
{
    char display_score_ascii[6];
    itoa(score, display_score_ascii, 10);
    X = strlen(display_score_ascii); 
    for (Y = 0; Y != 5 - X; Y++) {
        score_str[Y] = 26; // '0'
    }
    Y = 4;
    do {
        score_str[Y--] = 26 + (display_score_ascii[--X] - '0');
    } while (X);
}

INIT_BANK void display_init()
{
    // Sprites palette
    // Fire
    *P0C1 = multisprite_color(0x37); // Orange
    *P0C2 = multisprite_color(0x1c); // Yellow 
    *P0C3 = 0x0f; // White
    
    // Blue & Red palette
    *P1C1 = multisprite_color(0x84); // Dark blue 
    *P1C2 = multisprite_color(0x34); // Red
    *P1C3 = multisprite_color(0xac); // Turquoise 

    // Grey palette
    *P2C1 = 0x04; // Dark gray
    *P2C2 = 0x08; // Medium gray
    *P2C3 = 0x0c; // Dark gray

    *P3C1 = multisprite_color(0xd0); 
    *P3C2 = multisprite_color(0x87); // Light blue
    *P3C3 = multisprite_color(0xd1); 
   
    // Background display
    char c, d, y = 0;
    for (c = 3; c != 0; c--) {
        for (d = 2; d != 0; d--) {
            y += 16;
            multisprite_display_sprite_aligned(0, y, star1, 1, 0, 0);
            y += 16;
            multisprite_display_sprite_aligned(0, y, star2, 1, 0, 0);
        }
    }

    scoreboard_display();
    // Save it
    multisprite_save();
}

#define DOBKERATOPS_GETS_IN (((64 * 8) + 160) / 32) 

// DLI management
ramchip char dli_counter;
ramchip char rom_bank;
ramchip char scoreboard_and_music;

void interrupt dli()
{
    if (dli_counter != -1) {
        scoreboard_and_music = 1;
        if (level_progress_high >= DOBKERATOPS_GETS_IN) {
            if (dli_counter == 0) {
                // Switch to dobkeratops palette    
                if (_ms_pal_detected) {
                    *P4C1 = 0x4c; 
                    *P4C2 = 0x49; 
                    *P4C3 = 0x46; 
                    *P5C1 = 0x34; 
                    *P5C2 = 0x32; 
                    *P7C1 = 0xd9; 
                    *P7C2 = 0xd6; 
                    *P7C3 = 0x53; // Red (unused)
                } else {
                    *P4C1 = 0x3c; 
                    *P4C2 = 0x39; 
                    *P4C3 = 0x36; 
                    *P5C1 = 0x24; 
                    *P5C2 = 0x22; 
                    *P7C1 = 0xc9; 
                    *P7C2 = 0xc6; 
                    *P7C3 = 0x43; // Red (unused)
                }
                *P5C3 = 0x0e; 
                *P6C1 = 0x0a; 
                *P6C2 = 0x04; 
                *P6C3 = 0x02; 
                scoreboard_and_music = 0;
                dli_counter = 1;
            } else if (dli_counter == 1) {
                // Switch to level1 palette
                if (_ms_pal_detected) {
                    // Beige palette
                    *P4C1 = 0x22; 
                    *P4C2 = 0x24; 
                    *P4C3 = 0x26; 
                    // Blue palette
                    *P5C1 = 0x94; // Dark blue 
                    *P5C2 = 0x97; // Light blue
                    *P5C3 = 0xbc; // Turquoise 
                                  // Rose palette
                    *P6C1 = 0x44; // Dark Rose
                    *P6C2 = 0x48; // Rose 
                    *P6C3 = 0x4c; // Light Rose 
                } else {
                    // Beige palette
                    *P4C1 = 0x12; 
                    *P4C2 = 0x14; 
                    *P4C3 = 0x16; 
                    // Blue palette
                    *P5C1 = 0x84; // Dark blue 
                    *P5C2 = 0x87; // Light blue
                    *P5C3 = 0xac; // Turquoise 
                                  // Rose palette
                    *P6C1 = 0x34; // Dark Rose
                    *P6C2 = 0x38; // Rose 
                    *P6C3 = 0x3c; // Light Rose 
                }
                // Grey palette 
                *P7C1 = 0x04; // Dark gray
                *P7C2 = 0x08; // Medium gray
                *P7C3 = 0x0c; // Dark gray
                scoreboard_and_music = 0;
                dli_counter = 2;
            }
        }
        if (scoreboard_and_music) {
            // Set the RIOT timer to 32
            do {
                *TIM64T = 32 + 10;
            } while (*INTIM != 31 + 10);
            
            *CTRL = 0x43; // DMA on, 320A/C mode, One (1) byte characters mode

            // Play the music
            if (sfx_to_play) {
                sfx_schedule(sfx_to_play);
                sfx_to_play = NULL;
            }
            sfx_play();
#ifdef POKEY_MUSIC
            // This will switch to bank7
            pokey_play();
#endif
            // Wait for the end of timer
            while (*INTIM >= 10); // We may miss the 0 due to DMA. Take a 10 margin

            // Go back to the right rombank
            *ROM_SELECT = rom_bank;
            dli_counter = -1;
        }
    }
}

void main()
{
    char x = 0;

    dli_counter = -1;
    scroll_background_counter1 = 0;
    scroll_background_counter2 = 0;
    button_pressed = 0;
    rom_bank = 0;
    sfx_to_play = NULL;

    sfx_init();
#ifdef POKEY_MUSIC
    pokey_init();
#endif

    copy_dobkeratops_to_ram();
    joystick_init();
    my_multisprite_init(); // Custom multisprite init
    display_init();
    game_init();
   
    // Level 1 init  
    rtype_level1_palette(); // In bank1, so that everything thet follows is in bank1 also
    sparse_tiling_init_vmem(tilemap_level1_data_ptrs, brown_tiles1);

    sparse_tiling_display();
    multisprite_flip();
    sparse_tiling_scroll(1); // Offset of 1 compared to previous screen
    sparse_tiling_display();
    multisprite_flip();
    
    multisprite_enable_dli(13);

    do {
        if (level_progress_high < DOBKERATOPS_GETS_IN) {
            scroll_stars(4);
            sparse_tiling_scroll(1); // Scroll 1 pixels to the right for this buffer (so 0.5 pixel from frame to frame due to double buffering)
            level_progress_low++;
            if (level_progress_low == 32) {
                level_progress_high++;
                level_progress_low = 0;
                if (level_progress_high == 3) {
                    spawn_papapatas();
                }
            }
        } else {
            scroll_stars(1);
            x = 180 + DOBKERATOPS_GETS_IN - level_progress_high;
            draw_dobkeratops(x, 16, counter_tail);
            counter_tail++;
            if (counter_tail == 60) counter_tail = 0;
            x = 0;
            if (level_progress_low == 0) {
                if (level_progress_high == DOBKERATOPS_GETS_IN) {
                    sparse_tiling_scroll(1); // Scroll 1 pixels to the right for this buffer (so 0.5 pixel from frame to frame due to double buffering)
                    x = 1; // To active dlis on line 1 and 12 for dobkeratops palette switching
                }
            }
            if (level_progress_high < 114) {
                level_progress_low++;
                if (level_progress_low == 4) {
                    level_progress_high++;
                    level_progress_low = 0;
                }
            }
        }
        joystick_input();
        step();
        if (update_score) {
            display_score_update(display_score_str);
            if (score >= high_score) {
                high_score = score;
                display_score_update(display_high_score_str);
            }
            update_score = 0;
        }
        multisprite_flip();
        if (x == 1) {
            multisprite_enable_dli(1);
            multisprite_enable_dli(12);
            x = 0;
        }
        dli_counter = 0;
        *CTRL = 0x50; // DMA on, 160A/B mode, Two (2) byte characters mode
    } while (1);
}
