#ifndef _TICTACTOE_4X4_H
#define _TICTACTOE_4X4_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// 4x4 Board for Tic-Tac-Toe
template <typename T>
class TicTacToe_Board : public Board<T> {
public:
    TicTacToe_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    T get_cell(int x, int y) const;

    
private:
    bool is_adjacent(int old_x, int old_y, int new_x, int new_y);
};

// Player class for Tic-Tac-Toe
template <typename T>
class TicTacToe_Player : public Player<T> {
public:
    TicTacToe_Player(string name, T symbol);
    void getmove(int& x, int& y) override ;
};

// Random Player for Tic-Tac-Toe
template <typename T>
class TicTacToe_Random_Player : public RandomPlayer<T> {
public:
    TicTacToe_Random_Player(T symbol, TicTacToe_Board<T>* board);
    void getmove(int& x, int& y) override;

private:
    TicTacToe_Board<T>* board; // Pointer to the board
};

//--------------------------------------------------------------------------------- IMPLEMENTATION

// Constructor for TicTacToe_Board
template <typename T>
TicTacToe_Board<T>::TicTacToe_Board() {
    this->rows = this->columns = 4;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' '; // Initialize cells to empty space
        }
    }

    // Pre-place tokens for both players
    this->board[0][1] = this->board[0][3] = 'X';
    this->board[3][0] = this->board[3][2] = 'X';
    this->board[0][0] = this->board[0][2] = 'O';
    this->board[3][1] = this->board[3][3] = 'O';


    this->n_moves = 0;
}
// Check adjacency (horizontal/vertical)
template <typename T>
bool TicTacToe_Board<T>::is_adjacent(int old_x, int old_y, int new_x, int new_y) {
    return (abs(old_x - new_x) + abs(old_y - new_y)) == 1;
}

// Update board: Move a token if conditions are valid
template <typename T>
bool TicTacToe_Board<T>::update_board(int x, int y, T symbol) {
    int old_x = x / 10, old_y = x % 10; // Decode old position
    int new_x = y / 10, new_y = y % 10; // Decode new position

    // Check if old and new positions are within bounds
    if(old_x < 0 || old_x >= this->rows || old_y < 0 || old_y >= this->columns ||
       new_x < 0 || new_x >= this->rows || new_y < 0 || new_y >= this->columns){
       cout << "Position out of bounds! Try again. \n";
       return false;
    }

    // Check if the old position contains the player's symbol
    if(this->board[old_x][old_y] != symbol){
        cout << "Invalid move! You must move your own token.\n";
        return false;
    }

    // Check if the new position is empty
    if(this->board[new_x][new_y] != ' '){
        cout << "Invalid move! The destination is not empty.\n";
        return false;
    }

    // Check if the move is adjacent
    if(!is_adjacent(old_x,old_y,new_x,new_y)){
        cout << "Invalid move! You can only move to an adjacent position.\n";
        return false;
    }
    
    // Perform the move
    this->board[old_x][old_y] = ' ';    // Clear the old position
    this->board[new_x][new_y] = symbol; // Place the symbol in the new position
    this->n_moves++;
    return true;

}

// Display the board and the pieces on it
template <typename T>
void TicTacToe_Board<T>::display_board() {
    cout << "\n Display 4x4 Tic Tac Toe Board:\n";
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}


// Check for a win (align 3 tokens)
template <typename T>
bool TicTacToe_Board<T>::is_win() {
    // Check rows, columns, and diagonals
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j <= 1; j++) { // Check 3 consecutive cells
            // Rows
            if (this->board[i][j] != ' ' &&
                this->board[i][j] == this->board[i][j + 1] &&
                this->board[i][j] == this->board[i][j + 2])
                return true;
            // Columns
            if (this->board[j][i] != ' ' &&
                this->board[j][i] == this->board[j + 1][i] &&
                this->board[j][i] == this->board[j + 2][i])
                return true;
        }
    }

    // Check diagonals
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            if (this->board[i][j] != ' ' &&
                this->board[i][j] == this->board[i + 1][j + 1] &&
                this->board[i][j] == this->board[i + 2][j + 2])
                return true;
            if (this->board[i][j + 2] != ' ' &&
                this->board[i][j + 2] == this->board[i + 1][j + 1] &&
                this->board[i][j + 2] == this->board[i + 2][j])
                return true;
        }
    }

    return false;
}

// Game over if there's a win
template <typename T>
bool TicTacToe_Board<T>::is_draw()  {
    return false;
}

// Game over if there's a win
template <typename T>
bool TicTacToe_Board<T>::game_is_over() {
    return is_win();
}

//--------------------------------------- PLAYER CLASS

template <typename T>
TicTacToe_Player<T>::TicTacToe_Player(string name, T symbol) : Player<T>(name, symbol) {}

// Encode positions in getmove
template <typename T>
void TicTacToe_Player<T>::getmove(int& x, int& y) {
    int old_x, old_y, new_x, new_y;

    cout << this->name << " (" << this->symbol << ") - Enter old position (x y): ";
    cin >> old_x >> old_y;
    cout << "Enter new position (x y): ";
    cin >> new_x >> new_y;

    x = old_x * 10 + old_y; // Encode old position
    y = new_x * 10 + new_y; // Encode new position
}

//Function to get the value of a cell
template <typename T>
T TicTacToe_Board<T>::get_cell(int x, int y) const {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns) {
        return this->board[x][y];
    }
    throw out_of_range("Cell coordinates are out of bounds");
}


// Constructor for TicTacToe_Random_Player
template <typename T>
TicTacToe_Random_Player<T>::TicTacToe_Random_Player(T symbol, TicTacToe_Board<T>* board) : RandomPlayer<T>(symbol) , board(board) {
    this->dimension = 4;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0))); // Seed random generator
}

//Function to get the valid random move
template <typename T>
void TicTacToe_Random_Player<T>::getmove(int& x, int& y) {
    int old_x, old_y, new_x, new_y ;
    bool valid_move = false;

    while(!valid_move){
        // Randomly select an old position containing the player's symbol
        old_x = rand() % this->dimension;
        old_y = rand() % this->dimension;
    
        // Check if the position contains the player's symbol
        if(board->get_cell(old_x,old_y) == this->symbol){
          // Generate a random adjacent move
          int dx[] = {-1,1,0,0};       // Movement in x direction
          int dy[] = {0,0,-1,1};       // Movement in y direction
          int direction = rand() % 4 ; // Pick a random direction
                                                   
          new_x = old_x + dx[direction];
          new_y = old_y + dy[direction];
        
            // Validate the move
            if(new_x >= 0 && new_x < this->dimension &&
               new_y >=0  && new_y < this->dimension &&
               board->get_cell(new_x,new_y) == ' '){
               valid_move = true; // The move is valid
            }
        }
    }
    
    // Encode the move into x and y
    x = old_x * 10 + old_y;
    y = new_x * 10 + new_y;
  
}

#endif //_TICTACTOE_4X4_H
