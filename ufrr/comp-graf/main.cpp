#include <iostream>
#include "array/array.hpp"
#include "line_rasterization/line_rasterization.h"

#define ARRAY_ROWS 5
#define ARRAY_COLS 10

#define X1 3
#define Y1 0

#define X2 5
#define Y2 4

int main(int, char**){
    arr::Array frame_buffer(10, 10);
    lr::LineRasterization line_rasterization;

    line_rasterization.analytical(3, 1, 8, 5, frame_buffer);

    frame_buffer.print_array();

    std::cout << "Hello, from trab_2!\n";
}
