#include <iostream>
#include "Board.h"

BoardNode *head = nullptr;
BoardNode *bottomLeft = nullptr;

void populate();

void populateDark();

void populateLight();

BoardNode *createNode(Piece piece) {
    auto *newNode = new BoardNode();
    newNode->piece = piece;
    newNode->up = nullptr;
    newNode->down = nullptr;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

BoardNode* insertDown(Piece piece) {
    BoardNode *newNode = createNode(piece);
    if (head == nullptr)
        head = newNode;
    else {
        BoardNode *p = head;
        for (; p->down != nullptr; p = p->down);
        p->down = newNode;
        newNode->up = p;
    }
    bottomLeft = newNode;
    return newNode;
}

void insertRight(BoardNode *node, Piece piece) {
    BoardNode *newNode = createNode(piece);
    if (node == nullptr) {
        std::cout << "Node was nullptr" << std::endl;
        return;
    } else {
        BoardNode *p = node;
        for (; p->right != nullptr; p = p->right);
        p->right = newNode;
        newNode->left = p;
    }
}

void printBoard() {
    BoardNode *p1 = head;
    BoardNode *p2 = head;
    for (; p1 != nullptr; p1 = p1->down) {
        for (p2 = p1; p2 != nullptr; p2 = p2->right) {
            switch (p2->piece.pieceType) {
                case NONE:
                    std::cout << "-";
                    break;
                case PAWN:
                    std::cout << (p2->piece.light ? "\u2659" : "\u265F");
                    break;
                case BISHOP:
                    std::cout << (p2->piece.light ? "\u2657" : "\u265D");
                    break;
                case ROOK:
                    std::cout << (p2->piece.light ? "\u2656" : "\u265C");
                    break;
                case KNIGHT:
                    std::cout << (p2->piece.light ? "\u2658" : "\u265E");
                    break;
                case KING:
                    std::cout << (p2->piece.light ? "\u2654" : "\u265A");
                    break;
                case QUEEN:
                    std::cout << (p2->piece.light ? "\u2655" : "\u265B");
                    break;
            }
        }
        std::cout << std::endl;
    }
}

void initialise() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        BoardNode* node = insertDown(Piece{});
        for (int j = 0; j < BOARD_SIZE - 1; ++j) {
            insertRight(node, Piece{});
        }
    }
    connect();
    populate();
}

void populate() {
    populateDark();
    bottomLeft->piece = {true, ROOK};
    populateLight();
}

void populateDark() {
    BoardNode* p = head;
    p->piece = {!WHITE, ROOK};
    p = p->right;
    p->piece = {!WHITE, KNIGHT};
    p = p->right;
    p->piece = {!WHITE, BISHOP};
    p = p->right;
    p->piece = {!WHITE, QUEEN};
    p = p->right;
    p->piece = {!WHITE, KING};
    p = p->right;
    p->piece = {!WHITE, BISHOP};
    p = p->right;
    p->piece = {!WHITE, KNIGHT};
    p = p->right;
    p->piece = {!WHITE, ROOK};

    for (p=head->down; p != nullptr ; p=p->right) {
        p->piece = {!WHITE, PAWN};
    }
}

void populateLight() {
    BoardNode* p = head;
    p->piece = {WHITE, ROOK};
    p = p->right;
    p->piece = {WHITE, KNIGHT};
    p = p->right;
    p->piece = {WHITE, BISHOP};
    p = p->right;
    p->piece = {WHITE, QUEEN};
    p = p->right;
    p->piece = {WHITE, KING};
    p = p->right;
    p->piece = {WHITE, BISHOP};
    p = p->right;
    p->piece = {WHITE, KNIGHT};
    p = p->right;
    p->piece = {WHITE, ROOK};

    for (p=head->down; p != nullptr ; p=p->right) {
        p->piece = {WHITE, PAWN};
    }
}



void connect() {
    if (head != nullptr) {
        BoardNode* p1 = head;
        BoardNode* p2 = head;
        for (; p1->down != nullptr; p1 = p1->down) {
            for (p2 = p1; p2 != nullptr; p2 = p2->right) {
                if(p2->down == nullptr)
                {
                    p2->down = p2->left->down->right;
                    p2->left->down->right->up = p2;
                }
            }
        }
    } else {
        std::cout << "Head is nullptr, cannot connect" << std::endl;
    }
}

void findPossibleMoves() {

}

void move(Piece piece) {
//    BoardNode* p = head;
//    p = p->right->right->right->right->right->right->right;
//    p = p->down->down->down->down->down->down->down;
//    p = p->left->left->left->left->left->left->left;
//    p = p->right;
//    p = p->up->up->up->up->up->up->up;
//    p->piece = piece;
}