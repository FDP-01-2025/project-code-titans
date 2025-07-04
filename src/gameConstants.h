#ifndef GAME_CONSTANTS_H // Start of include guard to prevent multiple inclusions
#define GAME_CONSTANTS_H // Define macro indicating that the file has been included

#include <string> // Include string to handle text
#include <cmath>  // Include cmath to use mathematical constants like M_PI

using namespace std; // To avoid writing std:: before string or cout

// Define the maximum number of records that will be stored in a player's history
const int MAX_RECORDS = 100;

// Define the difficulty levels for the Blackjack game with the number of initial cards
const int NORMAL = 2; // Normal level starts with 2 cards
const int MEDIUM = 3; // Medium level starts with 3 cards
const int HARD = 4;   // Hard level starts with 4 cards

// Constants related to Roulette
const int NUMBERS = 37; // The roulette has 37 numbers (0-36)

// Array with the numbers of the roulette, in the order they appear on the wheel
const int numbers[NUMBERS] = {
    0, 32, 15, 19, 4, 21, 2, 25, 17, 34, 6,
    27, 13, 36, 11, 30, 8, 23, 10, 5, 24,
    16, 33, 1, 20, 14, 31, 9, 22, 18, 29,
    7, 28, 12, 35, 3, 26};

// Array with the colors corresponding to each number on the roulette
// 'G' = Green (for 0), 'R' = Red, 'N' = Black
const char colors[NUMBERS] = {
    'G', 'N', 'R', 'N', 'R', 'N', 'R', 'N', 'R', 'N', 'R',
    'N', 'R', 'N', 'R', 'N', 'R', 'N', 'R', 'N', 'R',
    'N', 'R', 'N', 'R', 'N', 'R', 'N', 'R', 'N', 'R',
    'N', 'R', 'N', 'R', 'N', 'R'};

// ANSI codes for colors in console
// These codes allow changing the text color in compatible terminals
const string red = "\033[31m";              // Code for red text
const string black = "\033[30m";            // Code for black text
const string green = "\033[32m";            // Code for green text
const string white_background = "\033[47m"; // Code for white background
const string reset = "\033[0m";             // Code to reset colors to default values

// Constants for the visualization of the roulette in the console (wheel graphic)
struct Position
{
    int x, y;
};                               // Structure to store coordinates (x,y)
const int WIDTH = 90;            // Total width of the visual area
const int HEIGHT = 30;           // Total height of the visual area
const int RADIUS = 13;           // Radius of the roulette (size)
const int CENTER_X = WIDTH / 2;  // X coordinate of the center of the roulette
const int CENTER_Y = HEIGHT / 2; // Y coordinate of the center of the roulette

extern Position positions[NUMBERS]; // External declaration of the positions of each number on the roulette
                                    // Defined in another file (e.g., player.h)

// Define structure to record a description of the player's action history
struct Record
{
    string description; // Text that describes the action or event
};

#endif // GAME_CONSTANTS_H                // End of include guard
