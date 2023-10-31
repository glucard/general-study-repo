#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "array2d.hpp"
#include "LineRasterization.hpp"
#include <vector>

struct Point{
    int x;
    int y;
};
namespace rtz {
    
    class Polygon {
        private:
        public:
            Polygon(int _color);
            std::vector<Point> vertices;
            int color;
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