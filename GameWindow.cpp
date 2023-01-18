#include <iostream>

#include "GameWindow.h"
#include "character.h"
#include "global.h"
#include "elec.h"
#include "coin.h"

//extern Panda *panda;
bool draw = false;
bool mute = false;
int present_window = 0;

const char *title = "Final Project TEAM 48";

// ALLEGRO Variables
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_SAMPLE *song = NULL;
ALLEGRO_SAMPLE_INSTANCE *sample_instance;
ALLEGRO_SAMPLE *sample = NULL;
ALLEGRO_SAMPLE_INSTANCE *startSound = NULL;
//ALLEGRO_SAMPLE_INSTANCE *failSound = NULL;
ALLEGRO_SAMPLE_INSTANCE *backgroundSound = NULL;

int Game_establish()
{
    int msg = 0;

    game_init();
    game_begin();
    while ( msg != GAME_TERMINATE )
    {
        msg = game_run();
        srand(time(NULL));
        if ( msg == GAME_TERMINATE )
            printf( "Game Over\n" );
    }
    game_destroy();
    return 0;
}
void game_init()
{
    printf( "Game Initializing...\n" );
    al_init();
    al_install_audio();     // init audio
    al_init_acodec_addon();
    display = al_create_display(WIDTH, HEIGHT);// Create display
    event_queue = al_create_event_queue();// create event queue

    // Initialize Allegro settings
    al_set_window_position(display, 0, 0);
    al_set_window_title(display, title);
    al_init_primitives_addon();
    al_init_font_addon();   // initialize the font addon
    al_init_ttf_addon();    // initialize the ttf (True Type Font) addon
    al_init_image_addon();  // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon
    al_install_keyboard();  // install keyboard event
    al_install_mouse();     // install mouse event
    al_install_audio();     // install audio event

    // Register event
    al_register_event_source(event_queue, al_get_display_event_source( display ));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    fps = al_create_timer( 1.0 / FPS );
    al_register_event_source(event_queue, al_get_timer_event_source( fps )) ;
    // initialize the icon on the display
    ALLEGRO_BITMAP *icon = al_load_bitmap("./icon.jpg");
    al_set_display_icon(display, icon);
}
void game_begin()
{
    al_reserve_samples(3);
    // Load start sound
    sample = al_load_sample("./start_sound.mp3");
    startSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(startSound, ALLEGRO_PLAYMODE_ONCE);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(startSound, al_get_default_mixer());

    // Load background sound
    song = al_load_sample("./backgroundmusic.mp3");
    backgroundSound = al_create_sample_instance(song);
    al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(backgroundSound, al_get_default_mixer());
    // set the volume of instance
    //al_set_sample_instance_gain(sample_instance, 3) ;
    al_play_sample_instance(startSound);


    while(al_get_sample_instance_playing(startSound));
    al_play_sample_instance(backgroundSound);

    al_start_timer(fps);
    // initialize the menu before entering the loop
    //printf("SUCCESS\n");
    home_init();
}

void game_update()
{
    //1->menu
    //2->game_scene
    //3->dress
    //4->instruction
    //5->over
    //6->pause
    if (judge_next_window)
    {
        if(next_window == 1)     // menu
        {
            if(present_window == 0)
            {
                home_destroy();
                menu_init();
                judge_next_window = false;
                next_window = 0;
                present_window = 1;
            }
            else if (present_window == 3)
            {
                dress_scene_destroy();
                menu_init();
                judge_next_window = false;
                next_window = 0;
                present_window = 1;
            }
            else if (present_window == 5)
            {
                over_scene_destroy();
                menu_init();
                judge_next_window = false;
                next_window = 0;
                present_window = 1;
            }
        }
        else if (next_window == 2)  //game_scene
        {
            if(present_window == 1)
            {
                menu_destroy();
                coin_count = 0;
                total = 0;
                game_scene_init();
                judge_next_window = false;
                next_window = 0;
                present_window = 2;
            }
            else if (present_window == 5)
            {
                game_scene_destroy();
                game_scene_init();
                judge_next_window = false;
                next_window = 0;
                present_window = 2;
            }
        }
        else if (next_window == 3)
        {
            if (present_window == 1)
            {
                dress_scene_init();
                judge_next_window = false;
                next_window = 0;
                present_window = 3;
            }
        }
        else if (next_window == 4)
        {
            if (present_window ==1)
            {
                instructions_scene_init();
                judge_next_window = false;
                next_window = 0;
                present_window = 4;
            }
        }
    }
    else if (back_front_window)
    {
        if (present_window == 3)
        {
            dress_scene_destroy();
            menu_init();
            back_front_window = false;
            present_window = 1;
        }
        else if (present_window == 4)
        {
            instructions_scene_destroy();
            menu_init();
            back_front_window = false;
            present_window = 1;
        }
    }
    if (present_window == 2)
    {
        game_scene_update();
        //need change
        //character_update();
    }
    if(end_round == 1)
    {
        over_scene_init();
        //game_scene_destroy();
        end_round = 0;
        present_window = 5;
    }
}

int process_event()
{
    // Request the event
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event); //copied the first event in event_queue to &event
    // process the event of other component
    if(present_window == 0)
        home_process(event);
    else if(present_window == 1)
        menu_process(event);
    else if(present_window == 2)
        game_process(event);
    else if(present_window ==3)
        dress_scene_process(event);
    else if(present_window ==4 )
        instructions_scene_process(event);
    else if(present_window ==5)
        over_scene_process(event);

    // Shutdown our program
    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        return GAME_TERMINATE;
    }
    if(event.keyboard.keycode==ALLEGRO_KEY_ESCAPE)
    {
        return GAME_TERMINATE;
    }
    if(event.keyboard.keycode == ALLEGRO_KEY_M)
    {
        mute = !mute;
        if(mute)
            al_stop_sample_instance(backgroundSound);
        else
            al_play_sample_instance(backgroundSound);
    }
    else if(event.type == ALLEGRO_EVENT_TIMER)
        if(event.timer.source == fps)
            draw = true;
    if(draw)
        game_update();

    return 0;
}
void game_draw()
{
    if(present_window == 0)
        home_draw();
    if(present_window == 1)
        menu_draw();
    else if(present_window == 2)
        game_scene_draw();
    else if(present_window == 3)
        dress_scene_draw();
    else if(present_window == 4)
        instructions_scene_draw();
    else if(present_window == 5)
        over_scene_draw();

    al_flip_display();
}
int game_run()
{
    int error = 0;
    if( draw )
    {
        game_draw();
        draw = false; //after draw the scene, keep draw as default:false
    }
    if ( !al_is_event_queue_empty(event_queue) )
    {
        //al_is_event_queue_empty() return true if event_queue is empty
        //so now if there is sth in the event_queue, get in this if here.
        error = process_event();  //if there is sth in the event_queue, process the event.
    }
    return error;
}

void game_destroy()
{
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    game_scene_destroy();

    if( present_window == 0)
        home_destroy();
    if( present_window == 1)
        menu_destroy();
    else if(present_window == 2)
        game_scene_destroy();
    else if(present_window == 3)
        dress_scene_destroy();
    else if(present_window == 4)
        instructions_scene_destroy();
    else if (present_window == 5)
        over_scene_draw();
}
