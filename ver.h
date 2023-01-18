#ifndef VER_H_INCLUDED
#define VER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "global.h"
#include "character.h"

class Ver
{
private:
    int x, y, speed;
    bool exist;
public:
    Ver();
    void ~Ver();
    void ver_init();
    void ver_draw();
    void ver_update(int speed, int x, int y);
    void ver_create();
    int ver_encounter(int objx, int objy, int charx, int chary);
};

#endif // VER_H_INCLUDED
