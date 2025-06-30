#ifndef PANTALLA_CARGA_H
#define PANTALLA_CARGA_H

#include <iostream>     // I use this library to print to the console
#include "utils.h"      // I include my own utility functions, like clearing the screen

// Depending on the operating system, I include the right library to pause execution
#ifdef _WIN32
    #include <windows.h>    // On Windows, I use Sleep
#else
    #include <unistd.h>     // On Linux/Mac, I use usleep (in microseconds)
#endif

using namespace std; // This saves me from writing std:: before things like cout or endl

// Function to pause the program for a given number of milliseconds
inline void esperar(int miliseconds) {
#ifdef _WIN32
    Sleep(miliseconds); // On Windows, Sleep uses milliseconds directly
#else
    usleep(miliseconds * 1000); // On Unix-like systems, I convert milliseconds to microseconds
#endif
}

// Function to show the loading screen with a logo and progress bar
inline void mostrarPantallaCarga() {
    limpiarConsola(); // First, I clear the screen so everything looks clean

    // I print the ASCII logo of the game (just for visual style)
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

                   WELCOME TO THE VIRTUAL CASINO

    )" << endl;

    esperar(800); // I wait a bit so the player can see the logo

    // Define the total width of the loading bar
    const int barLength = 30;
    cout << "\nLoading system...\n"; // Initial message

    // Start printing the loading bar
    for (int i = 0; i <= barLength; ++i) {
        int percent = (i * 100) / barLength; // Calculate the percentage of progress
        cout << "\r["; // \r brings the cursor back to the beginning of the line

        // Draw the bar: filled sections with '#' and pending ones with '-'
        for (int j = 0; j < barLength; ++j) {
            cout << (j < i ? "#" : "-");
        }

        cout << "] " << percent << "%"; // Show current percentage
        cout.flush(); // Force output to appear instantly

        esperar(70); // Wait a bit before the next step
    }

    cout << "\nLoading complete!\n"; // Let the player know it's done
    esperar(600); // Short pause before continuing
    limpiarConsola(); // Clear the screen before showing the next menu
}

#endif // PANTALLA_CARGA_H
