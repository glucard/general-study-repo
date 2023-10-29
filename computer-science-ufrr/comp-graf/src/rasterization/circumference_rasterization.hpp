#ifndef CIRCUMFERENCE_RASTERIZATION_H_GUARD
#define CIRCUMFERENCE_RASTERIZATION_H_GUARD

#include <iostream>
#include "../array/array.hpp"

namespace cr {
    class CircumferenceRasterization {
        private:
            void simmetric_dot(int** array, int x_center, int y_center, int x_k, int y_k, int value=1);
        public:
            void parametric_equation(int x, int y, int radius, arr::Array frame_buffer);
            void simmetric_incremental(int x, int y, int radius, arr::Array frame_buffer, int value=1, int teta=1);
            void bresenham(int x, int y, int radius, arr::Array frame_buffer, int value=1);
    };
}

#endif