#include "array2d.hpp"

arr::Array2d::Array2d(int cols, int rows, int initial_value){
    this->rows = rows;
    this->cols = cols;
    
    this->data = new int*[this->rows];

    for (int i = 0; i < this->rows; i++)
        this->data[i] = new int[this->cols];

    this->reset_array();
}

void arr::Array2d::print_array(){

    // print array inverted (to looks more like a cartesian map)
    int i, j;
    for (i = this->rows - 1; i >= 0; i--){
        for (j = 0; j < this->cols; j++)
            std::cout << this->data[i][j] << " ";
        std::cout << std::endl;
    }
}

void arr::Array2d::reset_array(int value){
    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->cols; j++) this->data[i][j] = 0;
}

void arr::Array2d::del_array(){
    for (int i = 0; i < this->rows; i++) {
        delete this->data[i];
    }
    delete this->data;
}
