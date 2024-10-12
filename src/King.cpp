#include <iostream>
#include <vector>
#include "Square.h"
#include "Pieces.h"
#include "King.h"
using namespace std;

King::King(int color)
{
    isWhite = color;
    isAlive = true;
    blackKing.loadFromFile("Textures/b_king.png");
    whiteKing.loadFromFile("Textures/w_king.png");
    piece.setTexture((color == 0) ? blackKing : whiteKing);
    x = (color == 0) ? 0 : 7;
    y = 4;
    occupied_value = 3;
    piece.setPosition(y * 100.0f + 50.f, x * 100.f + 50.f);
    piece.setOrigin(sf::Vector2f(piece.getTexture()->getSize().x / 2, piece.getTexture()->getSize().y / 2));
    piece.setScale(sf::Vector2f(0.375f, 0.375f));
}
vector<Square> King::getMoves(Square Cells[][8], int x, int y)
{
    possibleMoves.clear();
    int dx[] = {1, 1, 1, -1, -1, -1, 0, 0}; // all possible moves.
    int dy[] = {1, -1, 0, -1, 1, 0, -1, 1}; // all possible moves.
    for (int i = 0; i < 8; i++)
    {
        if (x + dx[i] > 7 || x + dx[i] < 0)
            continue;
        if (y + dy[i] > 7 || y + dy[i] < 0)
            continue;
        if (Cells[x + dx[i]][y + dy[i]].occupied_color == Cells[x][y].occupied_color)
            continue;
        possibleMoves.push_back(Cells[x + dx[i]][y + dy[i]]);
    }
    return possibleMoves;
}

bool King::isCheck(Square Cells[][8], int x, int y)
{
    int r = x + 1;
    // below four loops are to check if king is being attacked from all four dieections
    while (r < 8)
    {
        if (Cells[r][y].occupied_color == 0)
            continue;
        else if (Cells[r][y].occupied_color == Cells[x][y].occupied_color)
            break;
        else
        {
            if (Cells[r][y].occupied_value == 2 || Cells[r][y].occupied_value == 1)
                return true;
            else
                break;
        }
        r++;
    }
    r = x - 1;
    while (r >= 0)
    {
        if (Cells[r][y].occupied_color == 0)
            continue;
        else if (Cells[r][y].occupied_color == Cells[x][y].occupied_color)
            break;
        else
        {
            if (Cells[r][y].occupied_value == 2 || Cells[r][y].occupied_value == 1)
                return true;
            else
                break;
        }
        r--;
    }
    r = y + 1;
    while (r < 8)
    {
        if (Cells[x][r].occupied_color == 0)
            continue;
        else if (Cells[x][r].occupied_color == Cells[x][y].occupied_color)
            break;
        else
        {
            if (Cells[x][r].occupied_value == 2 || Cells[r][y].occupied_value == 1)
                return true;
            else
                break;
        }
        r++;
    }
    r = y - 1;
    while (r >= 0)
    {
        if (Cells[x][r].occupied_color == 0)
            continue;
        else if (Cells[x][r].occupied_color == Cells[x][y].occupied_color)
            break;
        else
        {
            if (Cells[x][r].occupied_value == 2 || Cells[r][y].occupied_value == 1)
                return true;
            else
                break;
        }
        r--;
    }
    // below four loops are to check if it is being attacked from diagonals
    int a = x + 1, b = y + 1;
    while (a < 8 && b < 8)
    {
        if (Cells[a][b].occupied_color == 0)
            continue;
        else if (Cells[a][b].occupied_color == Cells[x][y].occupied_color)
            break;
        else
        {
            if (Cells[a][b].occupied_value == 2 || Cells[a][b].occupied_value == -2)
                return true;
            else
                break;
        }
        a++;
        b++;
    }
    a = x + 1, b = y - 1;
    while (a < 8 && b >= 0)
    {
        if (Cells[a][b].occupied_color == 0)
            continue;
        else if (Cells[a][b].occupied_color == Cells[x][y].occupied_color)
            break;
        else
        {
            if (Cells[a][b].occupied_value == 2 || Cells[a][b].occupied_value == -2)
                return true;
            else
                break;
        }
        a++;
        b--;
    }
    a = x - 1, b = y + 1;
    while (a >= 0 && b < 8)
    {
        if (Cells[a][b].occupied_color == 0)
            continue;
        else if (Cells[a][b].occupied_color == Cells[x][y].occupied_color)
            break;
        else
        {
            if (Cells[a][b].occupied_value == 2 || Cells[a][b].occupied_value == -2)
                return true;
            else
                break;
        }
        a--;
        b++;
    }
    a = x - 1, b - y - 1;
    while (a >= 0 && b >= 0)
    {
        if (Cells[a][b].occupied_color == 0)
            continue;
        else if (Cells[a][b].occupied_color == Cells[x][y].occupied_color)
            break;
        else
        {
            if (Cells[a][b].occupied_value == 2 || Cells[a][b].occupied_value == -2)
                return true;
            else
                break;
        }
        a--;
        b--;
    }
    // loop to check if the king is being attacked by another king
    int dx[] = {0, 0, 1, 1, 1, -1, -1, -1};
    int dy[] = {1, -1, 1, -1, 0, 0, -1, 1};
    for (int i = 0; i < 8; i++)
    {
        if (Cells[x + dx[i]][y + dy[i]].occupied_color != Cells[x][y].occupied_color && Cells[x + dx[i]][y + dy[i]].occupied_value == 3)
            return true;
    }
    // loop to check if the king is being attacked by knight of opposite color
    int xa[] = {2, 2, -2, -2, 1, 1, -1, -1}; // all possible moves.
    int ya[] = {1, -1, 1, -1, 2, -2, 2, -2}; // all possible moves.
    for (int i = 0; i < 8; i++)
    {
        if (Cells[x + xa[i]][y + ya[i]].occupied_color != Cells[x][y].occupied_color && Cells[x + xa[i]][y + ya[i]].occupied_value == -1)
            return true;
    }
    // loops to check if the king is being attacked by the pawn of another color
    if (Cells[x][y].occupied_color == 1)
    {
        if (x < 8 && y > 0 && Cells[x + 1][y - 1].occupied_color == 0 && Cells[x + 1][y - 1].occupied_value == -3)
            return true;
        if (x < 8 && y < 8 && Cells[x + 1][y + 1].occupied_color == 0 && Cells[x + 1][y + 1].occupied_value == -3)
            return true;
    }
    else if (Cells[x][y].occupied_color == -1)
    {
        if (x > 0 && y > 0 && Cells[x - 1][y - 1].occupied_color == 0 && Cells[x - 1][y - 1].occupied_value == -3)
            return true;
        if (x > 0 && y < 8 && Cells[x - 1][y + 1].occupied_color == 0 && Cells[x - 1][y + 1].occupied_value == -3)
            return true;
    }
    return false;
}

bool King::isCheckmate(Square Cells[][8], int x, int y)
{
    if (!possibleMoves.size() && isCheck(Cells, x, y))
        return true;
    return false;
}

bool King::isStaleMate(Square Cells[][8], int x, int y)
{
    if (!possibleMoves.size() && !isCheck(Cells, x, y))
        return true;
    return false;
}
