#ifndef __CURVE_HPP__
#define __CURVE_HPP__

#include <iostream>
#include <vector>
#include <cmath>

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
        void de_casteljau(int max_steps, arr::Array2d frame_buffer);
    };
} 


#endif