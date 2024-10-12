#ifndef SQUARE_H
#define SQUARE_H
#include <SFML/Graphics.hpp>

class Square
{
public:
    Square();
    int x, y;
    int occupied_value; // 0 if unoccupied, 3 if King, 2 if Queen, 1 if Rook, -1 if Knight, -2 if Bishop, -3 if Pawn
    int occupied_color; // 0 if unoccupied, 1 if white, -1 if black.
    int cell_color;     // 0 if black, 1 if white.
    sf::RectangleShape square;
};

#endif
