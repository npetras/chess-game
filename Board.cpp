#include <iostream>
#include <string>

#include "Board.h"

BoardNode *head = nullptr;
BoardNode *bottomLeft = nullptr;

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
    bool whiteSquare = WHITE;
    int currRow = 8;

    for (; p1 != nullptr; p1 = p1->down) {
        std::cout << currRow-- << " ";
        for (p2 = p1; p2 != nullptr; p2 = p2->right) {
            switch (p2->piece.pieceType) {
                case NONE:
                    std::cout << (whiteSquare ? "\u25A1" : "\u25A0");
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
            whiteSquare = !whiteSquare;
        }
        whiteSquare = !whiteSquare;
        std::cout << std::endl;
    }

    std::cout << "  ";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::cout << static_cast<char>(65 + i);
    }
    std::cout << std::endl;
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
    BoardNode* p = bottomLeft;
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

    p=bottomLeft;
    p=p->up->up->up->right->right->right;
    p->piece = {WHITE, ROOK};

    for (p=bottomLeft->up; p != nullptr ; p=p->right) {
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

BoardNode* findSquare(std::string boardPosition) {

    int row = (int)boardPosition[1] - 49;
    int col = (int)boardPosition[0] - 65;

    //    std::cout << row << std::endl;
    //    std::cout << col << std::endl;

    BoardNode* p = bottomLeft;

    for (int i = 0; i < row; ++i) {
        p = p->up;
    }
    for (int i = 0; i < col; ++i) {
        p = p->right;
    }

//    std::cout << p->piece.light << " " << pieceTypeToString(p->piece.pieceType) << std::endl;
    return p;
}

void findPossibleMoves() {

}

void move(BoardNode* pieceNode, BoardNode* squareToMoveTo) {
    bool moveValid;

    switch (pieceNode->piece.pieceType) {
        case NONE:
            break;
        case PAWN:
            break;
        case ROOK:
            moveValid = isRookMoveValid(pieceNode, squareToMoveTo);
//            std::cout << "RookMoveValid: " << moveValid << std::endl;
            break;
        case KNIGHT:
            break;
        case BISHOP:
            break;
        case KING:
            break;
        case QUEEN:
            break;
    }
    if (moveValid) {
        squareToMoveTo->piece = pieceNode->piece;
        pieceNode->piece = Piece{};
    }
}

bool isRookMoveValid(BoardNode* pieceNode, BoardNode* squareToMoveTo) {
    BoardNode* p = pieceNode->up;

    while(p != nullptr) {
        if (p->piece.pieceType != NONE && p->piece.light == pieceNode->piece.light) {
            break;
        }
        if (p == squareToMoveTo) {
            return true;
        }
        if (p->piece.pieceType != NONE && p->piece.light != pieceNode->piece.light) {
            break;
        }
        p = p->up;
    }

    p = pieceNode->right;
    while(p != nullptr) {
        if (p->piece.pieceType != NONE && p->piece.light == pieceNode->piece.light) {
            break;
        }
        if (p == squareToMoveTo) {
            return true;
        }
        if (p->piece.pieceType != NONE && p->piece.light != pieceNode->piece.light) {
            break;
        }
        p = p->right;
    }

    p = pieceNode->down;
    while(p != nullptr) {
        if (p->piece.pieceType != NONE && p->piece.light == pieceNode->piece.light) {
            break;
        }
        if (p == squareToMoveTo) {
            return true;
        }
        if (p->piece.pieceType != NONE && p->piece.light != pieceNode->piece.light) {
            break;
        }
        p = p->down;
    }

    p = pieceNode->left;
    while(p != nullptr) {
        if (p->piece.pieceType != NONE && p->piece.light == pieceNode->piece.light) {
            break;
        }
        if (p == squareToMoveTo) {
            return true;
        }
        if (p->piece.pieceType != NONE && p->piece.light != pieceNode->piece.light) {
            break;
        }
        p = p->left;
    }
    return false;
}

bool isKnightMoveValid(BoardNode* pieceNode, BoardNode* squareToMoveTo) {
    BoardNode* p =pieceNode;
    if(p->up != nullptr && p->up->up !=nullptr){
        if(p->up->up->right == squareToMoveTo &&(p->piece.pieceType != NONE && p->piece.light != pieceNode->piece.light))
            return true;
        if(p->up->up->left == squareToMoveTo &&(p->piece.pieceType != NONE && p->piece.light != pieceNode->piece.light))
            return true;
    }

    if(p->down != nullptr && p->down->down != nullptr){
        if(p->down->down->right == squareToMoveTo &&(p->piece.pieceType != NONE && p->piece.light != pieceNode->piece.light))
            return true;
        if(p->down->down->left == squareToMoveTo &&(p->piece.pieceType != NONE && p->piece.light != pieceNode->piece.light))
            return true;
    }
    if(p->left != nullptr && p->left->left != nullptr){
        if(p->left->left->up == squareToMoveTo &&(p->piece.pieceType != NONE && p->piece.light != pieceNode->piece.light))
            return true;
        if(p->left->left->down == squareToMoveTo &&(p->piece.pieceType != NONE && p->piece.light != pieceNode->piece.light))
            return true;
    }
    if(p->right != nullptr && p->right->right != nullptr){
        if(p->right->right->up == squareToMoveTo &&(p->piece.pieceType != NONE && p->piece.light != pieceNode->piece.light))
            return true;
        if(p->right->right->down == squareToMoveTo &&(p->piece.pieceType != NONE && p->piece.light != pieceNode->piece.light))
            return true;
    }

    return false;
}

bool isBishopMoveValid(BoardNode* pieceNode, BoardNode* squareToMoveTo) {
    BoardNode* p = pieceNode;

    if(p->up != nullptr && p->right != nullptr)
        p = pieceNode->up->right;

    while (p != nullptr) {
        if (p->piece.pieceType != NONE && p->piece.light == pieceNode->piece.light) {
            break;
        }
        if (p == squareToMoveTo) {
            return true;
        }
        if (p->piece.pieceType != NONE && p->piece.light != pieceNode->piece.light) {
            break;
        }
        if (p->up != nullptr && p->right != nullptr)
            p = pieceNode->up->right;
    }

    if (p->up != nullptr && p->left != nullptr)
         p = pieceNode->up->left;
    while (p != nullptr) {
        if (p->piece.pieceType != NONE && p->piece.light == pieceNode->piece.light) {
            break;
        }
        if (p == squareToMoveTo) {
            return true;
        }
        if (p->piece.pieceType != NONE && p->piece.light != pieceNode->piece.light) {
            break;
        }
        if (p->up != nullptr && p->left != nullptr)
            p = pieceNode->up->left;
    }

    if (p->down != nullptr && p->right != nullptr)
        p = pieceNode->down->right;
    while (p != nullptr) {
        if (p->piece.pieceType != NONE && p->piece.light == pieceNode->piece.light) {
            break;
        }
        if (p == squareToMoveTo) {
            return true;
        }
        if (p->piece.pieceType != NONE && p->piece.light != pieceNode->piece.light) {
            break;
        }
        if (p->down != nullptr && p->right != nullptr)
             p = pieceNode->down->right;
    }

    if (p->down != nullptr && p->left != nullptr)
         p = pieceNode->down->left;
    while (p != nullptr) {
        if (p->piece.pieceType != NONE && p->piece.light == pieceNode->piece.light) {
            break;
        }
        if (p == squareToMoveTo) {
            return true;
        }
        if (p->piece.pieceType != NONE && p->piece.light != pieceNode->piece.light) {
            break;
        }
        if (p->down != nullptr && p->left != nullptr)
             p = pieceNode->down->left;
    }
    return false;
}
