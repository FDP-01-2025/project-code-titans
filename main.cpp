#include <iostream>
#include <ctime>   // For time()
#include <cstdlib> // For srand()

#include "./src/mainMenu.h" // For the main menu functions

#ifdef _WIN32
#include <windows.h> // For SetConsoleOutputCP on Windows
#endif

int main() {
    // If we are on Windows, configure the console for UTF-8
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

    // Initialize the random number generator with the current time seed
    srand(static_cast<unsigned int>(time(nullptr)));

    // Call the main menu where the user can select the game mode
    gameModeMenu();

    return 0;
}
