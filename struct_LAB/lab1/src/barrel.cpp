#include "barrel.hpp"
#include <iostream>

using namespace std;

Barrel::Barrel(double v, double alc): size(v), alcohol(alc){}
double Barrel::get_conentrat(){
    return (alcohol/size)*100.0;
} 
void Barrel::pereliv(Barrel &other){
    double transfer = other.alcohol/other.size;//считаем какое количество спирта перельём
    alcohol+= transfer;
    other.alcohol -= transfer;
}