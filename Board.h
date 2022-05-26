//
// Created by Nicolas Petras on 25/05/2022.
//

#include "Piece.h"

#ifndef CHESS_GAME_BOARD_H
#define CHESS_GAME_BOARD_H

#endif //CHESS_GAME_BOARD_H

struct BoardNode {
    Piece piece;
    BoardNode* up;
    BoardNode* down;
    BoardNode* right;
    BoardNode* left;
};

BoardNode* createNode(Piece piece);
void initialise();