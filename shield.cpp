#include <stdio.h>
#include "global.h"
#include "shield.h"
#include "character.h"
//define part
#define NUM_SHIELD 1
#define SHIELD_SIZE_X 99
#define SHIELD_SIZE_Y 92
//character
#define CHAR_SIZE_X 130     //each pic differ
#define CHAR_SIZE_Y 188     //each pic differ

ALLEGRO_BITMAP *shield_img = NULL;

ALLEGRO_SAMPLE_INSTANCE *shield_sound;
ALLEGRO_SAMPLE *sound = NULL;

Shield shield;


void shield_init()
{
    shield_img = al_load_bitmap("./image/shield.png");
    shield.exist = false;
}
void shield_draw()
{
    if(shield.exist)
            al_draw_bitmap(shield_img, shield.x, shield.y, 0);
}
void shield_update(int x, int y)
{
    if(shield.exist)
    {
        if(shield_encounter(shield.x, shield.y, x,y))
        {
            //character get shield
            shield_get=1;
            shield_count = 300;
            shield.exist = false;
        }
        shield.x -= speed;
        if(shield.x+ SHIELD_SIZE_X <= 0)
        {
            shield.exist = false;
        }
    }
}
void shield_create()
{
    if (!shield.exist && shield_get == 0)
    {
        if (rand() % 2 == 0)
        {
            shield.exist = true;
            shield.x = WIDTH;
            shield.y = coin_validy[2];
        }
    }
}
void shield_destroy()
{
    al_destroy_bitmap(shield_img);
}
int shield_encounter(int objx, int objy, int charx, int chary)
{
    if ((objx - charx <= CHAR_SIZE_X) && (objx >= charx))
    {
        if (((chary - objy) <= SHIELD_SIZE_Y) && (chary > objy))
        {
            return 1;
        }
        else if (((objy - chary) <= CHAR_SIZE_Y) && (objy > chary))
        {
            return 1;
        }
    }
    if ((charx - objx <= SHIELD_SIZE_X) && (objx <= charx))
    {
        if (((chary - objy) <= SHIELD_SIZE_Y) && (chary > objy))
        {
            return 1;
        }
        else if (((objy - chary) <= CHAR_SIZE_Y) && (objy > chary))
        {
            return 1;
        }
    }
    return 0;
}
