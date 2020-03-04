#include <iostream>
#include <ctime>
#include <list>
#include <cmath>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "settings.h"
#include "sprite.h"
#include "ship.h"
#include "bomb.h"
#include "submarines.h"
#include "mine.h"

using namespace std;

template <typename T1, typename T2> 
bool collision(T1 obj1, T2 obj2) {
    float Lx1 = obj1->x;
    float Rx1 = obj1->x + obj1->width;
    float Ty1 = obj1->y;
    float By1 = obj1->y + obj1->height;
    
    float Lx2 = obj2->x;
    float Rx2 = obj2->x + obj2->width;
    float Ty2 = obj2->y;
    float By2 = obj2->y + obj2->height;

    if( (Lx1 >= Lx2 && Lx1 <= Rx2) || (Rx1 >=Lx2 && Rx1 <= Rx2) ) {
        if( (Ty1 >= Ty2 && Ty1 <= By2) || (By1 >= Ty2 && By1 <= By2) ) {
            return true;
        }
    }
    if( (Lx2 >= Lx1 && Lx2 <= Rx1) || (Rx2 >=Lx1 && Rx2 <= Rx1) ) {
        if( (Ty2 >= Ty1 && Ty2 <= By1) || (By2 >= Ty1 && By2 <= By1) ) {
            return true;
        }
    }
    return false;
}

int main(int argc, char * argv[]) {

    srand(time(NULL));
    ALLEGRO_DISPLAY * display = NULL;
    ALLEGRO_EVENT_QUEUE * event_queue = NULL;
    ALLEGRO_TIMER * timer = NULL;
    ALLEGRO_BITMAP * background = NULL;

    if(!al_init()) {
        std::cerr << "Failed to initialize allegro library" << std::endl;
        return -1;
    }

    display = al_create_display(WIDTH, HEIGHT);
    if(!display) {
        std::cerr << "Failed to create a display" << std::endl;
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
        std::cerr << "Failed to create a timer" << std::endl;
        al_destroy_display(display);
        return -1;
    }

    event_queue = al_create_event_queue();
    if(!event_queue) {
        std::cerr << "Failed to create a event queue" << std::endl;
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }
    

    // attach additional
    al_install_keyboard();
    al_init_image_addon();
    al_init_primitives_addon();

    // register
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));


    // preparing board
    background = al_load_bitmap(BACKGROUND_IMAGE_2);

    // sprites groups
    std::list<Sprite*> all_sprites;
    std::list<Bomb*> bombs;
    std::list<Submarine*> submarines;
    std::list<Mine*> mines;

    // create player
    Ship * ship = new Ship();
    all_sprites.push_back(ship);

    // create submarines
    for(int i = 0; i < 6; i++) {

        // test 
        //Submarine * submarine;
        //submarine = new SubmarineAdvance();
        //submarines.push_back(submarine);
        //all_sprites.push_back(submarine);
        
        //game       
        Submarine * submarine;
        if(i < 3) submarine = new SubmarinePrime();
        else if (i < 5) submarine = new SubmarineMedium();
        else submarine = new SubmarineAdvance();
        submarines.push_back(submarine);
        all_sprites.push_back(submarine);
        
    }

   
    
    // main loop
    enum Direction {RIGHT, LEFT, NONE};
    int dir = NONE;
    al_start_timer(timer);
    bool showInfo = false;
    
    bool run = true;
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
                    bombs.push_back(bomb_tmp);
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
        for(auto s = submarines.begin(); s!=submarines.end(); s++) {
            if((*s)->live==false) {
                submarines.remove(*s);
                all_sprites.remove(*s);
                delete *s;
                continue;
            }
            if((*s)->attack() && (*s)->active) {
                Mine * mine;
                mine = new Mine((*s)->x, (*s)->y);
                mines.push_back(mine);
                all_sprites.push_back(mine);
            }
        }

        // update         
        for(auto it = all_sprites.begin(); it!=all_sprites.end(); it++) {
            (*it)->update();
        }

        // collision check
        for(auto m = mines.begin(); m!=mines.end(); m++) {
            if( !(*m)->live ) {
                if(collision(*m,ship)) {
                    cout << "statek dostal" << endl;
                }
                mines.remove(*m);
                all_sprites.remove(*m);
                delete *m;
            }
            else {
                for(auto b = bombs.begin(); b!=bombs.end(); b++) {
                    if((*m)->active == false) break;
                    if(collision(*b,*m)) {
                        bombs.remove(*b);
                        all_sprites.remove(*b);
                        delete *b;
                        (*m)->deactive();
                    }
                }
            }
        }

        for(auto b = bombs.begin(); b!=bombs.end(); b++) {
            if(!(*b)->live) {
                bombs.remove(*b);
                all_sprites.remove(*b);
                delete *b;
            }
            else {
                for(auto s = submarines.begin(); s!=submarines.end(); s++) {
                    if((*s)->active) {
                        if(collision(*b,*s)) {
                            bombs.remove(*b);
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

    // destroy
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_bitmap(background);
    for(auto it = all_sprites.begin(); it!=all_sprites.end(); it++) delete *it;
    
    return 0;
}
