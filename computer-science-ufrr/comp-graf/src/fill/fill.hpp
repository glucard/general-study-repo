#ifndef FILL_HPP
#define FILL_HPP

#include "array2d.hpp"

namespace rtz {
    class Fill {
        private:
            void flood_fill_recursive(int x, int y, arr::Array2d frame_buffer, char seed_color, char new_color);
        public:
            void flood_fill(int x, int y, arr::Array2d frame_buffer, char new_color='+');
            void geometric(int x_min, int y_min, int x_max, int y_max, arr::Array2d frame_buffer, char border_color, char color='+');
    };
}

#endif