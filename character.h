#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "global.h"
#include "GameWindow.h"
#include "elec.h"
#include "shield.h"
#include "coin.h"


enum { RUN = 0, JUMP, DOWN, OVER};
//enum class Body{Large=0,Medium,Small};
//enum class Key {hold=0,press};

class Panda
{
private:
    //int init_speed;
    const int jump_unit = 10;

public:
    Panda();
    ~Panda();
    void Panda_process(ALLEGRO_EVENT event);
    void Panda_update();
    void Panda_draw();
    Panda *Panda_create();
    int state;      // RUN, FASTER, SLOWER, STOP
    int anime;      // counting the time of animation
    int anime_time; // indicate how long the animation
    ALLEGRO_BITMAP *img[20];
    double velocity;
    double accleration;
    // double y;
    double init_velocity;
    int position;
    int init_position;
    int x, y, width, height;
};

#endif // CHARACTER_H_INCLUDED
