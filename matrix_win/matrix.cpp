#include "matrix.h"

#include <utility>

Matrix::Matrix(int row_size_, int col_size_){
    this->col_size = col_size_;
    this->row_size = row_size_;

    for(int i = 0; i < row_size; ++i){
        std::vector<int> row;
        for(int j = 0; j < col_size; ++j){
            row.push_back(0);
        }
        matrix.push_back(row);
    }
}

void Matrix::resize(int row_size_, int col_size_){
    this->col_size = col_size_;
    this->row_size = row_size_;

    for(int i = 0; i < row_size; ++i){
        std::vector<int> row;
        for(int j = 0; j < col_size; ++j){
            row.push_back(0);
        }
        matrix.push_back(row);
    }
}

Matrix::Matrix(std::vector<std::vector<int>> matrix_, int row_size_, int col_size_){
    this->row_size = row_size_;
    this->col_size = col_size_;
    this->matrix = std::move(matrix_);
}

void Matrix::fill(){
    for(int i = 0; i < row_size; ++i){
        for(int j = 0; j < col_size; ++j){
            matrix[i][j] = rand() % 9 + 1;
        }
    }
}

void Matrix::print(){
    for(int i = 0; i < row_size; ++i){
        for(int j = 0; j < col_size; ++j){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int Matrix::getElement(int i, int j){
    return matrix[i][j];
}

int Matrix::getRowSize() const{
    return  row_size;
}

int Matrix::getColSize() const{
    return col_size;
}

Matrix& Matrix::operator=(Matrix copy) {
    if (this == &copy)
        return *this;
    this->matrix = copy.matrix;
    this->row_size = copy.row_size;
    this->col_size = copy.col_size;
    return (*this);
}

Matrix operator+(Matrix copy1, Matrix copy2){
    std::vector<std::vector<int>> mtr;
    for(int i = 0; i < copy1.getRowSize(); ++i){
        std::vector<int> row;
        for(int j = 0; j < copy1.getColSize(); ++j){
            row.push_back(copy1.getElement(i,j) + copy2.getElement(i,j));
        }
        mtr.push_back(row);
    }

    Matrix res(mtr, copy1.getRowSize(), copy1.getColSize());
    return res;
}

Matrix operator*(Matrix copy1,Matrix copy2) {
    std::vector<std::vector<int>> res;
    for (int i = 0; i < copy1.getRowSize(); i++) {
        std::vector<int> row;
        for (int j = 0; j < copy2.getColSize(); j++) {
            int c_i_j = 0;
            for (int k = 0; k < copy1.getColSize(); k++) {
                c_i_j += copy1.getElement(i,k) * copy2.getElement(k,j);
            }
            row.push_back(c_i_j);
        }
        res.push_back(row);
    }
    Matrix matrix(res, copy1.getRowSize(), copy2.getColSize());
    return matrix;
}

Matrix Matrix::multiply(const Matrix& copy1, const Matrix& copy2){
    return copy1 * copy2;
}

std::vector<std::vector<Matrix>> Matrix::split(int block_size){
    std::vector<std::vector<Matrix>> res;
    for(int i = 0; i < this->getRowSize(); i += block_size){
        std::vector<Matrix> row_of_res;
        for(int j = 0; j < this->getColSize(); j += block_size){
            std::vector<std::vector<int>> blockOfMatrix;
            int k_i = i;
            int currentBlockSizeI = 0;
            int currentBlockSizeJ = 0;
            if (i + block_size > this->getRowSize()) {
                currentBlockSizeI =this->getRowSize() % block_size;
            }
            else {
                currentBlockSizeI = block_size;
            }
            while (k_i < i + currentBlockSizeI) {
                std::vector<int> row;
                int k_j = j;
                if (j + block_size > this->getColSize()) {
                    currentBlockSizeJ = this->getRowSize() % block_size;
                }
                else {
                    currentBlockSizeJ = block_size;
                }
                while (k_j < j + currentBlockSizeJ) {
                    row.push_back(this->getElement(k_i, k_j));
                    k_j++;
                }
                blockOfMatrix.push_back(row);
                k_i++;
            }
            Matrix matrix1(blockOfMatrix, blockOfMatrix.size(), blockOfMatrix[0].size());
            row_of_res.push_back(matrix1);
        }
        res.push_back(row_of_res);
    }
    return res;
}