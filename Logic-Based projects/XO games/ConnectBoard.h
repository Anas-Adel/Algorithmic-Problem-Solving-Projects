#ifndef OOPASSIGNMENT3_CONNECTBOARD_H
#define OOPASSIGNMENT3_CONNECTBOARD_H


#include "BoardGame_CLASSES.h"

// This class inherits from the Board class
class ConnectBoard : public Board {
public:
    // Default constructor for the ConnectBoard class
    ConnectBoard();

    // Updates the board with the given mark ('X' or 'O') at the specified location
    bool update_board(int x, int col, char mark);

    // Displays the current state of the board
    void display_board();

    // Checks if there is a winner in the current state of the game
    bool is_winner();

    // Checks if the game is over (either there is a winner or the board is full)
    bool game_is_over();

    // Checks if the game is a draw (the board is full and there is no winner)
    bool is_draw();
};

#endif //OOPASSIGNMENT3_CONNECTBOARD_H
