#ifndef MTR_CHANNEL_BLOCK_MATRIX_H
#define MTR_CHANNEL_BLOCK_MATRIX_H

#include "matrix.h"
#include "thread"
#include "channel.h"


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
    static void multiplyBloks(BlockMatrix matrix1, BlockMatrix matrix2, BlockMatrix& result, int i, int j, int k);
    Matrix getElement(int i, int j);
    void SetElement(int i, int j, Matrix copy);
    int getSize() const;

};

#endif //MTR_CHANNEL_BLOCK_MATRIX_H
