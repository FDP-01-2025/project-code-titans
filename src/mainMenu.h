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
#include "asciiGraphics.h"

using namespace std; // Use the standard namespace to avoid writing std:: all the time

// This function displays the available options in the main casino menu
inline void showMenu()
{
    clearConsole(); // Use the function I already have to clear the screen before showing the menu

    showDateTime();
    setColor(36);
    cout << "       Main Menu - Virtual Casino\n\n";
    resetColor();
    cout << "1) Deposit money\n";
    cout << "2) Withdraw money\n";
    setColor(32);
    cout << "3) Roulette\n";
    cout << "4) Blackjack\n";
    cout << "5) Slot Machine\n";
    cout << "6) Craps (Dice)\n";
    cout << "7) Hi-Lo\n";
    resetColor();
    cout << "8) Show history\n";
    cout << "9) Show statistics \n";
    cout << "10) Exit\n\n";
    setColor(36);
    cout << "+--------------------------------------+\n";
    resetColor();
}

// This function displays a submenu to view or delete the player's game history
inline void showHistoryMenu(Player &player)
{
    int subOption;             // Here I store the option chosen by the player
    bool inHistoryMenu = true; // I use this flag to keep the submenu active until the player decides to exit

    // While the flag is true, I keep showing the submenu
    while (inHistoryMenu)
    {
        clearConsole(); // I clear the console to keep things tidy

        // I display the title and submenu options in cyan color
        cout << "\033[36m+===========* HISTORY MENU *===========+\033[0m\n\n";
        cout << "  1. View Game History\n";     // Option to view the player's history
        cout << "  2. Delete Game History\n";   // Option to delete the player's history
        cout << "  3. Return to Main Menu\n\n"; // Option to go back to the main menu
        setColor(33);
        cout << "+-----------------------\n";
        cout << "| Choose an option: ";
        resetColor();
        cin >> subOption; // I read the selected option

        // I check if there was an input error
        if (cin.fail())
        {
            cin.clear();                                         // I clear the error state of cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // I clear the keyboard buffer
            cout << "Invalid input.\n";                          // I inform the player about the invalid input
            continue;                                            // I return to the beginning of the loop to show the menu again
        }

        // I clear any remaining characters in the buffer after reading the number
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Based on the option chosen by the player, I execute a different action
        switch (subOption)
        {
        case 1:
            player.showHistory(); // I show the player's game history
            break;
        case 2:
            player.deleteHistory(); // I delete the player's game history
            break;
        case 3:
            inHistoryMenu = false; // I exit the submenu
            break;
        default:
            cout << "Invalid option.\n"; // I notify the player if the option is invalid
        }

        // If the submenu is still active, I wait for the player to press Enter before continuing
        if (inHistoryMenu)
        {
            cout << "\nPress Enter to continue...";
            cin.get(); // I pause the program until Enter is pressed
        }
    }
}

// Show the statistics menu for the player
inline void showStatisticsMenu(Player &player)
{
    int subOption;           // I save the chosen option
    bool inStatsMenu = true; // I stay in the menu as long as it is true
    while (inStatsMenu)
    {
        clearConsole(); // Clear the screen
        cout << "\033[36m+===========* STATISTICS MENU *===========+\033[0m\n\n";
        cout << "  1. View Text Statistics\n";
        cout << "  2. View Graphical Statistics\n";
        cout << "  3. Return to Main Menu\n\n";
        setColor(33);
        cout << "+-----------------------\n";
        cout << "| Choose an option: ";
        resetColor();

        cin >> subOption;

        // Check if there was an error when entering
        if (cin.fail())
        {
            cin.clear();                                         // Remove the error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clean input
            cout << "Invalid input.\n";
            cout << "Press Enter to continue...";
            cin.get();
            continue; // Show the menu again
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer

        switch (subOption)
        {
        case 1:
            player.showStatistics(); // Show statistics in text
            break;
        case 2:
            clearConsole();
            showStatistics(player.name); // Sampling statistics with bars
            break;
        case 3:
            inStatsMenu = false; // I exit the menu
            break;
        default:
            cout << "Invalid option.\n"; // If you write something outside the range
        }

        // Pause until you press Enter
        if (inStatsMenu)
        {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
    }
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
        setColor(36);
        cout << "| Current money: $" << player.money << "\n";
        cout << "║ Choose an option: ";
        resetColor();
        cin >> option; // Read the user's option

        if (cin.fail())
        {                                                        // Check if there was an input error
            cin.clear();                                         // Clear the error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer
            cout << "Invalid input.\n";
            cout << "Press Enter to continue...";
            cin.get();
            continue; // Return to the start of the loop
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any leftover characters

        switch (option)
        { // Evaluate the user's option
        case 1:
        {
            clearConsole();
            int amount;
            setColor(32);
            cout << "+-----------* VIRTUAL BANK *-------------\n";
            cout << "|\n";
            cout << "| Current money: $" << player.money << "\n";
            cout << "|\n";
            cout << "+----------------------------------------\n\n";
            resetColor();
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
            setColor(32);
            cout << "+-----------* VIRTUAL BANK *-------------\n";
            cout << "|\n";
            cout << "| Current money: $" << player.money << "\n";
            cout << "|\n";
            cout << "+----------------------------------------\n\n";
            resetColor();
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
            showHistoryMenu(player); // Submenu for viewing or deleting game history
            break;
        case 9:
            showStatisticsMenu(player); // Show player statistics
            break;
        case 10:
            cout << "Thank you for playing. See you later!\n";
            playing = false; // Exit the loop and the game
            break;
        default:
            cout << "Invalid option.\n"; // Capture any invalid option
            cout << "Press Enter to continue...";
            cin.get();
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
        setColor(32);
        cout << "\n*============* START MENU *============*\n\n";
        resetColor();
        showDateTime();
        cout << "1) Log in\n";
        cout << "2) Register\n";
        cout << "3) Recover password\n";
        cout << "4) Delete user\n";
        cout << "5) Exit\n\n";
        setColor(32);
        cout << "+--------------------------------------+\n";
        cout << "| Choose an option: ";
        resetColor();
        int option;
        cin >> option;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            cout << "Press Enter to continue...";
            cin.get();
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
            cout << "Press Enter to continue...";
            cin.get();
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
        setColor(32);
        cout << "\n*============* GAME MODE *=============*\n\n";
        resetColor();
        showDateTime();
        cout << "1) Play solo\n";
        cout << "2) Local multiplayer\n";
        cout << "3) Exit the game\n\n";
        setColor(32);
        cout << "+--------------------------------------+\n";
        cout << "| Choose an option: ";
        resetColor();
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
            cout << "Press Enter to continue...";
            cin.get();
        }
    }
}

#endif // MAIN_MENU_H
