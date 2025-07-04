#ifndef GAME_START_H
#define GAME_START_H

#include "loadingScreen.h" // I include the loading screen to show the logo and the animated progress bar
#include "mainMenu.h"      // I include the main menu where the game mode selection function is located

// The main function I call to start the entire game
inline void startGame()
{
    showLoadingScreen(); // First, I show the loading screen so the user sees the logo and loading animation

    // After loading, I show the main menu where the player can choose to play solo, multiplayer, or exit
    gameModeMenu();
}

#endif // GAME_START_H
