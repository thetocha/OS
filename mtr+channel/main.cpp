#include <iostream>
#include "block_matrix.h"
#include "channel.h"


int main(){
    BufferedChannel<std::vector<int>> bufferedChannel(1000);

    int size = 4;
    int block_size = 2;

    Matrix matrix(size,size);
    matrix.fill();
    matrix.print();
    BlockMatrix blockMatrix(matrix.split(block_size));

    std::cout << std::endl;

    Matrix matrix1(size,size);
    matrix1.fill();
    matrix1.print();
    BlockMatrix blockMatrix1(matrix1.split(block_size));

    std::cout << std::endl;

    Matrix matrix2(size,size);
    matrix2.print();
    BlockMatrix blockMatrix2(matrix2.split(block_size));

    BlockMatrix::multiply(blockMatrix1, blockMatrix, blockMatrix);

    blockMatrix2.print();
    return 0;
}
