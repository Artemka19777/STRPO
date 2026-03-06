#include "matrix.hpp"
#include <iostream>
#include <cstdio>

using namespace std;
Matrix::Matrix(int n): rows(n), cols(n){
    data = new double[n * n];
    for(int i = 0; i<n*n; i++)
        data[i]=0.0;
    for(int i = 0; i<n; i++)
        data[n*i+i]=1.0;
}
Matrix::Matrix(int m, int n, double fill_value):rows(m), cols(n){
    data = new double[n * m];
    for(int i = 0; i<n*m; i++)
        data[i]=0.0;
}

Matrix::Matrix(const Matrix& other): rows(other.rows), cols(other.cols){
    data = new double[rows * cols];
    for (int i = 0; i < rows * cols; ++i)
        data[i] = other.data[i];
}
Matrix::~Matrix(){
    delete[] data;
}

double Matrix::get(int i, int j) const{
    return data[i*cols+j];
}

void Matrix::set(int i, int j, double value){
    data[i*cols +j] = value;
}

int Matrix::get_height() const{
    return rows;
}

int Matrix::get_width() const{
    return cols;
}

void Matrix::negate(){
    for(int i = 0; i<rows*cols; i++){
        data[i]=-data[i];
    }
}
void Matrix::add_in_place(Matrix &other){
    if (rows != other.rows || cols != other.cols)
        throw runtime_error("Не проходит по размеру");
    for(int i = 0;i<rows*cols;i++)
        data[i]+=other.data[i];
}

Matrix Matrix::multiply(const Matrix &other) const{
    if (cols != other.rows)
        throw runtime_error("Не проходит по размеру");

    Matrix result(rows, other.cols, 0.0);
    for(int i = 0; i<rows;i++){
        for (int j = 0; j<cols;j++){
            double s=0.0;
            for(int z = 0; z<cols; z++)
                s+=get(i,z) * other.get(z,j);
            
            result.set(i,j,s);
        }
    }
    return result;
}

Matrix& Matrix::operator=(const Matrix& other)//прописываем оператор, т.к. без него память освобождается несколько раз 
{
    if (this == &other)
        return *this;
    delete[] data;
    rows = other.rows;
    cols = other.cols;
    data = new double[rows * cols];
    for (int i = 0; i < rows * cols; ++i)
        data[i] = other.data[i];
    return *this;
}
//lab3
Matrix& Matrix::operator+=(const Matrix& other){
    if( rows != other.rows || cols != other.cols)
        throw runtime_error("Не проходит по размеру");
    for(int i=0; i<rows*cols;i++){
        data[i]+=other.data[i];
    }
    return *this;
}
Matrix& Matrix::operator-=(const Matrix& other){
    if( rows != other.rows || cols != other.cols)
        throw runtime_error("Не проходит по размеру");
    for(int i=0; i<rows*cols;i++){
        data[i]-=other.data[i];
    }
    return *this;
}
Matrix& Matrix::operator*=(const double d){
    for(int i=0;i<rows*cols;i++){
        data[i]*=d;
    }
    return *this;
} 
Matrix& Matrix::operator/=(const double d){
    if (d==0.0)
        throw runtime_error ("Нельзя поеделить");
    for(int i=0;i<rows*cols;i++){
        data[i]/=d;
    }
    return *this;
} 
Matrix Matrix::operator+(const Matrix& other)const {
    Matrix res(*this);
    res+=other;
    return res;
}
Matrix Matrix::operator-(const Matrix& other) const{
    Matrix res(*this);
    res-=other;
    return res;
}
Matrix Matrix::operator*(const Matrix& other) const{
    return this->multiply(other);
}
Matrix Matrix::operator*(const double d) const{
    Matrix res(*this);
    res*=d;
    return res;
}
Matrix Matrix::operator/(const double d) const{
    Matrix res(*this);
    res/=d;
    return res;
}
Matrix operator*(double d, const Matrix& m){
    return m * d;// грубо говоря, просто поменяли местами
}
Matrix operator-(const Matrix& m){
    Matrix res(m);
    res*= -1.0;
    return res;
}

//move
Matrix::Matrix(Matrix&& other)
    : data(other.data), rows(other.rows), cols(other.cols) {
    other.data = nullptr;
    other.rows = 0;
    other.cols = 0;
}
Matrix& Matrix::operator=(Matrix&& other){
    if (this != &other) {
        delete[] data; //нельзя через список инициализаторов, т.к. сначала стоит освободитт старые данные, чтобы не было утечек

        data = other.data;
        rows = other.rows;
        cols = other.cols;

        other.data = nullptr;
        other.rows = 0;
        other.cols = 0;
    }
    return *this;
}