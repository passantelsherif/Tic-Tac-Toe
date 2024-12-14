#ifndef _ULTIMATE_X_O_H
#define _ULTIMATE_X_O_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype> 
#include <vector>
#include <limits>
using namespace std;


// Smaller Tic Tac Toe Board (3x3)
template <typename T>
class Small_X_O_Board : public Board<T> {
public:
    Small_X_O_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    T getCell(int row, int col) ;                  
    void set_winner(T symbol);   
    bool has_winner();  
};


// Ultimate Tic Tac Toe Board
template <typename T>
class Ultimate_X_O_Board : public Board<T> {
private:
    Small_X_O_Board<T> boards[3][3]; // 3x3 grid of smaller boards
    char main_board[3][3];          // 3x3 grid to track winners of smaller boards

public:
    Ultimate_X_O_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

//Template class for a player in the game
template <typename T>
class X_O_Player : public Player<T> {
public:
    X_O_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

// Template class for a random computer player
// Generates random moves for the game.
template <typename T>
class X_O_Random_Player : public RandomPlayer<T>{
public:
    X_O_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};



//--------------------------------------- IMPLEMENTATION


// Constructor for Small_X_O_Board
template <typename T>
Small_X_O_Board<T>::Small_X_O_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
}

//Function to get cell coordinates
template <typename T>
T Small_X_O_Board<T>::getCell(int row, int col) {                       
    return this->board[row][col];
}

//Function to set the winner smaller board with the symbol
template <typename T>
void Small_X_O_Board<T>::set_winner(T symbol) {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            // Set the entire board to the winner symbol 
            this->board[i][j] = toupper(symbol);  
        }
    }
}

//Function determine the winner in the small board
template <typename T>
bool Small_X_O_Board<T>::has_winner() {
    // Check if there is a winner already
    return this->board[0][0] != ' ' && this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] ||
           this->board[0][2] != ' ' && this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] ||
           this->board[0][0] != ' ' && this->board[0][0] == this->board[1][0] && this->board[1][0] == this->board[2][0] ||
           this->board[0][1] != ' ' && this->board[0][1] == this->board[1][1] && this->board[1][1] == this->board[2][1] ||
           this->board[0][2] != ' ' && this->board[0][2] == this->board[1][2] && this->board[1][2] == this->board[2][2];
}

// Updates the board at a specified position with the given mark (symbol).
template <typename T>
bool Small_X_O_Board<T>::update_board(int x, int y, T mark) {
   
    if (this->has_winner()) {
        // No moves allowed on this board if there's a winner
        return false;
    }
   
    // Only update if move is valid
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && (this->board[x][y] == ' ' || mark == 0)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        } else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

       // If there's a winner, set the winner symbol in all cells
        if (this->is_win()) {
            this->set_winner(mark);
        }

        return true;
    }
    return false;
}

// Displays the current state of the board with coordinates and symbols.
template <typename T>
void Small_X_O_Board<T>::display_board() {
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

//Check if there is a winner in small board
template <typename T>
bool Small_X_O_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != ' ') ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != ' ')) {
            return true;
        }
    }
    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != ' ') ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != ' ')) {
        return true;
    }
    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool Small_X_O_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

// Determines if the game is over due to win, draw, or move limit.
template <typename T>
bool Small_X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}


// Constructor for Ultimate_X_O_Board
template <typename T>
Ultimate_X_O_Board<T>::Ultimate_X_O_Board() {
    this->rows = this->columns = 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            main_board[i][j] = ' ';
        }
    }
}

// Updates the state of the smaller board and the main board
template <typename T>
bool Ultimate_X_O_Board<T>::update_board(int x, int y, T symbol) {
    int main_x = x / 3;
    int main_y = y / 3;
    int sub_x = x % 3;
    int sub_y = y % 3;

    // Check if the small board already has a winner
    if (boards[main_x][main_y].has_winner()) {
        cout << "This small board at has already been won! Please choose another board." << endl;
        return false;  // Prevent move on already won board
    }

    if (boards[main_x][main_y].update_board(sub_x, sub_y, symbol)) {
        // Update main board if the smaller board has a winner
        if (boards[main_x][main_y].is_win()) {
            main_board[main_x][main_y] = symbol;
        }
        return true;
    }
    return false;
}

//Function to display the ultimate board
template <typename T>
void Ultimate_X_O_Board<T>::display_board() {
    cout << "\nUltimate Tic Tac Toe Board:\n";
    for (int i = 0; i < 3; i++) {
        for (int sub_i = 0; sub_i < 3; sub_i++) {
            for (int j = 0; j < 3; j++) {
                for (int sub_j = 0; sub_j < 3; sub_j++) {
                    //Calculate global row and column indices
                    int global_row = i*3 + sub_i;
                    int global_col = j*3 + sub_j;
                    cout << "(" << global_row << "," << global_col << ") ";
                    cout << boards[i][j].getCell(sub_i,sub_j) << " ";
                }
                cout << " | ";
            }
            cout << endl;
        }
        cout << "-----------------------------------------------------------------------------------\n";
    }
}

//Check if there is a winner in the main (ultimate) board
template <typename T>
bool Ultimate_X_O_Board<T>::is_win() {
    // Check rows, columns, and diagonals on the main board
    for (int i = 0; i < 3; i++) {
        if ((main_board[i][0] == main_board[i][1] && main_board[i][1] == main_board[i][2] && main_board[i][0] != ' ') ||
            (main_board[0][i] == main_board[1][i] && main_board[1][i] == main_board[2][i] && main_board[0][i] != ' ')) {
            return true;
        }
    }
    if ((main_board[0][0] == main_board[1][1] && main_board[1][1] == main_board[2][2] && main_board[0][0] != ' ') ||
        (main_board[0][2] == main_board[1][1] && main_board[1][1] == main_board[2][0] && main_board[0][2] != ' ')) {
        return true;
    }
    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool Ultimate_X_O_Board<T>::is_draw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (main_board[i][j] == ' ') {
                return false;
            }
        }
    }
    return !is_win();
}

// Determines if the game is over due to win, or draw.
template <typename T>
bool Ultimate_X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}


//--------------------------------------

// Constructor for X_O_Player
// Initializes a player with a name and a symbol.
template <typename T>
X_O_Player<T>::X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

// Prompts the player to input their move coordinates.
template <typename T>
void X_O_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 8) separated by spaces: \n"
         <<"Please make sure that your inputs are positive integer numbers and unused cells:\n";
    while (true)
    {
        if (cin >> x >> y) {
            if (x < 0 || y < 0 || x > 8 || y > 8)
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
X_O_Random_Player<T>::X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 9;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

// Generates a random move for the random player.
template <typename T>
void X_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}


#endif // _ULTIMATE_X_O_H