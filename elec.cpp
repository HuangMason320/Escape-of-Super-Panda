#include <stdio.h>
#include <stdlib.h>

#include "elec.h"

#define ELEC_HRZ_SHORT_SIZE_X 200 // 206
#define ELEC_HRZ_SHORT_SIZE_Y 55  // 59
#define ELEC_HRZ_LONG_SIZE_X 250  // 259
#define ELEC_HRZ_LONG_SIZE_Y 90   // 99

#define ELEC_VER_SIZE_X 55  // 60
#define ELEC_VER_SIZE_Y 200 // 205

#define ELEC_INC_SHORT_X 115 // 122
#define ELEC_INC_SHORT_Y 105 // 109
#define ELEC_INC_LONG_X 195  // 200
#define ELEC_INC_LONG_Y 175  // 180

#define CHAR_SIZE_X 130 // each pic differ
#define CHAR_SIZE_Y 188 // each pic differ

ALLEGRO_BITMAP *ver_img = NULL;
ALLEGRO_BITMAP *inc_short_img = NULL;
ALLEGRO_BITMAP *inc_long_img = NULL;
ALLEGRO_BITMAP *hrz_short_img = NULL;
ALLEGRO_BITMAP *hrz_long_img = NULL;

// double shield_time_total;

Elec inc_long[2], inc_short[2], ver[2], hrz_long[2], hrz_short[2];
int check[3] = {0};
int choose;
int place = 0;
int x_check = 0;

void elec_init()
{
    ver_img = al_load_bitmap("./image/ver.png");
    inc_long_img = al_load_bitmap("./image/incline200.png");
    inc_short_img = al_load_bitmap("./image/incline150.png");
    hrz_long_img = al_load_bitmap("./image/hori200.png");
    hrz_short_img = al_load_bitmap("./image/hori150.png");
    for (int i = 0; i < 2; i++)
    {
        inc_long[i].exist = false;
        inc_short[i].exist = false;
        ver[i].exist = false;
        hrz_long[i].exist = false;
        hrz_short[i].exist = false;
    }
}
void elec_draw()
{
    for (int i = 0; i < 2; i++)
    {
        if (inc_long[i].exist)
            al_draw_bitmap(inc_long_img, inc_long[i].x, inc_long[i].y, 0);
        if (inc_short[i].exist)
            al_draw_bitmap(inc_short_img, inc_short[i].x, inc_short[i].y, 0);
        if (ver[i].exist)
            al_draw_bitmap(ver_img, ver[i].x, ver[i].y, 0);
        if (hrz_long[i].exist)
            al_draw_bitmap(hrz_long_img, hrz_long[i].x, hrz_long[i].y, 0);
        if (hrz_short[i].exist)
            al_draw_bitmap(hrz_short_img, hrz_short[i].x, hrz_short[i].y, 0);
    }
}
void elec_update(int x, int y)
{
    for (int i = 0; i < 2; i++)
    {
        if (inc_long[i].exist)
        {
            if (inc_long_encounter(inc_long[i].x, inc_long[i].y, x, y) && immortal == 0)
            {
                // inc_long[i].exist = false;
                // total--;
                // panda.panda_update();
                // character over
                // continue;
                if (shield_get == 1)
                {
                    shield_start = true;
                }
                else
                {
                    total = 0;
                    end_round = 1;
                    judge_next_window = true;
                    over_scene_init();
                }
            }
            inc_long[i].x -= speed;
            if (inc_long[i].x + ELEC_INC_LONG_X <= 0)
            {
                inc_long[i].exist = false;
                total -= 1;
                // inc_long_destroy();
            }
        }
        if (inc_short[i].exist)
        {
            if (inc_short_encounter(inc_short[i].x, inc_short[i].y, x, y) && immortal == 0)
            {
                // inc_short[i].exist = false;
                // total--;
                // continue;
                if (shield_get == 1)
                {
                    shield_start = true;
                }
                if (shield_get == 0)
                {
                    total = 0;
                    end_round = 1;
                    judge_next_window = true;
                    over_scene_init();
                }
            }
            inc_short[i].x -= speed;
            if (inc_short[i].x + ELEC_INC_SHORT_X <= 0)
            {
                inc_short[i].exist = false;
                total -= 1;
                // inc_short_destroy();
            }
        }
        if (ver[i].exist)
        {
            if (ver_encounter(ver[i].x, ver[i].y, x, y)&& !immortal )
            {
                // ver[i].exist = false;
                // total--;
                // continue;
                if (shield_get == 1)
                {
                    shield_start = true;
                }
                else
                {
                    printf("DEAD\n");
                    total = 0;
                    end_round = 1;
                    judge_next_window = true;
                    over_scene_init();
                }
            }
            ver[i].x -= speed;
            if (ver[i].x + ELEC_VER_SIZE_X <= 0)
            {
                ver[i].exist = false;
                total -= 1;
                // ver_destroy();
            }
        }
        if (hrz_long[i].exist)
        {
            if (hrz_long_encounter(hrz_long[i].x, hrz_long[i].y, x, y) && immortal == 0)
            {
                // hrz_long[i].exist = false;
                // total--;
                // continue;
                if (shield_get == 1)
                {
                    shield_start = true;
                }
                else
                {
                    total = 0;
                    end_round = 1;
                    judge_next_window = true;
                    over_scene_init();
                }
            }
            hrz_long[i].x -= speed;
            if (hrz_long[i].x + ELEC_HRZ_LONG_SIZE_X <= 0)
            {
                hrz_long[i].exist = false;
                total -= 1;
                // hrz_long_destroy();
            }
        }
        if (hrz_short[i].exist)
        {
            if (hrz_short_encounter(hrz_short[i].x, hrz_short[i].y, x, y) && immortal == 0)
            {
                if (shield_get == 1)
                {
                    shield_start = true;
                }
                else
                {
                    total = 0;
                    end_round = 1;
                    judge_next_window = true;
                    over_scene_init();
                }
            }
            hrz_short[i].x -= speed;
            if (hrz_short[i].x + ELEC_HRZ_SHORT_SIZE_X <= 0)
            {
                hrz_short[i].exist = false;
                total -= 1;
                // hrz_short_destroy();
            }
        }
    }
    // printf("SUCCESS\n");
}
void elec_create()
{
    // printf("YES\n");
    for (int i = 0; i < 5; i++)
    {
        int choose = rand() % 5;
        if (rand() % 4 == 0 && total <= 3)
        {
            if (choose == 0) // ver
            {
                if (!ver[0].exist)
                {
                    ver[0].exist = true;
                    ver[0].x = WIDTH;
                    ver[0].y = validy[1]; // find Height
                    total++;
                }
            }
            else if (choose == 1) // inc_long
            {
                if (!inc_long[0].exist)
                {
                    inc_long[0].exist = true;
                    inc_long[0].x = WIDTH;
                    inc_long[0].y = validy[0]; // find Heigh
                    total++;
                }
                /*
                else if (!inc_long[1].exist)
                {
                    inc_long[1].exist = true;
                    inc_long[1].x = WIDTH;
                    inc_long[1].y = validy[4];//find Height
                    total++;
                }*/
            }
            else if (choose == 2) // inc_short
            {
                if (!inc_short[0].exist)
                {
                    inc_short[0].exist = true;
                    inc_short[0].x = WIDTH;
                    inc_short[0].y = validy[3]; // find Heigh
                    total++;
                }
                /*
                else if (!inc_short[1].exist)
                {
                    inc_short[1].exist = true;
                    inc_short[1].x = WIDTH;
                    inc_short[1].y = validy[rand()%4];//find Height
                    total++;
                }*/
            }
            else if (choose == 3) // hrz_long
            {
                if (!hrz_long[0].exist)
                {
                    hrz_long[0].exist = true;
                    hrz_long[0].x = WIDTH;
                    hrz_long[0].y = validy[0]; // find Heigh
                    total++;
                }
                else if (!hrz_long[1].exist)
                {
                    hrz_long[1].exist = true;
                    hrz_long[1].x = WIDTH;
                    hrz_long[1].y = validy[2]; // find Height
                    total++;
                }
            }
            else if (choose == 4) // hrz_short
            {
                if (!hrz_short[0].exist)
                {
                    hrz_short[0].exist = true;
                    hrz_short[0].x = WIDTH;
                    hrz_short[0].y = validy[1]; // find Heigh
                    total++;
                }
                else if (!hrz_short[1].exist)
                {
                    hrz_short[1].exist = true;
                    hrz_short[1].x = WIDTH;
                    hrz_short[1].y = validy[3]; // find Height
                    total++;
                }
            }
        }
    }
}
void elec_destroy()
{
    al_destroy_bitmap(ver_img);
    al_destroy_bitmap(hrz_long_img);
    al_destroy_bitmap(hrz_short_img);
    al_destroy_bitmap(inc_short_img);
    al_destroy_bitmap(inc_long_img);
}

int inc_short_encounter(int objx, int objy, int charx, int chary)
{
    /*
    int obj_2_x = objx +ELEC_INC_SHORT_X, obj_2_y = objy - ELEC_INC_SHORT_Y;
    int char_2_x = charx + CHAR_SIZE_X, char_2_y = chary;
    if(((obj_2_x - char_2_x) / (obj_2_y - char_2_y)) == ((char_2_x - objx) / (char_2_y - objy)))
    {
        if(obj_2_x > char_2_x && obj_2_x - char_2_x <= CHAR_SIZE_X)
        {
            if((obj_2_y > chary)&&(obj_2_y < char_2_y))
                return 1;
        }
        else if (obj_2_x > charx && obj_2_x - charx <= CHAR_SIZE_X)
        {
            if((obj_2_y > chary)&&(obj_2_y < char_2_y))
                return 1;
        }
    }
    return 0;
    */
    if ((objx - charx <= CHAR_SIZE_X) && (objx >= charx))
    {
        if (((chary - objy) <= ELEC_INC_SHORT_Y) && (chary >= objy))
        {
            return 1;
        }
        else if (((objy - chary) <= CHAR_SIZE_Y) && (objy >= chary))
        {
            return 1;
        }
    }
    else if ((charx - objx <= ELEC_INC_SHORT_X) && (objx <= charx))
    {
        if (((chary - objy) <= ELEC_INC_SHORT_Y) && (chary >= objy))
        {
            return 1;
        }
        else if (((objy - chary) <= CHAR_SIZE_Y) && (objy >= chary))
        {
            return 1;
        }
    }
    return 0;
}
int inc_long_encounter(int objx, int objy, int charx, int chary)
{
    if ((objx - charx <= CHAR_SIZE_X) && (objx >= charx))
    {
        if (((chary - objy) <= ELEC_INC_LONG_Y) && (chary >= objy))
        {
            return 1;
        }
        else if (((objy - chary) <= CHAR_SIZE_Y) && (objy >= chary))
        {
            return 1;
        }
    }
    else if ((charx - objx <= ELEC_INC_LONG_X) && (objx <= charx))
    {
        if (((chary - objy) <= ELEC_INC_LONG_Y) && (chary >= objy))
        {
            return 1;
        }
        else if (((objy - chary) <= CHAR_SIZE_Y) && (objy >= chary))
        {
            return 1;
        }
    }
    return 0;
}
int hrz_short_encounter(int objx, int objy, int charx, int chary)
{
    if ((objx - charx <= CHAR_SIZE_X) && (objx >= charx))
    {
        if (((chary - objy) <= ELEC_HRZ_SHORT_SIZE_Y) && (chary > objy))
        {
            printf("1\n");
            return 1;
        }
        else if (((objy - chary) <= CHAR_SIZE_Y) && (objy > chary))
        {
            printf("1\n");
            return 1;
        }
    }
    if ((charx - objx <= ELEC_HRZ_SHORT_SIZE_X) && (objx <= charx))
    {
        if (((chary - objy) <= ELEC_HRZ_SHORT_SIZE_Y) && (chary > objy))
        {
            printf("1\n");
            return 1;
        }
        else if (((objy - chary) <= CHAR_SIZE_Y) && (objy > chary))
        {
            printf("1\n");
            return 1;
        }
    }
    printf("0\n");
    return 0;
}
int hrz_long_encounter(int objx, int objy, int charx, int chary)
{
    if ((objx - charx <= CHAR_SIZE_X) && (objx >= charx))
    {
        if (((chary - objy) <= ELEC_HRZ_LONG_SIZE_Y) && (chary > objy))
        {
            return 1;
        }
        else if (((objy - chary) <= CHAR_SIZE_Y) && (objy > chary))
        {
            return 1;
        }
    }
    if ((charx - objx <= ELEC_HRZ_LONG_SIZE_X) && (objx <= charx))
    {
        if (((chary - objy) <= ELEC_HRZ_LONG_SIZE_Y) && (chary > objy))
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
int ver_encounter(int objx, int objy, int charx, int chary)
{
    if ((objx - charx <= ELEC_VER_SIZE_X) && (objx >= charx))
    {
        if (((chary - objy) <= ELEC_VER_SIZE_Y) && (chary >= objy))
        {
            return 1;
        }
        else if (((objy - chary) <= CHAR_SIZE_Y) && (objy >= chary))
        {
            return 1;
        }
    }
    else if ((charx - objx <= ELEC_VER_SIZE_X) && (objx <= charx))
    {
        if (((chary - objy) <= ELEC_VER_SIZE_Y) && (chary >= objy))
        {
            return 1;
        }
        else if (((objy - chary) <= CHAR_SIZE_Y) && (objy >= chary))
        {
            return 1;
        }
    }
    return 0;
}
