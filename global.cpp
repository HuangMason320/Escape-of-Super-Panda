#include "global.h"

// variables for global usage
const float FPS = 60.0;
const int WIDTH = 1920;
const int HEIGHT = 1000;

ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *fps = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
int validy[4] = {0, 300, 700, 900};
int coin_validy[4] = {40, 200, 450, 600};

// Check whether jump to next window
bool judge_next_window = false;
bool back_front_window = false;

// num of the next window
int next_window = 0;

bool dress_up = false;
int wear_cloth = 3;
int end_round = 0;
int init_speed = 10;
int speed = init_speed;
int long_press = 0;
int coin_count;
int total;
int shield_count = 120;
bool shield_start = false;
bool immortal = 0;
//
double game_start_time;
double game_over_time;
double game_time_total;
//
int game_cnt = 0;
int shield_get = 0;
