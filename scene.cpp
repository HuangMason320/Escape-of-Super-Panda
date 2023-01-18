#include "scene.h"
#include "character.h"
#include "elec.h"
#include "global.h"
#include "coin.h"
#include "shield.h"
#include "GameWindow.h"

typedef struct bg
{
    double x, y, vely;
    int height, width;

} BackGround;

BackGround BG;
ALLEGRO_SAMPLE_INSTANCE *scene_menu;
// extra add
ALLEGRO_SAMPLE *over_input = NULL;
ALLEGRO_SAMPLE_INSTANCE *over_sound = NULL;

Panda *panda;

int game_pic;

ALLEGRO_FONT *font_subtitle = NULL;
ALLEGRO_FONT *font_title = NULL;
ALLEGRO_FONT *font_subtitle2 = NULL;
ALLEGRO_FONT *font_num = NULL;

ALLEGRO_SAMPLE *menu_s = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *background_prev = NULL;
ALLEGRO_BITMAP *cloth1 = NULL;
ALLEGRO_BITMAP *cloth2 = NULL;
ALLEGRO_BITMAP *cloth3 = NULL;

// function of home page
void home_init()
{
    font_subtitle = al_load_ttf_font("./font/Vacaciones.ttf", 50, 0);
    font_title = al_load_ttf_font("./font/Vacaciones.ttf", 80, 0);
    background = al_load_bitmap("./image/cover.png"); // ./image/image_panda/panda/cloth_panda/yet_wear.png
}
void home_process(ALLEGRO_EVENT event)
{
    if (event.type == ALLEGRO_EVENT_KEY_UP)
    {
        if (event.keyboard.keycode == ALLEGRO_KEY_ENTER)
        {
            // get to menu
            judge_next_window = true;
            next_window = 1;
        }
    }
}
void home_draw()
{
    al_clear_to_color(al_map_rgb(100, 200, 100));
    al_draw_bitmap(background, 0, 0, 0);
    al_draw_text(font_title, al_map_rgb(50, 255, 50), WIDTH / 2 + 300, HEIGHT / 2 - 100, ALLEGRO_ALIGN_CENTRE, "Escape Of Super Panda");
    al_draw_text(font_subtitle, al_map_rgb(255, 255, 255), WIDTH / 2 + 300, HEIGHT / 2 + 110, ALLEGRO_ALIGN_CENTRE, " Press 'Enter' to start ");
    al_draw_rectangle(WIDTH / 2 + 10, HEIGHT / 2 + 100, WIDTH / 2 + 600, HEIGHT / 2 + 180, al_map_rgb(255, 255, 255), 8);
}
void home_destroy()
{
    al_destroy_font(font_subtitle);
    al_destroy_font(font_title);
    al_destroy_bitmap(background);
}
// function of menu
void menu_init()
{
    font_title = al_load_ttf_font("./font/Vacaciones.ttf", 60, 0);
    font_subtitle = al_load_ttf_font("./font/Vacaciones.ttf", 30, 0);
}
void menu_process(ALLEGRO_EVENT event)
{
    if (event.type == ALLEGRO_EVENT_KEY_UP)
    {
        if (event.keyboard.keycode == ALLEGRO_KEY_P)
        {
            // Start
            judge_next_window = true;
            next_window = 2;
        }

        if (event.keyboard.keycode == ALLEGRO_KEY_W)
        {
            // Wardrobe
            judge_next_window = true;
            next_window = 3;
        }

        if (event.keyboard.keycode == ALLEGRO_KEY_L)
        {
            // Rule
            judge_next_window = true;
            next_window = 4;
        }
    }
}

void menu_draw()
{
    al_clear_to_color(al_map_rgb(200, 100, 200));
    al_draw_text(font_title, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 - 300, ALLEGRO_ALIGN_CENTRE, "MENU");
    al_draw_text(font_subtitle, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 - 100, ALLEGRO_ALIGN_CENTRE, "Press 'P' to Play");
    al_draw_text(font_subtitle, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "Press 'W' to Wardrobe");
    al_draw_text(font_subtitle, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 100, ALLEGRO_ALIGN_CENTRE, "Press 'L' to Rules");
    al_draw_text(font_subtitle, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 200, ALLEGRO_ALIGN_CENTRE, "Press 'ESC' to Leave");
    al_draw_rectangle(WIDTH / 2 - 180, 400 - 10, WIDTH / 2 + 180, 440 + 10, al_map_rgb(255, 255, 255), 8);
    al_draw_rectangle(WIDTH / 2 - 180, 500 - 10, WIDTH / 2 + 180, 540 + 10, al_map_rgb(255, 255, 255), 8);
    al_draw_rectangle(WIDTH / 2 - 180, 600 - 10, WIDTH / 2 + 180, 640 + 10, al_map_rgb(255, 255, 255), 8);
    al_draw_rectangle(WIDTH / 2 - 180, 700 - 10, WIDTH / 2 + 180, 740 + 10, al_map_rgb(255, 255, 255), 8);
}

void menu_destroy()
{
    al_destroy_font(font_subtitle);
    al_destroy_sample_instance(scene_menu);
}

// function of game_scene
void game_scene_init()
{
    font_num = al_load_ttf_font("./font/Nunito_ExtraBold.ttf", 40, 4);
    game_start_time = al_get_time();
    game_pic = 0;
    // character_init
    panda = new Panda();
    coin_init();
    shield_init();
    elec_init();
    // background change
    background = al_load_bitmap("./image/background1.png");
    background_prev = background;
    game_start_time = al_get_time();
    game_cnt = 0;
    BG.height = HEIGHT;
    BG.width = WIDTH;
    BG.x = 0;
    BG.y = 0;
}
void game_process(ALLEGRO_EVENT event)
{
    panda->Panda_process(event);
}
void game_scene_update()
{
    // prop create
    coin_create();
    shield_create();
    elec_create();
    BG.x -= speed;
    // prop update
    elec_update(300, panda->y);
    shield_update(300, panda->y);
    coin_update(300, panda->y);
    if (shield_start == true)
    {
        shield_count--;
        if (shield_count == 0)
        {
            shield_start = false;
            shield_get = 0;
        }
    }
    if (game_cnt == 5)
    {
        if (game_pic == 0)
        {
            background = al_load_bitmap("./image/background2.png");
            game_pic++;
            game_cnt = 0;
            speed += 1;
        }
        else if (game_pic == 1)
        {
            background_prev = background;
            background = al_load_bitmap("./image/background3.png");
            game_pic++;
            game_cnt = 0;
            speed += 2;
        }
        else if (game_pic == 2)
        {
            background_prev = background;
            background = al_load_bitmap("./image/background1.png");
            game_pic = 0;
            game_cnt = 0;
            speed += 2;
        }
    }
    if (BG.x + BG.width < 0)
    {
        background_prev = background;
        BG.x = 0;
        game_cnt++;
    }
}

void game_scene_draw()
{
    al_draw_bitmap(background_prev, BG.x, BG.y, 0);

    if (BG.x + BG.width <= WIDTH)
        al_draw_bitmap(background, BG.x + BG.width, BG.y, 0);

    // draw items
    coin_draw();
    elec_draw();
    shield_draw();
    // character_draw
    panda->Panda_draw();
    // count draw
    al_draw_text(font_num, al_map_rgb(250, 150, 0), 50, 10, ALLEGRO_ALIGN_LEFT, "Coins:");
    al_draw_textf(font_num, al_map_rgb(250, 150, 0), 300, 10, ALLEGRO_ALIGN_RIGHT, "%d", coin_count);
    game_over_time = al_get_time();
    game_time_total = game_over_time - game_start_time;
    al_draw_text(font_num, al_map_rgb(250, 150, 0), 50, 40, ALLEGRO_ALIGN_LEFT, "Time:              s");
    al_draw_textf(font_num, al_map_rgb(250, 150, 0), 300, 40, ALLEGRO_ALIGN_RIGHT, "%6.2f", game_time_total);
}

void game_scene_destroy()
{
    al_destroy_bitmap(background);
    elec_destroy();
    coin_destroy();
    shield_destroy();
    // character_destory
    panda->~Panda();
}

// function of dress_scene
void dress_scene_init()
{
    background = al_load_bitmap("./image/wardrobe_panda.png");
    font_title = al_load_ttf_font("./font/Vacaciones.ttf", 60, 4);
    font_subtitle = al_load_ttf_font("./font/Vacaciones.ttf", 30, 0);
    cloth2 = al_load_bitmap("./image/purple_cloth_cut.png");
    cloth3 = al_load_bitmap("./image/red_cloth_cut.png");
}
void dress_scene_process(ALLEGRO_EVENT event)
{
    if (event.type == ALLEGRO_EVENT_KEY_UP)
    {
        if (event.keyboard.keycode == ALLEGRO_KEY_O)
        {
            back_front_window = true;
        }
        if (event.keyboard.keycode == ALLEGRO_KEY_N)
        {
            // dress_up=true;
            wear_cloth = 2;
        }
        if (event.keyboard.keycode == ALLEGRO_KEY_B)
        {
            // dress_up=true;
            wear_cloth = 3;
        }
    }
}

void dress_scene_draw()
{
    al_clear_to_color(al_map_rgb(255, 245, 219));
    al_draw_bitmap(background, WIDTH / 2 - 403, 0, 0);
    al_draw_text(font_title, al_map_rgb(255, 100, 100), WIDTH / 2, 60, ALLEGRO_ALIGN_CENTRE, "Wardrobe");
    al_draw_text(font_subtitle, al_map_rgb(255, 150, 150), WIDTH / 2, 140, ALLEGRO_ALIGN_CENTRE, "Let's choose our outfit !");
    al_draw_text(font_subtitle, al_map_rgb(255, 100, 100), 100, HEIGHT - 140, ALLEGRO_ALIGN_LEFT, "Press 'N' to wear                      cloth"); // 22
    al_draw_text(font_subtitle, al_map_rgb(255, 100, 255), 100 + 270, HEIGHT - 140, ALLEGRO_ALIGN_LEFT, "purple");
    al_draw_text(font_subtitle, al_map_rgb(255, 100, 100), 100, HEIGHT - 100, ALLEGRO_ALIGN_LEFT, "Press 'B' to wear              cloth"); // 14
    al_draw_text(font_subtitle, al_map_rgb(255, 10, 10), 100 + 270, HEIGHT - 100, ALLEGRO_ALIGN_LEFT, "red");
    al_draw_text(font_subtitle, al_map_rgb(255, 100, 100), 100, HEIGHT - 60, ALLEGRO_ALIGN_LEFT, "Press 'O' back to MENU");
    if (wear_cloth == 2)
    {
        // change to second color
        al_draw_bitmap(cloth2, 0, 5, 0);
    }
    if (wear_cloth == 3)
    {
        // change to third color
        al_draw_bitmap(cloth3, 0, 5, 0);
    }
}
void dress_scene_destroy()
{
    al_destroy_font(font_subtitle);
    al_destroy_font(font_title);
    al_destroy_bitmap(background);
    al_destroy_bitmap(cloth2);
    al_destroy_bitmap(cloth3);
}

// function of instructions_scene
void instructions_scene_init()
{
    font_title = al_load_ttf_font("./font/Vacaciones.ttf", 60, 4);
    font_subtitle = al_load_ttf_font("./font/Nunito_ExtraBold.ttf", 25, 0);
    font_subtitle2 = al_load_ttf_font("./font/Nunito_ExtraBold.ttf", 25, 0);
}

void instructions_scene_process(ALLEGRO_EVENT event)
{
    if (event.type == ALLEGRO_EVENT_KEY_UP)
        if (event.keyboard.keycode == ALLEGRO_KEY_O)
            back_front_window = true;
}
void instructions_scene_draw()
{
    al_clear_to_color(al_map_rgb(255, 255, 0));
    int lines[50] = {0};

    for (int i = 0; i < 15; i++)
    {
        lines[i] = 240 + i * 30;
    }
    al_draw_text(font_title, al_map_rgb(250, 150, 0), WIDTH / 2, 60 + 60, ALLEGRO_ALIGN_CENTRE, "Story of Panda");
    al_draw_text(font_subtitle, al_map_rgb(250, 150, 0), WIDTH / 2, lines[0], ALLEGRO_ALIGN_CENTRE, "Super Panda is trying to steal the Logo of NYCU.");
    al_draw_text(font_subtitle, al_map_rgb(250, 150, 0), WIDTH / 2, lines[1], ALLEGRO_ALIGN_CENTRE, "He has to avoid the obstacles in NTHU and NYCU");
    al_draw_text(font_subtitle, al_map_rgb(250, 150, 0), WIDTH / 2, lines[2], ALLEGRO_ALIGN_CENTRE, "setting by NYCU's students to finish the mission.");
    al_draw_text(font_subtitle, al_map_rgb(250, 150, 0), WIDTH / 2, lines[3], ALLEGRO_ALIGN_CENTRE, "Once he touch the obstacles three times,");
    al_draw_text(font_subtitle, al_map_rgb(250, 150, 0), WIDTH / 2, lines[4], ALLEGRO_ALIGN_CENTRE, "he will get caught by the polices");
    al_draw_text(font_subtitle, al_map_rgb(250, 150, 0), WIDTH / 2, lines[5], ALLEGRO_ALIGN_CENTRE, "and you will lose the game.");
    al_draw_text(font_subtitle, al_map_rgb(250, 150, 0), WIDTH / 2, lines[6], ALLEGRO_ALIGN_CENTRE, "Beside avoiding the obstacles, trying to ");
    al_draw_text(font_subtitle, al_map_rgb(250, 150, 0), WIDTH / 2, lines[7], ALLEGRO_ALIGN_CENTRE, "get as much coin as you can.");
    al_draw_text(font_subtitle, al_map_rgb(250, 150, 0), WIDTH / 2, lines[8], ALLEGRO_ALIGN_CENTRE, "There will be a shield for Panda to protect him ");
    al_draw_text(font_subtitle, al_map_rgb(250, 150, 0), WIDTH / 2, lines[9], ALLEGRO_ALIGN_CENTRE, "for five second after he touch the obstacles.");
    al_draw_text(font_subtitle, al_map_rgb(250, 150, 0), WIDTH / 2, lines[10], ALLEGRO_ALIGN_CENTRE, "In addition, the obstacles include different kinds of electric wires.");
    al_draw_text(font_subtitle, al_map_rgb(250, 150, 0), WIDTH / 2, lines[11], ALLEGRO_ALIGN_CENTRE, "Trying your best to make Super Panda stay alive, ");
    al_draw_text(font_subtitle, al_map_rgb(250, 150, 0), WIDTH / 2, lines[12], ALLEGRO_ALIGN_CENTRE, "and gain as much coins as possible.");
    al_draw_text(font_subtitle, al_map_rgb(250, 150, 0), WIDTH / 2, lines[13], ALLEGRO_ALIGN_CENTRE, "Good Luck!!");
    al_draw_text(font_subtitle, al_map_rgb(250, 150, 0), WIDTH / 2, lines[14], ALLEGRO_ALIGN_CENTRE, "");

    al_draw_text(font_title, al_map_rgb(250, 150, 0), WIDTH / 2, HEIGHT / 2 + 200, ALLEGRO_ALIGN_CENTRE, "How to Play");
    al_draw_text(font_subtitle2, al_map_rgb(250, 150, 0), WIDTH / 2, 790, ALLEGRO_ALIGN_CENTRE, "Press or Hold 'SPACE' to Jump");
    al_draw_text(font_subtitle2, al_map_rgb(250, 150, 0), WIDTH / 2, 830, ALLEGRO_ALIGN_CENTRE, "Press 'M' to Mute or Unmute");
    al_draw_text(font_subtitle2, al_map_rgb(250, 150, 0), WIDTH / 2, 870, ALLEGRO_ALIGN_CENTRE, "Press 'O' to Back to MENU");
}

void instructions_scene_destroy()
{
    al_destroy_font(font_subtitle);
    al_destroy_font(font_title);
    al_destroy_font(font_subtitle2);
}
void over_scene_init()
{
    game_over_time = al_get_time();
    game_time_total = game_over_time - game_start_time;
    font_title = al_load_ttf_font("./font/Vacaciones.ttf", 80, 4);
    font_subtitle = al_load_ttf_font("./font/Vacaciones.ttf", 30, 0);
    font_num = al_load_ttf_font("./font/Nunito_ExtraBold.ttf", 80, 4);
    background = al_load_bitmap("./image/lose_panda.png");
    // music //extra add
    over_input = al_load_sample("./GameOverSound.mp3");
    over_sound = al_create_sample_instance(over_input);
    al_set_sample_instance_playmode(over_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(over_sound, al_get_default_mixer());
    // extra add
    al_play_sample_instance(over_sound);
    al_attach_sample_instance_to_mixer(over_sound, al_get_default_mixer());

    over_scene_draw();
}
void over_scene_draw()
{

    // printf("over_scene_draw\n");
    al_clear_to_color(al_map_rgb(200, 0, 0));
    al_draw_text(font_title, al_map_rgb(250, 150, 0), WIDTH / 2, 60 + 60, ALLEGRO_ALIGN_CENTRE, "Game over...");
    // printf("%d\n",game_over_time);
    al_draw_text(font_title, al_map_rgb(250, 150, 0), WIDTH / 2 - 450, HEIGHT / 2 - 50, ALLEGRO_ALIGN_LEFT, "Time Record:                s");
    al_draw_textf(font_num, al_map_rgb(250, 150, 0), WIDTH / 2 + 350, HEIGHT / 2 - 50, ALLEGRO_ALIGN_RIGHT, "%6.2f", game_time_total);
    al_draw_text(font_title, al_map_rgb(250, 150, 0), WIDTH / 2 - 450, HEIGHT / 2 + 50, ALLEGRO_ALIGN_LEFT, "Coin Record:");
    al_draw_textf(font_num, al_map_rgb(250, 150, 0), WIDTH / 2 + 350, HEIGHT / 2 + 55, ALLEGRO_ALIGN_RIGHT, "%d", coin_count);
    al_draw_text(font_subtitle, al_map_rgb(255, 255, 255), 100, 1000 - 140, ALLEGRO_ALIGN_LEFT, "Press 'R' to Replay");
    al_draw_text(font_subtitle, al_map_rgb(255, 255, 255), 100, 1000 - 100, ALLEGRO_ALIGN_LEFT, "Press 'O' to MENU");
    al_draw_text(font_subtitle, al_map_rgb(255, 255, 255), 100, 1000 - 60, ALLEGRO_ALIGN_LEFT, "Press 'ESC' to Leave");
    // al_draw_bitmap(background, WIDTH/2-190, HEIGHT/2-150, 0);
}
void over_scene_process(ALLEGRO_EVENT event)
{
    if (event.type == ALLEGRO_EVENT_KEY_UP)
    {
        // leave
        if (event.keyboard.keycode == ALLEGRO_KEY_O)
        {
            // panda->Panda_update();
            judge_next_window = true;
            next_window = 1;
            coin_count = 0;
            speed = init_speed;
            long_press = 0;
            shield_get = 0;
            total = 0;
            game_start_time = al_get_time();
            game_update();
        }
        // replay
        else if (event.keyboard.keycode == ALLEGRO_KEY_R)
        {
            // panda->Panda_update();
            judge_next_window = true;
            next_window = 2;
            coin_count = 0;
            long_press = 0;
            shield_get = 0;
            speed = init_speed;
            total = 0;
            game_start_time = al_get_time();
            game_update();
        }
    }
}
void over_scene_destroy()
{
    // al_destroy_bitmap(background);
    al_destroy_font(font_title);
    al_destroy_font(font_subtitle);
    // extra add
    // al_destroy_sample_instance(over_sound);
}
