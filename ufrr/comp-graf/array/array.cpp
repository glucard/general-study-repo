#include "array.hpp"

arr::Array::Array(int rows, int cols, int initial_value){
    this->rows = rows;
    this->cols = cols;
    
    this->data = new int*[this->rows];

    for (int i = 0; i < this->rows; i++)
        this->data[i] = new int[this->cols];

    this->reset_array();
}

void arr::Array::print_array(){

    // print array inverted (to looks more like a cartesian map)
    int i, j;
    for (i = this->rows - 1; i >= 0; i--){
        for (j = 0; j < this->cols; j++)
            std::cout << this->data[i][j] << " ";
        std::cout << std::endl;
    }
}

void arr::Array::reset_array(int value){
    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->cols; j++) this->data[i][j] = 0;
}

void arr::Array::del_array(){
    for (int i = 0; i < this->rows; i++) {
        delete this->data[i];
    }
    delete this->data;
}
