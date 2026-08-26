#include <iostream>
#include "MoveGenerator.h"
#include <vector>
#include <algorithm>

MoveGenerator::MoveGenerator(){
    PrecomputeMoveData();
}


void MoveGenerator::PrecomputeMoveData(){
    for (int file = 0; file < 8; file++){
        for(int rank = 0; rank < 8; rank++){

            //Calculates the 1D index from 0 to 63 from th 2D cords
            int squareIndex = rank * 8 + file;

            //Distance to the four main edges
            int numNorth = 7 - rank; 
            int numSouth = rank;
            int numWest = file;
            int numEast = 7 - file;

            //Store them in the array
            numSquaresToEdge[squareIndex][0] = numNorth;
            numSquaresToEdge[squareIndex][1] = numSouth;
            numSquaresToEdge[squareIndex][2] = numWest;
            numSquaresToEdge[squareIndex][3] = numEast;

            //Diagonals are combinations, ie North-West is just 
            //how far north and how far west you can go
            numSquaresToEdge[squareIndex][4] = std::min(numNorth, numWest);
            numSquaresToEdge[squareIndex][5] = std::min(numSouth, numEast);
            numSquaresToEdge[squareIndex][6] = std::min(numNorth, numEast);
            numSquaresToEdge[squareIndex][7] = std::min(numSouth, numWest);
         }
    }
}

std::vector<Move> MoveGenerator::GenerateMoves (Board& board){

    std::vector<Move> moves;

    for(int startSquare = 0; startSquare < 64; startSquare++){

        int piece = board.squares[startSquare];

        //Skips empty squares
        if (piece == Piece::Empty) 
        continue;

        if(isSlidingPiece(piece)){
            GenerateSlidingMoves(startSquare, piece, board, moves);
        }
    }
    return moves;
}

bool MoveGenerator::isSlidingPiece(int piece){
    int type;
    // 
    if (piece >= 16)// It's Black
    type = piece -16;
    else if(piece >=8)// It's White
    type = piece -8;
    else 
    type = piece; //It's Empty(0)

    return type == Piece::Rook || type == Piece::Bishop || type == Piece::Queen;
}

bool MoveGenerator::isFriendly(int myPiece, int otherPiece) {
    if (otherPiece == 0)
    return false;

    return (myPiece >=16) == (otherPiece >=16);
}

bool MoveGenerator::isEnemy(int myPiece, int otherPiece){
    if (otherPiece == 0)
    return false;

    return (myPiece >=16) != (otherPiece >=16);
}


void MoveGenerator::GenerateSlidingMoves(int startSquare, int piece, Board& board, std::vector<Move>& moves){

    int startDirIndex = (piece % 8 == Piece::Bishop) ? 4 : 0;
    int endDirIndex = (piece % 8 == Piece::Rook) ? 4 : 8;

    for(int directionIndex = startDirIndex; directionIndex < endDirIndex; directionIndex++ ){
        for(int n = 0; n < numSquaresToEdge[startSquare][directionIndex]; n++){

            //Finds the target square based on the direction
            int targetSquare = startSquare + directionOffsets[directionIndex] * (n + 1);
            int pieceOnTargetSquare = board.squares[targetSquare];

            //If it's blocked  by a friendly piece, stop looking 
            if (isFriendly(piece, pieceOnTargetSquare))
                break;
                
            moves.push_back(Move(startSquare, targetSquare));

            //If it's an enemy piece, we capture it and then stop looking
            if(isEnemy(piece, pieceOnTargetSquare)) 
                break;
        }
    }
}
