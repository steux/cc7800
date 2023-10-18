#include "prosystem.h"
#include "multisprite.h"
#include "joystick.h"

// Generated by sprites7800 bombjack_tiles.yaml 
#include "example_bombjack_tiles.c"

// Generated by sprites7800 bombjack_sprites.yaml 
#include "example_bombjack_sprites.c"

// Generated by tiles7800 --sparse bombjack_tiles.yaml --varname tileset_sphinx bombjack_sphinx.tmx
#include "example_bombjack_sphinx.c"

// Generated by tiles7800 --sparse bombjack_tiles.yaml --varname tilemap_arrangement_A bombjack_arrangement_A.tmx
#include "example_bombjack_arrangement_A.c"

const char topborder[15] = {6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8};
const char topborder_dl[] = { topborder, 0x60, topborder >> 8, (3 << 5) | (-15 & 0x1f), 0, 0, 0};

const char bottomborder[15] = {10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12};
const char bottomborder_dl[] = { bottomborder, 0x60, bottomborder >> 8, (3 << 5) | (-15 & 0x1f), 0, 0, 0};

#define BOMBS_RIGHT 0
#define BOMBS_UP    1
#define BOMBS_LEFT  2
#define BOMBS_DOWN  3

// Arrangements - x, y of first bomb, nb bombs, direction (0 to 3).
const char arrangement_A[] = { 
    6 + 6 * 8, 3 * 16 - 8, 4, BOMBS_RIGHT, 
    4 + 13 * 8, 8 + 4 * 16, 4, BOMBS_DOWN, 
    4, 5 * 16, 4, BOMBS_DOWN, 
    4 + 2 * 8, 0, 3, BOMBS_RIGHT,
    4 + 11 * 8, 11 * 16, 3, BOMBS_LEFT, 
    5 * 8, 13 * 16, 3, BOMBS_LEFT, 
    4 + 13 * 8, 0, 3, BOMBS_LEFT}; 
const char arrangements_nb_series[] = { 7 };
const char *arrangements[] = { arrangement_A }; 
const signed char arrangement_dx[4] = { 12, 0, -12, 0 };
const signed char arrangement_dy[4] = { 0, -24, 0, 24 };

ramchip char bomb_disposed[24];
char lighted_bomb;

void display_arrangement(char a)
{
    char *arrangement = arrangements[X = a];
    char i, j, k, nb_series = arrangements_nb_series[X];
    for (Y = 0, k = 0, i = 0; i != nb_series; i++) {
        char x = arrangement[Y++];
        char y = arrangement[Y++];
        char nb_bombs = arrangement[Y++];
        char direction = arrangement[Y++];
        _save_y = Y;
        for (j = 0; j != nb_bombs; k++, j++) {
            if (!bomb_disposed[X = k]) {
                lighted_bomb = X;
                multisprite_display_sprite_fast(x, y, bomb, 2, 2);
            }
            x += arrangement_dx[X = direction]; 
            y += arrangement_dy[X]; 
        }
        Y = _save_y;
    }
    if (lighted_bomb != 0) {
        // Display lighted bomb
    
    }
}

// All the bombjack states
#define BOMBJACK_LEFT           64
#define BOMBJACK_RIGHT          128
#define BOMBJACK_STILL          1
#define BOMBJACK_STILL_LEFT     (BOMBJACK_STILL | BOMBJACK_LEFT)
#define BOMBJACK_STILL_RIGHT    (BOMBJACK_STILL | BOMBJACK_RIGHT)
#define BOMBJACK_JUMPING        2
#define BOMBJACK_JUMPING_LEFT   (BOMBJACK_JUMPING | BOMBJACK_LEFT)
#define BOMBJACK_JUMPING_RIGHT  (BOMBJACK_JUMPING | BOMBJACK_RIGHT)
#define BOMBJACK_WALKING        4
#define BOMBJACK_WALKING_LEFT   (BOMBJACK_WALKING | BOMBJACK_LEFT)
#define BOMBJACK_WALKING_RIGHT  (BOMBJACK_WALKING | BOMBJACK_RIGHT)
#define BOMBJACK_FALLING        8 
#define BOMBJACK_FALLING_LEFT   (BOMBJACK_FALLING | BOMBJACK_LEFT) 
#define BOMBJACK_FALLING_RIGHT  (BOMBJACK_FALLING | BOMBJACK_RIGHT) 

#define BORDER_WIDTH 4
#define PLAYFIELD_HEIGHT 224
#define PLAYFIELD_WIDTH 112 
#define SPRITE_HEIGHT 16
#define SPRITE_WIDTH 12
#define PLATFORM_HEIGHT 8
#define GRAVITY 20 

ramchip char bombjack_xpos, bombjack_state, bombjack_counter;
ramchip char button_pressed, current_arrangement;
// ypos and yspeed are 16-bits to allow for fine vertical movement
ramchip unsigned short bombjack_yspeed, bombjack_ypos;

void bombjack_move_left()
{
    char x, top, collision;
    bombjack_xpos--;
    if (bombjack_xpos < 3) bombjack_xpos = 3;
    else {
        // Test if we bump into a platform with the head
        x = (bombjack_xpos - BORDER_WIDTH + 1) >> 3;
        top = (bombjack_ypos >> 8) >> 4;
        collision = multisprite_sparse_tiling_collision(top, x, x);
        if (collision != -1 && ((bombjack_ypos >> 8) & 0x0f) < PLATFORM_HEIGHT - 1) {
            bombjack_xpos++;
            return;
        }
        // Test if we bump into a platform with the foot 
        top = ((bombjack_ypos >> 8) + SPRITE_HEIGHT - 1) >> 4;
        collision = multisprite_sparse_tiling_collision(top, x, x);
        if (collision != -1) {
            bombjack_xpos++;
        }
    }
}

void bombjack_move_right()
{
    char x, top, collision;
    bombjack_xpos++;
    if (bombjack_xpos >= PLAYFIELD_WIDTH - SPRITE_WIDTH + 6) bombjack_xpos = PLAYFIELD_WIDTH - SPRITE_WIDTH + 5;
    else {
        // Test if we bump into a platform with the head
        x = (bombjack_xpos - BORDER_WIDTH + SPRITE_WIDTH - 3) >> 3;
        top = (bombjack_ypos >> 8) >> 4;
        collision = multisprite_sparse_tiling_collision(top, x, x);
        if (collision != -1 && ((bombjack_ypos >> 8) & 0x0f) < PLATFORM_HEIGHT - 1) {
            bombjack_xpos--;
            return;
        }
        // Test if we bump into a platform with the foot 
        top = ((bombjack_ypos >> 8) + SPRITE_HEIGHT - 1) >> 4;
        collision = multisprite_sparse_tiling_collision(top, x, x);
        if (collision != -1) {
            bombjack_xpos--;
        }
    }
}

void bombjack_dispose_bombs(char a)
{
    char *arrangement = arrangements[X = a];
    char x2 = bombjack_xpos + 2;
    char y2 = (bombjack_ypos >> 8) + 1;
    char i, j, k, nb_series = arrangements_nb_series[X];
    for (Y = 0, k = 0, i = 0; i != nb_series; i++) {
        char x = arrangement[Y++] + 1;
        char y = arrangement[Y++] + 6;
        char nb_bombs = arrangement[Y++];
        char direction = arrangement[Y++];
        for (j = 0; j != nb_bombs; k++, j++) {
            if (!bomb_disposed[X = k]) {
                multisprite_compute_box_collision(x, y, 5, 9, x2, y2, 7, 14);
                if (multisprite_collision_detected) {
                    bomb_disposed[X] = 1;
                }
            }
            x += arrangement_dx[X = direction]; 
            y += arrangement_dy[X]; 
        }
    }
}

void bombjack()
{
    char *gfx, y;
    char left, right, top, collision;
    if (bombjack_state & BOMBJACK_FALLING) {
        if (bombjack_state & BOMBJACK_LEFT) {
            gfx = bombjack_falling_left;
            bombjack_move_left();
        } else if (bombjack_state & BOMBJACK_RIGHT) {
            gfx = bombjack_falling_right;
            bombjack_move_right();
        } else {
            if (bombjack_yspeed == 0) {
                gfx = bombjack_jumping;
            } else {
                gfx = bombjack_falling;
            }
        }

        bombjack_yspeed += GRAVITY;
        bombjack_ypos += bombjack_yspeed;
        // Does it land on bottom of the screen ?
        if (bombjack_ypos >> 8 >= PLAYFIELD_HEIGHT - 16) {
            bombjack_ypos = (PLAYFIELD_HEIGHT - 16) << 8;
            bombjack_state = BOMBJACK_STILL;
        } else {
            // Does it land on a platform ?
            left = (bombjack_xpos + (4 - BORDER_WIDTH)) >> 3;
            right = (bombjack_xpos + (7 - BORDER_WIDTH)) >> 3;
            top = ((bombjack_ypos >> 8) >> 4) + 1;
            collision = multisprite_sparse_tiling_collision(top, left, right);
            if (collision != -1) {
                y = (top - 1) << 4;
                bombjack_ypos = y << 8;
                bombjack_state = BOMBJACK_STILL;
            }
        } 
    } else if (bombjack_state & BOMBJACK_JUMPING) {
        if (bombjack_state & BOMBJACK_LEFT) {
            gfx = bombjack_jumping_left;
            bombjack_move_left();
        } else if (bombjack_state & BOMBJACK_RIGHT) {
            gfx = bombjack_jumping_right;
            bombjack_move_right();
        } else gfx = bombjack_jumping;

        if (bombjack_yspeed < GRAVITY) {
            bombjack_yspeed = 0;
            bombjack_state = BOMBJACK_FALLING;
        } else {
            bombjack_yspeed -= GRAVITY;
            // Does it bump into the ceiling ?
            if (bombjack_ypos < bombjack_yspeed) {
                bombjack_ypos = 0;
                bombjack_yspeed = 0;
                bombjack_state = BOMBJACK_FALLING;
            } else {
                bombjack_ypos -= bombjack_yspeed;
                // Does it bump into a platform ?
                left = (bombjack_xpos + (4 - BORDER_WIDTH)) >> 3;
                right = (bombjack_xpos + (7 - BORDER_WIDTH)) >> 3;
                top = (((bombjack_ypos >> 8) + 7 ) >> 4);
                collision = multisprite_sparse_tiling_collision(top, left, right);
                if (collision != -1) {
                    y = (top << 4) + PLATFORM_HEIGHT; // Head below the platform
                    bombjack_ypos = y << 8; // Turn to 16 bits
                    bombjack_state = BOMBJACK_FALLING;
                    bombjack_yspeed = 0;
                }
            }
        }
    } else {
        bombjack_yspeed = 0;
    }

    if (bombjack_state & BOMBJACK_STILL) {
        if (bombjack_state == BOMBJACK_STILL_LEFT) {
            gfx = bombjack_still_left;
        } else if (bombjack_state == BOMBJACK_STILL_RIGHT) {
            gfx = bombjack_still_right;
        } else {
            gfx = bombjack_still;
        }
    } else if (bombjack_state & BOMBJACK_WALKING) {
        bombjack_counter++;
        if (bombjack_counter == 8) bombjack_counter = 0;
        y = bombjack_counter >> 1;
        // Walking animation
        if (bombjack_state & BOMBJACK_LEFT) {
            if (y == 0 || y == 2) {
                gfx = bombjack_walking_left1;
            } else if (y == 1) {
                gfx = bombjack_walking_left2;
            } else {
                gfx = bombjack_walking_left3;
            }
            bombjack_move_left();
        } else {
            if (y == 0 || y == 2) {
                gfx = bombjack_walking_right1;
            } else if (y == 1) {
                gfx = bombjack_walking_right2;
            } else {
                gfx = bombjack_walking_right3;
            }
            bombjack_move_right();
        }
        if (bombjack_ypos >> 8 != PLAYFIELD_HEIGHT - 16) {
            // Does it fall from a platform ?
            left = (bombjack_xpos + (4 - 4)) >> 3;
            right = (bombjack_xpos + (7 - 4)) >> 3;
            top = ((bombjack_ypos >> 8) + 17) >> 4;
            collision = multisprite_sparse_tiling_collision(top, left, right);
            if (collision == -1) {
                bombjack_state = BOMBJACK_FALLING | (bombjack_state & 0xc0);
            }
        }
    }

    y = bombjack_ypos >> 8;
    multisprite_display_sprite_ex(bombjack_xpos, y, gfx, 6, 0, 1);
    
    bombjack_dispose_bombs(current_arrangement);
}

void game_init()
{
    for (X = 23; X >= 0; X--) bomb_disposed[X] = 0; 
    bombjack_xpos = (PLAYFIELD_WIDTH - SPRITE_WIDTH) / 2 + BORDER_WIDTH;
    bombjack_ypos = (PLAYFIELD_WIDTH - 8) << 8;
    bombjack_yspeed = 0;
    bombjack_state = BOMBJACK_FALLING;
    current_arrangement = 0;
}

void joystick_input()
{
    char left_or_right;

    joystick_update();
    if (joystick[0] & JOYSTICK_BUTTON1) {
        if (!button_pressed) {
            button_pressed = 1;
            if (bombjack_state & BOMBJACK_STILL) left_or_right = 0; else left_or_right = bombjack_state & 0xc0;
            if ((bombjack_state & BOMBJACK_FALLING) || (bombjack_state & BOMBJACK_JUMPING)) {
                bombjack_state = BOMBJACK_FALLING | left_or_right;
                bombjack_yspeed = 0;
            } else {
                bombjack_state = BOMBJACK_JUMPING | left_or_right;
                if (!left_or_right && (joystick[0] & JOYSTICK_UP)) {
                    bombjack_yspeed = 1500;
                } else {
                    bombjack_yspeed = 1000;
                }
            }
            return;
        };
    } else button_pressed = 0;

    if (joystick[0] & JOYSTICK_LEFT) {
        if (bombjack_state & BOMBJACK_STILL) {
            bombjack_state = BOMBJACK_WALKING_LEFT;
            bombjack_counter = 0;
        } else if (bombjack_state & BOMBJACK_FALLING) {
            bombjack_state = BOMBJACK_FALLING_LEFT;
        } else if (bombjack_state & BOMBJACK_JUMPING) {
            bombjack_state = BOMBJACK_JUMPING_LEFT;
        } else if (bombjack_state != BOMBJACK_WALKING_LEFT) bombjack_state = BOMBJACK_STILL;
    } else if (joystick[0] & JOYSTICK_RIGHT) {
        if (bombjack_state & BOMBJACK_STILL) {
            bombjack_state = BOMBJACK_WALKING_RIGHT;
            bombjack_counter = 0;
        } else if (bombjack_state & BOMBJACK_FALLING) {
            bombjack_state = BOMBJACK_FALLING_RIGHT;
        } else if (bombjack_state & BOMBJACK_JUMPING) {
            bombjack_state = BOMBJACK_JUMPING_RIGHT;
        } else if (bombjack_state != BOMBJACK_WALKING_RIGHT) bombjack_state = BOMBJACK_STILL;
    } else {
        if (bombjack_state & BOMBJACK_WALKING) {
            bombjack_state = BOMBJACK_STILL | (bombjack_state & 0xc0);
        } else {
            bombjack_state &= ~(BOMBJACK_LEFT | BOMBJACK_RIGHT);
        }
    }
}

void init()
{
    char y;

    multisprite_init();
    multisprite_set_charbase(platform);
    joystick_init();
    
    // Top border in overscan
    if (_ms_pal_detected) {
        X = 4;
    } else {
        X = 1;
    }
    _ms_b0_dll[X] = topborder_dl >> 8;  
    _ms_b1_dll[X] = topborder_dl >> 8;
    _ms_b0_dll[++X] = topborder_dl;  
    _ms_b1_dll[X] = topborder_dl;
    // Bottom border in overscan
    X += (_MS_DLL_ARRAY_SIZE - 1) * 3 + 1;
    _ms_b0_dll[X] = 0x08; // 9 lines  
    _ms_b1_dll[X] = 0x08; // 9 lines 
    _ms_b0_dll[++X] = bottomborder_dl >> 8;  
    _ms_b1_dll[X] = bottomborder_dl >> 8;
    _ms_b0_dll[++X] = bottomborder_dl;  
    _ms_b1_dll[X] = bottomborder_dl;
    // Adjust the bottom of screen to fit the screen size
    X += 4;
    if (_ms_pal_detected) {
        _ms_b0_dll[X] = 0x07; // 8 lines  
        _ms_b1_dll[X] = 0x07; // 8 lines  
    } else {
        _ms_b0_dll[X] = 0x00; // 1 line  
        _ms_b1_dll[X] = 0x00; // 1 line  
    }
    // Display the sphinx and platforms
    multisprite_sparse_tiling(tilemap_sphinx_data_ptrs, 0, 4, 14);
    multisprite_sparse_tiling(tilemap_arrangement_A_data_ptrs, 0, 4, 14);
    // Left and right borders
    for (y = 0; y < PLAYFIELD_HEIGHT; y += 16) {
        multisprite_display_sprite_fast(0, y, border, 1, 3);
        multisprite_display_sprite_fast(116, y, border, 1, 3);
    }

    multisprite_save();
    
    // Enemies palette 
    *P0C1 = 0x04; // Dark gray
    *P0C2 = 0x08; // Medium gray
    *P0C3 = 0x34; // Red

    // Bombjack palette
    *P1C1 = multisprite_color(0x87); // Light blue
    *P1C2 = multisprite_color(0x3c); // Rose 
    *P1C3 = 0x00; // Black 

    // Bomb palette
    *P2C1 = multisprite_color(0x34); // Red
    *P2C2 = multisprite_color(0x1c); // Yellow 
    *P2C3 = 0x0f; // White 

    // Fire palette
    *P3C1 = multisprite_color(0x24); // Red
    *P3C2 = multisprite_color(0x28); // Orange
    *P3C3 = multisprite_color(0x1c); // Yellow 

    // Blue palette
    *P4C1 = multisprite_color(0x84); // Dark blue 
    
    // Sphinx palette
    *P5C1 = multisprite_color(0x12); // Red
    *P5C2 = multisprite_color(0x15); // Orange
    *P5C3 = multisprite_color(0x18); // Yellow 

    button_pressed = 0;
}

void main()
{
    init();
    game_init();
    
    // Main loop
    do {
        // Display the first arrangement
        display_arrangement(current_arrangement);
        joystick_input();
        bombjack();

        multisprite_flip();
    } while(1);
}
