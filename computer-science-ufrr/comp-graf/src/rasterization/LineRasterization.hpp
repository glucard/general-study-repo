#ifndef RASTERIZATION_HPP
#define RASTERIZATION_HPP

#include <iostream>
#include "array2d.hpp"
#include <math.h>

namespace rtz{
    class Line{
        private:
        public:
            void analytical(int x1, int y1, int x2, int y2, arr::Array2d frame_buffer, char value='@');
            void dda(int x1, int y1, int x2, int y2, arr::Array2d frame_buffer, char value='@');
            void bresenham(int x1, int y1, int x2, int y2, arr::Array2d frame_buffer, char value='@');
    };
}

#endif // RASTERIZATION_HPP