class Submarine : public Sprite {
    public:
        float speed;
        int frameCount = 0;
        int curFrame = 0;
        enum Direction {RIGHT, LEFT, UP, DOWN};
        int dir = RIGHT;
        bool live = true;
        bool active = true;
        clock_t start = clock();
        
        virtual ~Submarine() {};
    
        virtual bool attack() = 0;
        virtual void deactive() = 0;
        virtual void update() = 0;
        virtual void draw() = 0;
        virtual void draw_rectangle() = 0;
};


class SubmarinePrime : public Submarine {
public:
    SubmarinePrime();
    ~SubmarinePrime();

    bool attack();
    void deactive();
    void update();
    void draw();
    void draw_rectangle();
};

class SubmarineMedium : public Submarine {
public:
    SubmarineMedium();
    ~SubmarineMedium();

    bool attack();
    void deactive();
    void update();
    void draw();
    void draw_rectangle();  
};


class SubmarineAdvance : public Submarine {
public:
    SubmarineAdvance();
    ~SubmarineAdvance();

    void update();
    void deactive();
    void draw();
    bool attack();
    void draw_rectangle();
};

SubmarinePrime::SubmarinePrime() {
    x = rand() % WIDTH;
    y = rand() % (HEIGHT - 2 * SEA_LEVEL) + 1.25 * SEA_LEVEL;
    width = SUBMARINE_IMAGE_1_WIDTH;
    height = SUBMARINE_IMAGE_1_HEIGHT;
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
            if(active) curFrame = 8;
            else curFrame += 20; 
        }
    }
    else if (dir == LEFT) {
        x -= speed;
        if(x < 0) {
            x = 0;
            dir = RIGHT;
            if(active) curFrame = 0;
            else curFrame -= 20;
        }
    }
}

void SubmarinePrime::deactive() {
    active = false;
    if(dir == RIGHT) curFrame = 0;
    else curFrame = 20;
    frameCount = 0;
    image = al_load_bitmap(SUBMARINE_EXPLOSION_IMAGE_1);
    al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));

}

void SubmarinePrime::draw() {
    if(active) {
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
    else {
        if(dir == RIGHT) {
            if(++frameCount > 3) {
                if(curFrame > 20 && curFrame <= 39) curFrame = curFrame - 20;
                curFrame++;
                if(curFrame > 18) live = false;
                frameCount = 0;
            }
        }
        else if(dir == LEFT) {
            if(++frameCount > 3) {
                if(curFrame >= 0 && curFrame <= 19) curFrame = curFrame + 20;
                curFrame++;
                if(curFrame > 38) live = false;
                frameCount = 0;
            }
        }
        al_draw_bitmap_region(image, 0, curFrame * SUBMARINE_EXPLOSION_IMAGE_1_SPLIT, SUBMARINE_EXPLOSION_IMAGE_1_WIDTH, SUBMARINE_EXPLOSION_IMAGE_1_HEIGHT, x, y-20, 0);
    }
}

bool SubmarinePrime::attack() {
    if(((clock() - start * 1.0) / CLOCKS_PER_SEC) > SUBMARINE_FREQUENCY_ATTACK_1) {
        start = clock();
        return true;
    }
    else return false;
}

void SubmarinePrime::draw_rectangle() {
    al_draw_rectangle(x,y,x+SUBMARINE_IMAGE_1_WIDTH,y+SUBMARINE_IMAGE_1_HEIGHT, RED, 2);
}

/* 
    Submarine Medium
*/

SubmarineMedium::SubmarineMedium() {
    x = rand() % WIDTH;
    y = rand() % (HEIGHT - 2 * SEA_LEVEL) + 1.25 * SEA_LEVEL;
    width = SUBMARINE_IMAGE_2_WIDTH;
    height = SUBMARINE_IMAGE_2_HEIGHT;
        
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
            if(active) curFrame = 8;
            else curFrame += 20; 
        }
    }
    else if (dir == LEFT) {
        x -= speed;
        if(x < 0) {
            x = 0;
            dir = RIGHT;
            if(active) curFrame = 0;
            else curFrame -= 20; 
        }
    }   
}

void SubmarineMedium::deactive() {
    active = false;
    if(dir == RIGHT) curFrame = 0;
    else curFrame = 20;
    frameCount = 0;
    image = al_load_bitmap(SUBMARINE_EXPLOSION_IMAGE_2);
    al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));

}

void SubmarineMedium::draw()  {
    if(active) {
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
    else {
        if(dir == RIGHT) {
            if(++frameCount > 3) {
                if(curFrame > 20 && curFrame <= 39) curFrame = curFrame - 20;
                curFrame++;
                if(curFrame > 18) live = false;
                frameCount = 0;
            }
        }
        else if(dir == LEFT) {
            if(++frameCount > 3) {
                if(curFrame >= 0 && curFrame <= 19) curFrame = curFrame + 20;
                curFrame++;
                if(curFrame > 38) live = false;
                frameCount = 0;
            }
        }
        al_draw_bitmap_region(image, 0, curFrame * SUBMARINE_EXPLOSION_IMAGE_2_SPLIT, SUBMARINE_EXPLOSION_IMAGE_2_WIDTH, SUBMARINE_EXPLOSION_IMAGE_2_HEIGHT, x, y-20, 0);
    }
}

bool SubmarineMedium::attack() {
    if(((clock() - start * 1.0) / CLOCKS_PER_SEC) > SUBMARINE_FREQUENCY_ATTACK_2) {
        start = clock();
        return true;
    }
    else return false;
}

void SubmarineMedium::draw_rectangle() {
    al_draw_rectangle(x,y,x+SUBMARINE_IMAGE_2_WIDTH,y+SUBMARINE_IMAGE_2_HEIGHT, RED, 2);
}

/* 
    Submarine Advance
*/

SubmarineAdvance::SubmarineAdvance() {

    x = rand() % WIDTH;
    y = rand() % (HEIGHT - 2 * SEA_LEVEL) + 1.25 * SEA_LEVEL;
    width = SUBMARINE_IMAGE_3_WIDTH;
    height = SUBMARINE_IMAGE_3_HEIGHT;
        
    image = al_load_bitmap(SUBMARINE_IMAGE_3);
    speed = SUBMARINE_SPEED_3;
    al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));
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
            if(active) curFrame = 8;
            else curFrame += 20; 
        }
    }
    else if (dir == LEFT) {
        x -= speed;
        if(x < 0) {
            x = 0;
            dir = RIGHT;
            if(active) curFrame = 0;
            else curFrame -= 20; 
        }
    }
}

void SubmarineAdvance::deactive() {
    active = false;
    if(dir == RIGHT) curFrame = 0;
    else curFrame = 20;
    frameCount = 0;
    image = al_load_bitmap(SUBMARINE_EXPLOSION_IMAGE_3);
    al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));

}

void SubmarineAdvance::draw() {
    if(active) {
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
    else {
        if(dir == RIGHT) {
            if(++frameCount > 3) {
                if(curFrame > 20 && curFrame <= 39) curFrame = curFrame - 20;
                curFrame++;
                if(curFrame > 18) live = false;
                frameCount = 0;
            }
        }
        else if(dir == LEFT) {
            if(++frameCount > 3) {
                if(curFrame >= 0 && curFrame <= 19) curFrame = curFrame + 20;
                curFrame++;
                if(curFrame > 38) live = false;
                frameCount = 0;
            }
        }
        al_draw_bitmap_region(image, 0, curFrame * SUBMARINE_EXPLOSION_IMAGE_3_SPLIT, SUBMARINE_EXPLOSION_IMAGE_3_WIDTH, SUBMARINE_EXPLOSION_IMAGE_3_HEIGHT, x, y-20, 0);
    }
}

bool SubmarineAdvance::attack() {
    if(((clock() - start * 1.0) / CLOCKS_PER_SEC) > SUBMARINE_FREQUENCY_ATTACK_3) {
        start = clock();
        return true;
    }
    else return false;
}

void SubmarineAdvance::draw_rectangle() {
    al_draw_rectangle(x,y,x+SUBMARINE_IMAGE_3_WIDTH,y+SUBMARINE_IMAGE_3_HEIGHT, RED, 2);
}