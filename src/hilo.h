#ifndef HILO_GAME_H                 // Start of include guard to prevent multiple inclusions
#define HILO_GAME_H                 // Macro to indicate that this file has been included

#include <iostream>                 // For standard input/output (cout, cin)
#include <string>                   // For handling strings
#include <algorithm>                // For useful functions like std::transform
#include <ctime>                    // For time-related functions (random seed)
#include <cstdlib>                  // For rand(), system() functions
#include <fstream>                  // For file handling (ifstream, ofstream)
#include <limits>                   // For numeric_limits (to clear input buffer)
#include "player.h"                // Include Player structure
#include "utils.h"                  // For functions like toLower, clearConsole, waitMs
#include "playerData.h"             // For functions registerGame, saveBalance

using namespace std;                // Avoid writing std:: all the time

// Auxiliary functions for the Hi-Lo game

// Generate a random number between 1 and 13 representing the value of a card
inline int RandomCard() {
    return rand() % 13 + 1;         // Value between 1 (Ace) and 13 (King)
}

// Generate a random suit from four possible suits
inline string RandomSuit() {
    string suit[] = {"♠", "♥", "♦", "♣"};  // Common suits in cards
    return suit[rand() % 4];         // Random selection
}

// Change the numeric value of the card to its textual representation (A, J, Q, K)
inline string CardValue(int value) {
    if (value == 1) return "A";     // Ace
    if (value == 11) return "J";    // Jack
    if (value == 12) return "Q";    // Queen
    if (value == 13) return "K";    // King
    return to_string(value);         // For cards 2 to 10, convert to string directly
}

// Draw the card(s) in ASCII to show the player visually
inline void AsciiHiloCards(int value[], string suit[], int count) {
    string line[7];                  // 7 lines for the ASCII card
    for (int i = 0; i < count; i++) {
        string value2 = CardValue(value[i]);              // Get the textual value
        string left = value2.length() == 1 ? value2 + " " : value2;   // Format for left
        string right = value2.length() == 1 ? " " + value2 : value2;   // Format for right

        // Draw each line of the card and accumulate it
        line[0] += "┌─────────┐ ";
        line[1] += "│" + left + "       │ ";
        line[2] += "│         │ ";
        line[3] += "│    " + suit[i] + "    │ ";
        line[4] += "│         │ ";
        line[5] += "│       " + right + "│ ";
        line[6] += "└─────────┘ ";
    }

    // Print all accumulated lines for all cards
    for (int i = 0; i < 7; i++) {
        cout << line[i] << endl;
    }
}

// Main logic of a round of the Hi-Lo game
inline void hilo(Player& player, int& bet) {  // Receives reference to player and bet (by reference to modify)
    int card = RandomCard();                     // Generate the first random card
    char guess, going;                           // Variables to store choice and continue game
    bool keep = true;                            // Controls if the round continues or ends
    string suit1 = RandomSuit();                 // Generate the suit of the initial card

    // Show the first card to the player
    cout << "The first card is: \n";
    int values1[] = {card};
    string suits1[] = {suit1};
    AsciiHiloCards(values1, suits1, 1);          // Draw the card
    cout << "\n";

    while (keep == true) {                        // While the player decides to continue
        // Generate the next random card
        int card2 = RandomCard();
        string suit2 = RandomSuit();

        // Ask the player to guess if the next card will be higher or lower
        while (true) {
            cout << "The next card will be Higher (M) or Lower (L): ";
            cin >> guess;
            if (guess == 'M' || guess == 'm' || guess == 'L' || guess == 'l') break;  // Accept M/m and L/l (higher/lower)
            cout << "Invalid option, please select 'M' or 'm'\n";
        }

        // Show the next card
        cout << "---------------------------------------------------\n";
        cout << "The next card is: \n";
        int values2[] = {card2};
        string suits2[] = {suit2};
        AsciiHiloCards(values2, suits2, 1);
        cout << endl;

        // Check if the player guessed correctly
        if (((guess == 'M' || guess == 'm') && card < card2) ||       // Guessed higher and it is higher
            ((guess == 'L' || guess == 'l') && card > card2)) {       // Guessed lower and it is lower
            card = card2;                                              // Update the current card
            bet = bet * 2;                                             // Double the bet
            cout << "Congratulations, you won this round!\n";

            // Ask if they want to keep playing
            while (true) {
                cout << "Do you want to keep playing? (Y/N): ";
                cin >> going;
                if (going == 'S' || going == 's' || going == 'N' || going == 'n') break;
                cout << "Invalid option, please select 'S' or 'N'\n";
            }

            // If they don't want to continue, end and pay the winnings
            if (going == 'N' || going == 'n') {
                player.money += bet;                                 // Add winnings to balance
                cout << "Thank you for playing. Your winnings are: $" << bet << endl;
                player.gamesWon++;                             // Update statistics
                registerGame("Hi-Lo", player.name, bet, player.money); // Record game
                keep = false;                                          // End the round
            }

        } else if (card == card2) {                                    // Tie: the cards are equal
            cout << "It was a tie!\n";
            cout << "No one loses, no one wins.\n";

            // Ask if they want to keep playing in a tie
            while (true) {
                cout << "Do you want to keep playing? (Y/N): ";
                cin >> going;
                if (going == 'S' || going == 's' || going == 'N' || going == 'n') break;
                cout << "Invalid option, please select 'S' or 'N'\n";
            }

            // If they don't want to continue, return the bet
            if (going == 'N' || going == 'n') {
                player.money += bet;                                 // Return the bet
                cout << "Thank you for playing. Your returned bet is: $" << bet << endl;
                player.gamesTied++;                           // Update statistics
                registerGame("Hi-Lo", player.name, 0, player.money); // Record game with 0 winnings
                keep = false;                                          // End the round
            }
        }
        // If guessed wrong, lose the bet and end the round
        else {
            cout << "Incorrect! You lost your bet.\n";
            player.money -= bet;                                     // Subtract the bet from balance
            player.gamesLost++;                                // Update statistics
            registerGame("Hi-Lo", player.name, -bet, player.money); // Record game with loss
            bet = 0;                                                  // The bet is set to 0 (lost)
            keep = false;                                             // End the round
        }
        // After each round, save the balance and update statistics
        saveBalance(player.name, player.money);
        player.updateStatistics();
    }
}

// Function that confirms if the bet is valid and starts the game
inline void BetConfirm(Player& player, int& bet) {
    cout << "Your current money is $" << player.money << ". Enter your bet (minimum $10, maximum $500): $";

    while (true) {
        cin >> bet;
        // Check that the bet is valid, not greater than balance, and not less than 10 or greater than 500
        if (cin.fail() || bet < 10 || bet > 500 || bet > player.money) {
            cin.clear();                                           // Clear input error
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear buffer
            cout << "Invalid bet. It must be between $10 and $500 and cannot exceed your current balance.\n";
            cout << "Your current money is $" << player.money << ". Enter your bet: $";
            continue;                                             // Ask for the bet again
        }
        break;                                                    // Exit the loop if it's valid
    }
    player.gamesPlayed++;                                  // Increment games played
    hilo(player, bet);                                         // Start the game with validated bet
}

// Main menu of the Hi-Lo game
inline void playHilo(Player& player) {
    if (player.money <= 0) {                                  // Check if they have balance
        cout << "You do not have enough balance. Deposit to play.\n";
        return;                                                 // Exit if no balance
    }

    int bet = 0;                                                // Initialize bet
    int option;                                                 // Menu option

    do {
        // Show menu options
        cout << "\n---- Welcome to the HI-LO game! ----\n";
        cout << "1. Game explanation \n";
        cout << "2. Play \n";
        cout << "3. Check your balance \n";
        cout << "4. Exit \n";
        cout << "Choose an option: ";
        cin >> option;

        if (cin.fail()) {                                       // Handle invalid input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid option. Please enter a number.\n";
            continue;
        }

        // Execute action based on the option
        switch (option) {
            case 1:
                // Clear explanation of the game
                clearConsole();
                cout << "\nWelcome to the HI-LO game!\n\n";
                cout << "This is super easy to play!\n\n";
                cout << "1. First, make your bet.\n";
                cout << "2. The dealer shows you a card.\n";
                cout << "3. Now it's your turn to guess -> Will the next card be higher or lower?\n\n";
                cout << "If you guess correctly:\n";
                cout << "- You recover your doubled bet.\n";
                cout << "- You can keep playing to try to win even more, or cash out and take your reward.\n\n";
                cout << "If you guess incorrectly:\n";
                cout << "- You lose your bet.\n\n";
                break;
            case 2:
                clearConsole();
                // Start the game logic with the validated bet
                BetConfirm(player, bet);
                break;
            case 3:
                clearConsole();
                // Show current balance
                cout << "Your current balance is: $" << player.money << endl;
                break;
            case 4:
                clearConsole();
                cout << "Returning to the main menu... \n";
                break;
            default:
                cout << "Invalid option \n";
                break;
        }
    } while (option != 4);                                       // Repeat until they choose to exit
}

#endif // HILO_GAME_H
