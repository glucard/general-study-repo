#ifndef CIRCUMFERENCE_RASTERIZATION_HPP
#define CIRCUMFERENCE_RASTERIZATION_HPP

#include <iostream>
#include "array.hpp"
#include <math.h>

#define PI 3.14159265358979323846

namespace rtz {
    class Circumference {
        private:
            void simmetric_dot(int** array, int x_center, int y_center, int x_k, int y_k, int value=1);
        public:
            void parametric_equation(int x, int y, int radius, arr::Array frame_buffer);
            void simmetric_incremental(int x, int y, int radius, arr::Array frame_buffer, int value=1, int teta=1);
            void bresenham(int x, int y, int radius, arr::Array frame_buffer, int value=1);
    };
}

#endif // CIRCUMFERENCE_RASTERIZATION_HPP