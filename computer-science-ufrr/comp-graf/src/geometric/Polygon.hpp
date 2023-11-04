#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>

#include "array2d.hpp"
#include "LineRasterization.hpp"
#include "Point.hpp"

namespace rtz {
    
    class Polygon {
        private:
        public:
            std::vector<Point> vertices;
            int color;

            Polygon(int _color);
            void add_vertice(int x, int y);
            void raster(arr::Array2d frame_buffer);

            /* 
            Point min;
            Point max;
            void fill(int color);
            */
    };
}

#endif // POLYGON_HPP