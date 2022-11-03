#include "block_matrix.h"



BlockMatrix::BlockMatrix(int size_, int block_size_r_, int block_size_c_){
    this->size = size_;
    this->block_size_r = block_size_r_;
    this->block_size_c = block_size_c_;
    for(int i = 0; i < size; ++i){
        std::vector<Matrix> row;
        for(int j = 0; j < size; j++){
            Matrix matrix(block_size_r, block_size_c);
            row.push_back(matrix);
        }
        block_matrix.push_back(row);
    }
}
BlockMatrix::BlockMatrix(std::vector<std::vector<Matrix>> block_matrix_){
    this->block_matrix = block_matrix_;
    this->size = block_matrix.size();
    this->block_size_r = block_matrix[0].size();
    this->block_size_c = block_matrix[0][0].getColSize();
}

int BlockMatrix::getSize() const{
    return this->size;
}

Matrix BlockMatrix::getElement(int i, int j){
    return block_matrix[i][j];
}

void BlockMatrix::SetElement(int i, int j, Matrix copy){
    block_matrix[i][j] = copy;
}

void BlockMatrix::print(){
    for(int i = 0; i < this->getSize(); ++i){
        for(int j = 0; j < this->size; ++j){
            this->getElement(i,j).print();
            std::cout << '\n';
        }
        std::cout << "--------" << std::endl;
    }
}

BlockMatrix& BlockMatrix::operator = (BlockMatrix copy){
    this->block_matrix = copy.block_matrix;
    this->size = copy.size;
    this->block_size_c = copy.block_size_c;
    this->block_size_r = copy.block_size_r;
    return *this;
}

BlockMatrix operator + (BlockMatrix copy1, BlockMatrix copy2){
    std::vector<std::vector<Matrix>> res;
    for(int i = 0; i < copy1.getSize(); ++i){
        std::vector<Matrix> row;
        for(int j=0; j < copy2.getSize(); ++j){
            Matrix element(copy1.getElement(i,j).getRowSize(),copy1.getElement(i,j).getColSize());
            element = copy1.getElement(i,j) + copy2.getElement(i, j);
            row.push_back(element);
        }
        res.push_back(row);
    }
    BlockMatrix result(res);
    return result;
}


void BlockMatrix::multiply(BlockMatrix matrix1, BlockMatrix matrix2, BlockMatrix& result){
    std::vector<std::thread> vector_of_threads;
    BufferedChannel<int *> channel(3000);
    std::thread thread([&channel, &matrix2, &matrix1](){
        for(int i=0; i < matrix1.getSize(); ++i){
            for(int j=0; j < matrix2.getSize(); ++j){
                for(int k=0; k < matrix1.getSize(); ++k){
                    int *block_coordinates=new int[3]{i, j, k};
                    channel.Send(block_coordinates);
//                std::thread thread(multiplyBloks, matrix1, matrix2, std::ref(result), i,j,k);
//                vector_of_threads.push_back(std::move(thread));
                }
            }
        }
        channel.Close();
    });

    thread.join();

    std::vector<std::thread> vector_of_waiting;
    for(int i = 0; i < 7; ++i){
        vector_of_waiting.emplace_back([&](){
            std::pair<int*, bool> currentBlock = channel.Recv();
            bool channelState = currentBlock.second;
            while(!channelState){
                multiplyBloks(matrix1, matrix2, result, currentBlock.first[0], currentBlock.first[1],
                              currentBlock.first[2]);
                currentBlock = channel.Recv();
                channelState = currentBlock.second;
            }
        });
    }

    for(auto& thr : vector_of_waiting){
        thr.join();
    }

}


void BlockMatrix::multiplyBloks(BlockMatrix matrix1, BlockMatrix matrix2, BlockMatrix &result, int i, int j, int k){
    Matrix block(result.getElement(i,j).getRowSize(),result.getElement(i,j).getColSize());
    block = result.getElement(i,j) + matrix1.getElement(i,k) * matrix2.getElement(k,j);
    result.SetElement(i,j, block);
}