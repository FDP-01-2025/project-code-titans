#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include "gameConstants.h" // Use constants like MAX_REGISTROS and Registro
#include "playerData.h"    // For functions to save and load player data
#include "utils.h"         // Here I include clearConsole

using namespace std;

// Here I define the array of positions for the roulette that I will use in the program,
// I only define it once here to avoid multiple definitions
Position positions[NUMBERS];

// Define the Player structure with all the information I need to store about each player
struct Player
{
    string name;                 // Player's name
    int money = 0;               // Current money the player has
    Record history[MAX_RECORDS]; // History of movements and events
    int numRecords = 0;          // How many records the history has

    // Player statistics for the games
    int gamesPlayed = 0;
    int gamesWon = 0;
    int gamesLost = 0;
    int gamesTied = 0;

    // Update the player's statistics by saving them to the file
    inline void updateStatistics()
    {
        saveStatistics(name, gamesPlayed, gamesWon, gamesLost, gamesTied);
    }

    // Load the player's statistics from the file
    inline void loadPlayerStatistics()
    {
        int j, g, p, e;
        if (loadStatistics(name, j, g, p, e))
        {
            gamesPlayed = j;
            gamesWon = g;
            gamesLost = p;
            gamesTied = e;
        }
    }

    // Show the player's statistics in the console
    inline void showStatistics()
    {
        loadPlayerStatistics(); // First load to show updated data
        clearConsole();
        cout << "+======================================+\n";
        cout << "|         Your game statistics:        |\n";
        cout << "║                                      ║\n";
        cout << "| Games played: " << gamesPlayed << "                     |\n";
        cout << "║ Games won: " << gamesWon << "                         ║\n";
        cout << "| Games lost: " << gamesLost << "                        |\n";
        cout << "║ Games tied: " << gamesTied << "                        ║\n";
        cout << "|                                      |\n";
        cout << "+--------------------------------------+\n";
        cout << "\nPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    // Add a new record to the player's history (if there is space)
    inline void addRecord(const string &text)
    {
        if (numRecords < MAX_RECORDS)
        {
            history[numRecords++].description = text;
        }
    }

    // Method for the player to deposit money
    inline void deposit(int amount)
    {
        if (amount > 0)
        {
            money += amount; // Increase balance
            cout << "You have deposited $" << amount << ". Current balance: $" << money << "\n";
            addRecord("Deposit: $" + to_string(amount)); // Record the movement
            registerMoneyMovement("Deposit", name, amount, money);
            saveBalance(name, money); // Save updated balance
        }
        else
        {
            cout << "You cannot deposit a negative amount or zero.\n";
        }
    }

    // Method for the player to withdraw money
    inline bool withdraw(int amount)
    {
        if (amount > 0 && amount <= money)
        {
            money -= amount; // Decrease balance
            cout << "You have withdrawn $" << amount << ". Current balance: $" << money << "\n";
            addRecord("Withdrawal: $" + to_string(amount)); // Record movement
            registerMoneyMovement("Withdrawal", name, amount, money);
            saveBalance(name, money); // Save updated balance
            return true;              // Successful withdrawal
        }
        else
        {
            cout << "Invalid withdrawal or insufficient balance.\n";
            return false; // Failed withdrawal
        }
    }

    // Method to show the complete history of the player
    inline void showHistory()
    {
        // Open the file that contains all registered game events
        ifstream file("./documents/games.txt");

        // Check if the file opened correctly
        if (!file.is_open())
        {
            // If it could not be opened, inform the player and exit the function
            cout << "Could not open the game history.\n";
            return;
        }

        string line;             // Here I will store each line of the file while reading it
        bool hasHistory = false; // I create this flag to know if I found any line of the player

        clearConsole();
        // Show the header to make it look nice and organized
        cout << "\n===============  Game History =============== \n";

        // Read the file line by line using getline
        while (getline(file, line))
        {
            // Check if the line contains the player's name
            if (line.find("Player: " + name) != string::npos)
            {
                // If the line is from the player, show it on screen
                cout << line << "\n";
                hasHistory = true; // Change the flag to indicate that I found history
            }
        }

        // Close the file when I finish reading it
        file.close();

        // If I did not find any line for the player, inform them
        if (!hasHistory)
        {
            cout << "There is no registered history for this player.\n";
        }

        cout << "\nPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

        // Show the footer of the history to close it visually
        cout << "=================================\n";
    }
};

#endif // PLAYER_H
