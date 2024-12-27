

#ifndef SUS1_H
#define SUS1_H


#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <limits>

using namespace std;
int globalVar = 0;
template <typename T>
class SUS_Board : public Board<T> {
public:
    SUS_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();

private:
    int player1_sus_count; // SUS count for Player 1
    int player2_sus_count; // SUS count for Player 2

};

template <typename T>
class SUS_Player : public Player<T> {
public:
    SUS_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class SUS_Random_Player : public RandomPlayer<T> {
public:
    SUS_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

// Constructor for SUS_Board
template <typename T>
SUS_Board<T>::SUS_Board() : player1_sus_count(0), player2_sus_count(0) {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}
template <typename T>
bool SUS_Board<T>::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        int susCount =0;
        if (mark == 0) {
            this->n_moves--;
            globalVar--;
            this->board[x][y] = 0;
        } else {
            this->n_moves++;
            globalVar++;
            this->board[x][y] = toupper(mark);
        }
        // Check the row of the current move
        if (this->board[x][0] == 'S' && this->board[x][1] == 'U' && this->board[x][2] == 'S') {
            susCount++;
        }
        // Check the column of the current move
        if (this->board[0][y] == 'S' && this->board[1][y] == 'U' && this->board[2][y] == 'S') {
            susCount++;
        }
        // Check the primary diagonal if the move is on it
        if (x == y && this->board[0][0] == 'S' && this->board[1][1] == 'U' && this->board[2][2] == 'S') {
            susCount++;
        }
        // Check the secondary diagonal if the move is on it
        if (x + y == 2 && this->board[0][2] == 'S' && this->board[1][1] == 'U' && this->board[2][0] == 'S') {
            susCount++;
        } // Update the appropriate player's count
        if (mark == 'S') {
            player1_sus_count += susCount;
        } else if (mark == 'U') {
            player2_sus_count += susCount;
        }
        // Print updated counts
        cout << "Player 1 SUS count: " << player1_sus_count << "\n";
        cout << "Player 2 SUS count: " << player2_sus_count << "\n";

        return true;
    }else if (this->n_moves==10){
        return true;
    }
    return false;
}


// Display the board and the pieces on it
template <typename T>
void SUS_Board<T>::display_board() {
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
template <typename T>
bool SUS_Board<T>::is_win() {
    if(this->n_moves == 9) {
        if (player1_sus_count > player2_sus_count) {
            cout << "Player 1 wins with more SUS sequences!\n";
            return true;
        } else if (player1_sus_count < player2_sus_count) {
            this->n_moves++;
            globalVar++;
            return false;
        }
    }else if (this->n_moves == 10) {
        if (player1_sus_count < player2_sus_count) {
            cout << "Player 2 wins with more SUS sequences!\n";
            return true;
        }
    }//else {
    return false;
    //}
}



// Return true if 9 moves are done and no winner
template <typename T>
bool SUS_Board<T>::is_draw() {
    return ( (this->n_moves == 9 && !is_win()));
}

// Return true if the game is over
template <typename T>
bool SUS_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
SUS_Player<T>::SUS_Player(string name, T symbol) : Player<T>(name, symbol) {}
template <typename T>
void SUS_Player<T>::getmove(int& x, int& y) {

    if (globalVar%10==0 && globalVar != 0 ){
        x=0;
        y=0;
    }
    else {
        cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
        cin >>x>>y;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
// Constructor for X_O_Random_Player
template <typename T>
SUS_Random_Player<T>::SUS_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void SUS_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}


#endif //SUS1_H
