#include <iostream>
#include "matrix.h"
#include "blockMatrix.h"
#include <chrono>

int main(){
    const int size = 4;
    Matrix matrix1(size,size);
    Matrix matrix2(size,size);
    Matrix result(size,size);

    matrix1.fill();
    matrix2.fill();

    for(int i = 1; i <= size; ++i){
        const int block_size = i;

        auto start = std::chrono::steady_clock::now();

        BlockMatrix blockMatrix1(matrix1.split(block_size));
        BlockMatrix blockMatrix2(matrix2.split(block_size));
        BlockMatrix blockResult(result.split(block_size));

        BlockMatrix::multiply(blockMatrix1, blockMatrix2, blockResult);

        auto end = std::chrono::steady_clock::now();

        long long time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "Size of block: " << block_size << " " << "Time required to multiple: " << time << std:: endl;
    }

    return 0;
}