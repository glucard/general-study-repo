#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

namespace arr {
    class Array {
        public:
            Array(int rows, int cols, int initial_value=0);
            int** data;
            int rows;
            int cols;
            void print_array();
            void reset_array(int value=0);
            void del_array();
    };
}

#endif