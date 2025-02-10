#include "CircumferenceRasterization.hpp"

void rtz::Circumference::simmetric_dot(char** array, int x_center, int y_center, int x_k, int y_k, char value){
    array[y_center + (int)y_k][x_center + (int)x_k] = value;
    array[y_center + (int)y_k][x_center - (int)x_k] = value;
    array[y_center - (int)y_k][x_center + (int)x_k] = value;
    array[y_center - (int)y_k][x_center - (int)x_k] = value;
    
    array[y_center + (int)x_k][x_center + (int)y_k] = value;
    array[y_center + (int)x_k][x_center - (int)y_k] = value;
    array[y_center - (int)x_k][x_center + (int)y_k] = value;
    array[y_center - (int)x_k][x_center - (int)y_k] = value;
}

void rtz::Circumference::parametric_equation(int x_c, int y_c, int radius, arr::Array2d frame_buffer, char value) {
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
        frame_buffer.data[(int)round(y)][(int)round(x)] = value;
    }
}

void rtz::Circumference::simmetric_incremental(int x_center,int y_center, int radius, arr::Array2d frame_buffer, char value, int teta){
    int rows, cols;
    rows = frame_buffer.rows;
    cols = frame_buffer.cols;

    char** array = frame_buffer.data;

    float x = (float)radius;
    float y = 0;
    float teta0 = 1.f / radius;
    std::cout << teta0;
    float C = cosf(teta0);
    float S = sinf(teta0);
    int x_temp;
    while (y <= x) {
        simmetric_dot(array, x_center, y_center, (int)x, (int)y);
        x_temp = x;
        x = x * C - y * S;
        y = y * C + x_temp * S;
    }
    // simmetric_dot(array, x_center, y_center, x, y);
}

void rtz::Circumference::bresenham(int x_center, int y_center, int radius, arr::Array2d frame_buffer, char value) {
    int rows, cols;
    rows = frame_buffer.rows;
    cols = frame_buffer.cols;
    char** array = frame_buffer.data;

    int x, y;

    x = 0;
    y = radius;

    int p = 1 - radius;

    while (x <= y) {
        simmetric_dot(array, x_center, y_center, x, y, value=value);

        if (p >= 0) {
            y = y - 1;
            p = p + 2*(x - y) + 5;
            x = x + 1;
            continue;
        }

        // não altera y;
        p = p + 2*x +3;
        x = x + 1;
    }
    simmetric_dot(array, x_center, y_center, x, y, value=value);
}