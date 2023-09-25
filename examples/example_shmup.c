#include "prosystem.h"
#define _MS_TOP_SCROLLING_ZONE 1
#define VERTICAL_SCROLLING
#include "multisprite.h"
#include "joystick.h"
#include "string.h"

#include "example_shmup_sprites.c"
#include "example_shmup_tiles.c"

const signed short dx[24] = {300, 289, 259, 212, 149, 77, 0, -77, -150, -212, -259, -289, -300, -289, -259, -212, -149, -77, 0, 77, 149, 212, 259, 289};
const signed short dy[24] = {0, 124, 240, 339, 415, 463, 480, 463, 415, 339, 240, 124, 0, -124, -239, -339, -415, -463, -480, -463, -415, -339, -240, -124};

#define BULLETS_NB_MAX 32 
ramchip short bullet_xpos[BULLETS_NB_MAX], bullet_ypos[BULLETS_NB_MAX];
ramchip char bullet_direction[BULLETS_NB_MAX];
ramchip char bullet_first, bullet_last;

#define MISSILES_SPEED 10
#define MISSILES_NB_MAX 5
ramchip char xmissile[MISSILES_NB_MAX], ymissile[MISSILES_NB_MAX], nbmissiles;
ramchip char button_pressed;
ramchip char exhaust_state;
ramchip char spaceship_x, spaceship_y, spaceship_state, spaceship_state_counter; 
ramchip char scrolling_counter, scrolling_done;

ramchip int score;
ramchip char display_score_str[5];

void display_score_update()
{
    char display_score_ascii[6];
    itoa(score, display_score_ascii, 10);
    Y = strlen(display_score_ascii); 
    for (X = 0; X != 5 - Y; X++) {
        display_score_str[X] = 0; // '0'
    }
    X = 4;
    do {
        display_score_str[X--] = ((display_score_ascii[--Y] - '0') << 1);
    } while (Y);
}

ramchip char save_acc;

void interrupt dli()
{
    store(save_acc);
    multisprite_set_charbase(blue_objects1);
    load(save_acc);
}

void init()
{
    multisprite_init();
    multisprite_enable_dli(1);
    multisprite_set_charbase(blue_objects1);
    multisprite_vscroll_init_sparse_tiles(tilemap_data_ptrs);
    joystick_init();

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

    // Init game state variables
    nbmissiles = 0;
    button_pressed = 0;
    exhaust_state = 0;
    scrolling_counter = 255;
    scrolling_done = 0;

    // Initialize

    // Initialize spaceship state
    spaceship_x = 80 - 6;
    spaceship_y = 180;
    exhaust_state = 0;
    spaceship_state = 0;
     
    score = 0;
    // Score display
    display_score_update();
    multisprite_display_tiles(0, 0, display_score_str, 5, 3);
    multisprite_save();
}

void draw_evil_guys()
{
    multisprite_display_big_sprite((80 - 12), 8, boss, 12, 0, 3, 1);
}

void step()
{
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
                if (spaceship_y < 224 - 33 - 16) spaceship_y++;
            }
        }
        if (joystick[0] & JOYSTICK_BUTTON1) {
            if (!button_pressed) {
                button_pressed = 1;
                if (nbmissiles != MISSILES_NB_MAX) {
                    X = nbmissiles;
                    xmissile[X] = spaceship_x;
                    ymissile[X] = spaceship_y;
                    nbmissiles = ++X;
                }
            }
        } else button_pressed = 0;
    }

    // Draw missiles
    char x, y, i, j = -1;
    for (i = 0; i != nbmissiles; i++) {
        X = i;
        x = xmissile[X];
        y = ymissile[X] - MISSILES_SPEED;
        if (y < 0) {
            xmissile[X] = -1;
            if (j == -1) j = X;
        } else {
            ymissile[X] = y;
            multisprite_display_sprite_ex(x, y, missiles, 3, 3, 0);
        }
    }
    if (j != -1) {
        // Destroy dissapeared missiles
        for (X = j, Y = j; X != nbmissiles; X++) {
            if (xmissile[X] != -1) {
                xmissile[Y] = xmissile[X];
                ymissile[Y] = ymissile[X];
                Y++;
            }
        }
        nbmissiles = Y;
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
        if (exhaust_state > 0 && spaceship_y < 224 - 25 - 32) {
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

    // Draw evil guy
    draw_evil_guys();
    
    // Draw bullets (last, so if there is a DMA issue, it doesn't present spaceships to be desplayed)
    for (i = bullet_first; i != bullet_last; i++) {
        char xbullet, ybullet;
        if (i == BULLETS_NB_MAX) i = 0;
        X = i;
        Y = bullet_direction[X];
        if (Y != 255) {
            bullet_xpos[X] += dx[Y];
            bullet_ypos[X] += dy[Y];
            xbullet = bullet_xpos[X] >> 8;
            ybullet = bullet_ypos[X] >> 8;
            if (xbullet < 5 || xbullet >= 156 || ybullet < 5 || ybullet >= MS_YMAX - 20 - 16) {
                bullet_direction[X] = 255; // Removed
                do {
                    X++;
                    if (X == BULLETS_NB_MAX) X = 0;
                } while (X != bullet_last && bullet_direction[X] == 255);
                bullet_first = X;
            } else {
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
        }
    }
}

void main()
{
    init();

    // Main loop
    do {
        // Prepare scrolling data
        if (multisprite_vscroll_buffer_empty()) {
            if (!scrolling_done) {
                multisprite_vscroll_buffer_sparse_tiles(scrolling_counter);
                if (scrolling_counter) scrolling_counter--; else scrolling_done = 1; 
            } else if (scrolling_done == 1) {
                multisprite_vscroll_buffer_sparse_tiles(255);
                scrolling_done = 2;
            } else scrolling_done = 3;
        }

        step();

        multisprite_flip();
        multisprite_set_charbase(digits); // To display the score
        if (scrolling_done != 3) multisprite_vertical_scrolling(4);
    } while(1);
}
