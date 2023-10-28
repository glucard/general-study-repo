#ifndef CIRCUMFERENCE_RASTERIZATION_H_GUARD
#define CIRCUMFERENCE_RASTERIZATION_H_GUARD

#include <iostream>
#include "../array/array.hpp"

namespace cr {
    class CircumferenceRasterization {
        private:
        public:
            void parametric_equation(int x, int y, int radius, arr::Array frame_buffer);
            void simmetric_incremental(int x, int y, int radius, arr::Array frame_buffer, int value=1, int teta=1);
    };
}

#endif