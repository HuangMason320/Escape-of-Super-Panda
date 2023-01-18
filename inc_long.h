#ifndef INC_LONG_H_INCLUDED
#define INC_LONG_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "global.h"
#include "character.h"

class Inc_long
{
private:
    /* data */
    int x, y, speed;
    bool exist;
public:
    Inc_long();
    void ~Inc_long();
    void Inc_long_destroy();
    void Inc_long_create;
    void Inc_long_draw();
    void Inc_long_update(int speed, int x, int y);
    int Inc_long_encounter(int objx, int objy, int charx, int chary);
};

#endif // INC_LONG_H_INCLUDED
