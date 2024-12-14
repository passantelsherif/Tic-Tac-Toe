#ifndef FOURINROW_H
#define FOURINROW_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

template <typename T>
class ConnectFourBoard : public Board<T> {
private:
    char** board;
public:
    ConnectFourBoard();
    bool update_board(int x ,int y, T symbol);
    void display_board() ;
    bool is_win() ;
    bool is_draw() ;
    bool game_is_over() ;
    bool check_winner(int row, int col);
};

template <typename T>
class ConnectFourPlayer : public Player<T> {
public:
    ConnectFourPlayer(string name, T symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
class ConnectFour_Random_Player : public RandomPlayer<T> {
public:
    ConnectFour_Random_Player(T symbol);
    void getmove(int& x, int& y) override;
};

//-------------------------------------------------------------------- IMPLEMENTATION

template <typename T>
ConnectFourBoard<T>::ConnectFourBoard() {
    this->rows = 6;
    this->columns = 7;
    board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        board[i] = new char[this->columns];
        fill(board[i], board[i] + this->columns, '\0');
    }
    this->n_moves = 0;
}

template <typename T>
bool ConnectFourBoard<T>::update_board(int x ,int y, T symbol) {
    if (y < 0 || y >= this->columns) {
        return false;
    }

    for (int row = this->rows - 1; row >= 0; --row) {
        if (this->board[row][y] == 0) {
            this->board[row][y] = symbol;
            this->n_moves++;
            return true;
        }
    }

    return false;
}

template <typename T>
void ConnectFourBoard<T>::display_board() {
    cout << "\n   ";
    for (int j = 0; j < this->columns; j++) {
        // Display column coordinates
        cout << "  " << j << "   ";
    }cout << "\n";
    for (int i = 0; i < this->rows; i++) {
        // Display row coordinates
        cout << " " << i << " ";
        for (int j = 0; j < this->columns; j++) {
            cout << "  " << this->board[i][j] << "  ";
            if (j < this->columns - 1) cout << "|";
        }cout << "\n";
        if (i < this->rows - 1) {
            cout << "   "; // Align with row index
            for (int j = 0; j < this->columns; j++) {
                cout << "------";

             }
            cout << "\n";
        }
    }
    cout << endl;
}

template <typename T>
bool ConnectFourBoard<T>::check_winner(int row, int col) {
    const T symbol = board[row][col];
    if (symbol == 0) return false; // Skip empty cells

    // Horizontal check
    for (int c = max(0, col - 3); c <= min(col, this->columns - 4); ++c) {
        if (board[row][c] == symbol && board[row][c + 1] == symbol &&
            board[row][c + 2] == symbol && board[row][c + 3] == symbol) {
            return true;
        }
    }

    // Vertical check
    if (row <= this->rows - 4) {
        if (board[row][col] == symbol && board[row + 1][col] == symbol &&
            board[row + 2][col] == symbol && board[row + 3][col] == symbol) {
            return true;
        }
    }

    // Diagonal checks
    for (int d = -3; d <= 0; ++d) {
        // Bottom-left to top-right
        if (row + d >= 0 && row + d + 3 < this->rows &&
            col + d >= 0 && col + d + 3 < this->columns &&
            board[row + d][col + d] == symbol &&
            board[row + d + 1][col + d + 1] == symbol &&
            board[row + d + 2][col + d + 2] == symbol &&
            board[row + d + 3][col + d + 3] == symbol) {
            return true;
        }

        // Bottom-right to top-left
        if (row + d >= 0 && row + d + 3 < this->rows &&
            col - d >= 3 && col - d - 3 < this->columns &&
            board[row + d][col - d] == symbol &&
            board[row + d + 1][col - d - 1] == symbol &&
            board[row + d + 2][col - d - 2] == symbol &&
            board[row + d + 3][col - d - 3] == symbol) {
            return true;
        }
    }

    return false;
}

template <typename T>
bool ConnectFourBoard<T>::is_win() {
    for (int row = 0; row < this->rows; ++row) {
        for (int col = 0; col < this->columns; ++col) {
            if (board[row][col] != 0 && check_winner(row, col)) {
                return true;
            }
        }
    }
    return false;
}

template <typename T>
bool ConnectFourBoard<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

template <typename T>
bool ConnectFourBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

// Implementation for ConnectFourPlayer
template <typename T>
ConnectFourPlayer<T>::ConnectFourPlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void ConnectFourPlayer<T>::getmove(int& x, int& y) {
    while (true) {
        cout << "\nEnter your the number of columns you want from 0 to 6 :\n ";
        // Check if both y are integers
        if (cin >> y) {
            if (y <0)
            {
                cout << "Invalid input. Please enter a positive integer input.\n";
                cin >> y;
            }
            break;
        } else {
            cout << "Invalid input. Please enter a valid input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    x = 0;
}

// Implementation for ConnectFour_Random_Player
template <typename T>
ConnectFour_Random_Player<T>::ConnectFour_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    // number of columns
    this->dimension = 7;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void ConnectFour_Random_Player<T>::getmove(int& x, int& y) {
    x = 0;
    y = rand() % this->dimension;    // Random column between 0 and 6
}

#endif //FOURINROW_H
