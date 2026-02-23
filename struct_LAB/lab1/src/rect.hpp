#ifndef RECTH
#define RETCH
class Rect{
    private:
        //int left, right, up, down;
        int x, y, width, height;
        void normalize();
    public:
        Rect();
        Rect(int l,int r,int u,int d);
        Rect(const Rect& other);
        ~Rect();

        int get_left();
        int get_right(); 
        int get_top(); 
        int get_bottom();

        void set_all(int l, int r, int u, int d);
        void inflate(int amount);
        void inflate(int dw, int dh);
        void inflate(int d_left, int d_right, int d_top, int d_bottom);

        void move(int dx, int dy);
        void move(int dx);

        int get_width();
        int get_height();
        int get_square();

        void set_width(int a);
        void set_height(int a);

};

Rect bounding_rect(Rect r1, Rect r2);
void print_rect(Rect &r);
#endif