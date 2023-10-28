#ifndef CIRCUMFERENCE_RASTERIZATION_H_GUARD
#define CIRCUMFERENCE_RASTERIZATION_H_GUARD

#include <iostream>
#include "../array/array.hpp"

namespace cr {
    class CircumferenceRasterization {
        private:
        public:
            void parametric_equation(int x, int y, int radius, arr::Array frame_buffer);
    };
}

#endif