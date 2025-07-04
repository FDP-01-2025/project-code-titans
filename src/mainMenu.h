#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <iostream> // Include this library to display messages on screen
#include <string>   // Include this library to work with strings
#include <limits>   // Include this for clearing the buffer and validating inputs
#include <cstdlib>  // Include this for functions like srand
#include <ctime>    // Include this for working with time() when using srand

#include "player.h"          // Include the file that contains the structure and methods of the player
#include "userManager.h"     // Include functions for user management: login, registration, etc.
#include "rouletteGame.h"    // Include the roulette game
#include "blackjackGame.h"   // Include the blackjack game
#include "crapsGame.h"       // Include the craps game (dice)
#include "hilo.h"            // Include the Hi-Lo game
#include "multiplayer.h"     // Include the multiplayer mode
#include "slotMachineGame.h" // Include the slot machine game
#include "utils.h"           // Include clearConsole
#include "date_time.h"       // This includes the current date and time display function

using namespace std; // Use the standard namespace to avoid writing std:: all the time

// This function displays the available options in the main casino menu
inline void showMenu()
{
    clearConsole(); // Use the function I already have to clear the screen before showing the menu

    showDateTime();
    cout << "       Main Menu - Virtual Casino\n\n";
    cout << "1) Deposit money\n";
    cout << "2) Withdraw money\n";
    cout << "3) Roulette\n";
    cout << "4) Blackjack\n";
    cout << "5) Slot Machine\n";
    cout << "6) Craps (Dice)\n";
    cout << "7) Hi-Lo\n";
    cout << "8) Show history\n";
    cout << "9) Show statistics \n";
    cout << "10) Exit\n\n";
    cout << "+--------------------------------------+\n";
}

// This function starts the game once the user has logged in successfully
inline void start(const string &username)
{
    Player player;                        // Create a player
    player.name = username;               // Assign the received name
    player.money = loadBalance(username); // Load the player's balance from the file
    player.loadPlayerStatistics();        // Load the saved statistics of the player

    cout << "Hello, " << player.name << "! Current balance: $" << player.money << "\n";

    int option;          // Variable to store the menu option
    bool playing = true; // Flag to keep the loop active

    while (playing)
    {
        showMenu(); // Show the menu on screen
        cout << "| Current money: $" << player.money << "\n";
        cout << "║ Choose an option: ";
        cin >> option; // Read the user's option

        if (cin.fail())
        {                                                        // Check if there was an input error
            cin.clear();                                         // Clear the error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer
            cout << "Invalid input.\n";
            continue; // Return to the start of the loop
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any leftover characters

        switch (option)
        { // Evaluate the user's option
        case 1:
        {
            clearConsole();
            int amount;
            cout << "How much do you want to deposit? $";
            cin >> amount;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            player.deposit(amount); // Call the method to deposit money
            break;
        }
        case 2:
        {
            clearConsole();
            int amount;
            cout << "How much do you want to withdraw? $";
            cin >> amount;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            player.withdraw(amount); // Call the method to withdraw money
            break;
        }
        case 3:
            clearConsole();
            if (player.money <= 0)
                cout << "You do not have enough balance. Deposit to play.\n";
            else
                playRoulette(player); // Roulette game
            break;
        case 4:
            clearConsole();
            if (player.money <= 0)
            {
                cout << "You do not have enough balance. Deposit to play.\n";
            }
            else
            {
                playBlackjack(player); // Blackjack game
            }
            break;
        case 5:
            clearConsole();
            if (player.money <= 0)
                cout << "You do not have enough balance. Deposit to play.\n";
            else
                playSlotMachine(player); // Slot machine game
            break;
        case 6:
            clearConsole();
            if (player.money <= 0)
                cout << "You do not have enough balance. Deposit to play.\n";
            else
                playCraps(player); // Dice game (Craps)
            break;
        case 7:
            clearConsole();
            if (player.money <= 0)
                cout << "You do not have enough balance. Deposit to play.\n";
            else
                playHilo(player); // Hi-Lo game
            break;
        case 8:
            player.showHistory(); // Show the game history
            break;
        case 9:
            player.showStatistics(); // Show player statistics
            break;
        case 10:
            cout << "Thank you for playing. See you later!\n";
            playing = false; // Exit the loop and the game
            break;
        default:
            cout << "Invalid option.\n"; // Capture any invalid option
        }
        cout << endl; // Make a line break after each cycle
    }
}

// This function handles the initial menu where the user chooses whether to log in or register
inline void startMenu()
{
    string name;
    bool session = false;

    while (!session)
    {
        clearConsole(); // Use the function I already have to clear the screen before showing the menu
        cout << "\n*============* START MENU *============*\n\n";
        showDateTime();
        cout << "1) Log in\n";
        cout << "2) Register\n";
        cout << "3) Recover password\n";
        cout << "4) Delete user\n";
        cout << "5) Exit\n\n";
        cout << "+--------------------------------------+\n";
        cout << "| Choose an option: ";
        int option;
        cin >> option;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (option)
        {
        case 1:
            session = logIn(name); // Attempt to log in
            break;
        case 2:
            registerUser(); // Register a new user
            break;
        case 3:
            recoverPassword(); // Call password recovery
            break;
        case 4:
            deleteUser(); // Delete a user
            break;
        case 5:
            cout << "Exiting the program...\n";
            return; // Exit the function
        default:
            cout << "Invalid option. Please try again.\n";
        }
    }

    start(name); // If I successfully logged in, start the game
}

// This function allows me to choose whether I want to play solo or in local multiplayer mode
inline void gameModeMenu()
{
    int option;
    clearConsole(); // Use the function I already have to clear the screen before showing the menu
    while (true)
    {
        cout << "\n*============* GAME MODE *=============*\n\n";
        showDateTime();
        cout << "1) Play solo\n";
        cout << "2) Local multiplayer\n";
        cout << "3) Exit the game\n\n";
        cout << "+--------------------------------------+\n";
        cout << "| Choose an option: ";
        cin >> option;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a number from 1 to 3.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (option)
        {
        case 1:
            startMenu(); // Call the start menu for a single player
            return;
        case 2:
            multiplayerMode(); // Call the local multiplayer mode
            return;
        case 3:
            cout << "Thank you for playing! See you soon.\n";
            return;
        default:
            cout << "Invalid option. Try again.\n";
        }
    }
}

#endif // MAIN_MENU_H
