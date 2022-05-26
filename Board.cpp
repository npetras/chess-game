#include "Board.h"

BoardNode* head = nullptr;

BoardNode* createNode(Piece piece)
{
    auto* newNode = new BoardNode();
    newNode->piece = piece;
    newNode->up = nullptr;
    newNode->down = nullptr;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

//void insertEnd(int row, int col, Piece piece) {
//    BoardNode* newNode = createNode(row, col, piece);
//    if (head == nullptr)
//        head = newNode;
//    else
//    {
//        BoardNode* p = head;
//        for (; p->next != NULL; p = p->next);
//        p->next = newNode;
//        newNode->prev = p;
//    }
//}

void initialise() {

}

void findPossibleMoves() {

}

void move(int r1, int c1, int r2, int c2) {

}