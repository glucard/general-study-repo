#ifndef LINE_RASTERIZATION_HPP
#define LINE_RASTERIZATION_HPP

#include <iostream>
#include "array.hpp"

namespace lr{
    class LineRasterization {
        private:
        public:
            void analytical(int x1, int y1, int x2, int y2, arr::Array frame_buffer);
            void dda(int x1, int y1, int x2, int y2, arr::Array frame_buffer);
            void bresenham(int x1, int y1, int x2, int y2, arr::Array frame_buffer);
    };
}

#endif // LINE_RASTERIZATION_HPP