#ifndef ELEC_H_INCLUDED
#define ELEC_H_INCLUDED

#include <vector>
#include "global.h"
#include "character.h"


typedef struct Elec
{
    int x,y;
    bool exist;
    int speed;
};

void elec_init();
void elec_draw();
void elec_update(int x, int y);
void elec_create();
//destroy
void ver_destroy();
void inc_short_destroy();
void inc_long_destroy();
void hrz_short_destroy();
void hrz_long_destroy();
void elec_destroy();

int inc_short_encounter(int objx, int objy, int charx, int chary);
int inc_long_encounter(int objx, int objy, int charx, int chary);
int hrz_short_encounter(int objx, int objy, int charx, int chary);
int hrz_long_encounter(int objx, int objy, int charx, int chary);
int ver_encounter(int objx, int objy, int charx, int chary);

#endif // ELEC_H_INCLUDED
