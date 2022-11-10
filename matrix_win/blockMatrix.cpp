#include "blockMatrix.h"


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
    std::vector<HANDLE> vector_of_threads;
    CONST HANDLE my_mutex = CreateMutex(NULL, FALSE, NULL);
    for(int i = 0; i < matrix1.getSize(); ++i){
        for(int j=0; j < matrix2.getSize(); ++j){
            for(int k = 0; k < matrix1.getSize(); ++k){
                auto* params = new Params(matrix1, matrix2, std::ref(result), my_mutex,  i,j,k);
                HANDLE thread = CreateThread(NULL, 0,
                                             reinterpret_cast<LPTHREAD_START_ROUTINE>(&multiplyBloks),
                                             params, 0, NULL);
                vector_of_threads.push_back(thread);
                //std::thread thread(multiplyBloks, matrix1, matrix2, std::ref(result), i,j,k);
                //vector_of_threads.push_back(std::move(thread));
            }
        }
    }

    for(HANDLE thread : vector_of_threads){
        WaitForSingleObject(thread, INFINITE);
    }

    for(HANDLE thread : vector_of_threads){
        CloseHandle(thread);
    }

    CloseHandle(my_mutex);
}

DWORD WINAPI BlockMatrix::multiplyBloks(LPVOID lpParams){
    Params params = *((Params*)lpParams);
    CONST HANDLE mutex = params.mutex;
    WaitForSingleObject(mutex, INFINITE);
    Matrix block(params.result.getElement(params.i,params.j).getRowSize(),
                 params.result.getElement(params.i,params.j).getColSize());
    block = params.result.getElement(params.i,params.j) + params.matrix1.getElement(params.i,params.k) *
            params.matrix2.getElement(params.k,params.j);
    params.result.SetElement(params.i,params.j, block);
    ReleaseMutex(mutex);
    return 0;
}