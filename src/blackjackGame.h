#ifndef BLACKJACK_GAME_H         
#define BLACKJACK_GAME_H          

#include <string>                 // I use strings to handle text in the game
#include <iostream>               // Use to print and read data via console (cout, cin)
#include <cstdlib>                // Use to generate random numbers with rand()
#include <cctype>                 // Use for character functions like tolower()
#include <limits>                 // Use to handle limits and clear buffer on inputs
#include "gameConstants.h"        // Use constants like NORMAL, MEDIUM and HARD for difficulty
#include "utils.h"                // Use helper functions like clearConsole()
#include "playerData.h"           // Use functions to register game and save balance
#include "player.h"              // I use the Player structure with its attributes and methods

using namespace std;             // To avoid writing std:: in every use

// Function to generate a random card according to Blackjack rules
inline int generateCard() {
    int card = rand() % 13 + 1;  // Generate a number between 1 and 13 (the cards)
    if (card > 10) return 10;    // The cards J, Q, K are worth 10
    if (card == 1) return 11;    // The Ace is worth 11 initially
    return card;                 // The other cards are worth their number
}

// Function to get a random suit for the card (♠ ♥ ♦ ♣)
inline string getRandomSuit() {
    string suits[] = {"♠", "♥", "♦", "♣"};  // Define the suits
    return suits[rand() % 4];               // Return one at random
}

// Function to convert the numeric value of the card to its textual representation
inline string adjustValue(int value) {
    if (value == 11) return "A";  // Ace
    if (value == 10) return "10"; // Ten
    if (value == 9) return "9";
    if (value == 8) return "8";
    if (value == 7) return "7";
    if (value == 6) return "6";
    if (value == 5) return "5";
    if (value == 4) return "4";
    if (value == 3) return "3";
    if (value == 2) return "2";
    return "?";                   // Unexpected case
}

// Function to display cards in ASCII format across multiple lines, visually
inline void showCardsASCII(int values[], string suits[], int count) {
    string lines[7];             // Seven lines to show the "card"
    for (int i = 0; i < count; i++) {  // For each card
        string value = adjustValue(values[i]);  // Get text of the value
        string left = value.length() == 1 ? value + " " : value;  // Adjust left alignment
        string right = value.length() == 1 ? " " + value : value;  // Adjust right alignment

        lines[0] += "┌─────────┐ ";                      // Top border
        lines[1] += "│" + left + "       │ ";           // Left value
        lines[2] += "│         │ ";                     // Empty space
        lines[3] += "│    " + suits[i] + "    │ ";      // Centered suit
        lines[4] += "│         │ ";                     // Empty space
        lines[5] += "│       " + right + "│ ";          // Right value
        lines[6] += "└─────────┘ ";                     // Bottom border
    }

    for (int i = 0; i < 7; i++) {       // Print the seven lines forming the cards
        cout << lines[i] << endl;
    }
}

// Function to calculate the current score of a set of cards,
// considering that aces can be worth 1 or 11 as needed
inline int calculateScore(int cards[], int numCards) {
    int sum = 0, aces = 0;        // Sum cards and count aces
    for (int i = 0; i < numCards; i++) {
        sum += cards[i];          // Add the value of each card
        if (cards[i] == 11) aces++;  // Count the aces that are worth 11
    }
    while (sum > 21 && aces > 0) { // If I exceed 21 and have aces
        sum -= 10;                 // Change one ace from 11 to 1 (subtract 10)
        aces--;                    // Count that ace as 1 now
    }
    return sum;                   // Return the adjusted score
}

// Function to play Blackjack
inline void playBlackjack(Player& player) {
    char playAgain;  // Variable to ask if the player wants to play again

    do {
        if (player.money <= 0) {  // Check if they have money to bet
            cout << "You have no money to play Blackjack.\n";  // Message if no balance
            return;                  // Exit the function because they cannot play
        }

        int bet;  // Variable for the player's bet
        cout << "Your current money is $" << player.money << ". Enter your bet (minimum $10, maximum $500): $";

        while (true) {  // Bet validation
            cin >> bet;  // Read the player's bet
            if (cin.fail() || bet < 10 || bet > 500 || bet > player.money) {  // Check limits and errors
                cin.clear();  // Clear the error state of cin
                cin.ignore(1000, '\n');  // Ignore input buffer
                cout << "Invalid bet. It must be between $10 and $500 and cannot exceed your current balance.\n";
                cout << "Your current money is $" << player.money << ". Enter your bet: $";
                continue;  // Ask for bet again
            }
            break;  // Exit the loop if the bet is valid
        }
        player.gamesPlayed++;  // Increment the games played counter

        int difficultyLevel;  // Variable for the difficulty the player will choose
        while (true) {  // Loop to ask and validate difficulty
            clearConsole();
            cout << "======================================\n";
            cout << "     Select the difficulty level\n";
            cout << "--------------------------------------\n";
            cout << "  1. Normal  (2 cards)\n";
            cout << "  2. Medium   (3 cards)\n";
            cout << "  3. Hard (4 cards)\n";
            cout << "======================================\n";
            cout << "Option: ";

            cin >> difficultyLevel;  // Read option

            if (!cin.fail() && difficultyLevel >= 1 && difficultyLevel <= 3) {  // If valid
                clearConsole();  // Clear screen for better presentation
                cout << "You have selected the ";
                if (difficultyLevel == 1) cout << "Normal level.\n";
                else if (difficultyLevel == 2) cout << "Medium level.\n";
                else cout << "Hard level.\n";
                break;  // Exit the loop
            }

            cin.clear();  // Clear input errors
            cin.ignore(1000, '\n');  // Ignore buffer
            clearConsole();  // Clear console
            cout << "Invalid input. Please enter a number from 1 to 3.\n\n";  // Error message
        }

        int initialCards = NORMAL + (difficultyLevel - 1);  // Calculate how many initial cards will be dealt based on difficulty

        int playerValues[10], dealerValues[10];  // Arrays to store values of player and dealer cards
        string playerSuits[10], dealerSuits[10];   // Arrays to store suits of player and dealer cards
        int numPlayer = 0, numDealer = 0;           // Counters for current cards of player and dealer

        // Deal initial cards to both player and dealer
        for (int i = 0; i < initialCards; i++) {
            playerValues[numPlayer] = generateCard();           // Generate card for player
            playerSuits[numPlayer++] = getRandomSuit();         // Generate suit for player

            dealerValues[numDealer] = generateCard();           // Generate card for dealer
            dealerSuits[numDealer++] = getRandomSuit();         // Generate suit for dealer
        }

        cout << "\nYour cards:\n";  // Show the player's cards
        showCardsASCII(playerValues, playerSuits, numPlayer);
        cout << "(Total: " << calculateScore(playerValues, numPlayer) << ")\n";  // Show score

        cout << "\nDealer's visible card:\n";  // Show only one card of the dealer (the visible one)
        showCardsASCII(dealerValues, dealerSuits, 1);

        char option;  // Variable for the player to decide if they want an extra card
        while (true) {
            int score = calculateScore(playerValues, numPlayer);  // Calculate current score of the player
            if (score > 21) {  // If they exceed 21, they lose immediately
                cout << "\nYou exceeded 21. You lost.\n";
                player.money -= bet;  // Subtract the bet from the balance
                registerGame("Blackjack", player.name, -bet, player.money);  // Record loss
                saveBalance(player.name, player.money);  // Save updated balance
                player.gamesLost++;  // Increment lost games
                player.updateStatistics();  // Update player statistics
                return;  // End the function (game finished)
            }

            cout << "\nDo you want another card? (y/n): ";  // Ask if they want an extra card
            cin >> option;
            if (tolower(option) != 'y') break;  // If not 'y', exit the loop

            playerValues[numPlayer] = generateCard();           // Add extra card
            playerSuits[numPlayer++] = getRandomSuit();

            cout << "\nYour cards:\n";  // Show updated cards
            showCardsASCII(playerValues, playerSuits, numPlayer);
            cout << "(Total: " << calculateScore(playerValues, numPlayer) << ")\n";  // Show new score
        }

        cout << "\nDealer's turn...\n";  // Now the dealer plays
        showCardsASCII(dealerValues, dealerSuits, numDealer);
        cout << "(Total: " << calculateScore(dealerValues, numDealer) << ")\n";

        // Dealer must take cards until reaching at least 17 points
        while (calculateScore(dealerValues, numDealer) < 17) {
            dealerValues[numDealer] = generateCard();          // Dealer takes card
            dealerSuits[numDealer++] = getRandomSuit();

            cout << "\nDealer takes a card:\n";  // Show updated dealer cards
            showCardsASCII(dealerValues, dealerSuits, numDealer);
            cout << "(Total: " << calculateScore(dealerValues, numDealer) << ")\n";
        }

        int playerScore = calculateScore(playerValues, numPlayer);  // Final player score
        int dealerScore = calculateScore(dealerValues, numDealer);   // Final dealer score

        // Determine final result by comparing scores
        if (dealerScore > 21 || playerScore > dealerScore) {  // If dealer exceeds or player wins
            cout << "\nYou won!\n";
            player.money += bet;  // Increase balance with the winning bet
            player.gamesWon++;  // Increment games won
            registerGame("Blackjack", player.name, bet, player.money);  // Record victory
        } else if (playerScore == dealerScore) {  // Tie
            cout << "\nIt's a tie. You neither win nor lose.\n";
            registerGame("Blackjack", player.name, 0, player.money);  // Record tie
            player.gamesTied++;  // Increment tie counter
        } else {  // Otherwise, player loses
            cout << "\nYou lost.\n";
            player.money -= bet;  // Subtract bet
            registerGame("Blackjack", player.name, -bet, player.money);  // Record loss
            player.gamesLost++;  // Increment lost games
        }

        saveBalance(player.name, player.money);  // Save updated balance at the end
        player.updateStatistics();  // Update internal player statistics

        // Ask if they want to play again
        cout << "\nDo you want to play Blackjack again? (y/n): ";
        cin >> playAgain;
        
    } while (tolower(playAgain) == 'y');
}

#endif // BLACKJACK_GAME_H  
