#ifndef BEZIER_CURVE_HPP
#define BEZIER_CURVE_HPP

#include <iostream>
#include <vector>

#include "array2d.hpp"
#include "Point.hpp"

namespace bzc
{
    class BezierCurve {
    private:
        std::vector<rtz::Point> points;
    public:
        void add_point(int x, int y);
        void parametric(int max_steps, arr::Array2d frame_buffer);
    };
} 


#endif