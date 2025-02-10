#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

namespace arr {
    class Array2d {
        public:
            Array2d(int rows, int cols, char initial_value=' ');
            char** data;
            int rows;
            int cols;
            void print_array(bool reverse=true);
            void reset_array(char value=' ');
            void del_array();
    };
}

#endif