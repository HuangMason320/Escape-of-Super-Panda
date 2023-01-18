#include "character.h"

//Panda panda;

Panda::Panda(/* args */)
{
    elec_init();
    shield_init();
    coin_init();
    //
    img[0] = al_load_bitmap("./image/panda_run1.png");//
    img[1] = al_load_bitmap("./image/panda_run2.png");//
    img[2] = al_load_bitmap("./image/panda_fly.png");//
    img[3] = al_load_bitmap("./image/panda_down.png");//
    img[4] = al_load_bitmap("./image/shield_run1.png");//
    img[5] = al_load_bitmap("./image/shield_run2.png");//
    img[6] = al_load_bitmap("./image/shield_fly.png");//
    img[7] = al_load_bitmap("./image/shield_down.png");//
    img[8] = al_load_bitmap("./image/nthu_fly.png");//
    img[9] = al_load_bitmap("./image/nthu_down.png");//
    img[10] = al_load_bitmap("./image/nthu_shield_fly.png");//
    img[11] = al_load_bitmap("./image/nthu_shield_down.png");//
    //
    x = 300;
    y = HEIGHT - 280;
    velocity = 0;
    accleration = 1000;
    init_velocity = -10000000;
    init_position = HEIGHT - 280;
    velocity = init_velocity;
    position = 0;
    state = RUN;
    anime = 0;
    anime_time = 30;
    width = 0; //al_get_bitmap_width(img[0]);
    height = 0;//al_get_bitmap_height(img[0]);
}

Panda::~Panda()
{
    for (int i = 0; i <= 11; i++)
    {
        al_destroy_bitmap(img[i]);
    }
}

void Panda::Panda_process(ALLEGRO_EVENT event)
{
    if (event.type == ALLEGRO_EVENT_TIMER)
    {
        if (event.timer.source == fps)
        {
            anime++;
            anime %= anime_time;
            if (long_press == 1)
            {
                printf("long_press==1\n");
                state = JUMP;
                y = y - jump_unit;
                if (y <= 0)
                {
                    y = 0;
                }
            }
            else if (long_press == 2)
            {
                printf("long_press==2\n");
                state = DOWN;
                if (y >= HEIGHT - 280)
                {
                    state = RUN;
                    y = HEIGHT - 280;
                    long_press = 0;
                }
                y = y + jump_unit;
            }
        }
        // process the keyboard event
    }
    else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        if (event.keyboard.keycode == ALLEGRO_KEY_SPACE)
        {
            //printf("YES\n");
            long_press = 1;
        }
        anime = 0;
    }
    else if (event.type == ALLEGRO_EVENT_KEY_UP)
    {
        key_state[event.keyboard.keycode] = false;
        if (event.keyboard.keycode == ALLEGRO_KEY_SPACE)
        {
            // printf("event.keyboard.keycode == ALLEGRO_KEY_SPACE\n");
            long_press = 2;
        }
    }
}
void Panda::Panda_update()
{
    long_press = 0;
}

void Panda::Panda_draw()
{
    if (wear_cloth == 2)
    {
        if (shield_get == 0)
        {
            if (state == RUN)
            {
                if (anime < anime_time / 2)
                {
                    al_draw_bitmap(img[0], x, y, 0);
                }
                else
                {
                    al_draw_bitmap(img[1], x, y, 0);
                }
            }
            else if (state == JUMP)
            {
                al_draw_bitmap(img[8], x, y, 0);
            }
            else if (state == DOWN)
            {
                al_draw_bitmap(img[9], x, y, 0);
            }
        }
        else if (shield_get == 1)
        {
            printf("shield_get=1;\n");
            if (state == RUN)
            {

                if (anime < anime_time / 2)
                {
                    al_draw_bitmap(img[4], x, y, 0);
                }
                else
                {
                    al_draw_bitmap(img[5], x, y, 0);
                }
            }
            else if (state == JUMP)
            {
                al_draw_bitmap(img[10], x, y, 0);
            }
            else if (state == DOWN)
            {
                al_draw_bitmap(img[11], x, y, 0);
            }
            // shield_get=0;
        }
    }

    else if (wear_cloth == 3 || wear_cloth == 1)
    {
        if (shield_get == 0)
        {
            if (state == RUN)
            {
                if (anime < anime_time / 2)
                {
                    al_draw_bitmap(img[0], x, y, 0);
                }
                else
                {
                    al_draw_bitmap(img[1], x, y, 0);
                }
            }
            else if (state == JUMP)
            {
                al_draw_bitmap(img[2], x, y, 0);
            }
            else if (state == DOWN)
            {
                al_draw_bitmap(img[3], x, y, 0);
            }
        }
        else if (shield_get == 1)
        {
            printf("shield_get=1;\n");
            if (state == RUN)
            {

                if (anime < anime_time / 2)
                {
                    al_draw_bitmap(img[4], x, y, 0);
                }
                else
                {
                    al_draw_bitmap(img[5], x, y, 0);
                }
            }
            else if (state == JUMP)
            {
                al_draw_bitmap(img[6], x, y, 0);
            }
            else if (state == DOWN)
            {
                al_draw_bitmap(img[7], x, y, 0);
            }
            // shield_get=0;
        }
    }
}


