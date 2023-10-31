#include "fill.hpp"

using namespace rtz;

void Fill::flood_fill_recursive(int x, int y, arr::Array2d frame_buffer, int seed_color, int new_color){
    int rows, cols, **array;
    rows = frame_buffer.rows;
    cols = frame_buffer.cols;
    array = frame_buffer.data;

    if (x > cols || x < 0 || y > rows || y < 0)
        return;

    if (array[y][x] == seed_color) {
        // array[y][x] == -1; // view effect
        array[y][x] = new_color;
        this->flood_fill_recursive(x+1, y, frame_buffer, seed_color, new_color);
        this->flood_fill_recursive(x-1, y, frame_buffer, seed_color, new_color);
        this->flood_fill_recursive(x, y+1, frame_buffer, seed_color, new_color);
        this->flood_fill_recursive(x, y-1, frame_buffer, seed_color, new_color);
    }
}

void Fill::flood_fill(int x, int y, arr::Array2d frame_buffer, int new_color){

    int rows, cols, **array;
    rows = frame_buffer.rows;
    cols = frame_buffer.cols;
    array = frame_buffer.data;
    
    if (x > cols || x < 0 || y > rows || y < 0) {
        throw std::invalid_argument("Flood_fill coordinates out of bound.");
        return;
    }

    int seed_color = array[y][x];

    this->flood_fill_recursive(x, y, frame_buffer, seed_color, new_color);
}

void Fill::geometric(int x_min, int y_min, int x_max, int y_max, arr::Array2d frame_buffer, int color) {
    // fiz cansado, refatorar depois !!!
    // fiz cansado, refatorar depois !!!
    int** array = frame_buffer.data;
    int rows = frame_buffer.rows;
    int cols = frame_buffer.cols;

    int x, y, x_min_pair;
    bool pair;
    for (y = y_min; y <= y_max; y++) {
        x = x_min;
        pair = false;
        while (x <= x_max) {
            if (array[y][x] == color) {
                if (pair) {
                    if (x_min_pair == x - 1){
                        x_min_pair = x;
                    } else {
                        pair = false;
                        for (; x_min_pair < x; x_min_pair++)
                            array[y][x_min_pair] = color;
                    }                    
                } else {
                    pair = true;
                    x_min_pair = x;
                }
            }
            x++;
        }
    }
}