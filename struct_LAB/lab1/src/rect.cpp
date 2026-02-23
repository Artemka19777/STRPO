#include "rect.hpp"
#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;
// void Rect::normalize() {
//     if (left > right) swap(left, right);
//     if (down > up) swap(down, up);
// }

Rect::Rect(int l, int r, int u,int d)//:left(l),right(r), up(u), down(d) 
{
    // normalize();
    //cout<< "Вызван конструктор с параметрами "<<this<<'\n';
    if (l > r) swap(l, r);
    if (d > u) swap(d, u);

    x = l;
    y = d;
    width = r - l;
    height = u - d;
}
Rect::Rect():x(0), y(0), width(0), height(0)//:left(0), right(0), up(0), down(0)
{   
    //cout<< "Вызван конструктор по умолчанию "<<this<<'\n';
};
Rect::~Rect(){
    //cout<<"Деструктор вызван "<<this<<'\n';
}
Rect::Rect(const Rect& other): x(other.x),y(other.y),
    width(other.width),
    height(other.height) //left(other.left), right(other.right), up(other.up), down(other.down)
{
    //cout<< "Вызван конструктор копирования "<<this<<'\n';
}
int Rect::get_left() { 
    //return left; 
    return x;
}
int Rect::get_right() { 
    //return right; 
    return x + width;
}
int Rect::get_top() {
    //return up;
    return y + height; 
}
int Rect::get_bottom() { 
    //return down;
    return y;
}
void Rect:: set_all(int l, int r, int u, int d){
    // left = l;
    // right = r;
    // up=u;
    // down=d;
    // normalize();
    if (l > r) swap(l, r);
    if (d > u) swap(d, u);

    x = l;
    y = d;
    width = r - l;
    height = u - d;
} 
void Rect::inflate(int amount){
    // left-=amount;
    // right+=amount;
    // up+=amount;
    // down-=amount;
    x -= amount;
    width += 2*amount;
    y -= amount;
    height += 2*amount;
}
void Rect::inflate(int d_left, int d_right, int d_top, int d_bottom){
    // left-= d_left;
    // right+= d_right;
    // up+= d_top;
    // down-= d_bottom;
    x -= d_left;
    width += d_left + d_right;
    y -= d_bottom;
    height += d_bottom + d_top;
}

void Rect::inflate(int dw, int dh){
    // left-= dw;
    // right+= dw;
    // up += dh;
    // down-= dh;
    x -= dw;
    width += 2*dw;
    y -= dh;
    height += 2*dh;

}

void Rect::move(int dx, int dy){
    // left +=x;
    // right += x;
    // up+= y;
    // down+=y;
    x += dx;
    y += dy;
}
void Rect::move(int dx){
    // left +=x;
    // right += x;
    x += dx;
}
Rect bounding_rect(Rect r1, Rect r2){
    int left = min(r1.get_left(), r2.get_left());
    int right = max(r1.get_right(), r2.get_right());
    int down = min(r1.get_bottom(), r2.get_bottom());
    int up = max(r1.get_top(), r2.get_top());
    return Rect(left,right,up,down);
}
void print_rect(Rect &r){
    cout<< "Rect: "<< r.get_left() << ", "<< r.get_right() << ", "<< r.get_top() << ", "
    << r.get_bottom() << '\n';
}
int Rect::get_width(){
    //return right-left;
    return width;
}
int Rect::get_height(){
    // return up-down;
    return height;
}
int Rect::get_square(){
    // return (right-left) * (up-down);
    return width * height;
}
void Rect::set_width(int a){
    // right=left+a;
    width=a;
}
void Rect::set_height(int a){
    // up=down+a;
    height=a;
}