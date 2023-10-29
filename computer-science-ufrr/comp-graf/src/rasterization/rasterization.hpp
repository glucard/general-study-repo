#ifndef RASTERIZATION_HPP
#define RASTERIZATION_HPP

#include <iostream>
#include "array.hpp"
#include <math.h>

#define PI 3.14159265358979323846

namespace rtz{
    class Line{
        private:
        public:
            void analytical(int x1, int y1, int x2, int y2, arr::Array frame_buffer);
            void dda(int x1, int y1, int x2, int y2, arr::Array frame_buffer);
            void bresenham(int x1, int y1, int x2, int y2, arr::Array frame_buffer);
    };
    
    class Circumference {
        private:
            void simmetric_dot(int** array, int x_center, int y_center, int x_k, int y_k, int value=1);
        public:
            void parametric_equation(int x, int y, int radius, arr::Array frame_buffer);
            void simmetric_incremental(int x, int y, int radius, arr::Array frame_buffer, int value=1, int teta=1);
            void bresenham(int x, int y, int radius, arr::Array frame_buffer, int value=1);
    };
}

#endif // RASTERIZATION_HPP