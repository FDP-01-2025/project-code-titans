#ifndef PLAYER_DATA_H 
#define PLAYER_DATA_H 

#include <string>     // I include this because I will use string objects
#include <fstream>    // Needed to read and write files
#include <iostream>   // Included to debug or display messages if necessary
#include <cmath>      // Used in case I need math functions like abs
#include <limits>     // Used to handle limits, like file reading errors

using namespace std; // Using the standard namespace to avoid writing std:: everywhere

// This function is used to save movements like deposits or withdrawals in a history file
inline void saveMovement(const string& movementType, const string& player, int amount, int remainingMoney) {
    ofstream file("./documents/movements.txt", ios::app); // Open the file in append mode
    if (file.is_open()) { // Check if it opened correctly
        file << "Player: " << player << " | Event: " << movementType
             << " | Amount: $" << amount
             << " | Remaining money: $" << remainingMoney << "\n"; // Write all movement info
    }
}

// This function is used to log what happens in games: win, lose, or draw
inline void saveGame(const string& eventType, const string& player, int amount, int result, int remainingMoney) {
    ofstream file("./documents/games.txt", ios::app); // Open the file to append game events
    if (file.is_open()) {
        file << "Player: " << player << " | Event: " << eventType
             << " | Amount: $" << amount
             << " | Result: " << (result == 1 ? "Won" : (result == 0 ? "Lost" : "Draw"))
             << " | Remaining money: $" << remainingMoney << "\n"; // Write all event info
    }
}

// This function is a wrapper that simply calls saveMovement to register a deposit or withdrawal
inline void registerMoneyMovement(const string& movementType, const string& player, int amount, int remainingMoney) {
    saveMovement(movementType, player, amount, remainingMoney); // Directly calls saveMovement
}

// This function allows me to register a game result (win, loss, or draw)
inline void registerGame(const string& gameName, const string& player, int gainLoss, int remainingMoney) {
    int result = (gainLoss > 0) ? 1 : (gainLoss < 0) ? 0 : 2; // Determine if won, lost, or drew
    saveGame(gameName, player, abs(gainLoss), result, remainingMoney); // Log the result
}

// This function saves the player's current balance in their own text file
inline void saveBalance(const string& player, int money) {
    ofstream file("./documents/balance_" + player + ".txt"); // Open the player's balance file
    if (file.is_open()) {
        file << money << "\n"; // Write the balance directly
    }
}

// This function loads the balance from the corresponding player's file
inline int loadBalance(const string& player) {
    ifstream file("./documents/balance_" + player + ".txt"); // Open the player's file
    if (!file.is_open()) return 0; // If failed to open, return 0

    int savedMoney;
    file >> savedMoney; // Try to read the balance
    if (file.fail()) return 0; // If reading failed, return 0
    return savedMoney; // Return the read balance
}

// This function saves the player's game statistics to a text file
inline void saveStatistics(const string& name, int played, int won, int lost, int drawn) {
    ofstream file("./documents/statistics_" + name + ".txt"); // Open the statistics file
    if (file.is_open()) {
        file << "Games played: " << played << "\n";
        file << "Games won: " << won << "\n";
        file << "Games lost: " << lost << "\n";
        file << "Games drawn: " << drawn << "\n"; // Write the 4 stats
        file.close(); // Close the file when done
    }
}

// This function loads statistics from the player's file
inline bool loadStatistics(const string& name, int& played, int& won, int& lost, int& drawn) {
    ifstream file("./documents/statistics_" + name + ".txt"); // Try to open player's file

    if (!file.is_open()) return false; // If couldn't open, return false

    string key; // Will read the name of each stat
    int value;  // Will store the corresponding value

    // Read the file line by line
    while (file >> ws && getline(file, key, ':')) {
        file >> ws; // Remove whitespace

        if (!(file >> value)) { // Try to read the number
            file.clear(); // If failed, clear flags
            file.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of line
            continue; // Go to next
        }

        // Compare the read key and assign value to the correct variable
        if (key == "Games played") {
            played = value;
        } else if (key == "Games won") {
            won = value;
        } else if (key == "Games lost") {
            lost = value;
        } else if (key == "Games drawn") {
            drawn = value;
        }
    }

    file.close(); // Close the file when finished
    return true; // Return true because stats loaded successfully
}

#endif // PLAYER_DATA_H
