#ifndef ROULETTE_GAME_H
#define ROULETTE_GAME_H

#include <string>   // Use strings to handle text in the game
#include <iostream> // For printing and reading from the console (cout, cin)
#include <cmath>    // Use mathematical functions like cos, sin, and the constant M_PI
#include <limits>   // Used for clearing input buffer and handling limits
#include <cstdlib>  // Used to generate random numbers with rand()

#include "gameConstants.h" // Include constants and global variables for the game, such as numbers and colors
#include "utils.h"         // Use helper functions for text, console, and pauses
#include "playerData.h"    // Use functions to log results and save the player's balance
#include "player.h"        // Use the Player structure with its attributes and methods

using namespace std; // To avoid writing std:: every time

inline void calculatePositions()
{ // Function that calculates the X, Y position of each number on the roulette
    for (int i = 0; i < NUMBERS; i++)
    {                                                               // Loop through all the numbers on the roulette
        double angle = (2 * M_PI * i / NUMBERS) - M_PI / 2;         // Calculate the angle to place number i
        positions[i].x = CENTER_X + int(RADIUS * cos(angle) * 1.9); // Calculate the X position (adjusted)
        positions[i].y = CENTER_Y + int(RADIUS * sin(angle));       // Calculate the Y position
    }
}

inline void printCanvas(int highlighted)
{                                 // Function to draw the roulette in the console
    string canvas[HEIGHT][WIDTH]; // Create a 2D "canvas" to store characters by position

    for (int i = 0; i < HEIGHT; i++)    // Loop through rows
        for (int j = 0; j < WIDTH; j++) // Loop through columns
            canvas[i][j] = " ";         // Initialize each cell with an empty space

    for (int i = 0; i < NUMBERS; i++)
    {                           // For each number on the roulette
        int x = positions[i].x; // Get its X position
        int y = positions[i].y; // Get its Y position
        string color = (colors[i] == 'R') ? red : (colors[i] == 'N') ? black
                                                                     : green; // Assign color based on array

        if (i == highlighted)
            color = white_background + color; // If highlighted, change background to white

        string numStr = (numbers[i] < 10 ? " " : "") + to_string(numbers[i]); // Format the number for alignment

        if (x >= 0 && x + 1 < WIDTH && y >= 0 && y < HEIGHT)
        {                                          // Check if it's within the canvas
            canvas[y][x] = color + numStr + reset; // Place the colored number in the position
            canvas[y][x + 1] = "";                 // Clear the adjacent cell to avoid visual errors
        }
    }

    for (int r = 1; r < RADIUS - 2; r++)
    { // For inner radii for decoration
        for (int a = 0; a < 360; a += 15)
        {                                                    // Every 15 degrees
            double rad = a * M_PI / 180.0;                   // Convert degrees to radians
            int x = CENTER_X + int(r * cos(rad) * 0.5);      // Calculate X position
            int y = CENTER_Y + int(r * sin(rad));            // Calculate Y position
            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) // Check within the canvas
                canvas[y][x] = ".";                          // Place a dot for decoration
        }
    }

    canvas[CENTER_Y][CENTER_X] = "O"; // Place an 'O' in the center to mark the axis

    for (int i = 0; i < HEIGHT; i++)
    {                     // Loop through rows to print
        string line = ""; // Initialize the empty line
        for (int j = 0; j < WIDTH; j++)
        { // Loop through columns
            if (!canvas[i][j].empty())
                line += canvas[i][j]; // Concatenate if there's something
        }
        cout << line << "\n"; // Print the complete line
    }
}

inline string requestBetType()
{                // Function to request the type of bet and validate
    string type; // Variable to store the option
    while (true)
    { // Loop until the user enters a valid option
        clearConsole();
        cout << "\033[34m======================================\n";
        cout << "\033[32m           BETTING MENU               \n";
        cout << "\033[35m 1. Exact number      →  pays 35x     \n";
        cout << "\033[31m 2. Color (Red/Black) →  pays 2x      \n";
        cout << "\033[36m 3. Even or Odd       →  pays 2x      \n";
        cout << "\033[33m 4. Exit game                         \n";
        cout << "\033[34m======================================\n";
        cout << "→ Choose an option: "; // Request the option
        cin >> type;                    // Read the user's option
        type = toLower(type);           // Convert to lowercase to avoid errors

        if (type == "1" || type == "2" || type == "3") // If it's a valid option
            return type;                               // Return it and exit
        else if (type == "4" || type == "exit")
            return "exit";
        else
            cout << "\033[31mInvalid option, please try again.\n\033[0m";
    }
}

inline int requestNumber()
{            // Function to request a valid betting number (0-36)
    int num; // Variable to store the number
    while (true)
    {                                                       // Until it's valid
        cout << "\033[35mEnter the number (0-36): \033[0m"; // Request the number
        if (cin >> num)
        {                              // If the user entered an integer
            if (num >= 0 && num <= 36) // If it's within the valid range
                return num;            // Return the number
            else
                cout << "\033[31mInvalid number. It must be between 0 and 36.\n\033[0m"; // If not, show error
        }
        else
        {
            cout << "\033[31mInvalid input. Please enter an integer.\n\033[0m"; // If they didn't enter a number
            cin.clear();                                                        // Clear the error state of cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n');                // Ignore the rest of the line
        }
    }
}

inline char requestColor()
{                 // Function to request the color of the bet (red or black)
    string color; // Temporary variable to read text
    while (true)
    {                                                             // Repeat until receiving a valid response
        cout << "\033[34mEnter the color (Red / Black): \033[0m"; // Request the color
        cin >> color;                                             // Read the input
        color = toLower(color);                                   // Convert to lowercase for comparison
        if (color == "red")                                       // If it's red
            return 'R';                                           // Return code 'R'
        else if (color == "black")                                // If it's black
            return 'N';                                           // Return code 'N'
        else
            cout << "\033[31mInvalid color. Only 'Red' or 'Black'.\n\033[0m"; // Error message
    }
}

inline char requestParity()
{                  // Function to request if betting on even or odd
    string parity; // Temporary variable for the response
    while (true)
    {                                            // Until a valid response
        cout << "\033[33mEven or Odd?: \033[0m"; // Request the option
        cin >> parity;                           // Read input
        parity = toLower(parity);                // Convert to lowercase
        if (parity == "even")                    // If it's even
            return 'P';                          // Return code 'P'
        else if (parity == "odd")                // If it's odd
            return 'I';                          // Return code 'I'
        else
            cout << "\033[31mInvalid option. Only 'Even' or 'Odd'.\n\033[0m"; // Error message
    }
}

inline void playRoulette(Player &player)
{                         // Main function that handles the complete roulette game
    calculatePositions(); // Calculate positions to draw the roulette on the screen

    while (player.money > 0)
    { // While the player has money to bet
        if (player.money <= 0)
        {                                                                   // Check again if they have run out of money
            cout << "\033[31mYou have no money to play Roulette.\n\033[0m"; // Warning message
            return;                                                         // Exit the function because they cannot continue
        }

        cout << "\033[33m\n======================================\n\033[0m";
        cout << "\033[33m     WELCOME TO ROULETTE!\n\033[0m";
        cout << "\033[33m======================================\n\033[0m";
        cout << "Your current money: \033[32m$" << player.money << "\033[0m\n";

        int bet; // Variable for the player's bet
        cout << "\033[34mEnter your bet (minimum $10, maximum $500): $\033[0m";

        while (true)
        {               // Validate that the bet is correct
            cin >> bet; // Read the bet
            // If it fails or is out of range or exceeds balance
            if (cin.fail() || bet < 10 || bet > 500 || bet > player.money)
            {
                cin.clear();                                         // Clear cin error
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore buffer
                cout << "\033[31mInvalid bet. It must be between $10 and $500 and cannot exceed your current balance.\n\033[0m";
                cout << "Your current money is $" << player.money << ". Enter your bet: $";
                continue; // Ask for the bet again
            }
            break; // Exit if it's valid
        }

        player.gamesPlayed++; // Increment the count of games played

        string type = requestBetType(); // Ask for the type of bet (number, color, parity)
        int choice = -1;                // Initialize for exact number
        string summary;                 // To print the bet summary
        char chosenColor = 0;           // Initialize for color
        char chosenParity = 0;          // Initialize for parity

        if (type == "1")
        {                                                    // If betting on a number
            choice = requestNumber();                        // Ask for the chosen number
            summary = "Bet: on number " + to_string(choice); // Create summary
        }
        else if (type == "2")
        {                                 // If betting on color
            chosenColor = requestColor(); // Ask for the chosen color
            summary = "Bet: on color " + string((chosenColor == 'R') ? "Red" : "Black") + " | Amount: $" + to_string(bet);
        }
        else
        {                                   // If betting on even or odd
            chosenParity = requestParity(); // Ask for the chosen parity
            summary = "Bet: on " + string((chosenParity == 'P') ? "even" : "odd") + " | Amount: $" + to_string(bet);
        }

        cout << "\n"
             << summary << "\nSpinning the roulette...\n"; // Show summary and notify spinning

        int winner = rand() % NUMBERS;             // Generate random winning number (0 to 36)
        int spins = 3;                             // Define how many spins the roulette will make for the animation
        int totalSteps = spins * NUMBERS + winner; // Total steps to animate spin and stop at winner
        int highlighted = 0;                       // Highlighted number (simulates the ball spinning)

        for (int step = 0; step <= totalSteps; step++)
        {                                                                          // Loop that animates the roulette spinning
            clearConsole();                                                        // Clear screen to show next frame
            cout << "\033[33m\nCurrent balance: $" << player.money << "\033[0m\n"; // Show balance
            cout << "\033[33m" << summary << "\033[0m\n";                          // Show bet
            printCanvas(highlighted);                                              // Draw roulette with highlighted number
            highlighted = (highlighted + 1) % NUMBERS;                             // Move to the next highlighted number

            // Pauses to make the roulette slow down smoothly
            if (step > totalSteps - 10)
                waitMs(200);
            else if (step > totalSteps - 20)
                waitMs(150);
            else
                waitMs(60);
        }

        int winningNumber = numbers[winner]; // Actual winning number
        char winningColor = colors[winner];  // Winning color

        cout << "\033[33m\nThe roulette landed on number " << winningNumber << " (";
        cout << (winningColor == 'R' ? "Red" : winningColor == 'N' ? "Black"
                                                                   : "Green")
             << ")\033[0m\n"; // Show result

        bool won = false; // Variable to know if they won

        // Check if the player won based on their type of bet
        if (type == "1" && winningNumber == choice)
        { // Bet on exact number and it matches
            cout << "\033[32mYou won 35 times your bet!\n\033[0m";
            player.money += bet * 35; // Pay 35 times the bet
            player.gamesWon++;        // Increment games won
            won = true;
        }
        else if (type == "2" && winningColor == chosenColor)
        { // Bet on color and it matches
            cout << "\033[32mYou won 2 times your bet!\n\033[0m";
            player.money += bet * 2; // Pay 2 times the bet
            player.gamesWon++;
            won = true;
        }
        else if (type == "3")
        { // Bet on even or odd
            if (winningNumber != 0)
            { // The 0 does not count for even/odd
                if ((chosenParity == 'P' && winningNumber % 2 == 0) ||
                    (chosenParity == 'I' && winningNumber % 2 != 0))
                {
                    cout << "\033[32mYou won 2 times your bet!\n\033[0m";
                    player.money += bet * 2;
                    player.gamesWon++;
                    won = true;
                }
            }
        }

        if (!won)
        { // If they didn't win
            cout << "\033[31mYou didn't win this time.\033[0m\n";
            player.money -= bet; // Lose the bet
            player.gamesLost++;  // Increment games lost
        }

        // Show updated balance
        cout << "\033[32m\nUpdated balance: $" << player.money << "\033[0m\n";
        saveBalance(player.name, player.money); // Save balance to file
        player.updateStatistics();              // Update internal statistics

        // I log the game session with the bet result and updated balance
        registerGame("Roulette", player.name, won ? bet : -bet, player.money);

        if (!askToContinue())
            break; // Ask if they want to keep playing, if not, exit
    }

    if (player.money <= 0)
    {                                                        // If they ran out of money
        cout << "\nYou have run out of money. Game over.\n"; // Final message
        saveBalance(player.name, player.money);              // Save final balance
        player.updateStatistics();                           // Update statistics
    }

    cout << "\033[33m\nThank you for playing. Your final balance was: $" << player.money << "\n\033[0m"; // Farewell message
}

#endif // ROULETTE_GAME_H
