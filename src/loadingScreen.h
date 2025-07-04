#ifndef LOADING_SCREEN_H
#define LOADING_SCREEN_H

#include <iostream> // I use this library to print to the console
#include <ctime>    // I include this to get the current time for greeting
#include "utils.h"  // I include my own utility functions, like clearing the screen

#ifdef _WIN32
#include <windows.h> // On Windows, I use Sleep
#else
#include <unistd.h> // On Linux/Mac, I use usleep (in microseconds)
#endif

using namespace std; // This saves me from writing std:: before things like cout or endl

// Function to pause the program for a given number of milliseconds
inline void wait(int milliseconds)
{
#ifdef _WIN32
    Sleep(milliseconds); // On Windows, Sleep uses milliseconds directly
#else
    usleep(milliseconds * 1000); // On Unix-like systems, convert milliseconds to microseconds
#endif
}

// Function to get a greeting based on the current time of day
inline string getGreeting()
{
    time_t now = time(nullptr);      // Get current system time
    tm *localTime = localtime(&now); // Convert to local time

    int hour = localTime->tm_hour; // Extract hour (0-23)

    if (hour >= 6 && hour < 12)
        return "Good morning";
    else if (hour >= 12 && hour < 18)
        return "Good afternoon";
    else
        return "Good evening";
}

// Function to display the loading screen with logo, greeting and progress bar
inline void showLoadingScreen()
{
    clearConsole(); // Clear the screen for clean display

    // Print ASCII art logo of the game
    cout << R"(

                             __________
                       _____|          |_____
                      |     |    /\    |     |
                      |  ---|   /  \   |\    |
                    ------- |   \  /   ---------   
                  /   ---   \    \/   | *       | 
                 |  /     \  |        |    *    |     
                 |  \     /  |--------|       * | 
                  \   ---   /          ---------
                    -------
    )";

    // Print dynamic greeting before the welcome message
    cout << "           " << getGreeting() << ", welcome to the Virtual Casino\n\n";

    wait(800); // Pause so player can see logo and greeting

    // Define the total width of the loading bar
    const int barLength = 30;
    cout << "Loading system...\n"; // Initial loading message

    // Print loading bar progress
    for (int i = 0; i <= barLength; ++i)
    {
        int percent = (i * 100) / barLength; // Calculate progress percentage
        cout << "\r[";                       // Return cursor to line start

        // Draw the bar: filled sections '#' and empty '-'
        for (int j = 0; j < barLength; ++j)
        {
            cout << (j < i ? "#" : "-");
        }

        cout << "] " << percent << "%"; // Display current percent
        cout.flush();                   // Force output flush

        wait(70); // Pause between progress updates
    }

    cout << "\nLoading complete!\n"; // Notify load finished
    wait(600);                       // Short pause before clearing screen
    clearConsole();                  // Clear for next screen/menu
}

#endif // LOADING_SCREEN_H
