#ifndef SLOT_MACHINE_GAME_H
#define SLOT_MACHINE_GAME_H

#include <iostream>
#include <string>
#include <algorithm>    // For std::transform, because sometimes we need to transform things, like our lives.
#include <cstdlib>      // For rand(), because luck doesn't generate itself.
#include <ctime>        // For time(), because we need to know what time it is while losing money.
#include <limits>       // For numeric_limits, because sometimes numbers are bigger than our hopes.
#include "player.h"     // For the Player structure, because we need to know who is losing.
#include "utils.h"      // For setColor, resetColor, clearConsole, waitMs, because life is more colorful with colors.
#include "playerData.h" // For registerGame, saveBalance, because we need to keep track of our misfortunes.

using namespace std;

// --- General Functions for the Slot Machine ---

// Function to change the text color, because sometimes we need a little color in our lives.
inline void setColor(int colorCode)
{
    cout << "\033[" << colorCode << "m"; // Magic! We change the color as if we had superpowers!
}

// Function to reset to white color, because sometimes we need to return to reality.
inline void resetColor()
{
    cout << "\033[0m"; // And back to square one! White is the new black.
}

// Function to show the game instructions, because no one wants to get lost in confusion.
inline void showSlot()
{
    clearConsole(); // Clear when showing instructions, because clutter helps no one.
    cout << endl;
    cout << "* - * - * - * - * - * - * - * - *. . . . . . . . . . . . . . " << endl;
    cout << "|                                                          . " << endl;
    cout << "*                  ";
    setColor(36); // cian
    cout << " -PLAY SLOT MACHINE-";
    resetColor();
    cout << "                    . " << endl;
    cout << "|                                                          . " << endl;
    cout << "*    A slot machine is a game where a series of random     . " << endl;
    cout << "|    symbols are displayed on each spin. If all the        . " << endl;
    cout << ".    symbols on a line match, you win.                     | " << endl;
    cout << ".                                                          * " << endl;
    cout << ".                                                          | " << endl;
    cout << ".    ";
    setColor(31); // red
    cout << "MENU (M)                 ";
    setColor(32); // green
    cout << "                PLAY (P)";
    resetColor();
    cout << "     * " << endl;
    cout << ".                                                          | " << endl;
    cout << ". . . . . . . . . . . . . .* - * - * - * - * - * - * - * - * " << endl;
    cout << endl;
}

// Function to show the difficulty menu of the slot game
inline void showSlotMenu()
{
    clearConsole(); // Clear when showing difficulty menu, because clarity is key.
    cout << endl;
    cout << "* - * - * - * - * - * - * - * -*. . . . . . . . . . . . . . " << endl;
    cout << "|                                                          . " << endl;
    cout << "*                     ";
    setColor(36); // cian
    cout << " -SLOT MACHINE-                    ";
    resetColor();
    cout << "  . " << endl;
    cout << "|                                                          . " << endl;
    cout << "*                  Choose the difficulty:                  . " << endl;
    cout << "|                                                          . " << endl;
    cout << ".   ";
    setColor(32); // green
    cout << "(E) EASY:";
    resetColor();
    cout << "      3 lines (Bet: $100, Win: $300)          | " << endl;
    cout << ".   ";
    setColor(32);
    cout << "(M) MEDIUM:";
    resetColor();
    cout << "    4 lines (Bet: $200, Win: $800)          * " << endl;
    cout << ".   ";
    setColor(32);
    cout << "(H) HARD:";
    resetColor();
    cout << "      5 lines (Bet: $300, Win: $1500)         | " << endl;
    cout << ".                                                          * " << endl;
    cout << ".     ";
    setColor(31); // red
    cout << "BACK (B)";
    resetColor();
    cout << "                                             | " << endl;
    cout << ". . . . . . . . . . . . . .* - * - * - * - * - * - * - * - * " << endl;
    cout << endl;
}

// Function to show a random motivational phrase when the player loses
inline void losePhrases()
{
    string lSentence_0 = "The next move could change everything…";           // Yes, right! As if that were going to happen.
    string lSentence_1 = "The reels don't move by themselves! Dare!";        // Come on, don't be a chicken!
    string lSentence_2 = "The reels are heating up… don’t give up!";         // Almost, almost! Like when you try to open a jar.
    string lSentence_3 = "Almost there! The next turn could be the winner."; // Hope is the last thing to lose!
    int randomLphrase = rand() % 4;                                          // Choose a phrase at random, because life is a roulette.

    switch (randomLphrase)
    {
    case 0:
        cout << endl;
        cout << lSentence_0 << endl;
        break;
    case 1:
        cout << endl;
        cout << lSentence_1 << endl;
        break;
    case 2:
        cout << endl;
        cout << lSentence_2 << endl;
        break;
    case 3:
        cout << endl;
        cout << lSentence_3 << endl;
        break;
    default:
        cout << endl;
        cout << "Luck turns around… and yours is about to return." << endl; // Or so I hope!
        break;
    }
}

// --- Functions for EASY MODE ---

inline void emptySlotsE()
{
    clearConsole(); // Clear when showing difficulty menu, because clarity is key.
    cout << endl;
    cout << endl;
    cout << "* - * - * - * - * - *. . . . . . . " << endl;
    cout << "|                                ." << endl;
    cout << "*          ";
    setColor(36); // cian
    cout << "Try your luck!";
    resetColor();
    cout << "        ." << endl;
    cout << "|                                ." << endl;
    cout << "*    -----------------------     ." << endl;
    cout << ".   |       |       |       |    |" << endl;
    cout << ".   |   -   |   -   |   -   |    *" << endl;
    cout << ".   |       |       |       |    |" << endl;
    cout << ".    -----------------------     *" << endl;
    cout << ".   | ";
    setColor(32); // green
    cout << "Pull the lever (!)";
    resetColor();
    cout << "|        |" << endl;
    cout << ". . . . . . .* - * - * - * - * - *" << endl;
    cout << endl;
}

inline char randomSymbolE()
{
    char symbol[] = {'@', '$', '7'}; // Classic symbols, because originality isn't always necessary.
    return symbol[rand() % 3];       // Choose a symbol at random, like in life.
}

inline void symbolColorE(char slots[3])
{
    for (int i = 0; i < 3; i++)
    {
        switch (slots[i])
        {
        case '$':
            setColor(34); // Blue, because money should be blue, right?
            cout << slots[i];
            resetColor();
            cout << "   | " << "  ";
            break;
        case '7':
            setColor(33); // Yellow, like gold... or a banana.
            cout << slots[i];
            resetColor();
            cout << "   | " << "  ";
            break;
        case '@':
            setColor(35); // Magenta, because sometimes you have to be a little extravagant.
            cout << slots[i];
            resetColor();
            cout << "   | " << "  ";
            break;
        default:
            setColor(36); // Cyan, because it's a color that isn't used much.
            cout << slots[i];
            resetColor();
            cout << "   | " << "  ";
            break;
        }
    }
}

inline void finalSlotsE(char slots[3])
{
    cout << "-----------------------------------" << endl; // Separator line, because we need a little drama.
    cout << "* - * - * - * - * - *. . . . . . . " << endl;
    cout << "|                                ." << endl;
    cout << "*            ";
    setColor(36); // cian
    cout << "RESULTS!";
    resetColor();
    cout << "            ." << endl;
    cout << "|                                ." << endl;
    cout << "*    -----------------------     ." << endl;
    cout << ".   |       |       |       |    *" << endl;
    // Random symbols will be displayed on this line
    cout << ".   |   ";
    symbolColorE(slots); // Call the function to display the generated symbols with their respective colors
    cout << " |" << endl;
    cout << ".   |       |       |       |    *" << endl;
    cout << ".    -----------------------     |" << endl;
    cout << ". . . . . . .* - * - * - * - * - *" << endl;
    cout << endl;
}

inline bool jackpotE(char slots[3])
{
    return (slots[0] == slots[1] && slots[1] == slots[2]); // Jackpot! Or as I like to call it, "beginner's luck".
}

// Main game easy
inline void easyMode(Player &player)
{
    const int BET = 100; // Minimum bet, because I don't want to ruin myself in the first round.
    const int WIN = 300; // Winnings, because dreaming is free.
    char symbols[3];
    bool wonJackpot = false;
    string anotherRound;

    if (player.money < BET)
    {
        setColor(31);
        cout << "You do not have enough money to play in Easy mode. You need $" << BET << ".\n";
        resetColor();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Press Enter to continue...";
        cin.get();
        return; // Exit, because nothing is sadder than a player without money.
    }

    while (true)
    {
        wonJackpot = false;   // Reset for each new round, as if nothing has happened.
        player.gamesPlayed++; // Count the game played, because we need to keep track of our misfortunes.

        cout << "\nYou have bet $" << BET << " for this round in Easy mode.\n";
        clearConsole();        // Clear when showing instructions, because clutter helps no one.
        int opportunities = 4; // Four opportunities, because I don't want to be too generous.
        for (int i = opportunities; i > 0; i--)
        {
            while (true)
            {
                string nextSpin;
                cout << endl;
                cout << "You have " << i << " opportunities left!" << endl;
                cout << "(P) to continue..." << endl;
                getline(cin, nextSpin);
                if (nextSpin == "P" || nextSpin == "p")
                {
                    break; // Let's spin those reels!
                }
                else
                {
                    cout << endl;
                    setColor(31);
                    cout << "Please enter a valid option (P), try again." << endl; // Error message, because we all need one.
                    resetColor();
                }
            }

            while (true)
            {
                string pull;
                emptySlotsE(); // This function already clears the console, because life is a cycle.
                getline(cin, pull);

                if (pull == "!")
                {
                    for (int j = 0; j < 3; j++)
                    {
                        symbols[j] = randomSymbolE(); // Generate random symbols, because life is a box of surprises.
                    }
                    finalSlotsE(symbols); // This function already clears the console, because the surprise is better without clutter.

                    if (jackpotE(symbols))
                    {
                        setColor(32);
                        cout << "            * JACKPOT!! *   " << endl; // Congratulations! You hit the jackpot.
                        resetColor();
                        cout << endl;
                        cout << " Congratulations! You won: $" << WIN << endl; // Money, money, money!
                        cout << endl;
                        player.money += WIN;                                                 // Add the winnings, because that's what we want.
                        player.gamesWon++;                                                   // Count the victory, because we need to celebrate.
                        registerGame("Slot Machine (Easy)", player.name, WIN, player.money); // Save the record, because history must be told.
                        wonJackpot = true;                                                   // Mark that we won, because there's nothing like a good jackpot.
                        i = 0;                                                               // End the opportunities, because we already won.
                        break;
                    }
                    else
                    {
                        setColor(36);
                        cout << "            KEEP TRYING " << endl; // Don't give up! Luck can change.
                        resetColor();
                        losePhrases(); // Motivational phrases, because we all need a push.
                        break;
                    }
                }
                else
                {
                    cout << endl;
                    setColor(31);
                    cout << "Please enter a valid option (!), try again." << endl; // Error message, because we all need one.
                    resetColor();
                }
            }
            if (wonJackpot)
                break; // If they already won, exit the opportunities loop, because that's enough excitement for today.
        }

        if (!wonJackpot)
        {
            cout << endl;
            cout << "   You'll have better luck next time." << endl; // Next time will be better!
            cout << "-$" << BET << endl;                             // Subtract the bet if they didn't win, because we need to learn to lose.
            cout << endl;
            player.money -= BET;                                                  // Subtract the bet if they didn't win, because we need to learn to lose.
            player.gamesLost++;                                                   // Count the loss, because we need to be realistic.
            registerGame("Slot Machine (Easy)", player.name, -BET, player.money); // Save the record, because history must be told.
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Press Enter to continue...";
            cin.get();
        }

        // Save balance and statistics after each game
        saveBalance(player.name, player.money); // Save the balance, because we don't want to lose it all.
        player.updateStatistics();              // Update statistics, because we need to keep track.

        if (player.money < BET)
        {
            setColor(31);
            cout << "You do not have enough money for another round in Easy mode. You need $" << BET << ".\n"; // Farewell message, because sometimes you need to know when to stop.
            resetColor();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Press Enter to continue...";
            cin.get();
            break; // Exit if there's no money for another bet, because we shouldn't be stubborn.
        }

        while (true)
        {
            setColor(36); // cian
            cout << "\nDo you want to play another round?\n"
                 << endl;
            setColor(32); // green
            cout << "     YES (Y).";
            setColor(31); // red
            cout << "        NO(N)" << endl;
            resetColor();
            getline(cin, anotherRound);

            if (anotherRound == "S" || anotherRound == "s")
            {
                cout << endl;
                setColor(32);
                cout << "GOOD LUCK!!" << endl; // May luck be with you!
                resetColor();
                break;
            }
            else if (anotherRound == "N" || anotherRound == "n")
            {
                cout << endl;
                cout << "Returning to the menu..." << endl; // Until next time!
                break;
            }
            else
            {
                cout << endl;
                setColor(31);
                cout << "Please enter a valid option (S) or (N), try again." << endl; // Error message, because we all need one.
                resetColor();
            }
        }

        if (anotherRound == "N" || anotherRound == "n")
        {
            break; // Exit the loop if the player doesn't want to continue, because we must respect decisions.
        }
    }
}

// --- Functions for MEDIUM MODE ---

inline void emptySlotsM()
{
    clearConsole(); // Clear when showing difficulty menu, because clarity is key.
    cout << endl;
    cout << "* - * - * - * - * - . . . . . . . . . . ." << endl;
    cout << "|                                       ." << endl;
    cout << "*             ";
    setColor(36); // cian
    cout << "Try your luck!";
    resetColor();
    cout << "            ." << endl;
    cout << "|                                       ." << endl;
    cout << "*    -------------------------------    ." << endl;
    cout << ".   |       |       |       |       |   ." << endl;
    cout << ".   |   -   |   -   |   -   |   -   |   *" << endl;
    cout << ".   |       |       |       |       |   |" << endl;
    cout << "*    -------------------------------    *" << endl;
    cout << ".    | ";
    setColor(32); // green
    cout << "Pull the lever (!)";
    resetColor();
    cout << "|              |" << endl;
    cout << ". . . . . . . . . . . . * - * - * - * - *" << endl;
    cout << endl;
}

inline char randomSymbolM()
{
    char symbol[] = {'$', '7', '@'}; // Classic symbols, because originality isn't always necessary.
    return symbol[rand() % 3];       // Choose a symbol at random, like in life.
}

inline void symbolColorM(char slots[4])
{
    for (int i = 0; i < 4; i++)
    {
        switch (slots[i])
        {
        case '$':
            setColor(34); // Blue, because money should be blue, right?
            cout << slots[i];
            resetColor();
            cout << "   | " << "  ";
            break;
        case '7':
            setColor(33); // Yellow, like gold... or a banana.
            cout << slots[i];
            resetColor();
            cout << "   | " << "  ";
            break;
        case '@':
            setColor(35); // Magenta, because sometimes you have to be a little extravagant.
            cout << slots[i];
            resetColor();
            cout << "   | " << "  ";
            break;
        default:
            setColor(36); // Cyan, because it's a color that isn't used much.
            cout << slots[i];
            resetColor();
            cout << "   | " << "  ";
            break;
        }
    }
}

inline void finalSlotsM(char slots[4])
{
    cout << "-----------------------------------------" << endl; // Separator line, because we need a little drama.
    cout << endl;
    cout << "* - * - * - * - * - . . . . . . . . . . ." << endl;
    cout << "|                                       ." << endl;
    cout << "*                ";
    setColor(36); // cian
    cout << "RESULTS!";
    resetColor();
    cout << "               ." << endl;
    cout << "|                                       ." << endl;
    cout << "*    -------------------------------    ." << endl;
    cout << ".   |       |       |       |       |   ." << endl;
    // Random symbols will be displayed on this line
    cout << ".   |   ";
    symbolColorM(slots); // Call the function to display the generated symbols with their respective colors
    cout << "*" << endl;
    cout << ".   |       |       |       |       |   |" << endl;
    cout << "*    -------------------------------    *" << endl;
    cout << ".                                       |" << endl;
    cout << ". . . . . . . . . . . . * - * - * - * - *" << endl;
    cout << endl;
}

inline bool jackpotM(char slots[4])
{
    return (slots[0] == slots[1] && slots[1] == slots[2] && slots[2] == slots[3]); // Jackpot! Or as I like to call it, "beginner's luck".
}

inline void mediumMode(Player &player)
{
    const int BET = 200; // Minimum bet, because I don't want to ruin myself in the first round.
    const int WIN = 800; // Winnings, because dreaming is free.
    char symbols[4];
    bool wonJackpot = false;
    string anotherRound;

    if (player.money < BET)
    {
        setColor(31);
        cout << "You do not have enough money to play in Medium mode. You need $" << BET << ".\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Press Enter to continue...";
        cin.get();
        resetColor();
        return; // Exit, because nothing is sadder than a player without money.
    }

    while (true)
    {
        wonJackpot = false;   // Reset for each new round, as if nothing has happened.
        player.gamesPlayed++; // Count the game played, because we need to keep track of our misfortunes.

        cout << "\nYou have bet $" << BET << " for this round in Medium mode.\n";

        int opportunities = 8; // Eight opportunities, because I don't want to be too generous.
        for (int i = opportunities; i > 0; i--)
        {
            while (true)
            {
                string nextSpin;
                cout << endl;
                cout << "You have " << i << " opportunities left!" << endl;
                cout << "(P) to continue..." << endl;
                getline(cin, nextSpin);
                if (nextSpin == "P" || nextSpin == "p")
                {
                    break; // Let's spin those reels!
                }
                else
                {
                    cout << endl;
                    setColor(31);
                    cout << "Please enter a valid option (P), try again." << endl; // Error message, because we all need one.
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Press Enter to continue...";
                    cin.get();
                    resetColor();
                }
            }

            while (true)
            {
                string pull;
                emptySlotsM(); // This function already clears the console, because life is a cycle.
                getline(cin, pull);

                if (pull == "!")
                {
                    for (int j = 0; j < 4; j++)
                    {
                        symbols[j] = randomSymbolM(); // Generate random symbols, because life is a box of surprises.
                    }
                    finalSlotsM(symbols); // This function already clears the console, because the surprise is better without clutter.

                    if (jackpotM(symbols))
                    {
                        setColor(32);
                        cout << "               * JACKPOT!! *   " << endl; // Congratulations! You hit the jackpot.
                        resetColor();
                        cout << endl;
                        cout << " Congratulations! You won: $" << WIN << endl; // Money, money, money!
                        cout << endl;
                        player.money += WIN;                                                   // Add the winnings, because that's what we want.
                        player.gamesWon++;                                                     // Count the victory, because we need to celebrate.
                        registerGame("Slot Machine (Medium)", player.name, WIN, player.money); // Save the record, because history must be told.
                        wonJackpot = true;                                                     // Mark that we won, because there's nothing like a good jackpot.
                        i = 0;                                                                 // End the opportunities, because we already won.
                        break;
                    }
                    else
                    {
                        setColor(36);
                        cout << "               KEEP TRYING " << endl; // Don't give up! Luck can change.
                        resetColor();
                        losePhrases(); // Motivational phrases, because we all need a push.
                        break;
                    }
                }
                else
                {
                    cout << endl;
                    setColor(31);
                    cout << "Please enter a valid option (!), try again." << endl; // Error message, because we all need one.
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Press Enter to continue...";
                    cin.get();
                    resetColor();
                }
            }
            if (wonJackpot)
                break; // If they already won, exit the opportunities loop, because that's enough excitement for today.
        }

        if (!wonJackpot)
        {
            cout << endl;
            cout << "   You'll have better luck next time." << endl; // Next time will be better!
            cout << "-$" << BET << endl;                             // Subtract the bet if they didn't win, because we need to learn to lose.
            cout << endl;
            player.money -= BET;                                                    // Subtract the bet if they didn't win, because we need to learn to lose.
            player.gamesLost++;                                                     // Count the loss, because we need to be realistic.
            registerGame("Slot Machine (Medium)", player.name, -BET, player.money); // Save the record, because history must be told.
        }

        saveBalance(player.name, player.money); // Save the balance, because we don't want to lose it all.
        player.updateStatistics();              // Update statistics, because we need to keep track.

        if (player.money < BET)
        {
            setColor(31);
            cout << "You do not have enough money for another round in Medium mode. You need $" << BET << ".\n"; // Farewell message, because sometimes you need to know when to stop.
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Press Enter to continue...";
            cin.get();
            resetColor();
            break; // Exit if there's no money for another bet, because we shouldn't be stubborn.
        }

        while (true)
        {
            setColor(36); // cian
            cout << "\nDo you want to play another round?\n"
                 << endl;
            setColor(32); // green
            cout << "     YES (S).";
            setColor(31); // red
            cout << "        NO(N)" << endl;
            resetColor();
            getline(cin, anotherRound);

            if (anotherRound == "S" || anotherRound == "s")
            {
                cout << endl;
                setColor(32);
                cout << "GOOD LUCK!!" << endl; // May luck be with you!
                resetColor();
                break;
            }
            else if (anotherRound == "N" || anotherRound == "n")
            {
                cout << endl;
                cout << "Returning to the menu..." << endl; // Until next time!
                break;
            }
            else
            {
                cout << endl;
                setColor(31);
                cout << "Please enter a valid option (S) or (N), try again." << endl; // Error message, because we all need one.
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Press Enter to continue...";
                cin.get();
                resetColor();
            }
        }

        if (anotherRound == "N" || anotherRound == "n")
        {
            break; // Exit the loop if the player doesn't want to continue, because we must respect decisions.
        }
    }
}

// --- Functions for HARD MODE ---

inline void emptySlotsH()
{
    clearConsole(); // Clear when showing difficulty menu, because clarity is key.
    cout << endl;
    cout << "* - * - * - * - * - * - * . . . . . . . . . . . ." << endl;
    cout << "|                                               ." << endl;
    cout << "*                 ";
    setColor(36); // cian
    cout << "Try your luck!";
    resetColor();
    cout << "                ." << endl;
    cout << "|                                               ." << endl;
    cout << "*    ---------------------------------------    ." << endl;
    cout << ".   |       |       |       |       |       |   ." << endl;
    cout << ".   |   -   |   -   |   -   |   -   |   -   |   *" << endl;
    cout << ".   |       |       |       |       |       |   |" << endl;
    cout << ".    ---------------------------------------    *" << endl;
    cout << ".    | ";
    setColor(32); // green
    cout << "Pull the lever (!)";
    resetColor();
    cout << "|                      |" << endl;
    cout << ". . . . . . . . . . . . * - * - * - * - * - * - *" << endl;
    cout << endl;
}

inline char randomSymbolH()
{
    char symbol[] = {'$', '7', '@'}; // Classic symbols, because originality isn't always necessary.
    return symbol[rand() % 3];       // Choose a symbol at random, like in life.
}

inline void symbolColorH(char slots[5])
{
    for (int i = 0; i < 5; i++)
    {
        switch (slots[i])
        {
        case '$':
            setColor(34); // Blue, because money should be blue, right?
            cout << slots[i];
            resetColor();
            cout << "   | " << "  ";
            break;
        case '7':
            setColor(33); // Yellow, like gold... or a banana.
            cout << slots[i];
            resetColor();
            cout << "   | " << "  ";
            break;
        case '@':
            setColor(35); // Magenta, because sometimes you have to be a little extravagant.
            cout << slots[i];
            resetColor();
            cout << "   | " << "  ";
            break;
        default:
            setColor(36); // Cyan, because it's a color that isn't used much.
            cout << slots[i];
            resetColor();
            cout << "   | " << "  ";
            break;
        }
    }
}

inline void finalSlotsH(char slots[5])
{
    cout << "--------------------------------------------------" << endl; // Separator line, because we need a little drama.
    cout << endl;
    cout << "* - * - * - * - * - * - * . . . . . . . . . . . ." << endl;
    cout << "|                                               ." << endl;
    cout << "*                    ";
    setColor(36); // cian
    cout << "RESULTS!";
    resetColor();
    cout << "                   ." << endl;
    cout << "|                                               ." << endl;
    cout << "*    ---------------------------------------    ." << endl;
    cout << ".   |       |       |       |       |       |   ." << endl;
    // Random symbols will be displayed on this line
    cout << ".   |   ";
    symbolColorH(slots);
    cout << "." << endl;
    cout << ".   |       |       |       |       |       |   |" << endl;
    cout << ".    ---------------------------------------    *" << endl;
    cout << ".                                               |" << endl;
    cout << ". . . . . . . . . . . . * - * - * - * - * - * - *" << endl;
    cout << endl;
}

inline bool jackpotH(char slots[5])
{
    return (slots[0] == slots[1] && slots[1] == slots[2] && slots[2] == slots[3] && slots[3] == slots[4]); // Jackpot! Or as I like to call it, "beginner's luck".
}

inline void hardMode(Player &player)
{
    const int BET = 300;  // Minimum bet, because I don't want to ruin myself in the first round.
    const int WIN = 1500; // Winnings, because dreaming is free.
    char symbols[5];
    bool wonJackpot = false;
    string anotherRound;

    if (player.money < BET)
    {
        setColor(31);
        cout << "You do not have enough money to play in Hard mode. You need $" << BET << ".\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Press Enter to continue...";
        cin.get();
        resetColor();
        return; // Exit, because nothing is sadder than a player without money.
    }

    while (true)
    {
        wonJackpot = false;   // Reset for each new round, as if nothing has happened.
        player.gamesPlayed++; // Count the game played, because we need to keep track of our misfortunes.

        cout << "\nYou have bet $" << BET << " for this round in Hard mode.\n";

        int opportunities = 15; // Fifteen opportunities, because life is short and we must take advantage.
        for (int i = opportunities; i > 0; i--)
        {
            while (true)
            {
                string nextSpin;
                cout << endl;
                cout << "You have " << i << " opportunities left!" << endl;
                cout << "(P) to continue..." << endl;
                getline(cin, nextSpin);
                if (nextSpin == "P" || nextSpin == "p")
                {
                    break; // Let's spin those reels!
                }
                else
                {
                    cout << endl;
                    setColor(31);
                    cout << "Please enter a valid option (P), try again." << endl; // Error message, because we all need one.
                    resetColor();
                }
            }

            while (true)
            {
                string pull;
                emptySlotsH(); // This function already clears the console, because life is a cycle.
                getline(cin, pull);

                if (pull == "!")
                {
                    for (int j = 0; j < 5; j++)
                    {
                        symbols[j] = randomSymbolH(); // Generate random symbols, because life is a box of surprises.
                    }
                    finalSlotsH(symbols); // This function already clears the console, because the surprise is better without clutter.

                    if (jackpotH(symbols))
                    {
                        setColor(32);
                        cout << "                   * JACKPOT!! *   " << endl; // Congratulations! You hit the jackpot.
                        resetColor();
                        cout << endl;
                        cout << " Congratulations! You won: $" << WIN << endl; // Money, money, money!
                        cout << endl;
                        player.money += WIN;                                                 // Add the winnings, because that's what we want.
                        player.gamesWon++;                                                   // Count the victory, because we need to celebrate.
                        registerGame("Slot Machine (Hard)", player.name, WIN, player.money); // Save the record, because history must be told.
                        wonJackpot = true;                                                   // Mark that we won, because there's nothing like a good jackpot.
                        i = 0;                                                               // End the opportunities, because we already won.
                        break;
                    }
                    else
                    {
                        setColor(36);
                        cout << "                   KEEP TRYING " << endl; // Don't give up! Luck can change.
                        resetColor();
                        losePhrases(); // Motivational phrases, because we all need a push.
                        break;
                    }
                }
                else
                {
                    cout << endl;
                    setColor(31);
                    cout << "Please enter a valid option (!), try again." << endl; // Error message, because we all need one.
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Press Enter to continue...";
                    cin.get();
                    resetColor();
                }
            }
            if (wonJackpot)
                break; // If they already won, exit the opportunities loop, because that's enough excitement for today.
        }

        if (!wonJackpot)
        {
            cout << endl;
            cout << "   You'll have better luck next time." << endl; // Next time will be better!
            cout << "-$" << BET << endl;                             // Subtract the bet if they didn't win, because we need to learn to lose.
            cout << endl;
            player.money -= BET;                                                  // Subtract the bet if they didn't win, because we need to learn to lose.
            player.gamesLost++;                                                   // Count the loss, because we need to be realistic.
            registerGame("Slot Machine (Hard)", player.name, -BET, player.money); // Save the record, because history must be told.
        }

        saveBalance(player.name, player.money); // Save the balance, because we don't want to lose it all.
        player.updateStatistics();              // Update statistics, because we need to keep track.

        if (player.money < BET)
        {
            setColor(31);
            cout << "You do not have enough money for another round in Hard mode. You need $" << BET << ".\n"; // Farewell message, because sometimes you need to know when to stop.
            resetColor();
            break; // Exit if there's no money for another bet, because we shouldn't be stubborn.
        }

        while (true)
        {
            setColor(36); // cian
            cout << "\nDo you want to play another round?" << endl;
            setColor(32); // green
            cout << "     YES (S).";
            setColor(31); // red
            cout << "        NO(N)" << endl;
            resetColor();
            getline(cin, anotherRound);

            if (anotherRound == "S" || anotherRound == "s")
            {
                cout << endl;
                setColor(32);
                cout << "GOOD LUCK!!" << endl; // May luck be with you!
                resetColor();
                break;
            }
            else if (anotherRound == "N" || anotherRound == "n")
            {
                cout << endl;
                cout << "Returning to the menu..." << endl; // Until next time!
                break;
            }
            else
            {
                cout << endl;
                setColor(31);
                cout << "Please enter a valid option (S) or (N), try again." << endl; // Error message, because we all need one.
                resetColor();
            }
        }

        if (anotherRound == "N" || anotherRound == "n")
        {
            break; // Exit the loop if the player doesn't want to continue, because we must respect decisions.
        }
    }
}

// --- Main Function for the Slot Machine Game ---

inline void playSlotMachine(Player &player)
{
    if (player.money <= 0)
    {
        cout << "You do not have enough balance. Deposit to play.\n"; // Message of "no money, no game".
        return;                                                       // Exit, because nothing is sadder than a player without money.
    }

    while (true)
    {
        showSlot(); // This function already clears the console, because freshness is key.
        string option;
        getline(cin, option); // User enters option

        // Verification of entered option
        if (option == "M" || option == "m")
        {
            cout << "Returning to the main menu..." << endl; // Message of "see you later".
            break;
        }
        else if (option == "P" || option == "p")
        {
            while (true)
            {
                showSlotMenu(); // This function already clears the console, because freshness is key.
                string difficultyOption;
                getline(cin, difficultyOption); // User enters their option

                if (difficultyOption == "B" || difficultyOption == "b")
                {
                    break;
                }
                else if (difficultyOption == "E" || difficultyOption == "e")
                {
                    easyMode(player); // Mode functions already handle their cleanup, because freshness is key.
                }
                else if (difficultyOption == "M" || difficultyOption == "m")
                {
                    mediumMode(player); // Mode functions already handle their cleanup, because freshness is key.
                }
                else if (difficultyOption == "H" || difficultyOption == "h")
                {
                    hardMode(player); // Mode functions already handle their cleanup, because freshness is key.
                }
                else
                {
                    setColor(31);
                    cout << "Please enter a valid option (E), (M), (H) or (B), try again." << endl; // Error message, because we all need one.
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Press Enter to continue...";
                    cin.get();
                    resetColor();
                }
            }
        }
        else
        {
            setColor(31);
            cout << "Please enter a valid option (M) or (P), try again." << endl; // Error message, because we all need one.
            resetColor();
        }
    }
}

#endif // SLOT_MACHINE_GAME_H