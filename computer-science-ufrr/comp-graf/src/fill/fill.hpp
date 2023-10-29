#ifndef FILL_HPP
#define FILL_HPP

#include "array.hpp"

namespace rtz {
    class Fill {
        private:
            void flood_fill_recursive(int x, int y, arr::Array frame_buffer, int seed_color, int new_color);
        public:
            void flood_fill(int x, int y, arr::Array frame_buffer, int new_color);
    };
}

#endif