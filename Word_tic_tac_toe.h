#include "BoardGame_Classes.h"
#include <vector>
#include <unordered_set>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>

template <typename T>
class Word_tic_tac_Board : public Board<T> {

private:
    // Load words from "dic.txt"
    void load_dictionary();

    // To store valid words from dic.txt
    unordered_set<string> dictionary;

    // Check if a word is valid
    bool IsValidWord(const string& word);

public:
    Word_tic_tac_Board();
    bool update_board(int x, int y, T letter);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();


};



template <typename T>
class Word_tic_tac_Player : public Player<T> {
public:
    Word_tic_tac_Player (string name, T symbol) : Player<T>(name,symbol){};
    void getmove(int& x, int& y) ;
};



template <typename T>
class Word_tic_tac_Random_Player : public RandomPlayer<T>{
public:
    Word_tic_tac_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};


////////////////////////////////////////////////////////////////////////////////IMPLEMENTATION

// Constructor of Word_tic_tac_toe board
template <typename T>
Word_tic_tac_Board<T>::Word_tic_tac_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];

    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char [this->columns];
        for (int j = 0; j < this->columns; j++) {
            // Initialize as empty strings
            this->board[i][j] = '0';
        }
    }
    this->n_moves = 0;
    load_dictionary();
}


// Update the board with a letter
template <typename T>
bool Word_tic_tac_Board<T>::update_board(int x, int y, T mark) {

     //Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && this->board[x][y] == '0') {

        // Convert symbol to uppercase
        this->board[x][y] = toupper(mark);
        this->n_moves++;
        return true;

    }
    return false;
}

// Display the board
template <typename T>
void Word_tic_tac_Board<T>::display_board() {
    cout << " \nDisplay Word Tic Tac Toe Board\n";
    cout << "\n   ";
    for (int j = 0; j < this->columns; j++) {
        // Display column coordinates
        cout << "  " << j << "   ";
    }
    cout << "\n";

    for (int i = 0; i < this->rows; i++) {
        // Display row coordinates
        cout << " " << i << " ";
        for (int j = 0; j < this->columns; j++) {
            cout << "  " << this->board[i][j] << "  ";
            if (j < this->columns - 1) cout << "|";
        }
        cout << "\n";

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


// Load valid words into the dictionary
template <typename T>
void Word_tic_tac_Board<T>::load_dictionary() {
    ifstream file("dic.txt");

    if (!file) {
        cout << "File cannot be found. Ensure it exists in the same directory.\n";
        exit(1);
    }

    string word;
    while (file >> word) {
        if (!word.empty()) {
            dictionary.insert(word);
        }
    }
    file.close();
}


// Check if a word is valid
template <typename T>
bool Word_tic_tac_Board<T>::IsValidWord(const string& word) {
    for (const auto& Dicword : dictionary) {
        if (Dicword == word) {
            // Word found in the dictionary
            return true;
        }
    }
    return false;
}



// Check if there is a winner (valid word formed)
template <typename T>
bool Word_tic_tac_Board<T>::is_win() {
    // Check rows
    for (int i = 0; i < this->rows; ++i) {
        string RowWord = "";
        for (int j = 0; j < this->columns; ++j) {
            RowWord += this->board[i][j];
        }
        // Check the word and its reverse
        if (IsValidWord(RowWord) || IsValidWord(string(RowWord.rbegin(), RowWord.rend()))) {
            return true;
        }
    }



    // Check columns
    for (int j = 0; j < this->columns; ++j) {
        string ColumnsWord = "";
        for (int i = 0; i < this->rows; ++i) {
            ColumnsWord += this->board[i][j];
        }
        // Check the word and its reverse
        if (IsValidWord(ColumnsWord) || IsValidWord(string(ColumnsWord.rbegin(), ColumnsWord.rend()))) {
            return true;
        }
    }



    // Check main diagonal
    string MainDiagonal = "";
    for (int i = 0; i < this->rows; ++i) {
        MainDiagonal += this->board[i][i];
    }
    // Check the word and its reverse
    if (IsValidWord(MainDiagonal) || IsValidWord(string(MainDiagonal.rbegin(), MainDiagonal.rend()))) {
        return true;
    }



    // Check anti-diagonal
    string OffDiagonal = "";
    for (int i = 0; i < this->rows; ++i) {
        OffDiagonal += this->board[i][this->columns - i - 1];
    }
    // Check the word and its reverse
    if (IsValidWord(OffDiagonal) || IsValidWord(string(OffDiagonal.rbegin(), OffDiagonal.rend()))) {
        return true;
    }


    // No winning condition found
    return false;
}


// Check if the game is a draw (No winner)
template <typename T>
bool Word_tic_tac_Board<T>::is_draw() {
    return this->n_moves == 9 && !is_win();
}


// Check if the game is over
template <typename T>
bool Word_tic_tac_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//---------------------------------------------------------------------------- For the player

// Constructor for Word_tic_tac_Player
template <typename T>
void Word_tic_tac_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces:\n "
            "Please make sure that your inputs are positive integer numbers:\n";
    while (true)
    {
        // Validation for the input of moves
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


    while (true) {
        // Validation for the symbol that should be letter only
        cout << "Enter your character to place (a-z or A-Z):\n ";
        cin >> this->symbol;

        // Check if the input is a single alphabetic character
        if (isalpha(this->symbol)) {
            // Ensure the letter is uppercase
            this->symbol = toupper(this->symbol);
            break;
        } else {
            cout << "Invalid input. Please enter a valid letter from a-z or A-Z.\n";
        }
    }
}

//----------------------------------------------------------------------------For random player

// Constructor for Word_tic_tac_Random_Player
template <typename T>
Word_tic_tac_Random_Player<T>::Word_tic_tac_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Word_tic_tac_Random_Player<T>::getmove(int& x, int& y) {
    //Make random coordinates
    x = rand() % this->dimension;
    y = rand() % this->dimension;

    // Random uppercase letter (A-Z)
    this->symbol = 'A' + (rand() % 26);
}