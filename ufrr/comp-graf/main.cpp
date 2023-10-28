#include <iostream>
#include "array/array.hpp"
#include "line_rasterization/line_rasterization.h"
#include "circumference_rasterization/circumference_rasterization.hpp"

#define ARRAY_ROWS 5
#define ARRAY_COLS 10

#define X1 3
#define Y1 0

#define X2 5
#define Y2 4

int main(int, char**){
    arr::Array frame_buffer(30, 30);

    lr::LineRasterization line_rasterization;
    cr::CircumferenceRasterization circumference_rasterization;

    // line_rasterization.bresenham(3, 1, 8, 5, frame_buffer);
    circumference_rasterization.parametric_equation(15, 15, 5, frame_buffer);

    frame_buffer.print_array();

    std::cout << "Hello, from trab_2! 4\n";
}
