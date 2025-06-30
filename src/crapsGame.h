#ifndef CRAPS_GAME_H               
#define CRAPS_GAME_H               

#include <string>                  // Include string to handle text
#include <iostream>                // For input and output via console (cin, cout)
#include <cstdlib>                 // To generate random numbers with rand()
#include <cctype>                  // For character functions (tolower)
#include <limits>                  // To clear input buffer and handle limits
#ifdef _WIN32
#include <windows.h>               // On Windows, include windows.h for Sleep()
#endif
#include "utils.h"                 // Use functions like clearConsole and waitMs
#include "playerData.h"            // Use to register game and save balance
#include "player.h"               // Use Player structure with data and statistics

using namespace std;              // To avoid using std:: constantly

// Function that displays two dice in ASCII, die 1 and die 2
inline void showDiceASCII(int d1, int d2) {
    // Define the faces of the dice as arrays of strings (5 lines per die)
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

    // Clear the console depending on the operating system
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    // Loop that simulates dice spinning (10 repetitions)
    for (int i = 0; i < 10; ++i) {
        d1 = rand() % 6 + 1;  // Generate random die 1 between 1 and 6
        d2 = rand() % 6 + 1;  // Generate random die 2 between 1 and 6

        // Clear console to animate dice
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "Rolling dice...\n\n";  // Message while "rolling" the dice
        showDiceASCII(d1, d2);         // Show the current dice
        waitMs(100);                   // Wait 100 ms for animation effect
    }

    cout << "Final result:\n\n";      // Message with the final result
    showDiceASCII(d1, d2);           // Show the final dice
    return d1 + d2;                  // Return the sum of the dice
}

// Function to validate the input of the difficulty level (1 to 3)
inline int validateCrapsInput() {
    int choice = 0;  // Variable to store the user's selection
    cout << "Select your difficulty level: ";
    cin >> choice;   // Read input

    // While the input is invalid (not a number, not in range, or buffer not cleared)
    while (cin.fail() || cin.peek() != '\n' || choice < 1 || choice > 3) {
        cin.clear();                       // Clear input error state
        cin.ignore(1000, '\n');            // Ignore what remains in the buffer
        // Show message in a decorative box indicating the error and how to correct it
        cout << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                                                                                                      ║\n";
        cout << "║                                            ♠ ♥ Message ♥ ♣                                           ║\n";
        cout << "║                                                                                                      ║\n";
        cout << "║           Please do not enter letters or special characters, only numbers between 1 and 3            ║\n";
        cout << "║                                                                                                      ║\n";
        cout << "║                     Select your difficulty level:                                               ║\n";
        cout << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";
        cin >> choice;  // Try to read again
    }
    return choice;  // Return the valid option
}

// Function that executes the logic of the Craps game according to the allowed maximum attempts and the bet
inline int executeCrapsGame(Player& player, int maxAttempts, int bet) {
    cout << "Starting initial roll...\n";  // Message to start round
    waitMs(3000);                         // Wait 3 seconds

    int comeOutRoll = rollDiceAnimated(); // Perform animated initial roll
    cout << "The initial roll is: " << comeOutRoll << "\n";  // Show result
    waitMs(3000);                         // Wait 3 seconds

    // Immediate evaluation of the initial roll according to Craps rules
    if (comeOutRoll == 2 || comeOutRoll == 3 || comeOutRoll == 12) {
        // Loss message if Craps (2, 3, or 12) comes out
        cout << "╔═══════════════════════════════════════════════════╗\n";
        cout << "║                 ♠ ♥ You Lost ♥ ♣               ║\n";
        cout << "║                                                   ║\n";
        cout << "║           Craps! You lost the game.           ║\n";
        cout << "║                                                   ║\n";
        cout << "╚═══════════════════════════════════════════════════╝\n";
        registerGame("Craps", player.name, -bet, player.money - bet);  // Record loss
        player.gamesLost++;   // Increment lost games
        return -bet;          // Return loss
    }
    else if (comeOutRoll == 7 || comeOutRoll == 11) {
        // Instant win message if 7 or 11 comes out
        cout << "╔═══════════════════════════════════════════════╗\n";
        cout << "║                 ♠ ♥ You Won ♥ ♣            ║\n";
        cout << "║                                               ║\n";
        cout << "║     Congratulations, you won the round!        ║\n";
        cout << "║                                               ║\n";
        cout << "╚═══════════════════════════════════════════════╝\n";
        registerGame("Craps", player.name, bet, player.money + bet);  // Record win
        player.gamesWon++;  // Increment won games
        return bet;         // Return win
    }
    else {
        // If another number comes out, a point is established for the next round
        int point = comeOutRoll;
        cout << "╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                                                                                                             ║\n";
        cout << "║                                            ♠ ♥ Message ♥ ♣                                                  ║\n";
        cout << "║                                                                                                             ║\n";
        cout << "║                              The point is established, the shooter will roll again...                      ║\n";
        cout << "║                                                                                                             ║\n";
        cout << "║                                                                                                             ║\n";
        cout << "║                      If the roll is: " << comeOutRoll << ", the shooter wins; if it's 7, the shooter loses                      ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";
        waitMs(3000);  // Wait 3 seconds for suspense

        int attempts = 0;  // Counter for attempts made
        while (maxAttempts == 0 || attempts < maxAttempts) {  // Loop if unlimited attempts or less than maximum
            attempts++;  // Increment attempt
            comeOutRoll = rollDiceAnimated();  // New animated roll
            cout << "Attempt #" << attempts << endl;
            cout << "The new roll is: " << comeOutRoll << "\n";  // Show result
            waitMs(3000);

            if (comeOutRoll == point) {  // If the point comes out, the player wins
                cout << "╔═════════════════════════════════════════════════════╗\n";
                cout << "║                    ♠ ♥ You Won ♥ ♣               ║\n";
                cout << "║                                                     ║\n";
                cout << "║                Congratulations, you won!            ║\n";
                cout << "║                                                     ║\n";
                cout << "╚═════════════════════════════════════════════════════╝\n";
                registerGame("Craps", player.name, bet, player.money + bet);
                player.gamesWon++;
                return bet;
            }
            else if (comeOutRoll == 7) {  // If 7 comes out, the player loses
                cout << "╔═════════════════════════════════════════════════════╗\n";
                cout << "║                   ♠ ♥ You Lost ♥ ♣               ║\n";
                cout << "║                                                     ║\n";
                cout << "║               Sorry, you lost the game.      ║\n";
                cout << "║                                                     ║\n";
                cout << "╚═════════════════════════════════════════════════════╝\n";
                registerGame("Craps", player.name, -bet, player.money - bet);
                player.gamesLost++;
                return -bet;
            }
        }

        // If attempts run out without winning or losing, the player loses due to limit of attempts
        cout << "╔═══════════════════════════════════════════════════╗\n";
        cout << "║                  ♠ ♥ Message ♥ ♣                  ║\n";
        cout << "║                                                   ║\n";
        cout << "║       Sorry, you have run out of attempts.     ║\n";
        cout << "║                                                   ║\n";
        cout << "╚═══════════════════════════════════════════════════╝\n";
        registerGame("Craps", player.name, -bet, player.money - bet);
        player.gamesLost++;
        return -bet;
    }
}

// Main function that controls the Craps game session for a player
inline void playCraps(Player& player) {
    if (player.money <= 0) {  // Check if they have money to bet
        cout << "You do not have enough balance. Deposit to play.\n";  // Message if no balance
        return;
    }

    char playAgain;  // Variable to control if they play another round
    do {
        clearConsole();
        int bet;  // Variable for bet
        cout << "\nYour current money is $" << player.money << ". Enter your bet (minimum $10, maximum $500): $";

        while (true) {  // Loop to validate bet
            cin >> bet;
            if (bet == 0) {  // If they enter 0, cancel bet
                cout << "Bet canceled.\n";
                return;
            }
            if (cin.fail() || bet < 10 || bet > 500) {  // Validate range and input
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid bet. It must be between $10 and $500.\n";
                cout << "Enter your bet: $";
                continue;
            }
            if (bet > player.money) {  // Validate sufficient balance
                cout << "Insufficient balance. Your current balance is $" << player.money << ".\n";
                cout << "Enter your bet: $";
                continue;
            }
            break;  // Exit the loop if the bet is valid
        }

        // Show welcome menu with levels to select
        cout << "\n╔═══════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                       ♠ ♥ Welcome to Craps ♥ ♣                      ║\n";
        cout << "║                                                                       ║\n";
        cout << "║          Select the difficulty level to start:                      ║\n";
        cout << "║                                                                       ║\n";
        cout << "║                  1. Easy     ♣     2. Medium     ♦                    ║\n";
        cout << "║                            3. Hard       ♠                         ║\n";
        cout << "║                                                                       ║\n";
        cout << "╚═══════════════════════════════════════════════════════════════════════╝\n";

        int selection = validateCrapsInput();  // Ask and validate difficulty level

        player.gamesPlayed++;  // Increment games played

        int result = 0;          // Variable for game result
        switch (selection) {        // Depending on level, execute with different number of attempts
            case 1:
                cout << "You have selected the easy level (unlimited attempts)\n";
                result = executeCrapsGame(player, 0, bet);  // 0 = unlimited attempts
                break;
            case 2:
                cout << "You have selected the medium level (5 attempts)\n";
                result = executeCrapsGame(player, 5, bet);
                break;
            case 3:
                cout << "You have selected the hard level (3 attempts)\n";
                result = executeCrapsGame(player, 3, bet);
                break;
        }

        player.money += result;       // Update money according to result
        saveBalance(player.name, player.money);  // Save balance to file
        player.updateStatistics();  // Update internal statistics

        cout << "╔═══════════════════════════════════════════════════╗\n";
        cout << "║                Do you want to keep playing?             ║\n";
        cout << "║                                                   ║\n";
        cout << "║   Yes (Y)                               No (N)     ║\n";
        cout << "║                                                   ║\n";
        cout << "╚═══════════════════════════════════════════════════╝\n";

        cin >> playAgain;
        clearConsole();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear buffer to avoid errors

    } while (tolower(playAgain) == 'y');  // Repeat while they answer 'y'
}

#endif // CRAPS_GAME_H  
