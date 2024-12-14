#include <iostream>
#include "BoardGame_Classes.h"
#include "5x5X_O.h"
#include "AI5X5.h"
//#include "5x5DesisionTree.h"

using namespace std;

int main() {
    int choice1 , choice2 ;
    //Array to hold to players
    Player<char>* players[2];
    // Initialize a 5x5 X-O board
    X_O_Board_5x5<char>* B = new X_O_Board_5x5<char>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
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
            players[0] = new X_O_Player_5x5<char>(playerXName, 'X');        //Human player X
            break;
        case 2:
            players[0] = new X_O_Random_Player_5x5<char>('X');             //Random computer player X
            break;
        // case 3:
        //     players[0] = new X_O_MinMax_Player<char>('X');       //AI player X
        //     players[0]->setBoard(B);
        //     break;
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
            players[1] = new X_O_Player_5x5<char>(player2Name, 'O');          //Human player O
            break;
        case 2:
            players[1] = new X_O_Random_Player_5x5<char>('O');               //Random computer player O
            break;
        // case 3:
        //     players[1] = new X_O_MinMax_Player<char>('O');        //AI player O
        //     players[1]->setBoard(B);
        //     break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    // Link the board to both players
    players[0]->setBoard(B);
    players[1]->setBoard(B);


    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();
    int player1score = B-> count_three_in_a_row('X');
    int player2score = B-> count_three_in_a_row('O');
    if(player1score>player2score){
        cout << "Player one wins\n";
    }else if(player2score>player1score){
        cout << "Player two wins\n";
    }else if(player1score==player2score){
        cout << "Draw!";
    }

    // Clean up dynamically allocated memory
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}