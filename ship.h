class Ship : public Sprite {
public: 
    float speed = 0;
        
    Ship();
    ~Ship();

    void update();
    void draw();       
    void draw_rectangle();       
}; 

Ship::Ship() {
    x = rand() % WIDTH;
    y = SEA_LEVEL-SHIP_IMAGE_HEIGHT;
    width = SHIP_IMAGE_WIDTH;
    height = SHIP_IMAGE_HEIGHT;
    image = al_load_bitmap(SHIP_IMAGE);
    al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));
}

Ship::~Ship() {
    al_destroy_bitmap(image);
}

void Ship::update() {
    if(speed > SHIP_SPEED) speed = SHIP_SPEED;
    else if(speed < -SHIP_SPEED) speed = -SHIP_SPEED;
    else x += speed;
    if(x < 0) {
        x = 0;
        speed = 0;
    }
    else if(x + SHIP_IMAGE_WIDTH > WIDTH) {
        x = WIDTH - SHIP_IMAGE_WIDTH;
        speed = 0;
    }
}

void Ship::draw() {
    al_draw_bitmap(image, x, y, 0);
}

void Ship::draw_rectangle() {
    al_draw_rectangle(x, y, x + width, y + height, RED, 2);
}