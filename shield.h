#ifndef SHIELD_H_INCLUDED
#define SHIELD_H_INCLUDED

typedef struct shield
{
    int x,y;
    bool exist;
    int speed;

}Shield;

void shield_init();
void shield_draw();
void shield_update(int x, int y);
void shield_create();
void shield_destroy();
int shield_encounter(int objx, int objy, int charx, int chary);

#endif // SHIELD_H_INCLUDED
