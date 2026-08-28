#include "Board.h"
#include "MoveGenerator.h"
#include <iostream>

int main() {

    Board myBoard;
    MoveGenerator gen;

    std::string normalLayout = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

    myBoard.loadFromFen("8/8/4P1p1/8/5n2/8/8/8 w KQkq - 0 1");
    myBoard.display();

    std::vector<Move> moves = gen.GenerateMoves(myBoard);

    std::cout <<"\n";

    std::cout << "Total Moves found:" << moves.size() << "\n" ;

    for(const auto & move : moves){
        std::cout << getSquareName(move.startSquare) << getSquareName(move.targetSquare) << " ";
    }

    return 0;
}