#pragma once
#include <string>

namespace Piece {

    const int Empty = 0;
    const int King = 1;
    const int Pawn = 2; 
    const int Knight = 3;
    const int Bishop = 4; 
    const int Rook = 5;
    const int Queen = 6;

    const int White = 8;
    const int Black = 16;
}

class Board{
public:
    int squares[64];
    Board();
    void loadFromFen(std::string fen);
    void display();

};

std::string getSquareName(int squareIndex);