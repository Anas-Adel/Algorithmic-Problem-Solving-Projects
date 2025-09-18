//
// Created by men3em on 12/16/2023.
//

#ifndef OOPASSIGNMENT3_PYRAMIC_BOARD_H
#define OOPASSIGNMENT3_PYRAMIC_BOARD_H

#include "BoardGame_CLASSES.h"

class Pyramic_Board : public Board {
public:
    Pyramic_Board();

    bool update_board(int x, int y, char mark);

    void display_board();

    bool is_winner();

    bool is_draw();

    bool game_is_over();

    friend void Pyramid_AiPlayer::get_move(int &x, int &y,int depth, const Board& brd);
};

#endif //OOPASSIGNMENT3_PYRAMIC_BOARD_H
