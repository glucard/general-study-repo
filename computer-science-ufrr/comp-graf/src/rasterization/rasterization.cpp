#include "rasterization.hpp"

void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}

void rtz::Line::analytical(int x1, int y1, int x2, int y2, arr::Array frame_buffer){
    int** array = frame_buffer.data;
    int rows = frame_buffer.rows;
    int cols = frame_buffer.cols;

    if (x1 == x2){
        if (y2 < y1) 
            swap(&y1, &y2);

        for(int i = y1; i <= y2; i++)
            array[i][x1] = 1;
        return;
    }
    // find line equation
    float m = (float)(y2 - y1) / (x2 - x1);
    int b = (int)(y1 - m * x1);

    // x1 to x2 variation
    int y;
    for(int x = x1; x <= x2; x++){
        y = (int) (x * m + b);
        array[y][x] = 1;
        // cout << "(" << x << ", " << y << ") ";
    }
    return;
}

void rtz::Line::dda(int x1, int y1, int x2, int y2, arr::Array frame_buffer){
    int** array = frame_buffer.data;
    int rows = frame_buffer.rows;
    int cols = frame_buffer.cols;

    int d_x, d_y;
    d_x = x2 - x1;
    d_y = y2 - y1;

    float increment;

    if (abs(d_x) > abs(d_y)){
        float y;

        increment = (float) d_y / d_x;
        y = (float)y1;

        for(int x = x1; x <= x2; x++){
            array[(int)y][x] = 1;
            y += increment;
        }

        return;
    }

    increment = (float) d_x / d_y;
    float x = (float) x1;

    for(int y = y1; y <= y2; y++){
        array[y][(int)x] = 1;
        x += increment;
    }
}

void rtz::Line::bresenham(int x1, int y1, int x2, int y2, arr::Array frame_buffer) {
    int** array = frame_buffer.data;
    int rows = frame_buffer.rows;
    int cols = frame_buffer.cols;

    if (x2 < x1){
        swap(&x1, &x2);
        swap(&y1, &y2);
    }

    bool y1_bigger = false;

    if (y2 < y1) {
        y1 = -y1;
        y2 = -y2;
        y1_bigger = true;
    }

    int d_x, d_y, y, x;

    d_x = x2 - x1;
    d_y = y2 - y1;
    y = y1;
    x = x1;


    if (d_y > d_x) {
        int p = 2 * d_x - d_y;
        
        for (y = y1; y <= y2; y++) {
            
            y1_bigger ? array[-y][x] = 1 : array[y][x] = 1;

            if (p >= 0) {
                x += 1;
                p = p + 2 * (d_x - d_y);
                continue;
            }

            p = p + 2 * d_x;

        }
        return;
    }

    int p = 2 * d_y - d_x;
    
    for (int x = x1; x <= x2; x++) {
        
        y1_bigger ? array[-y][x] = 1 : array[y][x] = 1;

        if (p >= 0) {
            y += 1;
            p = p + 2 * (d_y - d_x);
            continue;
        }

        p = p + 2 * d_y;

    }
}


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

void rtz::Circumference::parametric_equation(int x_c, int y_c, int radius, arr::Array frame_buffer) {
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

void rtz::Circumference::simmetric_incremental(int x_center, int y_center, int radius, arr::Array frame_buffer, int value, int teta){
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

void rtz::Circumference::bresenham(int x_center, int y_center, int radius, arr::Array frame_buffer, int value) {
    int rows, cols;
    rows = frame_buffer.rows;
    cols = frame_buffer.cols;
    int** array = frame_buffer.data;

    int x, y;

    x = 0;
    y = radius;

    float p = 5.f / 4.f - radius;

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