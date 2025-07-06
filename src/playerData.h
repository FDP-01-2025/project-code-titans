#ifndef PLAYER_DATA_H
#define PLAYER_DATA_H

#include <string>   // Include this because I will use string objects
#include <fstream>  // I need this to read and write to files
#include <iostream> // I include this for debugging or displaying messages if necessary
#include <cmath>    // I use this in case I need mathematical functions like abs
#include <limits>   // I use this to handle limits, such as file reading errors
#include <ctime>    // I include this library to get the current date and time

using namespace std; // I use the standard namespace to avoid writing std:: all the time

// This function is used to save movements such as deposits or withdrawals to a history file
inline void saveMovement(const string &movementType, const string &player, int amount, int remainingMoney)
{
    ofstream file("./documents/movements.txt", ios::app); // Open the file in append mode
    if (file.is_open())
    { // Check if it opened correctly
        file << "Player: " << player << " | Event: " << movementType
             << " | Amount: $" << amount
             << " | Remaining money: $" << remainingMoney << "\n"; // Write all the movement information
    }
}

// This function is used to save the game result into the player's personal history file
inline void saveGame(const string &eventType, const string &player, int amount, int result, int remainingMoney)
{
    // Get current timestamp
    time_t now = time(nullptr);
    tm *localTime = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localTime);

    // Build path to player's personal history file
    string filePath = "./documents/history_" + player + ".txt";

    // Open file in append mode
    ofstream file(filePath, ios::app);
    if (file.is_open())
    {
        // Write the game record with all info
        file << "[" << timestamp << "] "
             << "Event: " << eventType
             << " | Amount: $" << amount
             << " | Result: " << (result == 1 ? "Won" : (result == 0 ? "Lost" : "Tie"))
             << " | Remaining money: $" << remainingMoney << "\n";
    }
}


// This function is a wrapper that simply calls saveMovement to record a deposit or withdrawal
inline void registerMoneyMovement(const string &movementType, const string &player, int amount, int remainingMoney)
{
    saveMovement(movementType, player, amount, remainingMoney); // Call saveMovement directly
}

// This function allows me to record a game result (win, loss, or tie)
inline void registerGame(const string &gameName, const string &player, int winLossAmount, int remainingMoney)
{
    // First, I determine if I won, lost, or tied based on the amount won or lost
    int result = (winLossAmount > 0) ? 1 : (winLossAmount < 0) ? 0
                                                               : 2;

    // Now I get the current date and time to save when this event happened
    time_t now = time(nullptr);                                             // I get the current time
    tm *localTime = localtime(&now);                                        // I convert it to local time
    char timestamp[20];                                                     // I create a buffer for the date and time
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localTime); // I format the date and time as YYYY-MM-DD HH:MM:SS

    // I open the file to append the information
    ofstream file("./documents/games.txt", ios::app); // I open the file in append mode
    if (file.is_open())
    {
        // I write the line with all the info: date, player, event, amount, result, and remaining money
        file << "[" << timestamp << "] "
             << "Player: " << player << " | Event: " << gameName
             << " | Amount: $" << abs(winLossAmount)
             << " | Result: " << (result == 1 ? "Won" : (result == 0 ? "Lost" : "Tie"))
             << " | Remaining money: $" << remainingMoney << "\n";
    }

    // También guardo una copia en el archivo personal del jugador para tener su historial separado
    saveGame(gameName, player, abs(winLossAmount), result, remainingMoney);
}

// This function saves the player's current balance to their own text file
inline void saveBalance(const string &player, int money)
{
    ofstream file("./documents/balance_" + player + ".txt"); // Open the player's balance file
    if (file.is_open())
    {
        file << money << "\n"; // Write the balance directly
    }
}

// This function loads the balance from the corresponding player file
inline int loadBalance(const string &player)
{
    ifstream file("./documents/balance_" + player + ".txt"); // Open the player's file
    if (!file.is_open())
        return 0; // If it fails to open, return 0

    int savedMoney;
    file >> savedMoney; // Try to read the balance
    if (file.fail())
        return 0;      // If there was an error reading, return 0
    return savedMoney; // Return the read balance
}

// This function saves the player's game statistics to a text file
inline void saveStatistics(const string &name, int played, int won, int lost, int tied)
{
    ofstream file("./documents/statistics_" + name + ".txt"); // Open the statistics file
    if (file.is_open())
    {
        file << "Games played: " << played << "\n";
        file << "Games won: " << won << "\n";
        file << "Games lost: " << lost << "\n";
        file << "Games tied: " << tied << "\n"; // Write the 4 statistics
        file.close();                           // Close the file when I finish
    }
}

// This function loads the statistics from the player's file
inline bool loadStatistics(const string &name, int &played, int &won, int &lost, int &tied)
{
    ifstream file("./documents/statistics_" + name + ".txt"); // Try to open the player's file

    if (!file.is_open())
        return false; // If I couldn't open it, return false

    string key; // Here I will read the name of each statistic
    int value;  // And here I will store the corresponding value

    // Read the file line by line
    while (file >> ws && getline(file, key, ':'))
    {
        file >> ws; // Remove whitespace

        if (!(file >> value))
        {                                                         // Try to read the number
            file.clear();                                         // If it failed, clear the flags
            file.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line
            continue;                                             // Move on to the next one
        }

        // Compare the read key and assign the value to the correct variable
        if (key == "Games played")
        {
            played = value;
        }
        else if (key == "Games won")
        {
            won = value;
        }
        else if (key == "Games lost")
        {
            lost = value;
        }
        else if (key == "Games tied")
        {
            tied = value;
        }
    }

    file.close(); // Close the file when I finish
    return true;  // Return true because I successfully loaded the statistics
}

#endif // PLAYER_DATA_H
