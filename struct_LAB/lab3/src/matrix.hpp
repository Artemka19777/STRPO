#ifndef MATRIX_H
#define MATRIX_H
class Matrix{
    private: 
        int rows;
        int cols;
        double* data;
    public:
        Matrix(int n);
        Matrix(int m, int n, double fill_value = 0);
        Matrix(const Matrix& other);
        Matrix& operator=(const Matrix& other);
        Matrix& operator+=(const Matrix& other);
        Matrix& operator-=(const Matrix& other);
        Matrix& operator*=(const double d);
        Matrix& operator/=(const double d);
        Matrix operator+(const Matrix& other)const;
        Matrix operator-(const Matrix& other)const;
        Matrix operator*(const Matrix& other) const;
        Matrix operator*(const double d)const;
        Matrix operator/(const double d)const;
        
        ~Matrix();
        double get(int i, int j) const;
        void set(int i, int j, double value);
        int get_height()const;
        int get_width()const;
        void negate();
        void add_in_place(Matrix &other);
        Matrix multiply(const Matrix &other) const;

        Matrix(Matrix&& other);
        Matrix& operator=(Matrix&& other);
};

Matrix operator*(double d, const Matrix& m);
Matrix operator-(const Matrix& m);//Это можно было сделать внутри класса
#endif