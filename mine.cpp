Mine::Mine(float x, float y) {
    
    this->x = x;
    this->y = y;
    width = MINE_IMAGE_WIDTH;
    height = MINE_IMAGE_HEIGHT;
    speed = MINE_SPEED;
    
    image = al_load_bitmap(MINE_IMAGE);
    al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));

}

Mine::~Mine() {
    al_destroy_bitmap(this->image);
}

void Mine::update() {
    y -= speed;
    if(y < SEA_LEVEL) live = false;
}

void Mine::draw() {
    if(curFrame > 7) curFrame = 0;
    al_draw_bitmap_region(image, 0, curFrame * MINE_IMAGE_SPLIT, MINE_IMAGE_WIDTH , MINE_IMAGE_HEIGHT, x, y, 0);
    if(++frameCount > 10) {
        curFrame++;
        frameCount = 0;
    }
}

void Mine::draw_rectangle() {
    al_draw_rectangle(x,y,x+MINE_IMAGE_WIDTH,y+MINE_IMAGE_HEIGHT, color, 2)
}
