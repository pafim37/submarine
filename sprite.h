class Sprite {
public:

    float rx, ry, rw, rh;

    float x;
    float y;
    float width;
    float height;

    ALLEGRO_BITMAP * image;

    virtual ~Sprite() {};
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void draw_rectangle() = 0;       
};
 
