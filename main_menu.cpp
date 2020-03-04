#include <iostream>
#include <string>
#include <ctime>
#include <list>
#include <cmath>

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_font.h>

using namespace std;

#include "settings.h"
#include "button.h"
#include "sprite.h"
#include "ship.h"
#include "bomb.h"
#include "submarines.h"
#include "mine.h"
#include "collision.h"

int main(int argc, char* argv[]) {

    // initialize allegro library and componets
    al_init();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_install_mouse();
    
    // create pointers 
    ALLEGRO_DISPLAY * display = NULL;
    ALLEGRO_TIMER * timer = NULL;
    ALLEGRO_BITMAP * background = NULL;
    ALLEGRO_FONT *font = NULL; 
    ALLEGRO_EVENT_QUEUE * event_queue = NULL;

    display = al_create_display(WIDTH, HEIGHT);
    timer = al_create_timer(1.0 / FPS);
    background = al_load_bitmap(BACKGROUND_IMAGE_0);
    font = al_load_font(FONT_STYLE, FONT_SIZE, 0);
    event_queue = al_create_event_queue();

    // register events 
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());



    

    //--------------------------------------------------------------------------
    //-------------W-E-L-C-O-M-E----S-C-R-E-E-N---------------------------------
    //--------------------------------------------------------------------------
    
    int menuDecision = 0;
    const int n = 3;
    Button* button_table[n];
    button_table[0] =  new Button(150, 200, "Play Game");
    button_table[1] =  new Button(100, 300, "Option");;
    button_table[2] =  new Button(70, 400, "Exit");
    
    int mx = 0;
    int my = 0;


    bool run = true;
    while(run) {
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);
        
        if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            run = false;
        }
        
        else if(events.type == ALLEGRO_EVENT_MOUSE_AXES) {
            mx = events.mouse.x;
            my = events.mouse.y;
        }

        // draw and update
        al_draw_bitmap(background, 0, 0, 0);
        al_draw_text(font, al_map_rgb(0, 0, 255), WIDTH/2, 20, ALLEGRO_ALIGN_CENTRE, "submarine_table by PAFiM37" );
        al_draw_line(0, 100, WIDTH, 100, al_map_rgb(255, 255, 255), 2);
        for(int i = 0; i < n; i++) {
            button_table[i]->update(mx, my);
            if(button_table[i]->action) {
                menuDecision = i+1;
                run = false;
            }
        }
        al_flip_display();
    }
    
    for(int i = 0; i < n; i++) delete button_table[i];
    al_uninstall_mouse();



    //--------------------------------------------------------------------------
    //-------------G-A-M-E----S-C-R-E-E-N---------------------------------------
    //--------------------------------------------------------------------------

    if(menuDecision==1) {
        background = al_load_bitmap(BACKGROUND_IMAGE_2);

        // sprites groups
        std::list<Sprite*> all_sprites;
        std::list<Bomb*> bomb_table;
        std::list<Submarine*> submarine_table;
        std::list<Mine*> mine_table;

        // create player
        Ship * ship = new Ship();
        all_sprites.push_back(ship);

        // create submarine_table
        for(int i = 0; i < 6; i++) {
            Submarine * submarine;
            if(i < 3) submarine = new SubmarinePrime();
            else if (i < 5) submarine = new SubmarineMedium();
            else submarine = new SubmarineAdvance();
            submarine_table.push_back(submarine);
            all_sprites.push_back(submarine);
        }

        enum Direction {RIGHT, LEFT, NONE};
        int dir = NONE;
        al_start_timer(timer);
        bool showInfo = false;
        
        // main loop
        run = true;
        while(run) {
            ALLEGRO_EVENT events;
            al_wait_for_event(event_queue, &events);

            if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                run = false;
            }
            
            if(events.type == ALLEGRO_EVENT_KEY_DOWN) {
                switch (events.keyboard.keycode) {
                    case ALLEGRO_KEY_RIGHT:
                        dir = RIGHT;
                        break;
                    case ALLEGRO_KEY_LEFT:
                        dir = LEFT;
                        break;
                    case ALLEGRO_KEY_DOWN:
                        Bomb * bomb_tmp;
                        bomb_tmp = new Bomb(ship->x + SEA_LEVEL / 2);
                        all_sprites.push_back(bomb_tmp);
                        bomb_table.push_back(bomb_tmp);
                        break;
                    case ALLEGRO_KEY_F1:
                        showInfo ? showInfo = false : showInfo = true;
                        break;
                    case ALLEGRO_KEY_ESCAPE:
                        run = false;
                        break;
                    default:
                        break;
                }
            }

            if(events.type == ALLEGRO_EVENT_TIMER) {
                switch (dir) {
                    case RIGHT:
                        ship->speed += 1;
                        break;
                    case LEFT:
                        ship->speed -= 1;
                        break;
                    default:
                        break;
                }
                dir = NONE;
            }

            // submarine attack or explosion
            for(auto s = submarine_table.begin(); s!=submarine_table.end(); s++) {
                if((*s)->live==false) {
                    submarine_table.remove(*s);
                    all_sprites.remove(*s);
                    delete *s;
                    continue;
                }
                if((*s)->attack() && (*s)->active) {
                    Mine * mine;
                    mine = new Mine((*s)->x, (*s)->y);
                    mine_table.push_back(mine);
                    all_sprites.push_back(mine);
                }
            }

            
            // update         
            for(auto it = all_sprites.begin(); it!=all_sprites.end(); it++) {
                (*it)->update();
            }


            
            // collision check
            for(auto m = mine_table.begin(); m!=mine_table.end(); m++) {
                if( !(*m)->live ) {
                    if(collision(*m,ship)) {
                        cout << "statek dostal" << endl;
                    }
                    mine_table.remove(*m);
                    all_sprites.remove(*m);
                    delete *m;
                }
                else {
                    for(auto b = bomb_table.begin(); b!=bomb_table.end(); b++) {
                        if((*m)->active == false) break;
                        if(collision(*b,*m)) {
                            bomb_table.remove(*b);
                            all_sprites.remove(*b);
                            delete *b;
                            (*m)->deactive();
                        }
                    }
                }
            }   





            for(auto b = bomb_table.begin(); b!=bomb_table.end(); b++) {
                if(!(*b)->live) {
                    bomb_table.remove(*b);
                    all_sprites.remove(*b);
                    delete *b;
                }
                else {
                    for(auto s = submarine_table.begin(); s!=submarine_table.end(); s++) {
                        if((*s)->active) {
                            if(collision(*b,*s)) {
                                bomb_table.remove(*b);
                                all_sprites.remove(*b);
                                delete *b;
                                (*s)->deactive();
                            }
                        }
                    }
                }
            }

            // draw
            al_draw_bitmap(background, 0, 0, 0);
            for(auto it = all_sprites.begin(); it!=all_sprites.end(); it++) {
                (*it)->draw();
                if(showInfo) (*it)->draw_rectangle();
            }
            al_flip_display();
        }   
    }


    if(menuDecision==2) cout << "Opcje";
    if(menuDecision==3) cout << "Exit";

    // memory 
    al_destroy_display(display);
    al_destroy_font(font);
    al_destroy_bitmap(background);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);

    return 0;
}