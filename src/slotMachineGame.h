#ifndef SLOT_MACHINE_GAME_H
#define SLOT_MACHINE_GAME_H

#include <iostream>
#include <string>
#include <algorithm>    // For std::transform, because sometimes we need to transform things — like our lives.
#include <cstdlib>      // For rand(), because luck doesn't generate itself.
#include <ctime>        // For time(), because we need to know what time it is while we lose money.
#include <limits>       // For numeric_limits, because sometimes numbers are bigger than our hopes.
#include "jugador.h"    // For the Jugador structure, because we need to know who's losing.
#include "utils.h"      // For setColor, resetColor, limpiarConsola, esperarMs — because life is more colorful with colors.
#include "playerData.h" // For registrarJuego, guardarSaldo — because we need to keep track of our misfortunes.

using namespace std;

// --- General Slot Machine Functions ---

// Function to change text color, because sometimes we need a bit of color in our life.
inline void setColor(int colorCode)
{
    cout << "\033[" << colorCode << "m"; // Magic! We change the color as if we had superpowers!
}

// Function to reset to white color, because sometimes we have to come back to reality.
inline void resetColor()
{
    cout << "\033[0m"; // And back to the start! White is the new black.
}

// Function to display game instructions, because nobody wants to be lost in confusion.
inline void showSlot()
{
    clearConsole(); // Clear screen when showing instructions, because clutter helps no one.
    cout << endl;
    cout << "* - * - * - * - * - * - * - * - *. . . . . . . . . . . . . . " << endl;
    cout << "|                                                          . " << endl;
    cout << "*                   -PLAY SLOT MACHINE-                    . " << endl;
    cout << "|                                                          . " << endl;
    cout << "*    A slot machine is a game where a series of random     . " << endl;
    cout << "|    symbols are displayed on each spin. If all the        . " << endl;
    cout << ".    symbols on a line match, you win.                     | " << endl;
    cout << ".                                                          * " << endl;
    cout << ".                                                          | " << endl;
    cout << ".    MENU (M)                                 PLAY (P)     * " << endl;
    cout << ".                                                          | " << endl;
    cout << ". . . . . . . . . . . . . .* - * - * - * - * - * - * - * - * " << endl;
    cout << endl;
}

// Function to show the slot machine difficulty menu
inline void showSlotmenu()
{
    clearConsole(); // Clear screen when showing difficulty menu, because clarity is key.
    cout << endl;
    cout << "* - * - * - * - * - * - * - * -*. . . . . . . . . . . . . . " << endl;
    cout << "|                                                          . " << endl;
    cout << "*                      -SLOT MACHINE-                      . " << endl;
    cout << "|                                                          . " << endl;
    cout << "*                  Choose the difficulty:                  . " << endl;
    cout << "|                                                          . " << endl;
    cout << ".   (E) EASY:      3 lines (Bet: $100, Win: $300)          | " << endl;
    cout << ".   (M) MEDIUM:    4 lines (Bet: $200, Win: $800)          * " << endl;
    cout << ".   (H) HARD:      5 lines (Bet: $300, Win: $1500)         | " << endl;
    cout << ".                                                          * " << endl;
    cout << ".     BACK (B)                                             | " << endl;
    cout << ". . . . . . . . . . . . . .* - * - * - * - * - * - * - * - * " << endl;
    cout << endl;
}

// Function to display a random motivational phrase when the player loses
inline void losePhrases()
{
    string lSentence_0 = "The next move could change everything…";           // Sure… like that's going to happen.
    string lSentence_1 = "The reels don't move by themselves! Dare!";        // Come on, don’t be a chicken!
    string lSentence_2 = "The reels are heating up… don’t give up!";         // So close! Like trying to open a jar.
    string LSentence_3 = "Almost there! The next turn could be the winner."; // Hope is the last thing to die!
    int randomLphase = rand() % 4;                                           // Pick a phrase at random, because life is a roulette.

    switch (randomLphase)
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
        cout << LSentence_3 << endl;
        break;
    default:
        cout << endl;
        cout << "Luck turns around… and yours is about to return." << endl; // Or so we hope!
        break;
    }
}

// --- Functions for Easy Mode ---

inline void emptySlotsE()
{
    clearConsole(); // Clear screen when showing difficulty menu, because clarity is key.
    cout << endl;
    cout << "* - * - * - * - * - *. . . . . . . " << endl;
    cout << "|                                ." << endl;
    cout << "*          Try your luck!        ." << endl;
    cout << "|                                ." << endl;
    cout << "*    -----------------------     ." << endl;
    cout << ".   |       |       |       |    | " << endl;
    cout << ".   |   -   |   -   |   -   |    *" << endl;
    cout << ".   |       |       |       |    | " << endl;
    cout << ".    -----------------------     *" << endl;
    cout << ".   | Pull the lever (!)|        | " << endl;
    cout << ". . . . . . .* - * - * - * - * - *" << endl;
    cout << endl;
}

inline char randomSymbolE()
{
    char symbol[] = {'@', '$', '7'}; // Classic symbols, because originality isn’t always necessary.
    return symbol[rand() % 3];       // Choose a random symbol, just like in life.
}

inline void symbolColorE(char slots[3])
{
    for (int i = 0; i < 3; i++)
    {
        switch (slots[i])
        {
        case '$':
            setColor(34); // Blue, because money *should* be blue, right?
            cout << slots[i];
            resetColor();
            cout << "   | " << "  ";
            break;
        case '7':
            setColor(33); // Yellow, like gold... or bananas.
            cout << slots[i];
            resetColor();
            cout << "   | " << "  ";
            break;
        case '@':
            setColor(35); // Magenta, because sometimes you have to be a bit extravagant.
            cout << slots[i];
            resetColor();
            cout << "   | " << "  ";
            break;
        default:
            setColor(36); // Cyan, because it’s a color that’s rarely used.
            cout << slots[i];
            resetColor();
            cout << "   | " << "  ";
            break;
        }
    }
}

inline void finalSlotsE(char slots[3])
{
    cout << "---------------------------------" << endl; // Divider line — adds a bit of drama.
    cout << "* - * - * - * - * - *. . . . . . . " << endl;
    cout << "|                                ." << endl;
    cout << "*            RESULTS!            ." << endl;
    cout << "|                                ." << endl;
    cout << "*    -----------------------     ." << endl;
    cout << ".   |       |       |       |    * " << endl;
    cout << ".   |   ";
    symbolColorE(slots); // Display the colored symbols, because life is more fun in color.
    cout << " |" << endl;
    cout << ".   |       |       |       |    * " << endl;
    cout << ".    -----------------------     | " << endl;
    cout << ". . . . . . .* - * - * - * - * - *" << endl;
    cout << endl;
}

inline bool jackpotE(char slots[3])
{
    return (slots[0] == slots[1] && slots[1] == slots[2]); // Jackpot! Or as I like to call it, “beginner’s luck.”
}

// Main game easy
inline void easyMode(Jugador &jugador)
{
    const int APUESTA = 100;  // Minimum bet, because I don't want to go broke in the first round.
    const int GANANCIA = 300; // Prize, because dreaming is free.
    char symbols[3];
    bool ganoJackpot = false;
    string anotherRound;

    if (jugador.dinero < APUESTA)
    {
        cout << "You don't have enough money to play in Easy Mode. You need $" << APUESTA << ".\n";
        return; // We exit, because there's nothing sadder than a player without money.
    }

    while (true)
    {
        ganoJackpot = false;       // Reset for each new round, as if nothing ever happened.
        jugador.partidasJugadas++; // Count the played round, because we need to keep track of our misfortunes.

        cout << "\nYou have bet $" << APUESTA << " for this round in Easy Mode.\n";
        clearConsole();      // Clear screen when showing instructions, because clutter helps no one.
        int oportunidades = 4; // Four chances, because I don't want to be too generous.
        for (int i = oportunidades; i > 0; i--)
        {
            while (true)
            {
                string nextSpin;
                cout << endl;
                cout << "You have " << i << " chances left!" << endl;
                cout << "Press (P) to continue..." << endl;
                getline(cin, nextSpin);
                if (nextSpin == "P" || nextSpin == "p")
                {
                    break; // Let's spin those reels!
                }
                else
                {
                    cout << endl;
                    setColor(31);
                    cout << "Please enter a valid option (P), try again." << endl; // Error message, because we all need it.
                    resetColor();
                }
            }

            while (true)
            {
                string pull;
                emptySlotsE(); // This function already clears the screen, because life is a cycle.
                getline(cin, pull);

                if (pull == "!")
                {
                    for (int j = 0; j < 3; j++)
                    {
                        symbols[j] = randomSymbolE(); // Generate random symbols, because life is a box of surprises.
                    }
                    finalSlotsE(symbols); // This function already clears the screen, because surprises are better without clutter.

                    if (jackpotE(symbols))
                    {
                        setColor(32);
                        cout << "            * JACKPOT!! *   " << endl; // Congrats! You've hit the big prize.
                        resetColor();
                        cout << endl;
                        cout << " Congratulations! You've won: $" << GANANCIA << endl; // Money, money, money!
                        cout << endl;
                        jugador.dinero += GANANCIA;                                                      // Add the prize, because that’s what we want.
                        jugador.partidasGanadas++;                                                       // Count the win, because we need to celebrate.
                        registrarJuego("Slot Machine (Easy)", jugador.nombre, GANANCIA, jugador.dinero); // Save the log, because history must be recorded.
                        ganoJackpot = true;                                                              // Mark that we won, because there’s nothing like a good jackpot.
                        i = 0;                                                                           // End the remaining chances, because we've already won.
                        break;
                    }
                    else
                    {
                        setColor(36);
                        cout << "            KEEP TRYING " << endl; // Don’t give up! Luck can change.
                        resetColor();
                        losePhrases(); // Motivational phrases, because we all need a little push.
                        break;
                    }
                }
                else
                {
                    cout << endl;
                    setColor(31);
                    cout << "Please enter a valid option (!), try again." << endl; // Error message, because we all need it.
                    resetColor();
                }
            }
            if (ganoJackpot)
                break; // If player won, exit the chances loop, because that’s enough excitement for today.
        }
        if (!ganoJackpot)
        {
            cout << endl;
            cout << "   Better luck next time." << endl; // Next time will be better!
            cout << "-$" << APUESTA << endl;             // Subtract the bet, because life isn't always fair.
            cout << endl;
            jugador.dinero -= APUESTA;                                                       // Subtract the bet if not won, because losing is part of the game.
            jugador.partidasPerdidas++;                                                      // Count the loss, because we have to be realistic.
            registrarJuego("Slot Machine (Easy)", jugador.nombre, -APUESTA, jugador.dinero); // Save the log, because the story must be told.
        }

        // Save balance and stats after each round
        guardarSaldo(jugador.nombre, jugador.dinero); // Save the balance, because we don’t want to lose everything.
        jugador.actualizarEstadisticas();             // Update stats, because we must keep track.

        if (jugador.dinero < APUESTA)
        {
            cout << "You don't have enough money for another round in Easy Mode. You need $" << APUESTA << ".\n"; // Goodbye message, because sometimes you need to know when to stop.
            break;                                                                                                // Exit if there's not enough money for another bet, because there's no point in being stubborn.
        }

        while (true)
        {
            cout << "\nDo you want to play another round?" << endl;
            cout << "     YES (S).        NO (N)" << endl;
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
                cout << "Returning to menu..." << endl; // Until next time!
                break;
            }
            else
            {
                cout << endl;
                setColor(31);
                cout << "Please enter a valid option (S) or (N), try again." << endl; // Error message, because we all need it.
                resetColor();
            }
        }

        if (anotherRound == "N" || anotherRound == "n")
        {
            break; // Exit the loop if the player doesn’t want to continue, because we respect decisions.
        }
    }
}

// --- Functions for Medium Mode (MEDIUM MODE) ---

inline void emptySlotsM()
{
    clearConsole(); // Clear screen when showing difficulty menu, because clarity is key.
    cout << endl;
    cout << "* - * - * - * - * - . . . . . . . . . . . " << endl;
    cout << "|                                       ." << endl;
    cout << "*             Try your luck!            ." << endl;
    cout << "|                                       ." << endl;
    cout << "*    -------------------------------    ." << endl;
    cout << ".   |       |       |       |       |   . " << endl;
    cout << ".   |   -   |   -   |   -   |   -   |   *" << endl;
    cout << ".   |       |       |       |       |   | " << endl;
    cout << "*    -------------------------------    *" << endl;
    cout << ".    | Pull the lever (!)|              | " << endl;
    cout << ". . . . . . . . . . . . * - * - * - * - * " << endl;
    cout << endl;
}
inline char randomSymbolM()
{
    char symbol[] = {'$', '7', '@'}; // Classic symbols, because originality isn't always necessary.
    return symbol[rand() % 3];       // We pick a random symbol—just like life.
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
            setColor(33); // Yellow, like gold... or bananas.
            cout << slots[i];
            resetColor();
            cout << "   | " << "  ";
            break;
        case '@':
            setColor(35); // Magenta, because sometimes you have to be a little flashy.
            cout << slots[i];
            resetColor();
            cout << "   | " << "  ";
            break;
        default:
            setColor(36); // Cyan, because it’s a color people don’t use much.
            cout << slots[i];
            resetColor();
            cout << "   | " << "  ";
            break;
        }
    }
}

inline void finalSlotsM(char slots[4])
{
    cout << "---------------------------------" << endl; // A dividing line, because we need some drama.
    cout << "* - * - * - * - * - . . . . . . . . . . . " << endl;
    cout << "|                                       ." << endl;
    cout << "*                RESULTS!               ." << endl;
    cout << "|                                       ." << endl;
    cout << "*    -------------------------------    ." << endl;
    cout << ".   |       |       |       |       |   . " << endl;
    cout << ".   |   ";
    symbolColorM(slots); // We show the symbols in color, because life is more fun in color.
    cout << "*" << endl;
    cout << ".   |       |       |       |       |   | " << endl;
    cout << "*    -------------------------------    *" << endl;
    cout << ".    | Pull the lever (!)|              | " << endl;
    cout << ". . . . . . . . . . . . * - * - * - * - * " << endl;
    cout << endl;
}

inline bool jackpotM(char slots[4])
{
    return (slots[0] == slots[1] && slots[1] == slots[2] && slots[2] == slots[3]); // Jackpot! Or as I like to call it, "beginner's luck".
}

inline void mediumMode(Jugador &jugador)
{
    const int APUESTA = 200;  // Minimum bet, because I don’t want to go broke in the first round.
    const int GANANCIA = 800; // Payout, because dreaming is free.
    char symbols[4];
    bool ganoJackpot = false;
    string anotherRound;

    if (jugador.dinero < APUESTA)
    {
        cout << "You don’t have enough money to play Medium Mode. You need $" << APUESTA << ".\n";
        return; // Exit, because there’s nothing sadder than a player with no money.
    }

    while (true)
    {
        ganoJackpot = false;       // Reset for each new round, as if nothing ever happened.
        jugador.partidasJugadas++; // Count the round played, because we must track our misfortunes.

        cout << "\nYou bet $" << APUESTA << " for this round in Medium Mode.\n";

        int oportunidades = 8; // Eight chances, because I don’t want to be too generous.
        for (int i = oportunidades; i > 0; i--)
        {
            while (true)
            {
                string nextSpin;
                cout << endl;
                cout << "You have " << i << " chances left!" << endl;
                cout << "(P) to continue..." << endl;
                getline(cin, nextSpin);
                if (nextSpin == "P" || nextSpin == "p")
                {
                    break; // Let’s spin those reels!
                }
                else
                {
                    cout << endl;
                    setColor(31);
                    cout << "Please enter a valid option (P), try again." << endl; // Error message, because we all need guidance.
                    resetColor();
                }
            }

            while (true)
            {
                string pull;
                emptySlotsM(); // This function already clears the screen—because life is cyclical.
                getline(cin, pull);

                if (pull == "!")
                {
                    for (int j = 0; j < 4; j++)
                    {
                        symbols[j] = randomSymbolM(); // Generate random symbols, because life is a box of surprises.
                    }
                    finalSlotsM(symbols); // This function already clears the screen—surprises are better without clutter.

                    if (jackpotM(symbols))
                    {
                        setColor(32);
                        cout << "               * JACKPOT!! *   " << endl; // Congratulations! You hit the jackpot.
                        resetColor();
                        cout << endl;
                        cout << " Congratulations! You won: $" << GANANCIA << endl; // Money, money, money!
                        cout << endl;
                        jugador.dinero += GANANCIA;                                                        // Add winnings—because that’s what we’re here for.
                        jugador.partidasGanadas++;                                                         // Count the win—because it’s worth celebrating.
                        registrarJuego("Slot Machine (Medium)", jugador.nombre, GANANCIA, jugador.dinero); // Save the record—because history must be told.
                        ganoJackpot = true;                                                                // Mark the win—because there’s nothing like a good jackpot.
                        i = 0;                                                                             // End the remaining attempts—because that's enough excitement for now.
                        break;
                    }
                    else
                    {
                        setColor(36);
                        cout << "               KEEP TRYING " << endl; // Don’t give up! Luck can change.
                        resetColor();
                        losePhrases(); // Motivational phrases—because everyone needs a push.
                        break;
                    }
                }
                else
                {
                    cout << endl;
                    setColor(31);
                    cout << "Please enter a valid option (!), try again." << endl; // Error message, because we all need guidance.
                    resetColor();
                }
            }
            if (ganoJackpot)
                break; // Exit opportunity loop if won—because that’s enough adrenaline for today.
        }

        if (!ganoJackpot)
        {
            cout << endl;
            cout << "   Better luck next time." << endl; // Next time will be better!
            cout << "-$" << APUESTA << endl;             // Deduct the bet—because life isn’t always fair.
            cout << endl;
            jugador.dinero -= APUESTA;                                                         // Deduct money if no win—because we must learn to lose.
            jugador.partidasPerdidas++;                                                        // Count the loss—because we need to be realistic.
            registrarJuego("Slot Machine (Medium)", jugador.nombre, -APUESTA, jugador.dinero); // Save the record—because history must be told.
        }
        guardarSaldo(jugador.nombre, jugador.dinero); // Save the balance, because we don’t want to lose everything.
        jugador.actualizarEstadisticas();             // Update statistics—because we need to keep track.

        if (jugador.dinero < APUESTA)
        {
            cout << "You don’t have enough money for another round in Medium Mode. You need $" << APUESTA << ".\n"; // Farewell message—sometimes you need to know when to stop.
            break;                                                                                                  // Exit if there’s not enough money—because stubbornness doesn’t pay off.
        }

        while (true)
        {
            cout << "\nDo you want to play another round?" << endl;
            cout << "     YES (S).        NO (N)" << endl;
            getline(cin, anotherRound);

            if (anotherRound == "S" || anotherRound == "s")
            {
                cout << endl;
                setColor(32);
                cout << "GOOD LUCK!!" << endl; // May the odds be ever in your favor!
                resetColor();
                break;
            }
            else if (anotherRound == "N" || anotherRound == "n")
            {
                cout << endl;
                cout << "Returning to menu..." << endl; // Until next time!
                break;
            }
            else
            {
                cout << endl;
                setColor(31);
                cout << "Please enter a valid option (S) or (N), try again." << endl; // Error message—because we all need guidance.
                resetColor();
            }
        }

        if (anotherRound == "N" || anotherRound == "n")
        {
            break; // Exit loop if the player doesn’t want to continue—because we must respect decisions.
        }
    }
}

// --- Functions for Hard Mode ---

inline void emptySlotsH()
{
    clearConsole(); // Clear screen when showing difficulty menu—clarity is key.
    cout << endl;
    cout << "* - * - * - * - * - * - * . . . . . . . . . . . . " << endl;
    cout << "|                                               ." << endl;
    cout << "*                 Try your luck!                ." << endl;
    cout << "|                                               ." << endl;
    cout << "*    ---------------------------------------    ." << endl;
    cout << ".   |       |       |       |       |       |   . " << endl;
    cout << ".   |   -   |   -   |   -   |   -   |   -   |   *" << endl;
    cout << ".   |       |       |       |       |       |   | " << endl;
    cout << ".    ---------------------------------------    *" << endl;
    cout << ".    | Pull the lever (!)|                      | " << endl;
    cout << ". . . . . . . . . . . . * - * - * - * - * - * - * " << endl;
    cout << endl;
}

inline char randomSymbolH()
{
    char symbol[] = {'$', '7', '@'}; // Classic symbols—because originality isn’t always necessary.
    return symbol[rand() % 3];       // Pick a random symbol, just like in life.
}

inline void symbolColorH(char slots[5])
{
    for (int i = 0; i < 5; i++)
    {
        switch (slots[i])
        {
        case '$':
            setColor(34); // Blue—because money *should* be blue, right?
            cout << slots[i];
            resetColor();
            cout << "   | " << "  ";
            break;
        case '7':
            setColor(33); // Yellow, like gold... or bananas.
            cout << slots[i];
            resetColor();
            cout << "   | " << "  ";
            break;
        case '@':
            setColor(35); // Magenta—because sometimes, you’ve got to be a bit extravagant.
            cout << slots[i];
            resetColor();
            cout << "   | " << "  ";
            break;
        default:
            setColor(36); // Cyan—because it’s a color that doesn’t get enough love.
            cout << slots[i];
            resetColor();
            cout << "   | " << "  ";
            break;
        }
    }
}

inline void finalSlotsH(char slots[5])
{
    cout << "---------------------------------" << endl; // Separator line—because we need a bit of drama.
    cout << "* - * - * - * - * - * - * . . . . . . . . . . . . " << endl;
    cout << "|                                               ." << endl;
    cout << "*                    RESULTS!                   ." << endl;
    cout << "|                                               ." << endl;
    cout << "*    ---------------------------------------    ." << endl;
    cout << ".   |       |       |       |       |       |   . " << endl;
    cout << ".   |   ";
    symbolColorH(slots); // Show the symbols in color—because life is more fun in color.
    cout << "." << endl;
    cout << ".   |       |       |       |       |       |   | " << endl;
    cout << ".    ---------------------------------------    *" << endl;
    cout << ".    | Pull the lever (!)|                      | " << endl;
    cout << ". . . . . . . . . . . . * - * - * - * - * - * - * " << endl;
    cout << endl;
}

inline bool jackpotH(char slots[5])
{
    return (slots[0] == slots[1] && slots[1] == slots[2] && slots[2] == slots[3] && slots[3] == slots[4]); // Jackpot! Or as I like to call it: beginner’s luck.
}
inline void hardMode(Jugador &jugador)
{
    const int APUESTA = 300;   // Minimum bet—because I don’t want to go broke in the first round.
    const int GANANCIA = 1500; // Prize—because dreaming is free.
    char symbols[5];
    bool ganoJackpot = false;
    string anotherRound;

    if (jugador.dinero < APUESTA)
    {
        cout << "You don’t have enough money to play in Hard Mode. You need $" << APUESTA << ".\n";
        return; // Exit—because there’s nothing sadder than a player without money.
    }

    while (true)
    {
        ganoJackpot = false;       // Reset each new round—as if nothing happened.
        jugador.partidasJugadas++; // Count the played round—because we have to keep track of our misfortunes.

        cout << "\nYou’ve bet $" << APUESTA << " for this round in Hard Mode.\n";

        int oportunidades = 15; // Fifteen chances—because life is short and we’ve got to make the most of it.
        for (int i = oportunidades; i > 0; i--)
        {
            while (true)
            {
                string nextSpin;
                cout << endl;
                cout << "You have " << i << " chances left!" << endl;
                cout << "(P) to continue..." << endl;
                getline(cin, nextSpin);
                if (nextSpin == "P" || nextSpin == "p")
                {
                    break; // Time to spin those reels!
                }
                else
                {
                    cout << endl;
                    setColor(31);
                    cout << "Please enter a valid option (P), try again." << endl; // Error message—because we all need guidance.
                    resetColor();
                }
            }

            while (true)
            {
                string pull;
                emptySlotsH(); // This function already clears the console—because life is a cycle.
                getline(cin, pull);

                if (pull == "!")
                {
                    for (int j = 0; j < 5; j++)
                    {
                        symbols[j] = randomSymbolH(); // Generate random symbols—because life is a box of surprises.
                    }
                    finalSlotsH(symbols); // This function shows the final reel—because surprises are best without clutter.

                    if (jackpotH(symbols))
                    {
                        setColor(32);
                        cout << "                   * JACKPOT!! *   " << endl; // Congrats! You hit the big one.
                        resetColor();
                        cout << endl;
                        cout << " Congratulations! You’ve won: $" << GANANCIA << endl; // Money, money, money!
                        cout << endl;
                        jugador.dinero += GANANCIA;                                                      // Add the prize—because that’s what we’re here for.
                        jugador.partidasGanadas++;                                                       // Count the win—because every victory matters.
                        registrarJuego("Slot Machine (Hard)", jugador.nombre, GANANCIA, jugador.dinero); // Save the record—because history must be written.
                        ganoJackpot = true;                                                              // Mark the win—because there’s nothing like a good jackpot.
                        i = 0;                                                                           // End the chances—because the excitement is enough for one day.
                        break;
                    }
                    else
                    {
                        setColor(36);
                        cout << "                   KEEP TRYING " << endl; // Don’t give up! Luck can change.
                        resetColor();
                        losePhrases(); // Motivational phrases—because we all need a little push.
                        break;
                    }
                }
                else
                {
                    cout << endl;
                    setColor(31);
                    cout << "Please enter a valid option (!), try again." << endl; // Error message—because we all need help sometimes.
                    resetColor();
                }
            }
            if (ganoJackpot)
                break; // If player won, break the chance loop—because that’s enough thrill for today.
        }

        if (!ganoJackpot)
        {
            cout << endl;
            cout << "   Better luck next time." << endl; // Next time will be better!
            cout << "-$" << APUESTA << endl;             // Subtract the bet—because life isn’t always fair.
            cout << endl;
            jugador.dinero -= APUESTA;                                                       // Subtract the bet if the player didn’t win—because we have to learn to lose.
            jugador.partidasPerdidas++;                                                      // Count the loss—because we have to be realistic.
            registrarJuego("Slot Machine (Hard)", jugador.nombre, -APUESTA, jugador.dinero); // Save the game record—because the story must be told.
        }

        guardarSaldo(jugador.nombre, jugador.dinero); // Save the balance—because we don’t want to lose it all.
        jugador.actualizarEstadisticas();             // Update stats—because someone’s got to keep track.

        if (jugador.dinero < APUESTA)
        {
            cout << "You don’t have enough money for another round in Hard Mode. You need $" << APUESTA << ".\n"; // Goodbye message—because sometimes you need to know when to stop.
            break;                                                                                                // Exit if there’s not enough for another bet—because stubbornness won’t help.
        }

        while (true)
        {
            cout << "\nDo you want to play another round?" << endl;
            cout << "     YES (Y).        NO (N)" << endl;
            getline(cin, anotherRound);

            if (anotherRound == "S" || anotherRound == "s")
            {
                cout << endl;
                setColor(32);
                cout << "GOOD LUCK!!" << endl; // May the odds be ever in your favor!
                resetColor();
                break;
            }
            else if (anotherRound == "N" || anotherRound == "n")
            {
                cout << endl;
                cout << "Returning to the menu..." << endl; // See you next time!
                break;
            }
            else
            {
                cout << endl;
                setColor(31);
                cout << "Please enter a valid option (S) or (N), try again." << endl; // Error message—because we all need a little help sometimes.
                resetColor();
            }
        }

        if (anotherRound == "N" || anotherRound == "n")
        {
            break; // Exit the loop if the player doesn’t want to continue—because you have to respect their decision.
        }
    }
}

// --- Main Slot Machine Game Function ---

inline void playSlotMachine(Jugador &jugador)
{
    if (jugador.dinero <= 0)
    {

        cout << "You don’t have enough balance. Please deposit to play.\n"; // Message: "No money, no game".
        return;                                                             // Exit, because nothing is sadder than a player with no money.
    }

    while (true)
    {
        showSlot(); // This function already clears the console, because freshness is key.
        string option;
        getline(cin, option); // User inputs option

        // Check the input option
        if (option == "M" || option == "m")
        {

            cout << "Returning to the main menu..." << endl; // Farewell message.
            break;
        }
        else if (option == "P" || option == "p")
        {
            while (true)
            {
                showSlotmenu(); // This function already clears the console, because freshness is key.
                string difficultyOption;
                getline(cin, difficultyOption); // User inputs their choice

                if (difficultyOption == "B" || difficultyOption == "b")
                {

                    break;
                }
                else if (difficultyOption == "E" || difficultyOption == "e")
                {
                    easyMode(jugador); // Mode functions already handle clearing, because freshness is key.
                }
                else if (difficultyOption == "M" || difficultyOption == "m")
                {
                    mediumMode(jugador); // Mode functions already handle clearing, because freshness is key.
                }
                else if (difficultyOption == "H" || difficultyOption == "h")
                {
                    hardMode(jugador); // Mode functions already handle clearing, because freshness is key.
                }
                else
                {

                    setColor(31);
                    cout << "Please enter a valid option (E), (M), (H) or (B), try again." << endl; // Error message, because we all need one sometimes.
                    resetColor();
                }
            }
        }
        else
        {

            setColor(31);
            cout << "Please enter a valid option (M) or (P), try again." << endl; // Error message, because we all need one sometimes.
            resetColor();
        }
    }
}

#endif // SLOT_MACHINE_GAME_H
