#ifndef UTILS_H
#define UTILS_H

// Include <string> to handle text strings easily with std::string
#include <string>
// Include <algorithm> to use useful functions like std::transform that helps convert text to lowercase
#include <algorithm>
// Include <cctype> to use character functions, like converting to lowercase (::tolower), validating letters (isalpha) or spaces (isspace)
#include <cctype>
// Include <iostream> to show console messages and read input (cout and cin)
#include <iostream>
// Include <limits> to access limits on data input (like numeric_limits), useful to clear buffer if needed
#include <limits>
// Include <cstdlib> to use system functions like system(), which helps clear the console
#include <cstdlib>

// Conditional include depending on the operating system:
// - If on Windows (<windows.h>), use Sleep() to pause execution in milliseconds
// - If on Linux/Mac (<unistd.h>), use usleep() to pause in microseconds
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

// Function used to convert any string to lowercase, avoiding problems with case when comparing text
inline string toLower(const string &s) {
   string res = s; // Copy the original string so it is not altered directly
    transform(res.begin(), res.end(), res.begin(), ::tolower); // Apply tolower to each character
    return res; // Return the transformed string
}

// Function used to trim whitespace from the start and end of a string, to clean user inputs and avoid errors
inline string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r"); // Find first non-whitespace character
    if (first == string::npos) return ""; // If only spaces, return empty string
    size_t last = str.find_last_not_of(" \t\n\r"); // Find last non-whitespace character
    return str.substr(first, (last - first + 1)); // Return only the part without outside spaces
}

// Function used to normalize text: removes all spaces and converts everything to lowercase.
// Useful to compare strings ignoring spaces and case differences
inline string normalize(const string& text) {
    string clean;
    for (char c : text) {
        if (!isspace(c))  // Only add characters that are not spaces
            clean += tolower(c); // Convert to lowercase
    }
    return clean;
}

// Function to validate that a name contains only letters and spaces
inline bool validName(const string& name) {
    for (char c : name) {
        if (!isalpha(c) && !isspace(c)) {
            return false;  // If not a letter or space, name is invalid
        }
    }
    return !name.empty(); // Name must not be empty
}

// Function to ask the player if they want to continue playing, accepting answers "yes" ("sí", "si") or "no" (case-insensitive)
inline bool askContinue() {
    string resp;
    while (true) {
        cout << "\nDo you want to keep playing? (yes / no): ";
        cin >> resp;
        resp = toLower(resp); // Normalize to simplify comparison
        if (resp == "si" || resp == "sí" || resp == "yes") return true; // If yes, return true
        else if (resp == "no") return false; // If no, return false
        else cout << "Invalid answer. Please respond with 'yes' or 'no'.\n"; // If invalid, prompt again
    }
}

// Functions to pause execution or clear the console, adapted to the operating system
#ifdef _WIN32
inline void waitMs(int ms) { Sleep(ms); } // On Windows use Sleep, which accepts milliseconds
inline void clearConsole() { system("cls"); } // Clear screen with cls command
#else
inline void waitMs(int ms) { usleep(ms * 1000); } // On Linux/Mac use usleep which accepts microseconds, so multiply by 1000
inline void clearConsole() { cout << "\033[2J\033[H"; } // Clear screen with ANSI terminal sequence
#endif

#endif // UTILS_H
