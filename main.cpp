#include <iostream>
#include <string>
using namespace std;

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_font.h>

#include "settings.h"
#include "button.h"
#include "sprite.h"
#include "ship.h"
#include "bomb.h"
#include "submarines.h"
#include "mine.h"

class WINDOW {
    public:
        WINDOW();
        ~WINDOW();
    
        void welcome_screen();
    
        ALLEGRO_DISPLAY *display = NULL;
        ALLEGRO_TIMER *timer = NULL;
        ALLEGRO_BITMAP *background = NULL;
        ALLEGRO_EVENT_QUEUE *event_queue = NULL;
};

WINDOW::WINDOW() {
    
    this->display = al_create_display(WIDTH, HEIGHT);
    this->timer = al_create_timer(1.0 / FPS);
    this->event_queue = al_create_event_queue();
}

WINDOW::~WINDOW() {
    al_destroy_display(this->display);
    al_destroy_timer(this->timer);
    //al_destroy_bitmap(this->background);
    //al_destroy_event_queue(event_queue);
}


void WINDOW::welcome_screen() {
    this->background = al_load_bitmap(BACKGROUND_IMAGE_0);
    ALLEGRO_FONT *font = al_load_font(FONT_STYLE, FONT_SIZE, 0);
    int mx = 0;
    int my = 0;
    Button button(300, 250, "Play Game");
    Button button1(300, 350, "Option");
    Button button2(300, 450, "Exit");
    bool run = true;
    while(run) {
        ALLEGRO_EVENT events;
        al_wait_for_event(this->event_queue, &events);
        /*
        if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            run = false;
        }
        else if(events.type == ALLEGRO_EVENT_MOUSE_AXES) {
            mx = events.mouse.x;
            my = events.mouse.y;
        }
        */
        // draw and update 
        al_draw_bitmap(this->background, 0, 0, 0);
        al_draw_text(font, al_map_rgb(0, 0, 0), WIDTH/2, 50, ALLEGRO_ALIGN_CENTRE, "SUBMARINES" );
        button.update(mx,my);
        button1.update(mx,my);
        button2.update(mx,my);
        al_flip_display();
    }
    al_destroy_font(font);
} 


//---------------------------------------------------------------
//-----------------M-A-I-N----F-U-N-C-T-I-O-N--------------------
//---------------------------------------------------------------

int main(int argc, char * argv[]) {
    
    al_init();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    al_install_keyboard();
    al_install_mouse();

    WINDOW game;
    game.welcome_screen();
    cout << "Kocham Marte" << endl;

}