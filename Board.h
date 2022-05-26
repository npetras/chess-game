#include "Piece.h"

#ifndef CHESS_GAME_BOARD_H
#define CHESS_GAME_BOARD_H

#endif //CHESS_GAME_BOARD_H

#define BOARD_SIZE 8

struct BoardNode {
    Piece piece;
    BoardNode* up;
    BoardNode* down;
    BoardNode* right;
    BoardNode* left;
};

BoardNode* createNode(Piece piece);
void initialise();
BoardNode* insertDown(Piece piece);
void insertRight(BoardNode* node, Piece piece);
void printBoard();
void connect();
void move(Piece piece);