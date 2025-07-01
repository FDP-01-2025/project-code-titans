#ifndef MULTIPLAYER_H 
#define MULTIPLAYER_H 

#include <iostream> // Include to use cin and cout
#include <cstdlib>  // Include for functions like rand and srand
#include <ctime>    // Include to use time and generate random numbers with srand
#include <algorithm> // Include to use functions like swap and copy
#include <cctype>  // For isalpha
#include "utils.h" // Include clearConsole

using namespace std; // Use the standard namespace to avoid writing std:: all the time

const int MAX_CARDS = 16; // Define the total number of cards to use in the memory game
const int MAX_NUMBERS = 8; // Define the number of elements for the number puzzle

// Define a structure to represent each player in the mini-games
struct MiniGamePlayer {
    string name; // Store the player's name
    int score = 0; // Initialize their score to 0
};

// Declare the functions that I will use later in the same file
void miniGamesMenu(MiniGamePlayer& p1, MiniGamePlayer& p2);
void memoryGame(MiniGamePlayer& p1, MiniGamePlayer& p2);
void strategyGame(MiniGamePlayer& p1, MiniGamePlayer& p2);
void numberPuzzle(MiniGamePlayer& p1, MiniGamePlayer& p2);
void showWinner(MiniGamePlayer& p1, MiniGamePlayer& p2);
void shuffleArray(int array[], int size);
bool isSorted(int array[], int size);

// Implement a function to randomly shuffle the values of an array
void shuffleArray(int array[], int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1); // Choose a random index between 0 and i
        swap(array[i], array[j]); // Swap the values at positions i and j
    }
}

// Implement a function to check if an array is sorted in ascending order
bool isSorted(int array[], int size) {
    for (int i = 0; i < size - 1; i++) {
        if (array[i] > array[i + 1]) {
            return false; // If I find an element greater than the next, the array is not sorted
        }
    }
    return true; // If everything is fine, return true
}

// Here I define the mini-games menu where players can choose what to play
void miniGamesMenu(MiniGamePlayer& p1, MiniGamePlayer& p2) {
    int option;
    do {
        if (cin.fail()) {
            // If the input is not a number, clear the error and discard the invalid input
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the entire line
            option = 0; // To enter the default case and show the message
        }
        clearConsole();
        // Show the available options
        cout << "-----------------------------------\n";
        cout << "\n*=======* MINI GAMES MENU *=======*\n";
        cout << "║                                 ║  ";
        cout << "\n| 1. Memory Game                  |";
        cout << "\n║ 2. Strategy Game                ║";
        cout << "\n| 3. Number Puzzle                |";
        cout << "\n║ 4. View Scores                  ║";
        cout << "\n| 5. Exit                         |";
        cout << "\n║                                 ║";
        cout <<endl;
        cout << "+=================================+\n";
        cout << "| Select a game: ";
        
        cin >> option; // Read the option selected by the player
        
        switch(option) {
            case 1:
                clearConsole();
                memoryGame(p1, p2); // Call the memory game
                break;
            case 2:
                clearConsole();
                strategyGame(p1, p2); // Call the strategy game
                break;
            case 3: 
                clearConsole();
                numberPuzzle(p1, p2); // Call the number puzzle
                break;
            case 4:
                clearConsole();
                showWinner(p1, p2); // Show who is winning
                cout << "\nPress ENTER to continue...";
                cin.ignore();
                cin.get();  // Wait for the user to press ENTER
                break;
            case 5:
                cout << "Returning to the main menu...\n"; // Farewell message
                break;
            default:
                cout << "Invalid option. Please try again.\n"; // If they do not choose a valid option
        }
    } while(option != 5); // Repeat while they do not choose to exit
}

// Here I define the memory game where players must match identical cards
// Here I define the memory game, but now with a menu to see rules before starting
void memoryGame(MiniGamePlayer& p1, MiniGamePlayer& p2) {
    int option; // Variable to store the menu option

    // Pre-menu to explain the game if the player wants
    do {
        cout << "---------------------------------\n";
      cout << "\n*=========* MEMORY GAME *=========*\n";
        cout << "║                                 ║";
        cout << "\n| 1. View game rules              |";
        cout << "\n║ 2. Start the game               ║";
        cout << "\n|                                 |";
        cout << "\n+---------------------------------+";
        cout << "\n| Select an option: ";
        cin >> option;

        // Validate invalid input
        if (cin.fail() || (option != 1 && option != 2)) {
            cin.clear(); // Clear the input error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore garbage
            cout << "Invalid option. Please try again.\n";
        } else if (option == 1) {
            clearConsole();
            // If they choose 1, show the rules
            cout << "--------------------------------------------------------\n";
            cout << "\n+------- *=======* MEMORY GAME RULES *=======* --------+";
            cout << "\n|                                                      |";
            cout << "\n║ 1. There are 16 cards (8 pairs) hidden.              ║";
            cout << "\n| 2. You select two cards per turn (0-15).             |";
            cout << "\n║ 3. If they are the same, you earn 10 points.         ║";
            cout << "\n| 4. If you fail, you lose your turn.                  |";
            cout << "\n║ 5. The player with the most points at the end wins.  ║";
            cout << "\n|                                                      |";
            cout << "\n+------------------------------------------------------+\n";
        }
    } while (option != 2); // Repeat until they choose to start

    // Start the actual game logic
    int cards[MAX_CARDS] = {1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8}; // The cards
    bool revealed[MAX_CARDS] = {false}; // All hidden at the start
    shuffleArray(cards, MAX_CARDS); // Shuffle randomly
    int pairsFound = 0; // Pair counter
    int turn = 0; // Start with player 1

    // While not all 8 pairs are found
    while(pairsFound < 8) {
        MiniGamePlayer& currentPlayer = (turn == 0) ? p1 : p2; // Decide who plays
        cout << "\nTurn of " << currentPlayer.name << endl;

        // Show the board
        cout << "Board:\n";
        for(int i = 0; i < MAX_CARDS; i++) {
            if(revealed[i])
                cout << cards[i] << " ";
            else
                cout << "* ";
            if((i+1) % 4 == 0) cout << endl;
        }

        // Ask the player for two positions
        int pos1, pos2;
        cout << "Select two cards (0-15): ";
        cin >> pos1 >> pos2;

        // Check if the input was valid or if they chose the same card
        if (cin.fail() || pos1 < 0 || pos1 >= MAX_CARDS || pos2 < 0 || pos2 >= MAX_CARDS || pos1 == pos2 || revealed[pos1] || revealed[pos2]) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid selection. You lose your turn.\n";
            turn = 1 - turn;
            continue;
        }

        // Reveal the chosen cards
        revealed[pos1] = true;
        revealed[pos2] = true;

        // Show what they chose
        cout << "You selected: " << cards[pos1] << " and " << cards[pos2] << endl;

        // If they guessed correctly
        if(cards[pos1] == cards[pos2]) {
            cout << "Pair found! +10 points\n";
            currentPlayer.score += 10;
            pairsFound++;
        } else {
            cout << "Not a pair. They will be hidden again.\n";
            revealed[pos1] = false;
            revealed[pos2] = false;
            turn = 1 - turn;
        }
    }

    // When the game ends
    cout << "\nGame over!\n";
    showWinner(p1, p2); // Show who won
}

// Here I define the strategy game where players must not exceed 21
void strategyGame(MiniGamePlayer& p1, MiniGamePlayer& p2) {
    int option; // Variable for the menu

    // Sub-menu to show rules if the player wants
    do {
        cout << "-----------------------------------\n";
        cout << "\n*========* STRATEGY GAME *========*\n";
        cout << "║                                 ║";
        cout << "\n| 1. View game rules              |";
        cout << "\n║ 2. Start the game               ║";
        cout << "\n|                                 |";
        cout << "\n+---------------------------------+";
        cout << "\n| Select an option: ";
        cin >> option;

        // Validate the chosen option
        if (cin.fail() || (option != 1 && option != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid option. Please try again.\n";
        } else if (option == 1) {
            // If they choose to see the rules
            cout << "----------------------------------------------------------------\n";
            cout << "\n+--------- *========* STRATEGY GAME RULES *========* ----------+";
            cout << "\n|                                                              |";
            cout << "\n║ 1. We start from 0.                                          ║";
            cout << "\n| 2. Each player adds a number between 1 and 5 on their turn.  |";
            cout << "\n║ 3. The one who makes the total reach 21 loses.               ║";
            cout << "\n| 4. The other player wins 15 points.                          |";
            cout << "\n║                                                              ║";
            cout << "\n+--------------------------------------------------------------+\n";

        }
    } while (option != 2); // Repeat until they choose to play

    // Main game logic
    int total = 0; // Start from zero
    int turn = 0; // Start with player 1

    while(total < 21) {
        MiniGamePlayer& currentPlayer = (turn == 0) ? p1 : p2;
        int sum;

        cout << "\nCurrent total: " << total;
        cout << "\n" << currentPlayer.name << ", add a number between 1 and 5: ";
        cin >> sum;

        // Check if the sum is valid
        if (cin.fail() || sum < 1 || sum > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid sum. It must be between 1 and 5.\n";
            continue;
        }

        total += sum; // Add to the total
        turn = 1 - turn; // Change turn
    }

    // Since the one who summed to 21 loses, the other wins
    MiniGamePlayer& winner = (turn == 0) ? p1 : p2;
    cout << "\n!" << winner.name << " wins 15 points for strategy!\n";
    winner.score += 15;

    showWinner(p1, p2); // Show the final score table
}

// Here I define the number puzzle where they have to order from 1 to 8
void numberPuzzle(MiniGamePlayer& p1, MiniGamePlayer& p2) {
    // Start the function for the number puzzle with two players

    int option; // Store the option the player chooses in the initial menu

    // Show a small menu for the player to see rules or start playing
    do {
        cout << "-------------------------------------\n";
        cout << "\n*=========* NUMBER PUZZLE *=========*\n";
        cout << "║                                   ║";
        cout << "\n| 1. View game rules                |";
        cout << "\n║ 2. Start the game                 ║";
        cout << "\n|                                   |";
        cout << "\n+-----------------------------------+";
        cout << "\n| Select an option: ";
        cin >> option; // Read the option entered by the player

        // If the input is invalid or the option is neither 1 nor 2, notify and ask again
        if (cin.fail() || (option != 1 && option != 2)) {
            cin.clear(); // Clear the error state of cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the garbage input
            cout << "Invalid option. Please try again.\n"; // Error message
        } 
        // If they choose to see the rules, show them
        else if (option == 1) {

            cout << "----------------------------------------------------------------------\n";
            cout << "\n+---------- *==========* NUMBER PUZZLE RULES *==========* -----------+";
            cout << "\n|                                                                    |";
            cout << "\n║ 1. You will be shown a shuffled sequence of numbers from 1 to 8.   ║";
            cout << "\n| 2. You must order them by swapping two positions per turn.         |";
            cout << "\n║ 3. The positions range from 0 to 7.                                ║";
            cout << "\n| 4. The player with the fewest attempts wins.                       |";
            cout << "\n║ 5. If there is a tie, both win points.                             ║";
            cout << "\n| 6. If you enter an invalid position, the attempt does not count.   |";
            cout << "\n║                                                                    ║";
            cout << "\n+--------------------------------------------------------------------+\n";
        }
    } while (option != 2); // Keep showing the menu until the player chooses to start

    // Now I start the game itself
    int numbers[MAX_NUMBERS] = {1,2,3,4,5,6,7,8}; // Create the base ordered array
    shuffleArray(numbers, MAX_NUMBERS); // Shuffle the numbers to create the puzzle

    int attemptsP1 = 0, attemptsP2 = 0; // Initialize the attempt counters

    // Player 1's turn
    cout << "\nTurn of " << p1.name << endl;
    int copyP1[MAX_NUMBERS]; // Create a copy for player 1 to play without modifying the original
    copy(numbers, numbers + MAX_NUMBERS, copyP1); // Copy the shuffled sequence

    // While the array is not sorted...
    while(!isSorted(copyP1, MAX_NUMBERS)) {
        cout << "Current sequence: ";
        for(int i = 0; i < MAX_NUMBERS; i++) cout << copyP1[i] << " "; // Show the current sequence
        cout << endl;

        int pos1, pos2; // Variables to store the positions to swap
        cout << "Enter two positions to swap (0-7): ";
        cin >> pos1 >> pos2; // Read the positions

        // Validate that the positions are valid and that the input is correct
        if (cin.fail() || pos1 < 0 || pos1 >= MAX_NUMBERS || pos2 < 0 || pos2 >= MAX_NUMBERS) {
            cin.clear(); // Clear the input error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore garbage in the buffer
            cout << "Invalid positions. Try again.\n"; // Error message
            continue; // Do not count the attempt and ask again
        }

        swap(copyP1[pos1], copyP1[pos2]); // Swap the positions
        attemptsP1++; // Increase the attempt counter for player 1
    }

    // Player 2's turn
    cout << "\nTurn of " << p2.name << endl;
    int copyP2[MAX_NUMBERS]; // Create the copy for player 2
    copy(numbers, numbers + MAX_NUMBERS, copyP2); // Copy the shuffled sequence for him

    // Same process for player 2
    while(!isSorted(copyP2, MAX_NUMBERS)) {
        cout << "Current sequence: ";
        for(int i = 0; i < MAX_NUMBERS; i++) cout << copyP2[i] << " ";
        cout << endl;

        int pos1, pos2;
        cout << "Enter two positions to swap (0-7): ";
        cin >> pos1 >> pos2;

        if (cin.fail() || pos1 < 0 || pos1 >= MAX_NUMBERS || pos2 < 0 || pos2 >= MAX_NUMBERS) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid positions. Try again.\n";
            continue;
        }

        swap(copyP2[pos1], copyP2[pos2]);
        attemptsP2++;
    }

    // Compare the attempts to determine the winner or if there is a tie
    if(attemptsP1 < attemptsP2) {
        cout << "\n!" << p1.name << " wins with " << attemptsP1 << " attempts! +20 points\n";
        p1.score += 20; // Assign points to the winner
    } else if(attemptsP2 < attemptsP1) {
        cout << "\n!" << p2.name << " wins with " << attemptsP2 << " attempts! +20 points\n";
        p2.score += 20;
    } else {
        cout << "\n!It's a tie! Both win 10 points\n";
        p1.score += 10;
        p2.score += 10;
    }

    showWinner(p1, p2); // Show the final score table
}

// This function is used to show who is winning or if they are tied
void showWinner(MiniGamePlayer& p1, MiniGamePlayer& p2) {
    // Start by showing a nice header

    cout << "\n+======================================+\n";
    cout << "|              * SCORES *              |\n";
    cout << "+--------------------------------------+\n";
    cout << "|\n";

    // Show player 1's name along with their current score  
    cout << "| " << p1.name << ": " << p1.score << " points";

    // Show player 2's name and their score as well
    cout << "\n| " << p2.name << ": " << p2.score << " points\n";
    cout << "+======================================+\n";

    // Here I compare the scores to see who is winning
    if(p1.score > p2.score) {
        // If player 1 has more points, announce them as the one winning
        cout << "\n!" << p1.name << " is winning!\n";
    } 
    else if(p2.score > p1.score) {
        // If player 2 has more points, then he is winning
        cout << "\n!" << p2.name << " is winning!\n";
    } 
    else {
        // If both have the same points, announce that they are tied
        cout << "\n!They are tied!\n";
    }
}

// Function to validate that the name only contains letters
bool isNameValidate(const string& name) {
    if (name.empty()) return false; // Cannot be empty
    for (char c : name) {
        if (!isalpha(c)) return false; // If there is anything that is not a letter, invalid
    }
    return true;
}

// Example usage in multiplayerMode()
void multiplayerMode() {
    string name1, name2;
    clearConsole();
    cout << "\n*=======* MULTIPLAYER MODE (Mini-Games) *=======*\n";

    do {
        cout << "\nPlayer 1 , enter your name: ";
        cin >> name1;
        if (!isNameValidate(name1)) {
            cout << "Invalid name. Use only letters without spaces or numbers.\n";
        }
    } while (!isNameValidate(name1));

    do {
        cout << "Player 2, enter your name: ";
        cin >> name2;
        if (!isNameValidate(name2)) {
            cout << "Invalid name. Use only letters without spaces or numbers.\n";
        }
    } while (!isNameValidate(name2));

    MiniGamePlayer p1 = {name1};
    MiniGamePlayer p2 = {name2};

    srand(time(nullptr)); // Initialize the random seed
    miniGamesMenu(p1, p2); // Call the menu with the two players
    cout << "\n*===========* FINAL RESULT *===========*\n";
    showWinner(p1, p2); // Show the final score
}

#endif // MULTIPLAYER_H