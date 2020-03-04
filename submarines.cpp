SubmarinePrime::SubmarinePrime() {
    x = rand() % WIDTH;
    y = rand() % (HEIGHT - 2 * SEA_LEVEL) + 1.25 * SEA_LEVEL;
    width = IMAGE_SUBMARINE_1_WIDTH;
    height = IMAGE_SUBMARINE_1_HEIGHT;
    image = al_load_bitmap(SUBMARINE_IMAGE_1);
    speed = SUBMARINE_SPEED_1;
    al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));
}
    
SubmarinePrime::~SubmarinePrime() {
    al_destroy_bitmap(image);
}

void SubmarinePrime::update() {
    if(dir == RIGHT) {
        x += speed;
        if(x > WIDTH - SUBMARINE_IMAGE_1_WIDTH) {
            x = WIDTH - SUBMARINE_IMAGE_1_WIDTH;
            dir = LEFT;
            curFrame = 8;
        }
    }
    else if (dir == LEFT) {
        x -= speed;
        if(x < 0) {
            x = 0;
            dir = RIGHT;
            curFrame = 0;
        }
    }
}

void SubmarinePrime::draw() {
    if(dir == RIGHT) {
        if(++frameCount > 20) {
            curFrame > 6 ? curFrame = 0 : curFrame++;;
            frameCount = 0;
        }
    }
    else if(dir == LEFT) {
        if(++frameCount > 20) {
            (curFrame)++;
            if(curFrame > 15) curFrame = 8;
            frameCount = 0;
        }
    }
    al_draw_bitmap_region(image, 0, curFrame * SUBMARINE_IMAGE_1_SPLIT, SUBMARINE_IMAGE_1_WIDTH, SUBMARINE_IMAGE_1_HEIGHT, x, y, 0);
}

bool SubmarinePrime::attack() {
    if(((clock() - start * 1.0) / CLOCKS_PER_SEC) > SUBMARINE_FREQUENCY_ATTACK_1) {
        start = clock();
        return true;
    }
    else return false;
}

void SubmarinePrime::draw_rectangle() {
    al_draw_rectangle(x,y,x+SUBMARINE_IMAGE_1_WIDTH,y+SUBMARINE_IMAGE_1_HEIGHT, color, 2)
}

/* 
    Submarine Medium
*/

SubmarineMedium::SubmarineMedium() {
    x = rand() % WIDTH;
    y = rand() % (HEIGHT - 2 * SEA_LEVEL) + 1.25 * SEA_LEVEL;
    width = IMAGE_SUBMARINE_2_WIDTH;
    height = IMAGE_SUBMARINE_2_HEIGHT;
        
    image = al_load_bitmap(SUBMARINE_IMAGE_2);
    speed = SUBMARINE_SPEED_2;
    al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));
}
    
SubmarineMedium::~SubmarineMedium() {
    al_destroy_bitmap(image);
}

void SubmarineMedium::update() {
    if(dir == RIGHT) {
        x += speed;
        if(x > WIDTH - SUBMARINE_IMAGE_2_WIDTH) {
            x = WIDTH - SUBMARINE_IMAGE_2_WIDTH;
            dir = LEFT;
            curFrame = 8;
        }
    }
    else if (dir == LEFT) {
        x -= speed;
        if(x < 0) {
            x = 0;
            dir = RIGHT;
            curFrame = 0;
        }
    }   
}

void SubmarineMedium::draw()  {
    if(dir == RIGHT) {
        if(++frameCount > 20) {
            (curFrame)++;
            if(curFrame > 7) curFrame = 0;
            frameCount = 0;
        }
    }
    else if(dir == LEFT) {
        if(++frameCount > 20) {
            (curFrame)++;
            if(curFrame > 15) curFrame = 8;
            frameCount = 0;
        }
    }
    al_draw_bitmap_region(image, 0, curFrame * SUBMARINE_IMAGE_2_SPLIT, SUBMARINE_IMAGE_2_WIDTH, SUBMARINE_IMAGE_2_HEIGHT, x, y, 0);
}

bool SubmarineMedium::attack() {
    if(((clock() - start * 1.0) / CLOCKS_PER_SEC) > SUBMARINE_FREQUENCY_ATTACK_2) {
        start = clock();
        return true;
    }
    else return false;
}

void SubmarineMedium::draw_rectangle() {
    al_draw_rectangle(x,y,x+SUBMARINE_IMAGE_2_WIDTH,y+SUBMARINE_IMAGE_2_HEIGHT, color, 2)
}

/* 
    Submarine Advance
*/

SubmarineAdvance::SubmarineAdvance() {

    x = rand() % WIDTH;
    y = rand() % (HEIGHT - 2 * SEA_LEVEL) + 1.25 * SEA_LEVEL;
    width = IMAGE_SUBMARINE_3_WIDTH;
    height = IMAGE_SUBMARINE_3_HEIGHT;
        
    image = al_load_bitmap(SUBMARINE_IMAGE_3);
    speed = SUBMARINE_SPEED_3;
    al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));

    cx = x + SUBMARINE_IMAGE_2_WIDTH / 2; // + al_get_bitmap_width(image) / 2.;
    cy = y + SUBMARINE_IMAGE_2_HEIGHT / 2; // + al_get_bitmap_height(image) / 2.;
    rx = SUBMARINE_IMAGE_2_WIDTH / 2.;
    ry = SUBMARINE_IMAGE_2_HEIGHT / 2.;
}

SubmarineAdvance::~SubmarineAdvance() {
    al_destroy_bitmap(image);
}

void SubmarineAdvance::update() {
    if(dir == RIGHT) {
        x += speed;
        if(x > WIDTH - SUBMARINE_IMAGE_3_WIDTH) {
            x = WIDTH - SUBMARINE_IMAGE_3_WIDTH;
            dir = LEFT;
            curFrame = 8;
        }
    }
    else if (dir == LEFT) {
        x -= speed;
        if(x < 0) {
            x = 0;
            dir = RIGHT;
            curFrame = 0;
        }
    }
}

void SubmarineAdvance::draw() {
    if(dir == RIGHT) {
        if(++frameCount > 10) {
            (curFrame)++;
            if(curFrame > 7) curFrame = 0;
            frameCount = 0;
        }

    }
    else if(dir == LEFT) {
        if(++frameCount > 10) {
            curFrame++;
            if(curFrame > 15) curFrame = 8;
            frameCount = 0;
        }
    }
    al_draw_bitmap_region(image, 0, curFrame * SUBMARINE_IMAGE_3_SPLIT, SUBMARINE_IMAGE_3_WIDTH, SUBMARINE_IMAGE_3_HEIGHT, x, y, 0);
}

bool SubmarineAdvance::attack() {
    if(((clock() - start * 1.0) / CLOCKS_PER_SEC) > SUBMARINE_FREQUENCY_ATTACK_3) {
        start = clock();
        return true;
    }
    else return false;
}

void SubmarineAdvance::draw_rectangle() {
    al_draw_rectangle(x,y,x+SUBMARINE_IMAGE_3_WIDTH,y+SUBMARINE_IMAGE_3_HEIGHT, color, 2)
}