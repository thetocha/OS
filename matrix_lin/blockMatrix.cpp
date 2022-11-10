#include "blockMatrix.h"

pthread_mutex_t mutex;

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
    std::vector<pthread_t> vector_of_threads;
    int status_adr;
    pthread_mutex_init(&mutex, nullptr);
    for(int i = 0; i < matrix1.getSize(); ++i){
        for(int j=0; j < matrix2.getSize(); ++j){
            for(int k = 0; k < matrix1.getSize(); ++k){
                pthread_t thread;
                auto* params = new Params(matrix1, matrix2, result, i, j, k);
                pthread_create(&thread, NULL, multiplyBloks, params);
                vector_of_threads.push_back(thread);

            }
        }
    }

    for(auto& item : vector_of_threads){
        pthread_join(item, (void**) &status_adr);
    }

    pthread_mutex_destroy(&mutex);
}

void* BlockMatrix::multiplyBloks(void* params){
    pthread_mutex_lock(&mutex);
    auto* local_params = (Params*) params;
    Matrix block(local_params->result.getElement(local_params->i,local_params->j).getRowSize(),
                 local_params->result.getElement(local_params->i,local_params->j).getColSize());
    block = local_params->result.getElement(local_params->i,local_params->j) +
            local_params->matrix1.getElement(local_params->i,local_params->k) *
            local_params->matrix2.getElement(local_params->k,local_params->j);
    local_params->result.SetElement(local_params->i,local_params->j, block);
    pthread_mutex_unlock(&mutex);
    return nullptr;
}