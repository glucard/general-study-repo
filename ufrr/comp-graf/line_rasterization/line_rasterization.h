#include <iostream>
#include "../array/array.hpp"

namespace lr{
    class LineRasterization {
        private:
        public:
            void analytical(int x1, int y1, int x2, int y2, arr::Array frame_buffer);
            void dda(int x1, int y1, int x2, int y2, int** array, int rows, int cols);
            void bresenham(int x1, int y1, int x2, int y2, int** array, int rows, int cols);
    };
}