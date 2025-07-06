#ifndef ASCII_GRAPHICS_H
#define ASCII_GRAPHICS_H

#include <iostream>  // I use this library to print to the console
#include <string>    // I use string to handle player names
#include <algorithm> // I use algorithm for functions like max()
#include "playerData.h" // I include the file where I keep the player statistics

using namespace std;

// I return an ANSI color code based on the type of bar I want to show
inline string getBarColor(char type) {
    switch (type) {
        case '#': return "\033[32m"; // Green for wins
        case '-': return "\033[31m"; // Red for losses
        case '=': return "\033[33m"; // Yellow for ties
        default:  return "\033[0m";  // Reset to default color
    }
}

// I draw a bar with the length I decide, using the character and color that correspond
inline void drawBar(int length, char barChar) {
    string color = getBarColor(barChar); // I get the corresponding color
    cout << color;                       // I apply the color before drawing
    for (int i = 0; i < length; ++i)    // I draw the bar character by character
        cout << barChar;
    cout << "\033[0m";                  // I reset the color after finishing
}

// I show the player's statistics as an ASCII bar graph
inline void showStatistics(const string &playerName) {
    int played, won, lost, tied; // Variables to store the statistics

    // I try to load the statistics from the player's file
    if (!loadStatistics(playerName, played, won, lost, tied)) {
        // If not found, I inform
        cout << "\033[31m[!] No statistics found for " << playerName << "\033[0m\n";
        return;
    }

    // If the player hasn't played any games yet, I also inform
    if (played == 0) {
        cout << "\033[33m[!] " << playerName << " hasn't played any games yet.\033[0m\n";
        return;
    }

    int maxBarLength = 50; // I define the max length a bar can have
    int maxValue = max({won, lost, tied, 1}); // I get the highest value to scale the bars

    // Decorative header
    cout << "\n\033[36m╔════════════════════════════════════════════════════════════╗\033[0m\n";
    cout << "\033[36m║\033[0m         \033[1m" << playerName << "'s Game Statistics\033[0m            \033[36m║\033[0m\n";
    cout << "\033[36m╠════════════════════════════════════════════════════════════╣\033[0m\n";
    cout << "  Games played: \033[1m" << played << "\033[0m\n\n";

    // I draw each bar with its real value and type
    cout << "  Won  [" << won  << "]  | "; drawBar((won  * maxBarLength) / maxValue, '#'); cout << "\n";
    cout << "  Lost [" << lost << "]  | "; drawBar((lost * maxBarLength) / maxValue, '-'); cout << "\n";
    cout << "  Tied [" << tied << "]  | "; drawBar((tied * maxBarLength) / maxValue, '='); cout << "\n";

    // Decorative footer
    cout << "\n\033[36m╚════════════════════════════════════════════════════════════╝\033[0m\n";
}

#endif // ASCII_GRAPHICS_H
