#include "prosystem.h"
#include "multisprite_8lines.h"

// Generated with sprites7800 cars.yaml
#include "example_gas_paddles_sprites.c"

#define MS_ONE_COLOR_SPRITES
#define MS_SELECT_FAST
#define MS_MAX_NB_SPRITES 4
char paddle[4];
#define kernel_short_macro \
   X = *INTIM; \
   if (!(*INPT0 & 0x80)) paddle[0] = X; \
   if (!(*INPT1 & 0x80)) paddle[1] = X; \
   if (!(*INPT2 & 0x80)) paddle[2] = X; \
   if (!(*INPT3 & 0x80)) paddle[3] = X;
#define kernel_medium_macro kernel_short_macro
#define kernel_long_macro \
   X = *INTIM; \
   if (!(*INPT0 & 0x80)) paddle[0] = X; \
   if (!(*INPT1 & 0x80)) paddle[1] = X; \
   strobe(WSYNC); \
   if (!(*INPT2 & 0x80)) paddle[2] = X; \
   if (!(*INPT3 & 0x80)) paddle[3] = X; \
   if (Y >= 163) *ENABL = 2;


const int dx[24] = {40, 38, 34, 28, 19, 10, 0, -10, -20, -28, -34, -38, -40, -38, -34, -28, -19, -10, 0, 10, 19, 28, 34, 38};
const int dy[24] = {0, 16, 32, 45, 55, 61, 64, 61, 55, 45, 32, 16, 0, -16, -31, -45, -55, -61, -64, -61, -55, -45, -32, -16};

unsigned int xpos[4], ypos[4], direction[4];
char speed[4], race_laps[4], race_step[4];
char pstate[4], pstate_counter[4];
char counter;
#define STATE_READY_SET_GO  0
#define STATE_FIRST         1
#define STATE_SECOND        2
#define STATE_THIRD         3
#define STATE_FOURTH        4
#define STATE_OUT_OF_GAME   5  
#define STATE_OK            6  
#define STATE_LAST_LAP      7  
char ranked[4];
char game_state;
#define GAME_STATE_STARTING     0
#define GAME_STATE_READY_SET_GO 1
#define GAME_STATE_RUNNING      2

const char paddle_trigger_flag[4] = {0x80, 0x40, 0x08, 0x04};

#define NB_WAYPOINTS 9
const char waypoint_xy[NB_WAYPOINTS] = {90, 128, 40, 108, 90, 60, 40, 32, 160};
#define WPT_UP      0
#define WPT_LEFT    1
#define WPT_DOWN    2
#define WPT_RIGHT   3
const char waypoint_dir[NB_WAYPOINTS] = {WPT_RIGHT, WPT_RIGHT, WPT_UP, WPT_LEFT, WPT_DOWN, WPT_LEFT, WPT_UP, WPT_LEFT, WPT_DOWN};

const char xinit[4] = {80, 80, 68, 68};
const char yinit[4] = {0, 12, 0, 12};

void game_init() 
{
    char i, y;
    for (X = 0; X < 4; X++) {
        xpos[X] = xinit[X] << 8;
        y = yinit[X] + 32;
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

#define DEADZONE 32 
void game_logic(char player)
{
    signed char psteering;
    X = player;
    psteering = paddle[X] - 128;
    if (psteering >= 0) {
        if (psteering >= DEADZONE) psteering -= DEADZONE;
        else psteering = 0;
    } else {
        if (psteering < -DEADZONE) psteering += DEADZONE;
        else psteering = 0;
    }
    psteering >>= 1;

    if (game_state == GAME_STATE_RUNNING && pstate[X] != STATE_OUT_OF_GAME) {
        Y = direction[X] >> 8;
        Y--;
    
        if ((*SWCHA) & paddle_trigger_flag[X]) {
            if (speed[X] >= 5) speed[X] -= 4;
            else speed[X] = 0;
        } else {
            if (paddle[X] > 240) {
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

void main()
{
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
    } while(1);
}
