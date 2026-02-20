#ifndef BARREL
#define BARREL
class Barrel{
    private:
        double size;
        double alcohol; 
    public:
        Barrel(double v, double alc);
        double get_conentrat();
        void pereliv(Barrel &other);
};
#endif