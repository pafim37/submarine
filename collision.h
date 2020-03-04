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