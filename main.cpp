/*
 * Created by Nicolas Petras, Billy Penton-Voak and Raymond Gorle
 */
#include <iostream>

#include "Board.h"

int main() {
    initialise();
    printBoard();
    Piece piece = Piece{true, PieceType::BISHOP};
    move(piece);
    std::cout << std::endl;
    printBoard();
    return 0;
}
