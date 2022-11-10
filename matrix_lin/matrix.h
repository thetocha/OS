#ifndef MATRIX_LIN_MATRIX_H
#define MATRIX_LIN_MATRIX_H

#include <vector>
#include <iostream>

class Matrix{
private:
    int row_size;
    int col_size;
    std::vector<std::vector<int>> matrix;
public:
    explicit Matrix(int row_size_, int col_size_);
    explicit Matrix(std::vector<std::vector<int>> matrix_, int row_size_,int  col_size_);
    void fill();
    void print();
    int getElement(int i, int j);
    int getRowSize() const;
    int getColSize() const;
    void resize(int row_size_, int col_size_);
    Matrix& operator = (Matrix copy);
    friend Matrix operator + (Matrix copy1, Matrix copy2);
    friend Matrix operator * (Matrix copy1, Matrix copy2);
    static Matrix multiply(const Matrix& matrix1,const Matrix& matrix2);
    std::vector<std::vector<Matrix>> split(int block_size);

};

#endif //MATRIX_LIN_MATRIX_H
