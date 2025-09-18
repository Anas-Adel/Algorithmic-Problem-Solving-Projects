#include "BoardGame_CLASSES.h"
#include "Pyramic_Board.h"

// Class definition for X_O_Board class
// Author:  Mohammad El-Ramly
// Date:    10/10/2022
// Version: 1

// Set the board
X_O_Board::X_O_Board() {
    n_rows = n_cols = 3;
    board = new char *[n_rows];
    for (int i = 0; i < n_rows; i++) {
        board[i] = new char[n_cols];
        for (int j = 0; j < n_cols; j++)
            board[i][j] = 0;
    }
}

// Return true  if move is valid and put it on board
// within board boundaries in empty cell
// Return false otherwise
bool X_O_Board::update_board(int x, int y, char mark) {
    // Only update if move is valid
    if (!(x < 0 || x > 2 || y < 0 || y > 2) && (board[x][y] == 0)) {
        board[x][y] = toupper(mark);
        n_moves++;
        return true;
    } else
        return false;
}

// Display the board and the pieces on it
void X_O_Board::display_board() {
    for (int i: {0, 1, 2}) {
        cout << "\n| ";
        for (int j: {0, 1, 2}) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
// either X or O
// Written in a complex way. DO NOT DO LIKE THIS.
bool X_O_Board::is_winner() {
    char row_win[3], col_win[3], diag_win[2];
    for (int i: {0, 1, 2}) {
        row_win[i] = board[i][0] & board[i][1] & board[i][2];
        col_win[i] = board[0][i] & board[1][i] & board[2][i];
    }
    diag_win[0] = board[0][0] & board[1][1] & board[2][2];
    diag_win[1] = board[2][0] & board[1][1] & board[0][2];

    for (int i: {0, 1, 2}) {
        if ((row_win[i] && (row_win[i] == board[i][0])) ||
            (col_win[i] && (col_win[i] == board[0][i]))) { return true; }
    }
    if ((diag_win[0] && diag_win[0] == board[1][1]) ||
        (diag_win[1] && diag_win[1] == board[1][1])) { return true; }
    return false;
}

// Return true if 9 moves are done and no winner
bool X_O_Board::is_draw() {
    return (n_moves == 9 && !is_winner());
}

bool X_O_Board::game_is_over() {
    return n_moves >= 9;
}




// Class definition for XO_Player class
// Author:  Mohammad El-Ramly
// Date:    10/10/2022
// Version: 1


// Give player a symbol to use in playing
// It can be X or O or others
// This is needed for computer players
// as it does not ask for a name
Player::Player(char symbol) {
    this->symbol = symbol;
}

// Optionally, you can give him ID or order
// Like Player 1 and Player 2
Player::Player(int order, char symbol) {
    cout << "Welcome player " << order << endl;
    cout << "Please enter your name: ";
    cin >> name;
    this->symbol = symbol;
}

// Get desired move: x y (each between 0 and 2)
// Virtual (can change for other player types)
void Player::get_move(int &x, int &y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Give player info as a string
string Player::to_string() {
    return "Player: " + name;
}

// Get symbol used by player
char Player::get_symbol() {
    return symbol;
}




// Class definition for XO_RandomPlayer class
// Which is a computer player playing randomly
// Author:  Mohammad El-Ramly
// Date:    10/10/2022
// Version: 1




// Set player symbol and name as Random Computer Player
RandomPlayer::RandomPlayer(char symbol, int dimension) : Player(symbol) {
    this->dimension = dimension;
    this->name = "Random Computer Player";
    cout << "My names is " << name << endl;
}

// Generate a random move
void RandomPlayer::get_move(int &x, int &y) {
    x = (int) (rand() / (RAND_MAX + 1.0) * dimension);
    y = (int) (rand() / (RAND_MAX + 1.0) * dimension);
}

// Set player symbol and name as Random Computer Player
Pyramid_AiPlayer::Pyramid_AiPlayer(char symbol, int dimension) : Player(symbol) {
    this->dimension = dimension;
    this->name = "Random Computer Player";
    cout << "My names is " << name << endl;
}

// Generate a random move
void Pyramid_AiPlayer::get_move(int &x, int &y,int depth, const Board& brd) {
    for (int z=0;z<depth;z++) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < (2 * i + 1); j++) {
                if(brd.board[i][j] == 0)

            }
        }
        depth--;
    }
}







// Class definition for XO_GameManager class
// Author:  Mohammad El-Ramly
// Date:    10/10/2022
// Version: 1





GameManager::GameManager(Board *bPtr, Player *playerPtr[2]) {
    boardPtr = bPtr;
    players[0] = playerPtr[0];
    players[1] = playerPtr[1];
}

void GameManager::run() {
    int x, y;

    boardPtr->display_board();

    while (!boardPtr->game_is_over()) {
        for (int i: {0, 1}) {
            players[i]->get_move(x, y);
            while (!boardPtr->update_board(x, y, players[i]->get_symbol())) {
                players[i]->get_move(x, y);
            }
            boardPtr->display_board();
            if (boardPtr->is_winner()) {
                cout << players[i]->to_string() << " wins\n";
                return;
            }
            if (boardPtr->is_draw()) {
                cout << "Draw!\n";
                return;
            }
        }
    }
}
