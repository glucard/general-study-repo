#include "LineRasterization.hpp"

void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}

void rtz::Line::analytical(int x1, int y1, int x2, int y2, arr::Array2d frame_buffer){
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

void rtz::Line::dda(int x1, int y1, int x2, int y2, arr::Array2d frame_buffer){
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

void rtz::Line::bresenham(int x1, int y1, int x2, int y2, arr::Array2d frame_buffer) {
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