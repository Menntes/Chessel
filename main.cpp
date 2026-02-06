#include "board.h"

int main() {

    Board myBoard;
    myBoard.loadFromFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    myBoard.display();
    return 0;
}