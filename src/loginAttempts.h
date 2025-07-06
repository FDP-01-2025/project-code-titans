#ifndef LOGIN_ATTEMPTS_H
#define LOGIN_ATTEMPTS_H

#include <string>    // I use this library to handle usernames
#include <fstream>   // Helps me read and write files where I store login attempts
#include <ctime>     // I need this to control how much time has passed since the last attempt
#include <iostream>  // Used for displaying messages in the console
#include <limits>    // Helps me clean the buffer when pausing with Enter

using namespace std;

// I define the maximum number of failed login attempts allowed
const int MAX_ATTEMPTS = 3;

// I define how long the user will be locked out (in seconds)
const int LOCK_TIME = 300; // 5 minutes

// This function helps me check how many attempts a user has made and when the last one was
inline bool getLoginAttempt(const string &user, int &attempts, time_t &lastAttempt)
{
    ifstream file("./documents/login_attempts.txt");
    if (!file.is_open())
        return false;

    string line, storedUser;
    int storedAttempts = 0;
    time_t storedTime = 0;

    // I read the file line by line where I store each user's attempts
    while (getline(file, line))
    {
        size_t sep1 = line.find('|');
        size_t sep2 = line.find('|', sep1 + 1);

        if (sep1 == string::npos || sep2 == string::npos)
            continue;

        // I extract the stored username
        storedUser = line.substr(0, sep1);
        if (storedUser != user)
            continue;

        // If I found the user, I get their attempts and time
        storedAttempts = stoi(line.substr(sep1 + 1, sep2 - sep1 - 1));
        storedTime = (time_t)stoll(line.substr(sep2 + 1));
        attempts = storedAttempts;
        lastAttempt = storedTime;
        file.close();
        return true;
    }

    // If I didn’t find the user, I return zeros
    file.close();
    attempts = 0;
    lastAttempt = 0;
    return false;
}

// This function saves or updates the attempt count and time for a user
inline void updateLoginAttempt(const string &user, int attempts, time_t lastAttempt)
{
    ifstream file("./documents/login_attempts.txt");
    ofstream temp("./documents/temp_attempts.txt");
    bool found = false;

    if (!temp.is_open())
    {
        cout << "Error updating login attempts.\n";
        return;
    }

    // I go through the original file line by line
    if (file.is_open())
    {
        string line, storedUser;
        while (getline(file, line))
        {
            size_t sep1 = line.find('|');
            if (sep1 == string::npos)
                continue;

            storedUser = line.substr(0, sep1);

            // If I find the user, I write the updated info
            if (storedUser == user)
            {
                temp << user << "|" << attempts << "|" << lastAttempt << "\n";
                found = true;
            }
            else
            {
                // If it's not the user, I copy the line as it is
                temp << line << "\n";
            }
        }
        file.close();
    }

    // If I didn’t find the user, I add a new line
    if (!found)
    {
        temp << user << "|" << attempts << "|" << lastAttempt << "\n";
    }

    temp.close();

    // I replace the original file with the temporary one
    remove("./documents/login_attempts.txt");
    rename("./documents/temp_attempts.txt", "./documents/login_attempts.txt");
}

// This function tells me if the user is currently blocked
inline bool isUserBlocked(const string &user)
{
    int attempts = 0;
    time_t lastAttempt = 0;
    time_t now = time(nullptr);

    getLoginAttempt(user, attempts, lastAttempt);

    // If they reached the limit and the lock time hasn't passed, I block them
    if (attempts >= MAX_ATTEMPTS && (now - lastAttempt) < LOCK_TIME)
        return true;

    return false;
}

// I use this function when a user logs in successfully
// That way I reset their previous failed attempts
inline void resetLoginAttempts(const string &user)
{
    updateLoginAttempt(user, 0, 0);
}

// With this function I show a warning message after a failed login
inline void showAttemptWarning(const string &user)
{
    int attempts = 0;
    time_t lastAttempt = 0;
    getLoginAttempt(user, attempts, lastAttempt);

    // I calculate how many attempts they have left
    int remaining = MAX_ATTEMPTS - attempts;

    if (remaining > 0)
    {
        // If they still have attempts, I warn them (in red)
        cout << "\033[31mYou have " << remaining << " attempt" << (remaining == 1 ? "" : "s")
             << " remaining before your account is temporarily locked.\033[0m\n";
    }
    else
    {
        // If they ran out of attempts, I notify them that their account is locked
        cout << "\033[31mYour account is now locked for a short time due to too many failed attempts.\033[0m\n";
    }

    // I pause so they can read the message
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

#endif
