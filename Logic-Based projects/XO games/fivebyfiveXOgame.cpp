#include "fivebyfiveXOgame.h"

fivebyfiveXOgame::fivebyfiveXOgame() {
    n_rows = n_cols = 5;
    fivebyfiveboard = new char *[n_rows];
    for (int i = 0; i < n_rows; i++) {
        fivebyfiveboard[i] = new char[n_cols];
        for (int j = 0; j < n_cols; j++)
            fivebyfiveboard[i][j] = 0;
    }
}

bool fivebyfiveXOgame::update_board(int x, int y, char mark) {
    if (!(x < 0 || x > 4 || y < 0 || y > 4) && (fivebyfiveboard[x][y] == 0)) {
        fivebyfiveboard[x][y] = toupper(mark);
        n_moves++;
        return true;
    } else {
        return false;
    }
}

void fivebyfiveXOgame::display_board() {
    if (n_moves == 24) {
        count_X_total = number_of_all_wins('X');
        count_O_total = number_of_all_wins('O');
    }
    for (int i = 0; i < 5; ++i) {
        cout << "\n| ";
        for (int j = 0; j < 5; ++j) {
            cout << "(" << i << "," << j << ")";
            cout << setw(3) << fivebyfiveboard[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
    if (n_moves == 24) {
        cout << "First player has " << count_X_total << " sequences \n";
        cout << "Second player has " << count_O_total << " sequences \n";
    }
}

bool fivebyfiveXOgame::is_winner() {
    if (count_X_total > count_O_total and n_moves >= 24) {
        cout << "Player 1 Wins!\n";
    } else if (count_O_total > count_X_total and n_moves >= 24) {
        cout << "Player 2 Wins!\n";
    }
    return false;
}

bool fivebyfiveXOgame::is_draw() {
    return (n_moves == 24 && count_X_total == count_O_total);
}

bool fivebyfiveXOgame::game_is_over() {
    return (n_moves >= 24);
}

//count number of sequences (3-in-a-row) for 'X' or 'O'
int fivebyfiveXOgame::number_of_all_wins(char symbol) {
    int count_each = 0;

    // Check rows
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (fivebyfiveboard[i][j] == symbol and fivebyfiveboard[i][j] == fivebyfiveboard[i][j + 1] and
                fivebyfiveboard[i][j] == fivebyfiveboard[i][j + 2]) {
                count_each++;
            }
        }
    }

    // Check columns
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (fivebyfiveboard[i][j] == symbol and fivebyfiveboard[i][j] == fivebyfiveboard[i + 1][j] and
                fivebyfiveboard[i][j] == fivebyfiveboard[i + 2][j]) {
                count_each++;
            }
        }
    }

    // Check diagonals
    // Check principal diagonal
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (fivebyfiveboard[i][j] == symbol and fivebyfiveboard[i][j] == fivebyfiveboard[i + 1][j + 1] and
                fivebyfiveboard[i][j] == fivebyfiveboard[i + 2][j + 2]) {
                count_each++;
            }
        }
    }

    // Check off diagonal
    for (int i = 1; i < 4; ++i) {
        for (int j = 1; j < 4; ++j) {
            if (fivebyfiveboard[i][j] == symbol and fivebyfiveboard[i][j] == fivebyfiveboard[i - 1][j + 1] and
                fivebyfiveboard[i][j] == fivebyfiveboard[i + 1][j - 1]) {
                count_each++;
            }
        }
    }
    return count_each;
}

//free dynamically allocated memory
fivebyfiveXOgame::~fivebyfiveXOgame() {
    // Release dynamically allocated memory for each inner array
    for (int i = 0; i < n_rows; ++i) {
        delete[] fivebyfiveboard[i];
    }

    // Release the main array pointer
    delete[] fivebyfiveboard;
}
