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
        cout << "|         \033[34mYour game statistics:\033[0m        |\n";
        cout << "║                                      ║\n";
        cout << "| \033[36mGames played: " << gamesPlayed << "\033[0m                     |\n";
        cout << "║ \033[32mGames won: " << gamesWon << "\033[0m                         ║\n";
        cout << "| \033[31mGames lost: " << gamesLost << "\033[0m                        |\n";
        cout << "║ \033[36mGames tied: " << gamesTied << "\033[0m                        ║\n";
        cout << "|                                      |\n";
        cout << "+--------------------------------------+\n";
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

        // Show the footer of the history to close it visually
        cout << "=================================\n";
    }

    inline void deleteHistory()
    {
        // Open the original game history file in read mode
        ifstream inFile("./documents/games.txt");

        // I open a temporary file in write mode where only the lines that do not belong to the current player are saved
        ofstream outFile("./documents/temp.txt");

        // Check if any of the files could not be opened correctly
        if (!inFile.is_open() || !outFile.is_open())
        {
            // Display an error message if a problem occurs with the files
            cout << "\033[31mError: Could not open game history file.\033[0m\n";
            return;
        }

        string line;        // Variable to store each line read from the file
        bool found = false; // bool to know if any line from the current player was found

        // Loop through each line of the original file
        while (getline(inFile, line))
        {
            // If the line does not contain the current player's name, copy it to the temporary file
            if (line.find("Player: " + name) == string::npos)
            {
                outFile << line << "\n";
            }
            else
            {
                // If the line belongs to the player, it is not copied and is marked as found
                found = true;
            }
        }

        // I close the files once the process is finished
        inFile.close();
        outFile.close();

        // Delete the original file and rename the temporary file to replace it
        if (remove("./documents/games.txt") != 0 || rename("./documents/temp.txt", "./documents/games.txt") != 0)
        {
            // Display an error message if a problem occurs while replacing the files
            cout << "\033[31mError: Could not update the history file.\033[0m\n";
        }
        else
        {
            // If player records were found, deletion is confirmed
            if (found)
                cout << "\033[33mYour game history has been deleted.\033[0m\n";
            else
                // If no records of the player were found, it is reported
                cout << "No history was found for this player.\n";
        }
        
    }
};

#endif // PLAYER_H
