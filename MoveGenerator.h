#include <iostream>
#include "Board.h"
#include "Move.h"
#include <vector>

#pragma once

class MoveGenerator {
    //64 squares 
    public: int numSquaresToEdge[64][8];
    public: int directionOffsets[8] = {8, -8, 1, -1, 7, -7, 9, -9};


    //The Constructer auto calls the math function
    public: MoveGenerator();
    public: void PrecomputeMoveData();
    public: std::vector<Move> GenerateMoves(Board& board);

    private: void GenerateSlidingMoves(int startSquare, int piece, Board& board, std::vector<Move>& moves);
    private: void GenerateKnightMoves(int startSquare, int piece, Board& board, std::vector<Move>& moves);
    private: void GenerateKingMoves(int startSquare, int piece, Board& board, std::vector<Move>& moves);
    private: void GeneratePawnMoves(int startSquare, int piece, Board& board, std::vector<Move>& moves);

    private: bool isSlidingPiece(int piece);
    private: bool isFriendly(int myPiece, int otherPiece);
    private: bool isEnemy(int myPiece, int otherPiece);
    

};


