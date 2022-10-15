#include "matrix.h"

Matrix::Matrix(std::vector<std::vector<int>> matrix){
    this->matrix = matrix;
    row_size = matrix.size();
    column_size = matrix[0].size();
}
Matrix::Matrix(Matrix &matrix1){
    this->matrix = matrix1.matrix;
}


Matrix::Matrix(int r_size, int c_size){
    this->row_size = r_size;
    this->column_size = c_size;
    for(int i = 0; i < row_size; ++i){
        std::vector<int> row(column_size, 0);
        matrix.push_back(row);
    }

}

std::vector<std::vector<int>> Matrix::multiple(Matrix matrix){
    if(this->matrix[0].size() != matrix.matrix.size()){
        throw new std::exception ("Can't multiple matrix");
    }


    std::vector<std::vector<int>> mult;


    for(int i = 0; i < this->matrix.size(); ++i){
        std::vector<int> row;
        for(int j = 0; j < matrix.matrix[0].size(); ++j){
            int element = 0;
            for(int k = 0; k < this->matrix.size(); ++k){
                element += this->matrix[i][k] * matrix.matrix[k][j];
            }
            row.push_back(element);
        }
        mult.push_back(row);
    }
    return mult;
}

int Matrix::get_Row_size(){
    return row_size;
}

int Matrix::get_Column_size(){
    return column_size;
}

int Matrix::get_Element(int i, int j){
    return matrix[i][j];
}

std::vector<std::vector<int>> Matrix::get_Mtr(){
    return this->matrix;
}

Matrix& Matrix::operator=(const Matrix& anotherMatrix) {
    if (this == &anotherMatrix)
        return *this;
    this->matrix = anotherMatrix.matrix;
    this->row_size = anotherMatrix.row_size;
    this->column_size = anotherMatrix.column_size;
    return (*this);
}

Matrix operator+(Matrix first_matrix, Matrix second_matrix){
    std::vector<std::vector<int>> result;
    for(int i = 0; i < first_matrix.get_Row_size(); ++i){
        for(int j = 0; j < first_matrix.get_Column_size(); ++j){
            result[i][j] = first_matrix.get_Element(i,j) + second_matrix.get_Element(i, j);
        }
    }
    Matrix Result(result);
    return Result;
}

Matrix& operator*(Matrix first, Matrix second){
    std::vector<std::vector<int>> res;
    res = first.multiple(second);
    Matrix* matrix = new Matrix(res);
    return (*matrix);
}

void  Matrix::fillMatrix(){
    for(int i = 0; i <row_size; ++i){
        for(int j = 0; j < column_size; ++j){
            matrix[i][j] = rand() % 9 + 1;
        }
    }
}

void Matrix::print(){
    for(int i = 0; i < row_size; ++i){
        for(int j = 0; j < column_size; ++j){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}



