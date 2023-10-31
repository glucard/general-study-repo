#include <iostream>
#include "array2d/array2d.hpp"
#include "rasterization/LineRasterization.hpp"
#include "rasterization/CircumferenceRasterization.hpp"
#include "fill/fill.hpp"
#include "polygon/polygon.hpp"

#define ARRAY_ROWS 5
#define ARRAY_COLS 10

#define X1 3
#define Y1 0

#define X2 5
#define Y2 4

int main(int, char**){
    arr::Array2d frame_buffer(21, 21);

    //rtz::Line line_rasterization;
    //rtz::Circumference circumference_rasterization;
    rtz::Fill fill;
    
    rtz::Polygon polygon(1);
    polygon.add_vertice(0, 0);
    polygon.add_vertice(18, 12);
    polygon.add_vertice(20, 5);
    polygon.add_vertice(20, 5);
    
    polygon.raster(frame_buffer);
    frame_buffer.print_array();
    
    fill.geometric(0,0,20,20, frame_buffer, 1);
    frame_buffer.print_array();

    frame_buffer.del_array();

    std::cout << "Hello, from trab_2! 4\n";
}
