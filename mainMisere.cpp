#include <iostream>
#include "BoardGame_Classes.h"
#include "Misere.h"
#include "MisereAI.h"
//#include "MisereDecisionTree.h"

using namespace std;

int main() {
    int choice1 , choice2 ;
    //Array to hold to players
    Player<char>* players[2];
    // Initialize a 3x3 X-O board
    Misere_Board<char>* B = new Misere_Board<char>();
    string playerXName, playerOName;

    cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player (X) name: ";
    cin >> playerXName;
    cout << "Choose Player (X) type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";

    while (true) {
        cin >> choice1;
        if (choice1 >= 1 && choice1 <= 3) {
            break;
        } else {
            cout << "Invalid choice. Please choose 1, 2, or 3: \n";
        }
    }

    switch(choice1) {
        case 1:
            players[0] = new Misere_Player<char>(playerXName, 'X');      //Human player X
            break;
        case 2:
            players[0] = new Misere_Random_Player<char>('X');           //Random player X
            break;
        case 3:
            
            players[0] = new inverse_MinMax_Player<char>('X');                  //AI player X
            players[0]->setBoard(B);
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    // Set up player 2
    cout << "Enter Player (O) name: ";
    cin >> playerOName;
    cout << "Choose Player (O) type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";

    while (true) {
        cin >> choice2;
        if (choice2 >= 1 && choice2 <= 3) {
            break;
        } else {
            cout << "Invalid choice. Please choose 1, 2, or 3: \n";
        }
    }

    switch(choice2) {
        case 1:
            players[1] = new Misere_Player<char>(playerOName, 'O');     //Human player O
            break;
        case 2:
            players[1] = new Misere_Random_Player<char>('O');          //Random computer O
            break;
        case 3:
            players[1] = new inverse_MinMax_Player<char>('O');                 //AI computer O
            players[1]->setBoard(B);
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up dynamically allocated memory
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}


