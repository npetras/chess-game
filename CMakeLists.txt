cmake_minimum_required(VERSION 3.22)
project(chess_game)

set(CMAKE_CXX_STANDARD 14)

add_executable(chess_game main.cpp Board.h Board.cpp Piece.h PieceType.h PieceType.cpp)
