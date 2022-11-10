#ifndef MATRIX_WIN_BLOCKMATRIX_H
#define MATRIX_WIN_BLOCKMATRIX_H

#include "matrix.h"
#include <windows.h>

class BlockMatrix{
private:
    std::vector<std::vector<Matrix>> block_matrix;
    int size;
    int block_size_r;
    int block_size_c;
public:
    BlockMatrix(int size_, int block_size_r_, int block_size_c_);
    explicit BlockMatrix(std::vector<std::vector<Matrix>> block_matrix_);
    void print();
    BlockMatrix& operator = (BlockMatrix copy);
    friend BlockMatrix operator + (BlockMatrix copy1, BlockMatrix copy2);
    static void multiply(BlockMatrix matrix1, BlockMatrix matrix2, BlockMatrix& result);
    static DWORD WINAPI multiplyBloks(LPVOID lpParams);
    Matrix getElement(int i, int j);
    void SetElement(int i, int j, Matrix copy);
    int getSize() const;

};

struct Params{
    BlockMatrix matrix1;
    BlockMatrix matrix2;
    BlockMatrix& result;
    CONST HANDLE mutex;
    int i, j, k;
    Params(BlockMatrix matrix1, BlockMatrix matrix2, BlockMatrix& result, CONST HANDLE mutex,  int i, int j, int k) : matrix1(matrix1),
                                                                                                 matrix2(matrix2),
                                                                                                 result(result),
                                                                                                 mutex(mutex),
                                                                                                 i(i),j(j),k(k){}

};


#endif //MATRIX_WIN_BLOCKMATRIX_H
