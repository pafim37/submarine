#include "bomb.h"

Bomb::Bomb(float x)  {
    this->x = x;
    this->y =  SEA_LEVEL;
    width = BOMB_IMAGE_WIDTH;
    height = BOMB_IMAGE_HEIGHT;
            
    image = al_load_bitmap(BOMB_IMAGE);
    al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));
}

Bomb::~Bomb() {
    al_destroy_bitmap(this->image);
}

void Bomb::update()  {
    if(!explosion) {
        cx = x + BOMB_IMAGE_WIDTH / 2;
        cy = y + BOMB_IMAGE_HEIGHT / 2;;
        y += speed;
        if(y > HEIGHT-40 && !explosion) {
            speed = 0;
            explosion = true;
            curFrame = 0;
            image = al_load_bitmap(BOMB_EXPLOSION_IMAGE);
            al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));
        }
    }
}

void Bomb::draw() {
    if(!explosion) {
        if(curFrame > maxCurFrame) curFrame = 0;
        al_draw_bitmap_region(image, 0, curFrame * BOMB_IMAGE_SPLIT, BOMB_IMAGE_WIDTH, BOMB_IMAGE_HEIGHT, x, y, 0);
        if(++frameCount > 5) {
            curFrame++;
            frameCount = 0;
        }
    }
    else {
        if(curFrame > 12) live = false;
        al_draw_bitmap_region(image, 0, curFrame * BOMB_EXPLOSION_IMAGE_SPLIT, BOMB_EXPLOSION_IMAGE_WIDTH, BOMB_EXPLOSION_IMAGE_HEIGHT, x, y, 0);
        if(++frameCount > 2) {
            curFrame++;
            frameCount = 0;
        }
    }
}

void Bomb::draw_rectangle() {
    al_draw_rectangle(x,y,x+BOMB_IMAGE_WIDTH,y+BOMB_IMAGE_HEIGHT, color, 2)
}