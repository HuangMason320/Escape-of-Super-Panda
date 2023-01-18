#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

#define GAME_TERMINATE -1

extern const float FPS;
extern const int WIDTH;
extern const int HEIGHT;

extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *fps;
extern bool key_state[ALLEGRO_KEY_MAX];
extern int validy[4];
extern int coin_validy[4];
//
extern bool judge_next_window;
extern bool back_front_window;
extern bool immortal;
//
extern int next_window;
//
extern bool dress_up;
extern int wear_cloth;
extern int end_round;
extern int speed;
extern int long_press;
extern int coin_count;
extern int total;
extern int shield_count; // shield time for 300fps
extern bool shield_start;
//
extern double game_start_time;
extern double game_over_time;
extern double game_time_total;
//
extern int game_cnt;
extern int init_speed;
extern int shield_get;

#endif // GLOBAL_H_INCLUDED
