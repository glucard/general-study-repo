#include <iostream>
#include "array2d/array2d.hpp"
#include "rasterization/LineRasterization.hpp"
#include "rasterization/CircumferenceRasterization.hpp"
#include "fill/fill.hpp"
#include "polygon/polygon.hpp"

#define LINE_COLS 5
#define LINE_ROWS 10
#define LINE_X1 0
#define LINE_Y1 0
#define LINE_X2 4
#define LINE_Y2 9

#define CIRCUMFERENCE_COLS 15
#define CIRCUMFERENCE_ROWS 15
#define CIRCUMFERENCE_X 7
#define CIRCUMFERENCE_Y 7
#define CIRCUMFERENCE_RADIUS 7

#define WINDOW_X 800
#define WINDOW_Y 600

void line_rasterization_demo(){
    std::cout <<  "LINE RASTERIZATION DEMO" << std::endl;
    std::cout <<  "---------------------------------" << std::endl;

    arr::Array2d frame_buffer(LINE_COLS, LINE_ROWS);

    rtz::Line line_rasterization;

    line_rasterization.analytical(LINE_X1, LINE_Y1, LINE_X2, LINE_Y2, frame_buffer);
    std::cout <<  "Analytical" << std::endl;
    frame_buffer.print_array();
    frame_buffer.reset_array();
    std::cout <<  "---------------------------------" << std::endl;
    
    line_rasterization.dda(LINE_X1, LINE_Y1, LINE_X2, LINE_Y2, frame_buffer);
    std::cout <<  "DDA" << std::endl;
    frame_buffer.print_array();
    frame_buffer.reset_array();
    std::cout <<  "---------------------------------" << std::endl;
    
    line_rasterization.bresenham(LINE_X1, LINE_Y1, LINE_X2, LINE_Y2, frame_buffer);
    std::cout <<  "Bresenham" << std::endl;
    frame_buffer.print_array();
    frame_buffer.reset_array();
    std::cout <<  "---------------------------------" << std::endl;

    frame_buffer.del_array();
}


void circumference_rasterization_demo(){
    std::cout <<  "CIRCUMFERENCE RASTERIZATION DEMO" << std::endl;
    std::cout <<  "---------------------------------" << std::endl;

    arr::Array2d frame_buffer(CIRCUMFERENCE_COLS, CIRCUMFERENCE_ROWS);

    rtz::Circumference circumference_rasterization;

    circumference_rasterization.parametric_equation(CIRCUMFERENCE_X, CIRCUMFERENCE_Y, CIRCUMFERENCE_RADIUS, frame_buffer);
    std::cout <<  "Parametric" << std::endl;
    frame_buffer.print_array();
    frame_buffer.reset_array();
    std::cout <<  "---------------------------------" << std::endl;

    circumference_rasterization.simmetric_incremental(CIRCUMFERENCE_X, CIRCUMFERENCE_Y, CIRCUMFERENCE_RADIUS, frame_buffer);
    std::cout <<  "Simmetric incremental" << std::endl;
    frame_buffer.print_array();
    frame_buffer.reset_array();
    std::cout <<  "---------------------------------" << std::endl;

    circumference_rasterization.bresenham(CIRCUMFERENCE_X, CIRCUMFERENCE_Y, CIRCUMFERENCE_RADIUS, frame_buffer);
    std::cout <<  "Bresenham" << std::endl;
    frame_buffer.print_array();
    frame_buffer.reset_array();
    std::cout <<  "---------------------------------" << std::endl;
    
    frame_buffer.del_array();
}


void fill_demo(){
    std::cout <<  "FILL DEMO" << std::endl;
    std::cout <<  "---------------------------------" << std::endl;

    arr::Array2d frame_buffer(50, 50);

    rtz::Fill fill;
    rtz::Polygon polygon(1);

    polygon.add_vertice(3,47);
    polygon.add_vertice(16,29);
    polygon.add_vertice(4,21);
    polygon.add_vertice(22,21);
    polygon.add_vertice(27,9);
    polygon.add_vertice(35,21);
    polygon.add_vertice(46,22);
    polygon.add_vertice(36,27);
    polygon.add_vertice(47,47);
    polygon.add_vertice(26,33);


    polygon.raster(frame_buffer);
    frame_buffer.print_array(false);

    fill.flood_fill(25, 25, frame_buffer, 1);
    std::cout <<  "FLOOD FILL" << std::endl;
    frame_buffer.print_array(false);
    frame_buffer.reset_array();
    std::cout <<  "---------------------------------" << std::endl;
    

    polygon.raster(frame_buffer);
    
    fill.geometric(0,0, 49, 49, frame_buffer, 1);
    std::cout <<  "GEOMETRIC FILL" << std::endl;
    frame_buffer.print_array(false);
    frame_buffer.reset_array();
    std::cout <<  "---------------------------------" << std::endl;
    
    frame_buffer.del_array();
}


int main(int, char**){

    line_rasterization_demo();
    circumference_rasterization_demo();
    fill_demo();

    /* 
    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "comp-graf");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    std::cout << "Hello, from trab_2! 4\n";
    */

    return 0;
}
