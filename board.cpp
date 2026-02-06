#include "board.h"
#include <iostream>
#include <map>
#include <cctype>

 void Board::loadFromFen(std::string fen){

    for(int i = 0; i <64; i++){
        squares[i] = Piece::Empty;
    }

    std::map<char, int> pieceTypeFromSybol = {
        {'k', Piece::King}, {'p', Piece::Pawn}, {'n', Piece::Knight}, 
        {'b',Piece::Bishop}, {'r', Piece::Rook}, {'q', Piece::Queen}
    };

    std::string fenBoard = fen.substr(0, fen.find(' '));
    int file = 0;
    int rank = 7;

    for(char symbol : fenBoard ) {

        if (symbol == '/') {
            file = 0;
            rank--;
        }
        else{
            if (isdigit(symbol)){
                file += (symbol - '0');
            }
            else{
                int pieceColour = (isupper(symbol)) ? Piece::White : Piece::Black;
                int pieceType = pieceTypeFromSybol[tolower(symbol)];

                squares[rank * 8 + file] = pieceType | pieceColour;
                file++;

            }

        }

    }

 }

void Board::display(){
        for(int rank = 7; rank>= 0; rank--){
            for (int file = 0; file <8; file++){
                std::cout << squares[rank * 8 + file] << " ";
            }
            std::cout << std::endl;
        }
    }