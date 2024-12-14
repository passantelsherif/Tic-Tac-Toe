
#ifndef _MISERE_H
#define _MISERE_H

#include "BoardGame_Classes.h"

//Add global variables for easy access
bool flag = false ;
int global_moves=0;

//Template class for a 5x5 Tic Tac Toe board
template <typename T>
class Misere_Board:public Board<T> {
public:
    Misere_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    bool has_3consecutive();

};

//Template class for a player in the game
template <typename T>
class Misere_Player : public Player<T> {
public:
    Misere_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

// Template class for a random computer player
// Generates random moves for the game.
template <typename T>
class Misere_Random_Player : public RandomPlayer<T>{
public:
    Misere_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  
#include <limits>

using namespace std;

// Constructor for X_O_Board
// Initializes a 3x3 board with zeros 
template <typename T>
Misere_Board<T>::Misere_Board() {
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

// Updates the board at a specified position with the given mark (symbol).
template <typename T>
bool Misere_Board<T>::update_board(int x, int y, T mark) {

    if(flag == true){
        return true;
    }                                     
    if(this->n_moves==9){
        this->n_moves++;
        return true;
    }

    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
            global_moves++;

        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void Misere_Board<T>::display_board() {
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

//Check the flag for winning conditions 
template <typename T>
bool Misere_Board<T>::has_3consecutive(){    
    if(flag == true){                    
        return true;
    }
    
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) || 
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            flag = true ;  
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        flag = true ;     
    }

    return false;
}


// Function to determine the winner
template <typename T>
bool Misere_Board<T>::is_win() {
    if(has_3consecutive()){
        return true;
    }
        return false;
}


// Return true if 9 moves are done and no winner
template <typename T>
bool Misere_Board<T>::is_draw() {
    return (this->n_moves == 9 && !has_3consecutive());
}

// Determines if the game is over due to win, draw, or move limit.
template <typename T>
bool Misere_Board<T>::game_is_over() {
    return global_moves > 9 ;
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
Misere_Player<T>::Misere_Player(string name, T symbol) : Player<T>(name, symbol)   {}

// Prompts the player to input their move coordinates.
template <typename T>
void Misere_Player<T>::getmove(int& x, int& y) {
    if(global_moves == 9 || flag == true){                                                           
        return;
    }
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces:\n "
            "Please make sure that your inputs are positive integer numbers and unused cells:\n";
    while (true)
    {
        if (cin >> x >> y) {
            if (x < 0 || y < 0 || x > 2 || y > 2)
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
template <typename T>
Misere_Random_Player<T>::Misere_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Misere_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}







#endif //_MISERE_H
