#include "Pyramic_Board.h"

// Set the board to be three rows and the number of coulums in a row is equal to 1+2i and i is the index of the row
Pyramic_Board::Pyramic_Board() {
    n_rows = 3;
    board = new char *[n_rows];
    for (int i = 0; i < n_rows; i++) {
        board[i] = new char[1 + 2 * i];
        for (int j = 0; j < 1 + 2 * i; j++)
            board[i][j] = ' ';
    }
}

// Return true if move is valid and put it on board
bool Pyramic_Board::update_board(int x, int y, char mark) {
    // Only update if move is valid
    if (!(x < 0 || x > 2 || y < 0 || y > 1 + 2 * x) && (board[x][y] == ' ')) {
        board[x][y] = toupper(mark);
        n_moves++;
        return true;
    } else
        return false;
}

// Display the board and the pieces on it
void Pyramic_Board::display_board() {


    for (int i: {0, 1, 2}) {

        cout << '\n';
        for (int j = 0; j < 2 - i; j++) {
            cout << "         ";
        }
        cout << "| ";
        for (int j = 0; j < 1 + 2 * i; j++) {
            cout << "(" << i << "," << j << ")";
            cout << board[i][j] << " | ";
        }
        if (i == 0)
            cout << "\n         ----------------------------";
        else
            cout << "\n----------------------------------------------";
    }
    cout << endl;


}

// Returns true if there is any winner and the trun decides who was the winner
bool Pyramic_Board::is_winner() {
    // checks if the middle colum has a winner or not
    if (board[0][0] == board[1][1] and board[0][0] != ' ') {
        if (board[0][0] == board[2][2])
            return true;
    }

    // checks if the left digonal has a winner or not
    if (board[0][0] == board[1][0] and board[0][0] != ' ') {
        if (board[0][0] == board[2][0])
            return true;
    }

    // checks if the right digonal has a winner or not
    if (board[0][0] == board[1][2] and board[0][0] != ' ') {
        if (board[0][0] == board[2][4])
            return true;
    }

    // checks if the last row has a winner or not
    for (int i = 1; i < 3; i++) {
        for (int j = 0; j < 2 * i - 1; j++) {
            if (board[i][j] == board[i][j + 1] and board[i][j] != ' ') {
                if (board[i][j] == board[i][j + 2])
                    return true;
            }
        }
    }

    return false;
}

// Return true if 9 moves are done and no winner
bool Pyramic_Board::is_draw() {
    return (n_moves == 9 && !is_winner());
}


// gmae over
bool Pyramic_Board::game_is_over() {
    return n_moves >= 9;
}