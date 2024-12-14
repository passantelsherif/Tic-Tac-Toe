#ifndef _5X5X_O_H
#define _5X5X_O_H

#include "BoardGame_Classes.h"

//Template class for a 5x5 Tic Tac Toe board
template <typename T>
class X_O_Board_5x5:public Board<T> {

private:
    //int count_three_in_a_row(T symbol);  // Count three-in-a-row sequences for a given symbol
    int count_three_x;  // Count of X's three-in-a-row sequences
    int count_three_o;  // Count of O's three-in-a-row sequences

public:
    int count_three_in_a_row(T symbol);
    X_O_Board_5x5 ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    int get_count_three_x() const { return count_three_x; }
    int get_count_three_o() const { return count_three_o; }

};

//Template class for a player in the game
template <typename T>
class X_O_Player_5x5 : public Player<T> {
public:
    X_O_Player_5x5 (string name, T symbol);
    void getmove(int& x, int& y) ;

};

// Template class for a random computer player
// Generates random moves for the game.
template <typename T>
class X_O_Random_Player_5x5 : public RandomPlayer<T>{
public:
    X_O_Random_Player_5x5 (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  
#include <limits>

using namespace std;

// Constructor for X_O_Board
// Initializes a 5x5 board with empty spaces and zero counts for sequences.
template <typename T>
X_O_Board_5x5<T>::X_O_Board_5x5() : count_three_x(0), count_three_o(0) {                     
    this->rows = this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}


// Counts the number of three-in-a-row sequences for a given symbol (X or O).
template <typename T>
int X_O_Board_5x5<T>::count_three_in_a_row(T symbol) {
    int count = 0;

    // Check rows, columns, and diagonals for three-in-a-row sequences
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            // Horizontal
            if (j <= this->columns - 3 &&
                this->board[i][j] == symbol && 
                this->board[i][j+1] == symbol && 
                this->board[i][j+2] == symbol) {
                count++;
            }
            // Vertical
            if (i <= this->rows - 3 &&
                this->board[i][j] == symbol && 
                this->board[i+1][j] == symbol && 
                this->board[i+2][j] == symbol) {
                count++;
            }
            // Diagonal (top-left to bottom-right)
            if (i <= this->rows - 3 && j <= this->columns - 3 &&
                this->board[i][j] == symbol && 
                this->board[i+1][j+1] == symbol && 
                this->board[i+2][j+2] == symbol) {
                count++;
            }
            // Diagonal (top-right to bottom-left)
            if (i <= this->rows - 3 && j >= 2 &&
                this->board[i][j] == symbol && 
                this->board[i+1][j-1] == symbol && 
                this->board[i+2][j-2] == symbol) {
                count++;
            }
        }
    }
    return count;
}

// Updates the board at a specified position with the given mark (symbol).
template <typename T>
bool X_O_Board_5x5<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        // Update three-in-a-row counts                                       
        count_three_x = count_three_in_a_row('X');
        cout<<"player one score: " <<count_three_x <<endl;
        count_three_o = count_three_in_a_row('O');
        cout<<"player two score: " <<count_three_o <<endl;

        return true;
    }
    return false;
}

// Displays the current state of the board with coordinates and symbols.
template <typename T>
void X_O_Board_5x5<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n--------------------------------------";
    }
    cout << endl;
}

// Checks if there is a winner after 24 moves (end of game).
template <typename T>
bool X_O_Board_5x5<T>::is_win() {
    // if (this->n_moves == 24) {
    //     cout<<"player one score: " <<count_three_x <<endl;
    //     cout<<"player two score: " <<count_three_o <<endl;
    //     if (count_three_x > count_three_o) {
    //         return true;  // 'X' wins
    //     } else if (count_three_o > count_three_x) {
    //         return true;  // 'O' wins
    //     }
    // }
    return false;  // No winner yet
}

// Return true if 24 moves are done and no winner
template <typename T>
bool X_O_Board_5x5<T>::is_draw() {
    return false; //(this->n_moves == 24 && !is_win());                              ///make sure 24 not 25                
}

// Determines if the game is over due to win, draw, or move limit.
template <typename T>
bool X_O_Board_5x5<T>::game_is_over() {
    return this->n_moves == 24 || is_win() || is_draw();  // game is over if 24 moves are made or if we have a winner or draw
}


//--------------------------------------

// Constructor for X_O_Player
// Initializes a player with a name and a symbol.
template <typename T>
X_O_Player_5x5<T>::X_O_Player_5x5(string name, T symbol) : Player<T>(name, symbol) {}

// Prompts the player to input their move coordinates.
template <typename T>
void X_O_Player_5x5<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces:\n "
            "Please make sure that your inputs are positive integer numbers and unused cells:\n";
    while (true)
    {
        if (cin >> x >> y) {
            if (x < 0 || y < 0 || x > 4 || y > 4)
            {
                cout << "Invalid input. Please enter a positive integer input.\n";
                cin >> x >> y;
            }
            break;
        } else {
            cout << "Invalid input. Please enter a valid input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Constructor for X_O_Random_Player
// Initializes a random player with a symbol and random seed.
template <typename T>
X_O_Random_Player_5x5<T>::X_O_Random_Player_5x5(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

// Generates a random move for the random player.
template <typename T>
void X_O_Random_Player_5x5<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}







#endif //_5X5X_O_H