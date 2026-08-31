#include "Board.h"
#include <iostream>
#include <map>
#include <cctype>
#include <sstream>

Board::Board() {
    for( int i = 0; i < 64; i++) 
    squares[i] = 0;
    sideToMove = Piece::White;
    whiteCanCastleKingside = false;
    whiteCanCastleQueenside = false;
    blackCanCastleKingside = false;
    blackCanCastleQueenside = false;
    enPassantSquare = -1;
    halfmoveClock = 0;
    fullmoveNumber = 1;

}

void Board::loadFromFen(std::string fen){
    
    for( int i = 0; i < 64; i++) 
    squares[i] = 0;
    sideToMove = Piece::White;
    whiteCanCastleKingside = false;
    whiteCanCastleQueenside = false;
    blackCanCastleKingside = false;
    blackCanCastleQueenside = false;
    enPassantSquare = -1;
    halfmoveClock = 0;
    fullmoveNumber = 1;
    
    std::map<char, int> pieceTypeFromSymbol = {
        {'k', Piece::King}, {'p', Piece::Pawn}, {'n', Piece::Knight}, 
        {'b',Piece::Bishop}, {'r', Piece::Rook}, {'q', Piece::Queen}
    };

    std::istringstream fenLine(fen);
    std::string fenBoard;
    char sideToMoveLine;
    std::string castlingRights;
    std::string enPassantTargetSquare;
    int halfMoveClockLine = 0;
    int fullMoveNumLine = 0;


    if (!(fenLine >> fenBoard >> sideToMoveLine >> castlingRights >> enPassantTargetSquare >> halfMoveClockLine >> fullMoveNumLine)) {
        std::cerr << "Incomplete Fenn \n";
        return;
    }

    //First part of parse, field 1

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
                int pieceType = pieceTypeFromSymbol[tolower(symbol)];

                squares[rank * 8 + file] = pieceType | pieceColour;
                file++;

            }
        }
    }
    
    //Second part of parse, side to move
    sideToMove = (sideToMoveLine == 'w') ? Piece::White : Piece::Black;

    //Third part of parse, castling rights
    for(char symbol : castlingRights) {
        switch (symbol){
            case 'K':
                whiteCanCastleKingside = true;
                break;
            case 'Q':
                whiteCanCastleQueenside = true;
                break;
            case 'k':
                blackCanCastleKingside = true;
                break;
            case 'q':
                blackCanCastleQueenside = true;
        }
    }

    //Fourth part of parse, En passant target
    if (enPassantTargetSquare == "-" || enPassantTargetSquare.size() < 2) {
        enPassantSquare = -1;
    }
    else {
        int epFile = enPassantTargetSquare[0] - 'a';
        int epRank = enPassantTargetSquare[1] - '1';
        enPassantSquare = epRank * 8 + epFile;
    }

    //Last parse, halfmove/fullmove
    halfmoveClock = halfMoveClockLine;
    fullmoveNumber = fullMoveNumLine;
    
 }

namespace {
    // Same letters loadFromFen reads (KQRBNP), uppercase = white, lowercase = black.
    char pieceToChar(int piece){
        char letter;
        switch (Piece::typeOf(piece)) {
            case Piece::King:   letter = 'k'; break;
            case Piece::Queen:  letter = 'q'; break;
            case Piece::Rook:   letter = 'r'; break;
            case Piece::Bishop: letter = 'b'; break;
            case Piece::Knight: letter = 'n'; break;
            case Piece::Pawn:   letter = 'p'; break;
            default:            return '.';
        }
        return (Piece::colorOf(piece) == Piece::White) ? toupper(letter) : letter;
    }
}

void Board::display(){
        for(int rank = 7; rank>= 0; rank--){
            for (int file = 0; file <8; file++){
                std::cout << pieceToChar(squares[rank * 8 + file]) << " ";
            }
            std::cout << std::endl;
        }
        std::cout <<"a  b  c  d  e  f  g  h" << std::endl;
    }

std::string getSquareName(int squareIndex){
    char file = 'a' + (squareIndex % 8);
    char rank = '1' + (squareIndex / 8);
    return std::string (1, file) + std::string(1, rank);
};

void Board::makeMove(const Move& move){
    int movedPiece = squares[move.startSquare];
    int capturedPiece = squares[move.targetSquare];

    //Saves what's about to be destroyed
    Undo u;
    u.capturedPiece = capturedPiece;
    u.previousEnPassantSqaure = enPassantSquare;
    u.previousHalfmoveClock = halfmoveClock;
    u.previousFullmoveNumber = fullmoveNumber;
    history.push_back(u);

    //Moves the piece
    squares[move.targetSquare] = movedPiece;
    squares[move.startSquare] = Piece::Empty;

    //En passant sqaure: only a double pawn push sets one, everything else clears it
    if (move.flag == MoveFlag::DoublePawnPush){
        if(sideToMove == Piece::White){
            enPassantSquare = (sideToMove == Piece::White) ? move.targetSquare - 8: move.targetSquare + 8;
        }
        else{
            enPassantSquare = -1;
        }
    }

    //Half move clock
    if (Piece::typeOf(movedPiece) == Piece::Pawn || capturedPiece != Piece::Empty){
        halfmoveClock = 0;
    }
    else{
        halfmoveClock++;
    }

    //Fullmove number
    if(sideToMove == Piece::Black){
        fullmoveNumber++;
    }

    //Flip sideToMove.
    sideToMove = (sideToMove == Piece::White) ? Piece::Black : Piece::White;
}

void Board::unmakeMove(const Move& move){
    Undo u = history.back();
    history.pop_back();

    int movedPiece = squares[move.targetSquare];

    squares[move.startSquare] = movedPiece;
    squares[move.targetSquare] = u.capturedPiece;

    enPassantSquare = u.previousEnPassantSqaure;
    halfmoveClock = u.previousHalfmoveClock;
    fullmoveNumber = u.previousFullmoveNumber;

    sideToMove = (sideToMove == Piece::White) ? Piece::Black : Piece::White;

}