#include "CircumferenceRasterization.hpp"

void rtz::Circumference::simmetric_dot(int** array, int x_center, int y_center, int x_k, int y_k, int value){
    array[y_center + (int)y_k][x_center + (int)x_k] = value;
    array[y_center + (int)y_k][x_center - (int)x_k] = value;
    array[y_center - (int)y_k][x_center + (int)x_k] = value;
    array[y_center - (int)y_k][x_center - (int)x_k] = value;
    
    array[x_center + (int)x_k][y_center + (int)y_k] = value;
    array[x_center + (int)x_k][y_center - (int)y_k] = value;
    array[x_center - (int)x_k][y_center + (int)y_k] = value;
    array[x_center - (int)x_k][y_center - (int)y_k] = value;
}

void rtz::Circumference::parametric_equation(int x_c, int y_c, int radius, arr::Array2d frame_buffer) {
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

void rtz::Circumference::simmetric_incremental(int x_center,int y_center, int radius, arr::Array2d frame_buffer, int value, int teta){
    int rows, cols;
    rows = frame_buffer.rows;
    cols = frame_buffer.cols;

    int** array = frame_buffer.data;

    float pi_180 = (float) PI / 180.f;

    float teta_radians, cos_teta, sin_teta;
    
    teta_radians = teta * pi_180;
    cos_teta = cosf(teta_radians);
    sin_teta = sinf(teta_radians);


    float vector_x, vector_y;

    vector_x = radius * cosf(teta_radians);
    vector_y = radius * sinf(teta_radians);

    int x, y, x_k, y_k;
    // int_limit = (360 / 8) * (45 / teta)

    for (int t = 2; t <= 45; t++) {
        x = x_center + (int)vector_x;
        y = y_center + (int)vector_y;

        x_k = (int)roundf(vector_x);
        y_k = (int)roundf(vector_y);

        this->simmetric_dot(array, x_center, y_center, x_k, y_k);

        vector_x = vector_x * cos_teta - vector_y * sin_teta;
        vector_y = vector_y * cos_teta + vector_x * sin_teta;
    }
}

void rtz::Circumference::bresenham(int x_center, int y_center,
 int radius, arr::Array2d frame_buffer, int value) {
    int rows, cols;
    rows = frame_buffer.rows;
    cols = frame_buffer.cols;
    int** array = frame_buffer.data;

    int x, y;

    x = 0;
    y = radius;

    int p = 1 - radius;

    while (x != y) {
        simmetric_dot(array, x_center, y_center, x, y);

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
    simmetric_dot(array, x_center, y_center, x, y);
}