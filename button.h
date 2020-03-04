class Button {
public:
    int x;
    int y;

    int xl;
    int yl;
    int xr;
    int yr;

    string text;
    bool action = false;
    
    ALLEGRO_COLOR color = BLACK;
    ALLEGRO_FONT *font;

    Button(int, int, string);
    ~Button();

    void update(int, int);
    void call();
};

Button::Button(int x, int y, string text) {
    
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_mouse();
    
    this->x = x;
    this->y = y;
    this->text = text;
    this->font = al_load_font(FONT_STYLE, FONT_SIZE, 0);

    int n = text.length();
    this->xl = x-0.2*FONT_SIZE*n;
    this->yl = y;
    this->xr = x+0.2*FONT_SIZE*n;
    this->yr = y+FONT_SIZE*0.8;
}

Button::~Button() {
    al_destroy_font(this->font);
}

void Button::update(int mx, int my) {
    // change color when mouse inside 
    if(mx > this->xl && mx < this->xr && my > this->yl && my < this->yr) {
        this->color = GREEN;
        ALLEGRO_MOUSE_STATE state;
        al_get_mouse_state(&state);
        if(state.buttons & 1) {
            this->action = true;
        }
    }
    else {
        this->color = BLACK;
    }

    const char * text = (this->text).c_str();
    al_draw_text(this->font, this->color, this->x, this->y, ALLEGRO_ALIGN_CENTRE, text);
    //al_draw_rectangle(this->xl, this->yl, this->xr, this->yr, this->color, 2);
}





