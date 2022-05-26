/*
 * Created by Nicolas Petras, Billy Penton-Voak and Raymond Gorle
 */
#include <iostream>

#include "Board.h"

int main() {

    bool won = false;
    bool whiteTurn = true;

    // printBoard();
    initialise();

    do {
        printBoard();
        // selecting a piece
        std::string piecePosition;
//        std::cout << "Provide the piece position (e.g. '1A'): ";
//        std::getline(std::cin, piecePosition);

        // TODO: check right format

        BoardNode* pieceNode = findPiece("A1");
        std::cout << "Do you want to move " << pieceNode->piece.pieceType << " at position " << piecePosition
            << std::endl;

        // moving a piece

//        move(pieceNode)

        std::cout << std::endl;
    } while(false);


    return 0;
}
