//
// Created by Nicolas Petras on 26/05/2022.
//

#include <string>
#include "PieceType.h"

std::string pieceTypeToString(PieceType pieceType) {
    std::string result;
    switch (pieceType) {
        case NONE:
            result = "";
            break;
        case PAWN:
            result = "Pawn";
            break;
        case ROOK:
            result = "Rook";
            break;
        case KNIGHT:
            result = "Knight";
            break;
        case BISHOP:
            result = "Bishop";
            break;
        case KING:
            result = "King";
            break;
        case QUEEN:
            result = "Queen";
            break;
    }
    return result;
}