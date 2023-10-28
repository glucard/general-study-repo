#include "circumference_rasterization.hpp"
#include <math.h>

#define PI 3.14159265358979323846

void cr::CircumferenceRasterization::parametric_equation(int x_c, int y_c, int radius, arr::Array frame_buffer) {
    int rows, cols;
    rows = frame_buffer.rows;
    cols = frame_buffer.cols;

    if (x_c + radius >= cols || x_c - radius < 0 || y_c + radius >= rows || y_c - radius < 0){ // enchant it
        throw std::invalid_argument("Circumference out of bound.");
        return;
    }
    
    int t;
    float x, y, t_radians;
    float pi_180 = (float) PI / 180.f;

    for(t = 1; t <= 360; t++) {
        t_radians = (float) t * pi_180;
        x = x_c + radius * cosf(t_radians);
        y = y_c + radius * sinf(t_radians);
        frame_buffer.data[(int)round(y)][(int)round(x)] = 1;
    }
}