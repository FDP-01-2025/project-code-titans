#ifndef DATE_TIME_H
#define DATE_TIME_H

#include <iostream> // I include this library to use input/output functions like cout.
#include <ctime>    // I include this library to work with the system's date and time.

using namespace std; // I use the standard namespace to avoid writing std:: every time.

// Function to get time of day as a greeting string
inline string getTimeOfDayGreeting(int hour)
{
    if (hour >= 6 && hour < 12)
    {
        return "           Good Morning!";
    }
    else if (hour >= 12 && hour < 18)
    {
        return "           Good Afternoon!";
    }
    else
    {
        return "           Good Night!";
    }
}

inline void showDateTime()
{                                    // I declare an inline function called showDateTime, so it can be used anywhere this header is included.
    time_t now = time(0);            // I create a variable called 'now' and assign it the current system time.
    tm *localTime = localtime(&now); // I convert that time into a human-readable local time using localtime().

    string greeting = getTimeOfDayGreeting(localTime->tm_hour); // Get the greeting based on the current hour

    // Print casino welcome message first
    setColor(31);
    cout << "+======================================+\n";
    cout << "|                                      |\n";
    cout << "║    ";
    setColor(34);
    cout << "WELCOME TO THE VIRTUAL CASINO";
    setColor(31);
    cout << "     ║\n";
    cout << "|                                      |\n";
    // I start printing the decorative frame using pseudographic characters:
    cout << "+--------------------------------------+\n";

    // Print greeting centered-ish
    cout << "| ";
    setColor(34);
    cout << greeting;
    setColor(31);
    cout << string(38 - 2 - greeting.length(), ' ') << " |\n";
    cout << "║                                      ║\n|";

    // I print the date line:
    resetColor();
    cout << " Date : ";
    cout << (localTime->tm_mday < 10 ? "0" : "") << localTime->tm_mday << "/"
         << (localTime->tm_mon + 1 < 10 ? "0" : "") << localTime->tm_mon + 1 << "/"
         << localTime->tm_year + 1900;

    cout << string(38 - 8 - 10, ' ') << "\033[31m|\n║";

    // I print the time line:
    resetColor();
    cout << " Time : ";
    cout << (localTime->tm_hour < 10 ? "0" : "") << localTime->tm_hour << ":"
         << (localTime->tm_min < 10 ? "0" : "") << localTime->tm_min << ":"
         << (localTime->tm_sec < 10 ? "0" : "") << localTime->tm_sec;

    cout << string(38 - 8 - 8, ' ') << "\033[31m║\n";

    // I finally print the bottom of the frame.
    cout << "+======================================+\n\n";
    resetColor();
}

#endif // DATE_TIME_H