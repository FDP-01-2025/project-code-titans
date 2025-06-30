#ifndef CRAPS_GAME_H               // Avoid multiple inclusions of the same file
#define CRAPS_GAME_H               // Define macro to indicate it has been included

#include <string>                  // Include string to handle text
#include <iostream>                // For console input and output (cin, cout)
#include <cstdlib>                 // To generate random numbers with rand()
#include <cctype>                  // For character functions (tolower)
#include <limits>                  // To clean input buffer and handle limits
#ifdef _WIN32
#include <windows.h>               // On Windows, include windows.h for Sleep()
#endif
#include "utils.h"                 // Use functions like clearConsole and waitMs
#include "playerData.h"            // Use to register game and save balance
#include "player.h"                // Use Player structure with data and statistics

using namespace std;              // To avoid using std:: constantly

// Function that shows two dice in ASCII, dice 1 and dice 2
inline void showDiceASCII(int d1, int d2) {
    // Define dice faces as string arrays (5 lines per die)
    const char* diceFaces[6][5] = {
        {"+-------+", "|       |", "|   o   |", "|       |", "+-------+"},   // 1
        {"+-------+", "| o     |", "|       |", "|     o |", "+-------+"},   // 2
        {"+-------+", "| o     |", "|   o   |", "|     o |", "+-------+"},   // 3
        {"+-------+", "| o   o |", "|       |", "| o   o |", "+-------+"},   // 4
        {"+-------+", "| o   o |", "|   o   |", "| o   o |", "+-------+"},   // 5
        {"+-------+", "| o   o |", "| o   o |", "| o   o |", "+-------+"}    // 6
    };

    // Print line by line the two dice side by side
    for (int i = 0; i < 5; ++i) {
        cout << diceFaces[d1 - 1][i] << "   " << diceFaces[d2 - 1][i] << "\n";
    }
    cout << endl;
}

// Function that rolls dice with animation, showing several quick changes
inline int rollDiceAnimated() {
    int d1 = 1, d2 = 1;  // Initialize dice

    // Clear console depending on operating system
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    // Loop that simulates dice rolling (10 repetitions)
    for (int i = 0; i < 10; ++i) {
        d1 = rand() % 6 + 1;  // Generate random dice 1 between 1 and 6
        d2 = rand() % 6 + 1;  // Generate random dice 2 between 1 and 6

        // Clear console to animate dice
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "Rolling dice...\n\n";     // Message while "rolling" dice
        showDiceASCII(d1, d2);             // Show current dice
        waitMs(100);                       // Wait 100 ms for animated effect
    }

    cout << "Final result:\n\n";          // Message with final result
    showDiceASCII(d1, d2);                // Show final dice
    return d1 + d2;                       // Return sum of dice
}

// Function to validate difficulty level input (1 to 3)
inline int validateCrapsInput() {
    int choice = 0;  // Variable to store user selection
    cout << "Select your difficulty level: ";
    cin >> choice;   // Read input

    // While input is invalid (not number, not in range, or buffer not clean)
    while (cin.fail() || cin.peek() != '\n' || choice < 1 || choice > 3) {
        cin.clear();                       // Clear input error state
        cin.ignore(1000, '\n');            // Ignore what's left in buffer
        cout << "Please enter a number between 1 and 3: ";
        cin >> choice;  // Try to read again
    }
    return choice;  // Return valid option
}

// Function that executes Craps game logic according to maximum attempts allowed and bet
inline int executeCrapsGame(Player& player, int maxAttempts, int bet) {
    cout << "Starting initial roll...\n";    // Message start round
    waitMs(3000);                         // Wait 3 seconds

    int comeOutRoll = rollDiceAnimated(); // Perform animated initial roll
    cout << "The initial roll is: " << comeOutRoll << "\n";  // Show result
    waitMs(3000);                         // Wait 3 seconds

    // Immediate evaluation of initial roll according to Craps rules
    if (comeOutRoll == 2 || comeOutRoll == 3 || comeOutRoll == 12) {
        cout << "You lost! Craps!\n";  // Loss message if 2, 3 or 12 comes out
        registerGame("Craps", player.name, -bet, player.money - bet);  // Register loss
        player.gamesLost++;   // Increment lost games
        return -bet;          // Return loss
    }
    else if (comeOutRoll == 7 || comeOutRoll == 11) {
        cout << "Congratulations, you won!\n";  // Instant win message if 7 or 11 comes out
        registerGame("Craps", player.name, bet, player.money + bet);  // Register win
        player.gamesWon++;  // Increment won games
        return bet;         // Return win
    }
    else {
        int point = comeOutRoll;  // If other number, establish point
        cout << "Point established. Roll " << point << " to win, 7 to lose.\n";
        waitMs(3000);

        int attempts = 0;  // Counter of attempts made
        while (maxAttempts == 0 || attempts < maxAttempts) {
            attempts++;
            comeOutRoll = rollDiceAnimated();
            cout << "Attempt #" << attempts << endl;
            cout << "New roll is: " << comeOutRoll << "\n";
            waitMs(3000);

            if (comeOutRoll == point) {
                cout << "Congratulations, you won!\n";
                registerGame("Craps", player.name, bet, player.money + bet);
                player.gamesWon++;
                return bet;
            }
            else if (comeOutRoll == 7) {
                cout << "You lost the game.\n";
                registerGame("Craps", player.name, -bet, player.money - bet);
                player.gamesLost++;
                return -bet;
            }
        }

        // If attempts run out without winning or losing, player loses
        cout << "You ran out of attempts. You lost.\n";
        registerGame("Craps", player.name, -bet, player.money - bet);
        player.gamesLost++;
        return -bet;
    }
}

// Main function that controls the Craps game session for a player
inline void playCraps(Player& player) {
    if (player.money <= 0) {  // Check that they have money to bet
        cout << "You don't have enough balance. Deposit to play.\n";
        return;
    }

    char playAgain;
    do {
        clearConsole();
        int bet;
        cout << "\nYour current balance is $" << player.money << ". Enter your bet ($10 to $500, or 0 to cancel): $";

        while (true) {  // Validate bet
            cin >> bet;
            if (bet == 0) {
                cout << "Bet canceled.\n";
                return;
            }
            if (cin.fail() || bet < 10 || bet > 500) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid bet. Must be between $10 and $500. Enter your bet: $";
                continue;
            }
            if (bet > player.money) {
                cout << "Insufficient balance. Your current balance is $" << player.money << ". Enter your bet: $";
                continue;
            }
            break;
        }

        cout << "\nWelcome to Craps! Select difficulty level:\n";
        cout << "1. Easy (Unlimited attempts)\n2. Medium (5 attempts)\n3. Hard (3 attempts)\n";

        int selection = validateCrapsInput();
        player.gamesPlayed++;

        int result = 0;
        switch (selection) {
            case 1:
                cout << "Easy mode selected.\n";
                result = executeCrapsGame(player, 0, bet);
                break;
            case 2:
                cout << "Medium mode selected.\n";
                result = executeCrapsGame(player, 5, bet);
                break;
            case 3:
                cout << "Hard mode selected.\n";
                result = executeCrapsGame(player, 3, bet);
                break;
        }

        player.money += result;
        saveBalance(player.name, player.money);
        player.updateStats();

        cout << "Do you want to play again? (Y/N): ";
        cin >> playAgain;
        clearConsole();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (tolower(playAgain) == 'y');
}

#endif // CRAPS_GAME_H
