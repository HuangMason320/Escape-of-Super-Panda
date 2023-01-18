#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include"global.h"
#include"character.h"

void home_init();
void home_process(ALLEGRO_EVENT event);
void home_draw();
void home_destroy();

void menu_init();
void menu_process(ALLEGRO_EVENT event);
void menu_draw();
void menu_destroy();

void game_scene_init();
void game_scene_draw();
void game_scene_destroy();
void game_process(ALLEGRO_EVENT event);
void game_scene_update();

void dress_scene_init();
void dress_scene_process(ALLEGRO_EVENT event);
//void dress_scene_update();
void dress_scene_draw();
void dress_scene_destroy();

void instructions_scene_init();
void instructions_scene_draw();
void instructions_scene_process(ALLEGRO_EVENT event);
void instructions_scene_destroy();

void over_scene_init();
void over_scene_draw();
void over_scene_process(ALLEGRO_EVENT event);
void over_scene_destroy();

//void pause_scene_init();
//void pause_scene_draw();
//void pause_scene_process(ALLEGRO_EVENT event);
//void pause_scene_destroy();

#endif // SCENE_H_INCLUDED
