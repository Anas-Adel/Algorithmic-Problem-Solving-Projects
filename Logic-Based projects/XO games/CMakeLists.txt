cmake_minimum_required(VERSION 3.27)
project(OOPAssignment3)

set(CMAKE_CXX_STANDARD 23)

add_executable(OOPAssignment3 main.cpp
        BoardGame_CLASSES.h
        BoardGame_CLASSES.cpp
        fivebyfiveXOgame.h
        fivebyfiveXOgame.cpp
        ConnectBoard.h
        ConnectBoard.cpp
        Pyramic_Board.h
        Pyramic_Board.cpp)
