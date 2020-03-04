Ship::Ship() {
    x = rand() % WIDTH;
    y = SEA_LEVEL-SHIP_IMAGE_HEIGHT;
    image = al_load_bitmap(SHIP_IMAGE);
    al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));
}

Ship::~Ship() {
    al_destroy_bitmap(image);
}

void Ship::update() {
    if(speed > SHIP_SPEED) {
        speed = SHIP_SPEED;
    }
    if(speed < -SHIP_SPEED) speed = -SHIP_SPEED;
    x += speed;
    if(x < 0) {
        x = 0;
        speed = 0;
    }
    if(x + SHIP_IMAGE_WIDTH > WIDTH) {
        x = WIDTH - SHIP_IMAGE_WIDTH;
        speed = 0;
        }
}

void Ship::draw() {
    al_draw_bitmap(image, x, y, 0);
}

void Ship::draw_rectangle() {
    al_draw_rectangle(x, y, x + SHIP_IMAGE_WIDTH, y + SHIP_IMAGE_HEIGHT);
}