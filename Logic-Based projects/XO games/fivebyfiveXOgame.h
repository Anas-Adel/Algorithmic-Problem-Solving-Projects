

#ifndef OOPASSIGNMENT3_FIVEBYFIVEXOGAME_H
#define OOPASSIGNMENT3_FIVEBYFIVEXOGAME_H

#include "BoardGame_CLASSES.h"

class fivebyfiveXOgame : public Board {
private:
    int count_X_total = 0;
    int count_O_total = 0;
    char **fivebyfiveboard;
public:
    fivebyfiveXOgame();

    //free dynamically allocated memory
    ~fivebyfiveXOgame();

    //update board with new move
    bool update_board(int x, int y, char mark) override;

    bool is_winner() override;

    // Return true if all moves are done and no winner
    bool is_draw() override;

    // Display the board and the pieces on it
    void display_board() override;

    // Return true if game is over (number of moves >= 24)
    bool game_is_over() override;

    //Counts the number of sequences for X or O
    int number_of_all_wins(char symbol);
};



#endif //OOPASSIGNMENT3_FIVEBYFIVEXOGAME_H
