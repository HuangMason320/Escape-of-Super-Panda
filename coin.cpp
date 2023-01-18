#include"global.h"
#include"coin.h"

#define NUM_COINS 20
#define COIN_SIZE_X 35
#define COIN_SIZE_Y 35
//
#define CHAR_SIZE_X 130     //each pic differ
#define CHAR_SIZE_Y 188     //each pic differ
//
ALLEGRO_BITMAP *coins_img = NULL;
ALLEGRO_SAMPLE *coin_input = NULL;
ALLEGRO_SAMPLE_INSTANCE *coin_sound = NULL;

Coin coins[NUM_COINS];
bool Coin_check = true;

void coin_init()
{
    coins_img = al_load_bitmap("./image/coin.png");
    for(int i=0;i<NUM_COINS;i++)
    {
        coins[i].exist = false;
    }
    //extra add
    al_reserve_samples(2);
    coin_input = al_load_sample("./coin_sound.wav");
    coin_sound = al_create_sample_instance(coin_input);
    al_set_sample_instance_playmode(coin_sound, ALLEGRO_PLAYMODE_ONCE);
    //al_restore_default_mixer();
    //al_attach_sample_instance_to_mixer(coin_sound, al_get_default_mixer());
}

void coin_draw()
{
    for(int i=0;i<NUM_COINS;i++)
    {
        if(coins[i].exist)
                al_draw_bitmap(coins_img,coins[i].x,coins[i].y,0);
    }
}

void coin_create()
{
    int random = rand()%3;
    int yplace = rand()%3;
    if(Coin_check)
    {
        if(random == 0)
        {
            //horizontal
            for(int i=0;i<NUM_COINS;i++)
            {
                coins[i].exist=true;
                coins[i].x = WIDTH+(i-1)*COIN_SIZE_X;
                coins[i].y = coin_validy[yplace];
            }
        }
        else if (random == 1)
        {
            //rectangle
            for(int i=0;i<NUM_COINS;i++)
            {
                coins[i].exist=true;
                coins[i].x = WIDTH+(i-1)*COIN_SIZE_X;
                coins[i].y = coin_validy[yplace]+(i/5)*COIN_SIZE_Y;
            }
        }
        else if (random == 2)
        {
            //rectangle 2
            for(int i=0;i<NUM_COINS;i++)
            {
                coins[i].exist=true;
                coins[i].x = WIDTH+(i/5)*COIN_SIZE_X;
                coins[i].y = coin_validy[yplace]+(i%5)*COIN_SIZE_Y;
            }
        }
        Coin_check = false;
        /*
        else if (random == 3)
        {

        }
        else if (random == 4)
        {

        }
        */
    }
}
void coin_update(int x, int y)
{
    for(int i=0;i<NUM_COINS;i++)
    {
        if(coins[i].exist)
        {
            if(coin_encounter(coins[i].x,coins[i].y,x,y))
            {
                coins[i].exist = false;
                coin_count++;
                //extra add
                al_play_sample_instance(coin_sound);
                //al_restore_default_mixer();
                al_attach_sample_instance_to_mixer(coin_sound, al_get_default_mixer());

            }
            coins[i].x-=speed;
            if(coins[i].x+COIN_SIZE_X<=0)
                coins[i].exist = false;
        }
    }
    for(int i=0;i<NUM_COINS;i++)
    {
        if(coins[i].exist==1)
            break;
        if(i==NUM_COINS-1&&!coins[i].exist)
            Coin_check = true;
    }
}

void coin_destroy()
{
    al_destroy_bitmap(coins_img);
    al_destroy_sample_instance(coin_sound);
}
int coin_encounter(int objx, int objy, int charx, int chary)
{
    if(objx<270)
        return 0;
    if(objx>charx&&objx-charx<=CHAR_SIZE_X)
    {
        if(objy>chary&&objy-chary<CHAR_SIZE_Y)
            return 1;
        else if (chary>objy&&chary-objy<COIN_SIZE_Y)
            return 1;
    }
    else if (objx<charx&&charx-objx<=CHAR_SIZE_X)
    {
        if(objy>chary&&objy-chary<CHAR_SIZE_Y)
            return 1;
        else if (chary>objy&&chary-objy<COIN_SIZE_Y)
            return 1;
    }
    return 0;
}
