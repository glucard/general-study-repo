#ifndef DRAW_HPP
#define DRAW_HPP

#include "array2d.hpp"
#include "SFML/Graphics.hpp"

namespace rtz{
    class DrawWindow {
    private:
        /* sf::RenderWindow window; */
        int length;
        int height;
    public:
        DrawWindow(int length, int height);
        void square_pattern(int pos_x, int pos_y, int length, int height, int cols, int rows);
    };
}

#endif // DRAW_HPP