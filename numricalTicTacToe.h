#ifndef _NUMERICAL_TIC_TAC_TOE_H
#define _NUMERICAL_TIC_TAC_TOE_H
#include "BoardGame_Classes.h"
#include <set>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
template <typename T>
class numboard:public Board<T> {
    private:
    set<int>used;
  public:
    numboard ();
    bool update_board (int x , int y , T symbol );
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};
template <typename T>
class numPlayer : public Player<T> {
public:
    numPlayer (string name, T symbol);
    void getmove(int& x, int& y) ;

};
template <typename T>
class numRandom_Player : public RandomPlayer<T>{
public:
    numRandom_Player (T symbol);
    void getmove(int &x, int &y) ;
};
//--------------------------------------- IMPLEMENTATION
template <typename T>
numboard<T>::numboard() {
    this->rows = this->columns = 3;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;  // Initialize with 0 (empty)
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool update_board(int x, int y, T symbol = 0); // Keep the default argument here

// In your implementation file (remove the default argument)
template <typename T>
bool numboard<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0) {
        return false;
    }

    bool isRandom = (symbol == 0); // Check if we're generating a random number
    if (isRandom) {
        // Generate a random number depending on the current turn
        if (this->n_moves % 2 == 0) {
            // Even move count: generate an odd number (1, 3, 5, 7, 9)
            do {
                symbol = 2 * (rand() % 5) + 1; // Generates a random odd number from 1 to 9
            } while (used.find(symbol) != used.end());
        } else {
            // Odd move count: generate an even number (2, 4, 6, 8)
            do {
                symbol = 2 * (rand() % 4) + 2; // Generates a random even number from 2 to 8
            } while (used.find(symbol) != used.end());
        }

        // Update the board with the generated symbol
        this->board[x][y] = symbol;
        used.insert(symbol); // Mark the number as used
    } else {
        cout << "Please enter a valid number from 1 to 9:\n";
        while (true) {
            cin >> symbol;
            if (used.find(symbol) == used.end() && symbol >= 1 && symbol <= 9) {
                if (this->n_moves % 2 == 0) {
                    if (symbol % 2 != 0) { // Even move: symbol must be odd
                        this->board[x][y] = symbol;
                        used.insert(symbol); // Mark the number as used
                        break;
                    } else {
                        cerr << "Error: Please enter an odd number.\n";
                    }
                } else {
                    if (symbol % 2 == 0) { // Odd move: symbol must be even
                        this->board[x][y] = symbol;
                        used.insert(symbol); // Mark the number as used
                        break;
                    } else {
                        cerr << "Error: Please enter an even number.\n";
                    }
                }
            } else {
                cerr << "Error: Used or Invalid number, please enter another one.\n";
            }
        }
    }

    this->n_moves++;
    return true;
}
// Display the board
template <typename T>
void numboard<T>::display_board() {
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
// Check for a win
template <typename T>
bool numboard<T>::is_win() {
    // Check rows, columns, and diagonals for sum of 15
    for (int i = 0; i < this->rows; i++) {
        if ((((this->board[i][0] + this->board[i][1] + this->board[i][2] == 15) && (this->board[i][0] != 0 &&this->board[i][1]!= 0 &&this->board[i][2]!=0 ))) ||
            ((this->board[0][i] + this->board[1][i] + this->board[2][i] == 15)) && (this->board[0][i] != 0 &&this->board[1][i]!= 0 &&this->board[2][i]!=0 )) {
            return true;
            }
    }
    if ((((this->board[0][0] + this->board[1][1] + this->board[2][2] == 15) && (this->board[0][0] != 0 &&this->board[1][1]!= 0 &&this->board[2][2]!=0 ) ||
        (this->board[0][2] + this->board[1][1] + this->board[2][0] == 15)&& (this->board[0][2] != 0 &&this->board[1][1]!= 0 &&this->board[2][0]!=0 )))) {
        return true;
        }
    return false;
}
// Check for a draw
template <typename T>
bool numboard<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

// Check if the game is over
template <typename T>
bool numboard<T>::game_is_over() {
    return is_win() || is_draw();
}
template <typename T>
numPlayer<T>::numPlayer(string name, T symbol) : Player<T>(name,symbol){}
template <typename T>
void numPlayer<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin>>x>>y;
}
template <typename T>
numRandom_Player<T>::numRandom_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->symbol = 0;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}
template <typename T>
void numRandom_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}
#endif //_NUMERICAL_TIC_TAC_TOE_H