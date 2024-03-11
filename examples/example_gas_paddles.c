#include "prosystem.h"
#define MODE_320AC
#include "multisprite_8lines.h"
#include "armyfont.h"
#include "sfx.h"

unsigned char X, Y;

// Generated with sprites7800 circuit.yaml
#include "example_gas_paddles_tiles.c"

// Generated with sprites7800 cars.yaml
#include "example_gas_paddles_sprites.c"

const char *stripped_car_models[24] = {stripped_car0, stripped_car1, stripped_car2, stripped_car3, stripped_car4, stripped_car5, stripped_car6, stripped_car7, stripped_car8, stripped_car9, stripped_car10, stripped_car11, stripped_car12, stripped_car13, stripped_car14, stripped_car15, stripped_car16, stripped_car17, stripped_car18, stripped_car19, stripped_car20, stripped_car21, stripped_car22, stripped_car23};
const char *backlight_car_models[24] = {backlight_car0, backlight_car1, backlight_car2, backlight_car3, backlight_car4, backlight_car5, backlight_car6, backlight_car7, backlight_car8, backlight_car9, backlight_car10, backlight_car11, backlight_car12, backlight_car13, backlight_car14, backlight_car15, backlight_car16, backlight_car17, backlight_car18, backlight_car19, backlight_car20, backlight_car21, backlight_car22, backlight_car23};

ramchip char paddle[4];
ramchip char dli_counter;

void interrupt dli()
{
#ifdef DEBUG
    *BACKGRND = 0x05;
#endif
    X = dli_counter;
    if (!X) {
        *VBLANK = 0x00; // Let paddle capacitors charging 
    }
    if (!(*INPT0 & 0x80)) paddle[0] = X;
    if (!(*INPT1 & 0x80)) paddle[1] = X;
    if (!(*INPT2 & 0x80)) paddle[2] = X;
    if (!(*INPT3 & 0x80)) paddle[3] = X;
    X++;
    dli_counter = X;
#ifdef DEBUG
   *BACKGRND = 0x00;
#endif
}

const int dx[24] = {40, 38, 34, 28, 19, 10, 0, -10, -20, -28, -34, -38, -40, -38, -34, -28, -19, -10, 0, 10, 19, 28, 34, 38};
const int dy[24] = {0, 16, 32, 45, 55, 61, 64, 61, 55, 45, 32, 16, 0, -16, -31, -45, -55, -61, -64, -61, -55, -45, -32, -16};

ramchip unsigned int xpos[4], ypos[4], direction[4];
ramchip char speed[4], race_laps[4], race_step[4];
ramchip char pstate[4], pstate_counter[4];
ramchip char counter;
#define STATE_READY_SET_GO  0
#define STATE_FIRST         1
#define STATE_SECOND        2
#define STATE_THIRD         3
#define STATE_FOURTH        4
#define STATE_OUT_OF_GAME   5  
#define STATE_OK            6  
#define STATE_LAST_LAP      7  
ramchip char ranked[4];
ramchip char game_state;
#define GAME_STATE_STARTING     0
#define GAME_STATE_READY_SET_GO 1
#define GAME_STATE_RUNNING      2

ramchip const char paddle_trigger_flag[4] = {0x80, 0x40, 0x08, 0x04};

#define NB_WAYPOINTS 9
const char waypoint_xy[NB_WAYPOINTS] = {90, 128, 40, 108, 90, 60, 40, 32, 160};
#define WPT_UP      0
#define WPT_LEFT    1
#define WPT_DOWN    2
#define WPT_RIGHT   3
const char waypoint_dir[NB_WAYPOINTS] = {WPT_RIGHT, WPT_RIGHT, WPT_UP, WPT_LEFT, WPT_DOWN, WPT_LEFT, WPT_UP, WPT_LEFT, WPT_DOWN};

const char xinit[4] = {80, 80, 68, 68};
const char yinit[4] = {0, 12, 0, 12};

void game_reset()
{
    char c;

    sfx_init();
    *P0C2 = multisprite_color(0x83); // Blue
    *P1C2 = multisprite_color(0x1c); // Yellow
    *P2C2 = 0x05;                    // Dark grey
    *P3C2 = 0x0a;                    // Light grey
    *P4C2 = multisprite_color(0x34); // Red 
    *P5C2 = multisprite_color(0xd3); // Green
    *P6C2 = 0x00;                    // Black 
    *P7C2 = 0x0f;                    // White
    multisprite_init();
    *BACKGRND = multisprite_color(0x12); // Brown
    multisprite_set_charbase(font);
    dli_counter = 0;
    for (c = 0; c != 28; c++) multisprite_enable_dli(c);
}

void game_init() 
{
    char i, y;
    for (X = 0; X < 4; X++) {
        xpos[X] = xinit[X] << 8;
        y = yinit[X];
        ypos[X] = y << 8;
        direction[X] = 256 + 128;
        speed[X] = 0;
        race_laps[X] = 0xf0;
        race_step[X] = 0x00;
        ranked[X] = -1;
        pstate[X] = STATE_OUT_OF_GAME; 
        pstate_counter[X] = 0;
        paddle[X] = 100;
    } 
    counter = 0;
    game_state = GAME_STATE_STARTING;
}

void game_prepare()
{
    char i, y;
    for (i = 0; i != 4; i++) {
        X = i;
        if (!((*SWCHA) & paddle_trigger_flag[X])) {
            // Car X is entering game ?
            if (pstate[X] == STATE_OUT_OF_GAME) {
                pstate[X] = STATE_OK;
                y = yinit[X] + 180;
                ypos[X] = y << 8;
            }
        }
    }
    // Reset to start the game
    if (!((*SWCHB) & 1)) {
        i = 0;
        for (X = 0; X != 4; X++) {
           if (pstate[X] == STATE_OK) i++;
        }
        if (i >= 2) {
            game_state = GAME_STATE_READY_SET_GO;
            for (X = 0; X != 4; X++) {
                if (pstate[X] == STATE_OK) pstate[X] = STATE_READY_SET_GO;
            }
        }
    }
}

void game_ready()
{
    for (X = 0; X != 4; X++) {
        if (pstate[X] == STATE_READY_SET_GO) {
            if ((counter & 1) == 0) {
                if (pstate_counter[X] < 126 - 9) pstate_counter[X]++;
                else game_state = GAME_STATE_RUNNING;
            }
        }
    }
}

inline void car_forward()
{
    xpos[X] += dx[Y];
    ypos[X] += dy[Y];
}

#define DEADZONE 1 
void game_logic(char player)
{
    signed char psteering;
    X = player;
    psteering = paddle[X] - 14;
    if (psteering >= 0) {
        if (psteering >= DEADZONE) psteering -= DEADZONE;
        else psteering = 0;
    } else {
        if (psteering < -DEADZONE) psteering += DEADZONE;
        else psteering = 0;
    }
    psteering <<= 1;

    if (game_state == GAME_STATE_RUNNING && pstate[X] != STATE_OUT_OF_GAME) {
        Y = direction[X] >> 8;
        Y--;
    
        if ((*SWCHA) & paddle_trigger_flag[X]) {
            if (speed[X] >= 5) speed[X] -= 4;
            else speed[X] = 0;
        } else {
            if (paddle[X] >= 27) {
                xpos[X] -= dx[Y];
                ypos[X] -= dy[Y];
                speed[X] = 0;
            } else if (speed[X] != 255) speed[X]++;
        }
        if (speed[X] != 0) {
            car_forward();
            if (speed[X] >= 64) {
                car_forward();
                if (speed[X] >= 128) {
                    car_forward();
                    if (speed[X] >= 192) {
                        car_forward();
                    } else {
                        psteering -= (psteering >> 2);
                    }
                } else {
                    psteering -= (psteering >> 1);
                }
            } else {
                signed char s = psteering >> 1;
                psteering -= s - (s >> 1);
            }
        } else psteering = 0; 
        direction[X] += psteering;
        Y = (direction[X] >> 8);
        if (Y == 0) {
            direction[X] += 24 * 256;
            Y = 24;
        } else if (Y == 25) {
            direction[X] -= 24 * 256;
            Y = 1;
        }
        Y--;
        if ((xpos[X] >> 8) < 2) { xpos[X] = 2 * 256; speed[X] = 0; }
        else if ((xpos[X] >> 8) >= 152) { xpos[X] = 151 * 256; speed[X] = 0; }
        if ((ypos[X] >> 8) < 22) { ypos[X] = 22 * 256; speed[X] = 0; }
        else if ((ypos[X] >> 8) >= 200) { ypos[X] = 199 * 256; speed[X] = 0; }

        // TODO: Display sprite model Y and test collision with playfield

        // Compute progress on the track
        char tmp = waypoint_dir[Y = race_laps[X] & 0x0f];
        if (tmp == WPT_RIGHT) {
            race_step[X] = (xpos[X] >> 8) - waypoint_xy[Y];
        } else if (tmp == WPT_UP) {
            race_step[X] = (ypos[X] >> 8) - waypoint_xy[Y];
        } else if (tmp == WPT_DOWN) {
            race_step[X] = waypoint_xy[Y] - (ypos[X] >> 8);
        } else {
            race_step[X] = waypoint_xy[Y] - (ypos[X] >> 8);
        }
        if (race_step[X] >= 0) {
            race_laps[X]++;
            if ((race_laps[X] & 0x0f) == NB_WAYPOINTS) {
                race_laps[X] = race_laps[X] & 0x0f;
            } else if ((race_laps[X] & 0x0f) == 1) {
                race_laps[X] = (race_laps[X] & 0xf0) + 0x11;
            }
            tmp = waypoint_dir[Y = race_laps[X] & 0x0f];
            if (tmp == WPT_RIGHT) {
                race_step[X] = (xpos[X] >> 8) - waypoint_xy[Y];
            } else if (tmp == WPT_UP) {
                race_step[X] = (ypos[X] >> 8) - waypoint_xy[Y];
            } else if (tmp == WPT_DOWN) {
                race_step[X] = waypoint_xy[Y] - (ypos[X] >> 8);
            } else {
                race_step[X] = waypoint_xy[Y] - (ypos[X] >> 8);
            }
        }
        // Update race ranking
        if ((race_laps[X] & 0xf0) != 0xf0) {
            Y = pstate[X];
            if (Y == STATE_READY_SET_GO) {
                for (Y = 0; Y != 4; Y++) {
                    if (ranked[Y] == -1) {
                        ranked[Y] = X; 
                        pstate[X] = ++Y;
                        pstate_counter[X] = 0;
                        break;
                    }
                }
            } else {
                if (Y >= STATE_SECOND) {
                    --Y;
                    Y = ranked[--Y]; // Y is the car that is potentially overtaken by car X
                    if (race_laps[Y] < race_laps[X] || (race_laps[Y] == race_laps[X] && race_step[Y] < race_step[X])) {
                        tmp = Y;
                        Y = pstate[X]; // pstate[X] is the former position of X
                        ranked[--Y] = tmp; // The overtaken car is ranked there
                        ranked[--Y] = X; // We put car X at the previous position        
                        pstate[X]--; // And we update the position of each X and Y cars
                        pstate[Y = tmp]++;
                    }
                } 
            }
        }
    }
}

void display_car1()
{
    X = 0;
    char x = xpos[X] >> 8;
    char y = ypos[X] >> 8;
    Y = direction[X] >> 8;
    char *gfx = stripped_car_models[--Y];
    multisprite_display_big_sprite(x, y, gfx, 4, 0, 2, 1); 
}

void display_car2()
{
    X = 1;
    char x = xpos[X] >> 8;
    char y = ypos[X] >> 8;
    Y = direction[X] >> 8;
    char *gfx = backlight_car_models[--Y];
    multisprite_display_big_sprite(x, y, gfx, 4, 0, 2, 1); 
}

void display_car3()
{
    X = 2;
    char x = xpos[X] >> 8;
    char y = ypos[X] >> 8;
    Y = direction[X] >> 8;
    char *gfx = stripped_car_models[--Y];
    multisprite_display_big_sprite(x, y, gfx, 4, 4, 2, 1); 
}

void display_car4()
{
    X = 3;
    char x = xpos[X] >> 8;
    char y = ypos[X] >> 8;
    Y = direction[X] >> 8;
    char *gfx = backlight_car_models[--Y];
    multisprite_display_big_sprite(x, y, gfx, 4, 4, 2, 1); 
}

void main()
{
    char i;
    game_reset();
start:
    game_init();

    do {
        // Do some logic here
        game_logic(0);
        game_logic(1);
        if (game_state == GAME_STATE_RUNNING) {
            if (!((*SWCHB) & 1)) goto start;
        } else if (game_state == GAME_STATE_STARTING) {
            game_prepare();
        } else {
            game_ready();
        }
        game_logic(2);
        game_logic(3);
        counter++;

        while (!(*MSTAT & 0x80)); // Wait for VBLANK
#ifdef DEBUG
        *BACKGRND = 0x0f;
#endif        
        counter++;
        *VBLANK = 0x80; // Dump paddles to ground
        sfx_play();
        if (multisprite_pal_frame_skip())
            sfx_play(); // Advance twice every 5 frames (to cope with 60Hz instead of 50Hz)
        // Display cars 
        dli_counter = 0;
        multisprite_restore();
        display_car1();
        display_car2();
        display_car3();
        display_car4();
#ifdef DEBUG
        *BACKGRND = 0x00;
#endif        
    } while(1);
}
