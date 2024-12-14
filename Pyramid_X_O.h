#ifndef Pyramid_X_O
#define Pyramid_X_O

#include "BoardGame_Classes.h"

template <typename T>
class Pyramid_X_O_Board : public Board<T> {
public:
    Pyramid_X_O_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Pyramid_X_O_Player : public Player<T> {
public:
    Pyramid_X_O_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class Pyramid_X_O_Random_Player : public RandomPlayer<T> {
public:
    Pyramid_X_O_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

////////////////////////////////////////////////////////////////////////////////IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>
#include <limits>

using namespace std;

// Constructor for Pyramid_X_O_Board
template <typename T>
Pyramid_X_O_Board<T>::Pyramid_X_O_Board() {
    this->rows = 3;
    this->columns = 5;
    this->board = new T*[this->rows];

    for (int i = 0; i < this->rows; i++) {
        int columns = 2 * i + 1;
        this->board[i] = new T[columns];

        // Initialize each cell to 0 (empty)
        for (int j = 0; j < columns; j++) {
            this->board[i][j] = 0;
        }
    }

    this->n_moves = 0; // Initialize move count
}


template <typename T>
bool Pyramid_X_O_Board<T>::update_board(int x, int y, T mark) {
    // Validate the coordinates based on the pyramid structure
    if (x < 0 || x >= this->rows || y < 0 || y >= (2 * x + 1)) {
        return false;
    }

    // Check if the cell is already filled or invalid input
    if (this->board[x][y] != 0 && mark != 0) {
        return false;
    }

    // Update the board and move count
    if (mark == 0) {
        this->n_moves--;
        this->board[x][y] = 0;
    } else {
        this->n_moves++;
        this->board[x][y] = toupper(mark);
    }

    return true;
}

template <typename T>
void Pyramid_X_O_Board<T>::display_board() {
    cout << "\n Display the Pyramid Tic Tac Toe board \n";

    // Maximum row width (base row)
    int MaxWidth = this->columns;
    for (int i = 0; i < this->rows; i++) {
        // Current row width
        int width = 2 * i + 1;


        // Print leading spaces to center the row
        int spaces = (MaxWidth - width) ;
        for (int s = 0; s < spaces; s++) {
            cout << "      ";
        }


        // Print the cells with its coordinate
        for (int j = 0; j < width; j++) {
            cout <<  "(" << i << "," << j << ")" ;
            cout << " [ " << this->board[i][j] << " ] ";
        }
        cout << "\n";


        // Print separator line between each row and control the space at the first of each row
        if (i < this->rows - 1) {
            for (int s = 0; s < spaces; s++) {
                cout << "      ";
            }
            for (int j = 0; j < width; j++) {
                cout << "------------";
            }
            cout << "\n";
        }
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool Pyramid_X_O_Board<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < (2 * i + 1); j++) {

            // Horizontal check
            if (j + 2 < (2 * i + 1) &&
                this->board[i][j] == this->board[i][j + 1] &&
                this->board[i][j] == this->board[i][j + 2] &&
                this->board[i][j] != 0) {
                return true;
            }


            // Vertical check
            if (i + 2 < this->rows &&
                j < (2 * (i + 1) + 1) && // Ensure the column exists in the next rows
                this->board[0][0] == this->board[1][1] &&
                this->board[1][1] == this->board[2][2] &&
                this->board[0][0] != 0) {
                return true;
            }


            // Main diagonal (\) check
            if (
                 this->board[0][0] == this->board[1][0] &&
                 this->board[1][0] == this->board[2][0] &&
                 this->board[0][0] != 0) {
                return true;
            }

            // Off diagonal (/) check
            if (
                 this->board[0][0] == this->board[1][2] &&
                 this->board[1][2] == this->board[2][4] &&
                 this->board[0][0] != 0) {
                return true;
            }
        }

    }

    return false;
}

//Return true as there is no winner
template <typename T>
bool Pyramid_X_O_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}


template <typename T>
bool Pyramid_X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//-----------------------------------------------------------------------------------------------For Player

// Constructor for Pyramid_X_O_Player
template <typename T>
Pyramid_X_O_Player<T>::Pyramid_X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Pyramid_X_O_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x (0 to 2) and y (0 to 4) separated by spaces:\n "
            "Please make sure that your inputs are positive integer numbers:\n";

    while (true)
    {
        // validation of inputs of moves
        if (cin >> x >> y) {
            if (x < 0 || y <0)
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

//------------------------------------------------------------------------------------------------For Random player

// Constructor for Pyramid_X_O_Random_Player
template <typename T>
Pyramid_X_O_Random_Player<T>::Pyramid_X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {

    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Pyramid_X_O_Random_Player<T>::getmove(int& x, int& y) {
    // Random number between 0 and 2
    x = rand() % 3;
    int NumColumns;

    if (x == 0) {
        // 1 column for row 0
        NumColumns = 1;

    } else if (x == 1) {
        // 3 columns for row 1
        NumColumns = 3;
    } else {
        // 5 columns for row 3
        NumColumns = 5;
    }

    // Randomly select a column (y) within the range for the chosen row
    y = rand() % NumColumns;  // Random column for the current row
}

#endif //Pyramid_X_O_H
