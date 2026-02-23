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

double Matrix::get(int i, int j){
    return data[i*cols+j];
}

void Matrix::set(int i, int j, double value){
    data[i*cols +j] = value;
}

int Matrix::get_height(){
    return rows;
}

int Matrix::get_width(){
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

Matrix Matrix::multiply(Matrix &other){
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