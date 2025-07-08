#ifndef BLACKJACK_GAME_H
#define BLACKJACK_GAME_H

#include <string>          // I use strings to handle text in the game
#include <iostream>        // Use to print and read data via console (cout, cin)
#include <cstdlib>         // Use to generate random numbers with rand()
#include <cctype>          // Use for character functions like tolower()
#include <limits>          // Use to handle limits and clear buffer on inputs
#include "gameConstants.h" // Use constants like NORMAL, MEDIUM and HARD for difficulty
#include "utils.h"         // Use helper functions like clearConsole()
#include "playerData.h"    // Use functions to register game and save balance
#include "player.h"        // I use the Player structure with its attributes and methods

using namespace std; // To avoid writing std:: in every use

// Function to generate a random card according to Blackjack rules
inline int generateCard()
{
    return rand() % 13 + 1; // Generate a number between 1 and 13 (1: Ace, 11: J, 12: Q, 13: K)
}

// Function to get a random suit for the card (♠ ♥ ♦ ♣)
inline string getRandomSuit()
{
    string suits[] = {"♠", "♥", "♦", "♣"}; // Define the suits
    return suits[rand() % 4];              // Return one at random
}

// Function to convert the numeric value of the card to its textual representation
inline string adjustValue(int value)
{
    // I convert the numeric card value to its textual representation
    if (value == 1)
        return "A"; // Ace is represented as "A"
    if (value == 11)
        return "J"; // Jack as "J"
    if (value == 12)
        return "Q"; // Queen as "Q"
    if (value == 13)
        return "K";          // King as "K"
    return to_string(value); // Numbers 2 to 10 converted normally
}

// Modified function to display cards in ASCII format with option to hide values
inline void showCardsASCII(int values[], string suits[], int count, bool showAll = true)
{
    string lines[7]; // I prepare 7 lines to build each "card" in ASCII

    for (int i = 0; i < count; i++)
    {
        string value = adjustValue(values[i]);                    // I convert the number to text
        string left = value.length() == 1 ? value + " " : value;  // Align left
        string right = value.length() == 1 ? " " + value : value; // Align right

        // Here I set the color of the value depending on the card:
        string colorValue;

        if (values[i] == 1)
            colorValue = "\033[34m"; // Blue for Ace
        else if (values[i] == 11)
            colorValue = "\033[36m"; // Cyan for Jack
        else if (values[i] == 12)
            colorValue = "\033[35m"; // Magenta for Queen
        else if (values[i] == 13)
            colorValue = "\033[33m"; // Yellow (gold) for King
        else
            colorValue = "\033[37m"; // White for normal numbers

        string colorSuit = (suits[i] == "♥" || suits[i] == "♦") ? "\033[31m" : "\033[37m";

        // I build each line of the card in the lines array
        lines[0] += "┌─────────┐ "; // Top border

        if (showAll || i == 0)
        {                                                              // Show all cards or only first card if hiding
            lines[1] += "│" + colorValue + left + "\033[0m       │ ";  // Left value with color
            lines[5] += "│       " + colorValue + right + "\033[0m│ "; // Right value with color
        }
        else
        {
            lines[1] += "│  ???    │ ";  // Hidden card value
            lines[5] += "│       ???│ "; // Hidden card value
        }

        lines[2] += "│         │ ";                                   // Empty space
        lines[3] += "│    " + colorSuit + suits[i] + "\033[0m    │ "; // Centered suit with color (always visible)
        lines[4] += "│         │ ";                                   // Empty space
        lines[6] += "└─────────┘ ";                                   // Bottom border for each card
    }

    // Finally I print all the lines to display the full cards
    for (int i = 0; i < 7; i++)
    {
        cout << lines[i] << endl;
    }
}

// Function to calculate the current score of a set of cards,
// considering that aces can be worth 1 or 11 as needed
inline int calculateScore(int cards[], int numCards)
{
    int sum = 0, aces = 0; // I start the sum and count the aces
    for (int i = 0; i < numCards; i++)
    {
        // I add the value of each card
        if (cards[i] >= 11 && cards[i] <= 13)
        {
            sum += 10; // Face cards (J, Q, K) count as 10
        }
        else if (cards[i] == 1)
        {
            sum += 11; // Ace counts as 11 initially
            aces++;    // I count this ace for possible adjustment
        }
        else
        {
            sum += cards[i]; // Others count as their numeric value
        }
    }
    // If I exceed 21 and have aces, I convert them from 11 to 1 by subtracting 10 each time
    while (sum > 21 && aces > 0)
    {
        sum -= 10; // I change one ace from 11 to 1 by subtracting 10
        aces--;    // I already counted one ace as 1
    }
    return sum; // I return the adjusted score
}

bool playHandFunction(Player &player, int values[], string suits[], int &numCards, int currentBet)
{
    char option;
    bool busted = false;

    while (true)
    {
        int score = calculateScore(values, numCards);

        if (score > 21)
        {
            cout << "\n\033[31mYou exceeded 21. You lost this hand.\033[0m\n";
            player.money -= currentBet;
            player.gamesLost++;
            registerGame("Blackjack", player.name, -currentBet, player.money);
            saveBalance(player.name, player.money);
            player.updateStatistics();
            busted = true;
            break;
        }

        cout << "\n\033[33mDo you want another card? (y/n): \033[0m";
        while (true)
        {
            cin >> option;
            option = tolower(option);
            if (option == 'y' || option == 'n')
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            cout << "\033[31mInvalid input. Please enter 'y' or 'n': \033[0m";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (option != 'y')
            break;

        if (numCards >= 10)
        {
            cout << "\033[31mYou cannot draw more cards, maximum reached.\033[0m\n";
            cout << "Press Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
        }

        values[numCards] = generateCard();
        suits[numCards++] = getRandomSuit();

        cout << "\nYour cards:\n";
        showCardsASCII(values, suits, numCards);
        cout << "\033[34m(Total: " << calculateScore(values, numCards) << ")\033[0m\n";
    }

    return busted;
}

inline void playBlackjack(Player &player)
{
    const int MAX_CARDS = 10; // Maximum cards a player or dealer can have
    char playAgain;           // Variable to ask if the player wants to play again

    do
    {
        if (player.money <= 0)
        {                                                                      // Check if they have money to bet
            cout << "\n\033[31mYou have no money to play Blackjack.\033[0m\n"; // Message if no balance
            return;                                                            // Exit the function because they cannot play
            cout << "Press Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }

        clearConsole();
        cout << "\033[33m\n======================================\n\033[0m";
        cout << "\033[33m     WELCOME TO BLACKJACK!\n\033[0m";
        cout << "\033[33m======================================\n\033[0m";
        cout << "Your current money: \033[32m$" << player.money << "\033[0m\n";

        int bet; // Variable for the player's bet
        cout << "Enter your bet (minimum $10, maximum $500): $";

        // Improved bet validation loop with better error handling
        while (true)
        {
            cin >> bet;

            // Clear any error flags and discard bad input
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\033[31mInvalid input. Please enter a number between 10 and 500: $\033[0m ";
                continue;
            }

            if (bet < 10 || bet > 500)
            {
                cout << "\033[31mBet must be between $10 and $500. Try again: $\033[0m ";
                continue;
            }

            if (bet > player.money)
            {
                cout << "\033[31mYou don't have enough money. Your balance: $" << player.money
                     << ". Enter a valid amount: $\033[0m ";
                continue;
            }

            break; // Exit the loop if the bet is valid
        }

        player.gamesPlayed++; // Increment the games played counter

        int difficultyLevel; // Variable for the difficulty the player will choose
        while (true)
        { // Loop to ask and validate difficulty
            cout << "Press Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            clearConsole();
            cout << "\033[33m" << "\n======================================\n"
                 << "\033[0m";
            cout << "\033[33m     Select the difficulty level\n\033[0m";
            cout << "\033[33m--------------------------------------\n\033[0m";
            cout << "  1. Normal  (2 cards)\n";
            cout << "  2. Medium  (3 cards)\n";
            cout << "  3. Hard    (4 cards)\n";
            cout << "  4. Exit\n";
            cout << "\033[33m" << "======================================\n"
                 << "\033[0m";
            cout << "Option: ";

            cin >> difficultyLevel;

            if (!cin.fail() && difficultyLevel >= 1 && difficultyLevel <= 4)
            { // If valid
                if (difficultyLevel == 4)
                {
                    cout << "\n\033[36mYou chose to exit the Blackjack table. See you next time!\033[0m\n";
                    return;
                }
                clearConsole(); // Clear screen for better presentation
                cout << "You have selected the ";
                if (difficultyLevel == 1)
                    cout << "\033[34m" << "Normal level.\n"
                         << "\033[0m";
                else if (difficultyLevel == 2)
                    cout << "\033[33m" << "Medium level.\n"
                         << "\033[0m";
                else
                    cout << "\033[31m" << "Hard level.\n"
                         << "\033[0m";
                break; // Exit the loop
            }

            cin.clear();                                         // Clear input errors
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Improved buffer clearing
            cout << "\033[31mInvalid input. Please enter a number from 1 to 3.\033[0m\n";
        }

        int initialCards = 2 + (difficultyLevel - 1); // Calculate how many initial cards will be dealt based on difficulty

        int playerValues[MAX_CARDS], dealerValues[MAX_CARDS];  // Arrays to store values of player and dealer cards
        string playerSuits[MAX_CARDS], dealerSuits[MAX_CARDS]; // Arrays to store suits of player and dealer cards
        int numPlayer = 0, numDealer = 0;                      // Counters for current cards of player and dealer

        // Deal initial cards to both player and dealer
        for (int i = 0; i < initialCards; i++)
        {
            if (numPlayer < MAX_CARDS)
            {
                playerValues[numPlayer] = generateCard();   // I generate a card value for the player
                playerSuits[numPlayer++] = getRandomSuit(); // I assign a random suit for that card
            }
            if (numDealer < MAX_CARDS)
            {
                dealerValues[numDealer] = generateCard();   // I generate a card value for the dealer
                dealerSuits[numDealer++] = getRandomSuit(); // I assign a random suit for that card
            }
        }

        // After dealing the cards, I show my cards immediately so I can see what I got
        cout << "\n\033[34mYour cards:\033[0m\n";
        showCardsASCII(playerValues, playerSuits, numPlayer); // I display my own cards in colorful ASCII
        cout << "\033[34m(Total: " << calculateScore(playerValues, numPlayer) << ")\033[0m\n";
        // I calculate the initial score based on the player's starting cards
        int initialScore = calculateScore(playerValues, numPlayer);

        // If the score is already over 21 at the start, the player automatically loses
        if (initialScore > 21)
        {
            // I inform the player that they went over 21 and lost right away
            cout << "\n\033[31mYou exceeded 21 with your initial cards. You lost.\033[0m\n";

            // I subtract the bet amount from the player's money
            player.money -= bet;

            // I increase the count of games lost
            player.gamesLost++;

            // I record this game as a loss in the game history
            registerGame("Blackjack", player.name, -bet, player.money);

            // I save the player's updated balance
            saveBalance(player.name, player.money);

            // I update the player's overall statistics
            player.updateStatistics();

            // I show the player's new balance after the loss
            cout << "Your current balance: \033[32m$" << player.money << "\033[0m\n";

            cout << "Press Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            // I ask the player if they want to play Blackjack again
            cout << "\n\033[33mDo you want to play Blackjack again? (y/n): \033[0m";
            while (true)
            {
                cin >> playAgain;
                playAgain = tolower(playAgain);

                // I only accept valid responses: 'y' or 'n'
                if (playAgain == 'y' || playAgain == 'n')
                    break;

                // I warn the user when the input is invalid
                cout << "\033[31mInvalid input. Please enter 'y' or 'n': \033[0m";
            }

            // Since the game ended here, I use 'continue' to go back to the beginning of the loop
            continue;
        }

        // I also show only the first card of the dealer face-up and hide the rest to add realism
        cout << "\n\033[35mDealer's visible card:\033[0m\n";
        showCardsASCII(dealerValues, dealerSuits, numDealer, false); // I display only the first card of the dealer
        cout << "\033[35m(Total: Hidden)\033[0m\n";                  // I keep the dealer’s total hidden for now

        // Ask if player wants to double the bet if possible
        char doubleOption;
        if (player.money >= bet * 2)
        {
            cout << "\n\033[33mDo you want to double your bet? (y/n): \033[0m";
            while (true)
            {
                cin >> doubleOption;
                doubleOption = tolower(doubleOption);
                if (doubleOption == 'y')
                {
                    bet *= 2; // Double the bet
                    cout << "Your bet has been doubled to \033[32m$" << bet << "\033[0m.\n";
                    break;
                }
                else if (doubleOption == 'n')
                {
                    break;
                }
                else
                {
                    cout << "\033[31mInvalid input. Please enter 'y' or 'n': \033[0m";
                }
            }
        }

        // Ask if player wants to split cards if first two cards are the same value
        bool hasSplit = false;
        int splitValues[MAX_CARDS], splitNum = 0;
        string splitSuits[MAX_CARDS];

        if (numPlayer == 2 && playerValues[0] == playerValues[1] && player.money >= bet)
        {
            char splitOption;
            cout << "\n\033[33mYour first two cards are the same. Do you want to split? (y/n): \033[0m";
            while (true)
            {
                cin >> splitOption;
                splitOption = tolower(splitOption);
                if (splitOption == 'y')
                {
                    hasSplit = true;
                    player.money -= bet; // Deduct bet for the split hand
                    // Move second card to split hand
                    splitValues[splitNum] = playerValues[1];
                    splitSuits[splitNum++] = playerSuits[1];
                    numPlayer = 1; // Keep only first card in original hand
                    cout << "You have split your hand into two.\n";
                    break;
                }
                else if (splitOption == 'n')
                {
                    break;
                }
                else
                {
                    cout << "\033[31mInvalid input. Please enter 'y' or 'n': \033[0m";
                }
            }
        }

        // Play the main hand
        bool playerBusted = playHandFunction(player, playerValues, playerSuits, numPlayer, bet);

        // Play split hand if applicable and main hand not busted
        bool splitBusted = false;
        if (hasSplit && !playerBusted)
        {
            cout << "\n\033[33mPlaying split hand:\033[0m\n";
            showCardsASCII(splitValues, splitSuits, splitNum);
            cout << "\033[34m(Total: " << calculateScore(splitValues, splitNum) << ")\033[0m\n";

            splitBusted = playHandFunction(player, playerValues, playerSuits, numPlayer, bet);
        }

        // If both hands busted, game over
        if (playerBusted && (hasSplit ? splitBusted : true))
        {
            cout << "\n\033[31mAll your hands busted. Game over.\033[0m\n";
            cout << "Your current balance: \033[32m$" << player.money << "\033[0m\n";
            // I ask the player if they want to play another round of Blackjack
            cout << "\n\033[33mDo you want to play Blackjack again? (y/n): \033[0m";
            // I start a loop to validate the user's input
            while (true)
            {
                cin >> playAgain;               // I read the user's answer
                playAgain = tolower(playAgain); // I convert the input to lowercase for easier comparison

                // I check if the input is valid ('y' or 'n')
                if (playAgain == 'y' || playAgain == 'n')
                    break;

                // If it's invalid, I show an error message and ask again
                cout << "\033[31mInvalid input. Please enter 'y' or 'n': \033[0m";
            }

            // I use 'continue' to return to the beginning of the game loop,
            // skipping the dealer's turn since the player already lost
            continue;
        }

        // Dealer's turn if any hand did not bust
        cout << "\n\033[35mDealer's turn...\033[0m\n";
        // Show dealer's full hand now
        showCardsASCII(dealerValues, dealerSuits, numDealer);
        cout << "\033[35m(Total: " << calculateScore(dealerValues, numDealer) << ")\033[0m\n";

        // Dealer draws cards until reaching at least 17 points
        while (calculateScore(dealerValues, numDealer) < 17 && numDealer < MAX_CARDS)
        {
            dealerValues[numDealer] = generateCard();
            dealerSuits[numDealer++] = getRandomSuit();

            cout << "\nDealer takes a card:\n";
            showCardsASCII(dealerValues, dealerSuits, numDealer);
            cout << "\033[35m(Total: " << calculateScore(dealerValues, numDealer) << ")\033[0m\n";
        }

        int dealerScore = calculateScore(dealerValues, numDealer);

        // Lambda to compare hands and update player's stats and money
        auto resolveHand = [&](int handScore, int currentBet, bool isSplit = false)
        {
            if (handScore > 21)
            {
                cout << "\n\033[31mYou busted this hand and lost $" << currentBet << ".\033[0m\n";
                player.money -= currentBet;
                player.gamesLost++;
                registerGame("Blackjack", player.name, -currentBet, player.money);
            }
            else if (dealerScore > 21 || handScore > dealerScore)
            {
                cout << "\n\033[32mYou won this hand and earned $" << currentBet << "!\033[0m\n";
                player.money += currentBet;
                player.gamesWon++;
                registerGame("Blackjack", player.name, currentBet, player.money);
            }
            else if (handScore == dealerScore)
            {
                cout << "\n\033[33mThis hand is a tie. Your bet is returned.\033[0m\n";
                player.gamesTied++;
                registerGame("Blackjack", player.name, 0, player.money);
            }
            else
            {
                cout << "\n\033[31mYou lost this hand and lost $" << currentBet << ".\033[0m\n";
                player.money -= currentBet;
                player.gamesLost++;
                registerGame("Blackjack", player.name, -currentBet, player.money);
            }

            saveBalance(player.name, player.money);
            player.updateStatistics();
        };

        // Resolve main hand if not busted
        if (!playerBusted)
            resolveHand(calculateScore(playerValues, numPlayer), bet);

        // Resolve split hand if any and not busted
        if (hasSplit && !splitBusted)
            resolveHand(calculateScore(splitValues, splitNum), bet, true);

        // Show updated balance after resolving all hands
        cout << "\nYour current balance: \033[32m$" << player.money << "\033[0m\n";

        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

        // Check if player still has money to continue
        if (player.money <= 0)
        {
            cout << "\n\033[31mYou ran out of money to continue playing Blackjack.\033[0m\n";
            break;
        }

        // Ask if they want to play again
        cout << "\n\033[33mDo you want to play Blackjack again? (y/n): \033[0m";
        while (true)
        {
            cin >> playAgain;
            playAgain = tolower(playAgain);
            if (playAgain == 'y' || playAgain == 'n')
                break;
            cout << "\033[31mInvalid input. Please enter 'y' or 'n': \033[0m";
        }

        cout << "Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        clearConsole();

    } while (playAgain == 'y');
}

#endif // BLACKJACK_GAME_H
