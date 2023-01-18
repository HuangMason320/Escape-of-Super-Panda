#ifndef INC_SHORT_H_INCLUDED
#define INC_SHORT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "global.h"
#include "character.h"

class Inc_short
{
private:
    /* data */
    int x, y, speed;
    bool exist;
public:
    Inc_short();
    void ~Inc_short();
    void Inc_short_destroy();
    void Inc_short_create;
    void Inc_short_draw();
    void Inc_short_update(int speed, int x, int y);
    int Inc_short_encounter(int objx, int objy, int charx, int chary);
};


#endif // INC_SHORT_H_INCLUDED
