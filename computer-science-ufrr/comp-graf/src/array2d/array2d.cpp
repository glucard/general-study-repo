#include "array2d.hpp"

arr::Array2d::Array2d(int cols, int rows, char initial_value){
    this->rows = rows;
    this->cols = cols;
    
    this->data = new char*[this->rows];

    for (int i = 0; i < this->rows; i++)
        this->data[i] = new char[this->cols];

    this->reset_array(initial_value);
}

void arr::Array2d::print_array(bool reverse){

    // print array inverted (to looks more like a cartesian map)
    int i, j;

    if (reverse){
        for (i = this->rows - 1; i >= 0; i--){
            for (j = 0; j < this->cols; j++)
                std::cout << this->data[i][j] << " ";
            std::cout << std::endl;
        }
        return;
    }
    
    for (i = 0; i < this->rows; i++){
        for (j = 0; j < this->cols; j++)
            std::cout << this->data[i][j] << " ";
        std::cout << std::endl;
    }
}

void arr::Array2d::reset_array(char value){
    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->cols; j++) this->data[i][j] = value;
}

void arr::Array2d::del_array(){
    for (int i = 0; i < this->rows; i++) {
        delete this->data[i];
    }
    delete this->data;
}

// Display the array using OpenCV
void arr::Array2d::display_with_cv() {
    // Convert char** to cv::Mat
    cv::Mat img(rows, cols, CV_8U);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            img.at<uchar>(i, j) = (data[i][j] == ' ') ? 0 : 255;  // Map empty space to black and filled space to white
        }
    }

    // Show image
    cv::imshow("Array2D Display", img);
    cv::waitKey(0);  // Wait for a key press
}