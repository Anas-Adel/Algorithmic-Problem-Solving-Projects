#include <bits/stdc++.h>
#include "ConnectBoard.h"

using namespace std;

// Constructor for the ConnectBoard class
ConnectBoard::ConnectBoard() {
    n_rows = 6;
    n_cols = 7;  // Set the number of rows and columns
    board = new char *[n_rows];  // Allocate memory for the board
    for (int i = 0; i < n_rows; i++) {
        board[i] = new char[n_cols];  // Allocate memory for each row
        for (int j = 0; j < n_cols; j++)
            board[i][j] = ' ';  // Initialize the board with empty spaces
    }
}

// Function to update the board with the player's mark at the specified location
bool ConnectBoard::update_board(int x, int col, char mark) {
    for (int row = n_rows - 1; row >= 0; --row) {
        // subtract 1 from col to Adjust for 0-based indexing.
        if (board[row][col - 1] == ' ') {  // If the cell is empty
            board[row][col - 1] = toupper(mark);  // Place the player's mark
            ++n_moves;  // Increment the number of moves
            return true;  // Return true if the update was successful
        }
    }
    return false;  // Return false if the column is full
}

// Function to check if there is a winner
bool ConnectBoard::is_winner() {
    // Check rows for winner
    for (int i = 0; i < n_rows; ++i) {
        for (int j = 0; j < n_cols - 3; ++j) {
            if (board[i][j] != ' ' && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2] &&
                board[i][j] == board[i][j + 3]) {
                return true;  // Return true if there is a winner
            }
        }
    }
    // Check columns for winner
    for (int i = 0; i < n_rows - 3; ++i) {
        for (int j = 0; j < n_cols; ++j) {
            if (board[i][j] != ' ' && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j] &&
                board[i][j] == board[i + 3][j]) {
                return true;  // Return true if there is a winner
            }
        }
    }
    // Check diagonals for winner

    // Check Principal diagonal
    for (int i = 0; i < n_rows - 3; ++i) {
        for (int j = 0; j < n_cols - 3; ++j) {
            if (board[i][j] != ' ' && board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2] &&
                board[i][j] == board[i + 3][j + 3]) {
                return true;  // Return true if there is a winner
            }
        }
    }
    // Check off diagonal
    for (int i = 3; i < n_rows; ++i) {
        for (int j = 0; j < n_cols - 3; ++j) {
            if (board[i][j] != ' ' && board[i][j] == board[i - 1][j + 1] && board[i][j] == board[i - 2][j + 2] &&
                board[i][j] == board[i - 3][j + 3]) {
                return true;  // Return true if there is a winner
            }
        }
    }
    return false;  // Return false if there is no winner
}

// Function to check if the game is a draw
bool ConnectBoard::is_draw() {
    return (n_moves == n_rows * n_cols && !is_winner());  // Return true if the board is full and there is no winner
}

// Function to check if the game is over
bool ConnectBoard::game_is_over() {
    return n_moves >= n_rows * n_cols;  // Return true if the board is full
}

// Function to display the current state of the board
void ConnectBoard::display_board() {
    for (int i = 0; i < n_rows; ++i) {
        cout << "\n| ";
        for (int j = 0; j < n_cols; ++j) {
            cout << setw(6) << board[i][j] << " |";  // Print each cell of the board
        }
        cout << "\n---------------------------------------------------------";
    }
    cout << endl;
}
