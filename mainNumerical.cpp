#include <iostream>
#include "BoardGame_Classes.h"
#include "numricalTicTacToe.h"


using namespace std;

int main() {
    int choice;
    Player<int>* players[2];
    numboard<int>* B = new numboard<int>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI Numrical Tic Tac Toe Game. :)\n";

    // Set up player 1
    cout << "Enter Player 1 name: ";
    cin >> playerXName;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new numPlayer<int>(playerXName, 'X');
        break;
        case 2:
            players[0] = new numRandom_Player<int>('X');
        break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
        return 1;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new numPlayer<int>(player2Name, 'O');
        break;
        case 2:
            players[1] = new numRandom_Player<int>('O');
        break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
        return 1;
    }

    // Create the game manager and run the game
    GameManager<int> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}



