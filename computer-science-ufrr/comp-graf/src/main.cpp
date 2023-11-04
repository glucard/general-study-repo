#include <iostream>
#include <stdio.h>
#include "array2d/array2d.hpp"
#include "rasterization/LineRasterization.hpp"
#include "rasterization/CircumferenceRasterization.hpp"
#include "fill/fill.hpp"
#include "geometric/Polygon.hpp"

#define LINE_COLS 30
#define LINE_ROWS 30
#define LINE_X1 0
#define LINE_Y1 0
#define LINE_X2 4
#define LINE_Y2 9

#define CIRCUMFERENCE_COLS 30
#define CIRCUMFERENCE_ROWS 30
#define CIRCUMFERENCE_X 7
#define CIRCUMFERENCE_Y 7
#define CIRCUMFERENCE_RADIUS 7

#define WINDOW_X 800
#define WINDOW_Y 600

void line_rasterization_demo(int x1, int y1, int x2, int y2){
    std::cout <<  "LINE RASTERIZATION DEMO" << std::endl;
    std::cout <<  "---------------------------------" << std::endl;

    arr::Array2d frame_buffer(LINE_COLS, LINE_ROWS);

    rtz::Line line_rasterization;

    line_rasterization.analytical(x1, y1, x2, y2, frame_buffer);
    std::cout <<  "Analytical" << std::endl;
    frame_buffer.print_array();
    frame_buffer.reset_array();
    std::cout <<  "---------------------------------" << std::endl;
    
    line_rasterization.dda(x1, y1, x2, y2, frame_buffer);
    std::cout <<  "DDA" << std::endl;
    frame_buffer.print_array();
    frame_buffer.reset_array();
    std::cout <<  "---------------------------------" << std::endl;
    
    line_rasterization.bresenham(x1, y1, x2, y2, frame_buffer);
    std::cout <<  "Bresenham" << std::endl;
    frame_buffer.print_array();
    frame_buffer.reset_array();
    std::cout <<  "---------------------------------" << std::endl;

    frame_buffer.del_array();
}


void circumference_rasterization_demo(int x_c, int y_c, int radius){
    std::cout <<  "CIRCUMFERENCE RASTERIZATION DEMO" << std::endl;
    std::cout <<  "---------------------------------" << std::endl;

    arr::Array2d frame_buffer(CIRCUMFERENCE_COLS, CIRCUMFERENCE_ROWS);

    rtz::Circumference circumference_rasterization;

    circumference_rasterization.parametric_equation(x_c, y_c, radius, frame_buffer);
    std::cout <<  "Parametric" << std::endl;
    frame_buffer.print_array();
    frame_buffer.reset_array();
    std::cout <<  "---------------------------------" << std::endl;

    circumference_rasterization.simmetric_incremental(x_c, y_c, radius, frame_buffer);
    std::cout <<  "Simmetric incremental" << std::endl;
    frame_buffer.print_array();
    frame_buffer.reset_array();
    std::cout <<  "---------------------------------" << std::endl;

    circumference_rasterization.bresenham(x_c, y_c, radius, frame_buffer);
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
    

    // line_rasterization_demo();
    // circumference_rasterization_demo();
    // fill_demo();


    int x, y;
    arr::Array2d frame_buffer(30, 30);
    rtz::Polygon polygon(1);
    rtz::Fill fill;

    int n;
    std::cout << "Choose task:" << std::endl;
    std::cout << "1 - line rasterization:" << std::endl;
    std::cout << "2 - circumference rasterization" << std::endl;
    std::cout << "3 - fill" << std::endl;
    std::cin >> n;


    switch(n){
        case 1:
            int x1, y1, x2, y2;
            std::cout << "x1 y1: ";
            scanf_s("%d%d", &x1, &y1);
            std::cout << "x2 y2: ";
            scanf_s("%d%d", &x2, &y2);
            line_rasterization_demo(x1, y1, x2, y2);
            break;
        case 2:

            int x_c, y_c, radius;
            std::cout << "x_center: ";
            scanf_s("%d", &x_c);
            std::cout << "y_center: ";
            scanf_s("%d", &y_c);
            std::cout << "radius: ";
            scanf_s("%d", &radius);
            circumference_rasterization_demo(x_c, y_c, radius);
            break;
        case 3:
            std::cout << "Create a polygon" << std::endl;
            while (polygon.vertices.size() < 3){
                std::cout << "-1 -1 to stop, must have at least 3 vertices" << std::endl;
                while(true){
                    std::cout << "add a vertice (x y): ";
                    scanf_s("%d%d", &x, &y);
                    if (x < 0 || y < 0){
                        break;
                    }
                    polygon.add_vertice(x, y);
                    if (polygon.vertices.size() >= 3) {
                        polygon.raster(frame_buffer);
                        frame_buffer.print_array();
                    }
                }
            }
            std::cout << "select method" << std::endl;
            std::cout << "1 - flood_fill" << std::endl;
            std::cout << "2 - geometric" << std::endl;
            std::cin >> n;
            switch(n){
                case 1:
                    std::cout << "select seed location " << std::endl;
                    std::cout << "x y: " << std::endl;
                    scanf_s("%d%d", &x, &y);
                    fill.flood_fill(x, y, frame_buffer, 1);
                    frame_buffer.print_array();
                    break;
                case 2:
                    fill.geometric(0, 0, 29, 29, frame_buffer, 1);
                    frame_buffer.print_array();
                    break;
                default:
                    std::cout << "command not found." << std::endl;
            }
            break;
        default:
            std::cout << "command not found." << std::endl;
    }
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
