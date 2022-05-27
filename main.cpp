/*
 * Created by Nicolas Petras, Billy Penton-Voak and Raymond Gorle
 */
#include <iostream>

#include "Board.h"

bool isPositionInputValid(std::string piecePosition) {
    bool isInvalid = true;

    if (piecePosition.length() != 2) {
        std::cout << "Wrong length" << std::endl;
    } else if (!isalpha(piecePosition[0]) || piecePosition[0] < 65 || piecePosition[0] > 72) {
        std::cout << "First character is not a valid letter" << std::endl;
    } else if (!isdigit(piecePosition[1])
               || piecePosition[1] < 49
               || piecePosition[1] > 56) {
        std::cout << static_cast<int>(piecePosition[1]);
        std::cout << "Second character is not a valid digit" << std::endl;
    } else {
        isInvalid = false;
    }
    return isInvalid;
}

int main() {

    bool won = false;
    bool whiteTurn = true;

    // printBoard();
    initialise();

    do {
        printBoard();
        // selecting a piece
        std::string piecePosition;

        // Check right format

        bool isInvalid = true;
        while (isInvalid) {
            std::cout << "Provide the piece position (e.g. 'A1'): ";
            std::getline(std::cin, piecePosition);
            isInvalid = isPositionInputValid(piecePosition);
        }

        BoardNode* pieceNode = findSquare(piecePosition);

        char yesNo;
        while (true) {
            std::cout << "Do you want to move " << pieceTypeToString(pieceNode->piece.pieceType) <<
                " at position " << piecePosition << " (Y/N): " << std::endl;
            std::cin >> yesNo;
            yesNo = (char)toupper(yesNo);
            if (yesNo == 'Y' || yesNo == 'N') {
                break;
            }
        }

        std::string newPosition;
        isInvalid = true;

        while (isInvalid) {
            std::cout << "Enter where you want the " << pieceTypeToString(pieceNode->piece.pieceType) << " "
                      << "at position " << piecePosition << " to be moved: ";
            getline(std::cin, newPosition);
            getline(std::cin, newPosition);
            isInvalid = isPositionInputValid(newPosition);
        }

        BoardNode* squareToMoveTo = findSquare(newPosition);
        if (move(pieceNode, squareToMoveTo, whiteTurn)) {
            whiteTurn = !whiteTurn;
        } else {
            std::cout << "You tried to move an opponent's piece\n";
        }

        std::cout << std::endl;
    } while(true);


    return 0;
}
