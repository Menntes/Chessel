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

    // Type bits (King..Queen) and color bits (White/Black) never overlap,
    // so masking each out is safe even for Piece::Empty (0).
    inline int typeOf(int piece) { return piece & 7; }
    inline int colorOf(int piece) { return piece & (White | Black); }
}

class Board{
public:
    int squares[64];

    int sideToMove;
    bool whiteCanCastleKingside;
    bool whiteCanCastleQueenside;
    bool blackCanCastleKingside;
    bool blackCanCastleQueenside;
    int enPassantSquare;
    int halfmoveClock;
    int fullmoveNumber;
    Board();
    void loadFromFen(std::string fen);
    void display();

};

std::string getSquareName(int squareIndex);
