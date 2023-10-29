#include <iostream>
#include "array/array.hpp"
#include "rasterization/rasterization.hpp"
#include "fill/fill.hpp"

#define ARRAY_ROWS 5
#define ARRAY_COLS 10

#define X1 3
#define Y1 0

#define X2 5
#define Y2 4

int main(int, char**){
    arr::Array frame_buffer(21, 21);

    rtz::Line line_rasterization;
    rtz::Circumference circumference_rasterization;
    rtz::Fill fill;
    // line_rasterization.bresenham(3, 1, 8, 5, frame_buffer);
    line_rasterization.analytical(10,10,10,10, frame_buffer);
    circumference_rasterization.bresenham(10, 10, 7, frame_buffer);

    frame_buffer.print_array();

    fill.flood_fill(10, 9, frame_buffer, 2);
    
    frame_buffer.print_array();

    frame_buffer.del_array();

    std::cout << "Hello, from trab_2! 4\n";
}
