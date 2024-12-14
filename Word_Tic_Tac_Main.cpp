#include <iostream>
#include "BoardGame_Classes.h"
#include "Word_tic_tac_toe.h"
#include <limits>
using namespace std;

// Function to check valid integer input
bool getValidInput(int& choice) {
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false; // Invalid input
    }
    return true; // Valid input
}

int main() {
    int choice;
    Player<char> *players[2];
    Word_tic_tac_Board<char> *B = new Word_tic_tac_Board<char>();
    string player1Name, player2Name;

    cout << "Welcome to Word Tic Tac Toe Game! \n";

    // Set up player 1
    cout << "Enter Player1 name: ";
    cin >> player1Name;

    // Loop to ensure valid choice for Player1
    do {
        cout << "Choose Player1 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "3. Smart Computer (AI)\n";

        if (!getValidInput(choice)) {
            cout << "Invalid input! Please enter a number between 1 and 3.\n";
            continue;
        }

        if (choice == 1) {

            players[0] = new Word_tic_tac_Player<char>(player1Name, 'X');
            break;  // Exit the loop if a valid choice is made

        } else if (choice == 2) {

            players[0] = new Word_tic_tac_Random_Player<char>('X');
            break;  // Exit the loop if a valid choice is made

        } else {
            cout << "Invalid choice for Player 1. Please choose again.\n";
        }
    } while (true);  // Repeat until a valid choice is made

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;

    // Loop to ensure valid choice for Player2
    do {
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "3. Smart Computer (AI)\n";

        if (!getValidInput(choice)) {
            cout << "Invalid input! Please enter a number between 1 and 3.\n";
            continue; // If input is invalid, ask again
        }

        if (choice == 1) {

            players[1] = new Word_tic_tac_Player<char>(player2Name, 'O');
            break;  // Exit the loop if a valid choice is made

        } else if (choice == 2) {

            players[1] = new Word_tic_tac_Random_Player<char>('O');
            break;  // Exit the loop if a valid choice is made


        } else {
            cout << "Invalid choice for Player 2. Please choose again.\n";
        }
    } while (true);  // Repeat until a valid choice is made

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;


}