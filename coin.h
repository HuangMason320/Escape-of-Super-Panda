#ifndef COIN_H_INCLUDED
#define COIN_H_INCLUDED

#include "global.h"
#include "character.h"

typedef struct coin
{
    int x, y;
    bool exist;
    int speed;
}Coin;


void coin_init();
void coin_draw();
void coin_update(int x, int y);
void coin_create();
void coin_get();
int coin_encounter(int objx, int objy, int charx, int chary);
void coin_destroy();
#endif // COIN_H_INCLUDED
