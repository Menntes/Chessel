#include <iostream>
#include "MoveGenerator.h"
#include <vector>
#include <algorithm>
#include <cmath>

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

        int type = piece % 8;
        if(isSlidingPiece(piece)){
            GenerateSlidingMoves(startSquare, piece, board, moves);
        }
        else if(type == Piece::Knight){
            GenerateKnightMoves(startSquare, piece, board, moves);
        }
        else if(type == Piece::King){
            GenerateKingMoves(startSquare, piece, board, moves);
        }
        else if(type == Piece::Pawn){
            GeneratePawnMoves(startSquare, piece, board, moves);
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

    return !((myPiece >=16) == (otherPiece >=16));
}

//Generates possible moves for sliding pieces: Rook, Bishop, and the Queen
void MoveGenerator::GenerateSlidingMoves(int startSquare, int piece, Board& board, std::vector<Move>& moves){

    int startDir = (piece % 8 == Piece::Bishop) ? 4 : 0;
    int endDir = (piece % 8 == Piece::Rook) ? 4 : 8;

    for(int directionIndex = startDir; directionIndex < endDir; directionIndex++ ){
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

//Generates possible moves for Knight
void MoveGenerator::GenerateKnightMoves(int startSquare, int piece, Board& board , std::vector<Move>& moves){
    int knightOffsets[] = {15, 17, 6, 10, -15, -17, -6, -10};
    int startFile = startSquare % 8;

     for (int offset : knightOffsets){
        int targetSquare = startSquare + offset;

        //is it on the board?
        if (targetSquare >= 0 && targetSquare <64){
            int targetFile = targetSquare % 8;
            int fileDistance = std::abs(targetFile - startFile);

            //Did it wrap around the board?
            if(fileDistance <= 2 ){
                int pieceOnTarget = board.squares[targetSquare];

                //Friendly piece check
                if (isEnemy(piece, pieceOnTarget)){
                    moves.push_back(Move(startSquare, targetSquare));
                }
            }
        } 
    }
}

//Generates possible moves for the king
void MoveGenerator::GenerateKingMoves(int startSquare, int piece, Board& board, std::vector<Move>&moves){
    int kingsOffset[] = {1, -1, 8, -8, 7, -7, 9, -9};
    int startFile = startSquare % 8;

    for(int offset : kingsOffset){
       int targetSquare = startSquare + offset;

       //Is it on the board?
       if (targetSquare > 0 && targetSquare < 64){
        int targetFile = targetSquare % 8;
        int fileDistance = std::abs(targetFile - startFile);

        //King can only move 1 file away
        if (fileDistance <=1){
            int pieceOnTarget = board.squares[targetSquare];

            //Friendly piece check
            if (isEnemy(piece, pieceOnTarget)){
                moves.push_back(Move(startSquare, targetSquare));
            }
        }
       }
    }
}

//Generates possible pawn moves
void MoveGenerator::GeneratePawnMoves(int startSquare, int piece, Board& board, std::vector<Move>& moves){
    bool isWhite = (piece >= 8 && piece < 16);
    int direction = isWhite ? 8 : -8;
    int startRank = startSquare / 8;
    int startFile = startSquare % 8;

    //Forward move (1 square)
    int oneSquareForward = startSquare + direction;
    if (board.squares[oneSquareForward] == Piece::Empty){
        moves.push_back(Move(startSquare,oneSquareForward));

        //Double push (Only from the starting rank!!)
        bool isStartingRank = (isWhite && startRank == 1) ||(!isWhite && startRank == 6);
        int twoSquaresForward = startSquare + (2*direction);
        if (isStartingRank && board.squares[twoSquaresForward] == Piece::Empty){
            moves.push_back(Move(startSquare, twoSquaresForward));
        }
    }
    
    //Captures
    int captureOffsets[] = {isWhite? 7:9,isWhite? 9:-7};
    for (int offset : captureOffsets){
        int targetSquare = startSquare + offset;

        //Check if target is on the board & not wrapping around
        if(targetSquare >= 0 && targetSquare < 64){
            int targetFile = targetSquare % 8;
            int fileDistance = std::abs(targetFile - startFile);
            if (fileDistance == 1){
                int pieceOnTarget = board.squares[targetSquare];

                if (isEnemy(piece, pieceOnTarget)){
                    moves.push_back(Move(startSquare, targetSquare));
                }
            }

        }
    }

}


