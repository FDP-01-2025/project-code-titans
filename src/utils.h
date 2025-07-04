#ifndef UTILS_H
#define UTILS_H

// Include <string> to easily handle text strings with std::string
#include <string>

// Include <algorithm> to use useful functions like std::transform which helps me convert text to lowercase
#include <algorithm>

// Include <cctype> to use character functions, such as converting to lowercase (::tolower), validating letters (isalpha) or spaces (isspace)
#include <cctype>

// Include <iostream> to display messages in the console and read inputs (cout and cin)
#include <iostream>

// Include <limits> to access limits in data inputs (like numeric_limits), useful for clearing the buffer if necessary
#include <limits>

// Include <cstdlib> to use system functions like system(), which helps me clear the console
#include <cstdlib>

// Conditionally include depending on the operating system:
// - If I'm on Windows (<windows.h>), I use Sleep() to pause execution in milliseconds
// - If I'm on Linux/Mac (<unistd.h>), I use usleep() to pause in microseconds
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

// Function that I use to convert any string to lowercase, avoiding case issues when comparing text
inline string toLower(const string &s)
{
    string res = s;                                            // Copy the original string to avoid altering it directly
    transform(res.begin(), res.end(), res.begin(), ::tolower); // Apply tolower to each character
    return res;                                                // Return the transformed string
}

// Function that I use to remove whitespace from the beginning and end of a string, to clean user inputs and avoid errors
inline string trim(const string &str)
{
    size_t first = str.find_first_not_of(" \t\n\r"); // Find the first character that is not a space
    if (first == string::npos)
        return "";                                 // If it was all spaces, return an empty string
    size_t last = str.find_last_not_of(" \t\n\r"); // Find the last character that is not a space
    return str.substr(first, (last - first + 1));  // Return only the part that does not have spaces outside
}

// Function that I use to normalize text: I remove all spaces and convert everything to lowercase.
// This helps me compare strings ignoring spaces and case.
inline string normalize(const string &text)
{
    string clean;
    for (char c : text)
    {
        if (!isspace(c))         // Only add characters that are not spaces
            clean += tolower(c); // Convert to lowercase
    }
    return clean;
}

// Function that validates that the name only contains letters and spaces
inline bool isNameValid(const string &name)
{
    for (char c : name)
    {
        if (!isalpha(c) && !isspace(c))
        {
            return false; // If it's not a letter or space, the name is not valid
        }
    }
    return !name.empty(); // The name must not be empty
}

// Function to ask the player if they want to continue playing, accepting responses "yes", "si" or "no" (regardless of case)
inline bool askToContinue()
{
    string response;
    while (true)
    {
        cout << "\033[33m\nDo you want to continue playing? (yes / no): \033[0m";
        cin >> response;
        response = toLower(response); // Normalize to facilitate comparison
        if (response == "Yes" || response == "yes")
            return true; // If they say yes, return true
        else if (response == "no")
            return false; // If they say no, return false
        else
            cout << "Invalid response. Please respond 'yes' or 'no'.\n"; // If they respond incorrectly, notify and repeat
    }
}

// Functions to pause execution or clear the console, adapted to the operating system
#ifdef _WIN32
inline void waitMs(int ms) { Sleep(ms); }     // On Windows, I use Sleep which takes milliseconds
inline void clearConsole() { system("cls"); } // Clear screen with cls command
#else
inline void waitMs(int ms) { usleep(ms * 1000); }       // On Linux/Mac, I use usleep which takes microseconds, hence I multiply by 1000
inline void clearConsole() { cout << "\033[2J\033[H"; } // Clear screen with ANSI sequence for terminal
#endif

#endif // UTILS_H
