#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <string>   // I use this library to handle text with strings, making it easy to work with names, passwords, and more.
#include <fstream>  // I use it to open and save files where I store user data.
#include <iostream> // It allows me to display messages and request data from the console to interact with the user.
#include <cstdlib>  // I need it to create random numbers, for example, to generate recovery codes.
#include <ctime>    // I use it to know the current date and time, to calculate if the user is of legal age.
#include <limits>   // This library helps me control limits when receiving data, although I don't use it directly here.
#include "utils.h"  // Here I have my own functions to clear and validate text, keeping the code more organized.

// I use the std namespace to avoid writing std:: every time I use standard functions or classes
using namespace std;

// Function that checks if a user already exists in the usuarios.txt file
inline bool userExists(const string& name) {
    // Open the file in read mode
    ifstream file("./documents/users.txt");

    // If the file could not be opened, return false because I can't find users
    if (!file.is_open()) return false;

    // Declare a variable to read each line of the file
    string line;

    // Normalize the username received to compare without case or space errors
    string normalizedName = normalize(name);

    // Start reading the file line by line until the end
    while (getline(file, line)) {
        // When I find a line that indicates the start of a user block
        if (line == "====== User ======") {
            // Read the next line, which should contain the username
            getline(file, line);

            // Remove the prefix "Name: " which has 6 characters and keep only the name
            string fileName = line.substr(6);

            // Normalize the name I read from the file to compare it correctly
            string normalizedFileName = normalize(fileName);

            // If the normalized name from the file is equal to the name I'm looking for, return true (user exists)
            if (normalizedFileName == normalizedName) return true;

            // If it's not the user I'm looking for, skip the next two lines which are password and code
            getline(file, line);
            getline(file, line);
        }
    }

    // If I finished reading the entire file and didn't find the user, return false
    return false;
}

inline void deleteUser () {
    // First, clear the screen so the user sees only what's necessary
    clearConsole();

    cout << "=== DELETE USER ===\n\n";

    // Ask for the username to delete
    cout << "Enter the username to delete: ";
    string name;
    getline(cin, name);

    // Ask for the recovery code to validate identity
    cout << "Enter recovery code: ";
    string code;
    getline(cin, code);

    // Normalize the data to avoid problems with uppercase or spaces
    string inputName = normalize(name);
    string inputCode = normalize(code);

    // Initialize a flag to know if a user was deleted
    bool deleted = false;

    // Open the original file for reading
    ifstream file("./documents/users.txt");
    // Create a temporary file to save the users that will NOT be deleted
    ofstream temp("./documents/temp.txt");

    // Check that both files open correctly
    if (!file.is_open() || !temp.is_open()) {
        cout << "Error: Could not access the necessary files.\n";
        return;
    }

    string line;
    // Read the file line by line
    while (getline(file, line)) {
        // When I find the start of a user block
        if (line == "====== User ======") {
            // Save the complete block to decide whether to copy it or ignore it
            string completeBlock = line + "\n";

            // Read the name and add it to the block
            getline(file, line);
            completeBlock += line + "\n";
            string fileName = trim(line.substr(6));  // Remove "Name: "

            // Read the password and add it to the block
            getline(file, line);
            completeBlock += line + "\n";
            string passwordFile = trim(line.substr(10));  // Remove "Password: "

            // Read the recovery code and add it to the block
            getline(file, line);
            completeBlock += line + "\n";
            string codeFile = trim(line.substr(6));  // Remove "Code: "

            // Read the empty line that closes the block
            while (getline(file, line)) {
                completeBlock += line + "\n";
                if (line == "=================") break;
            }

            // Check if this block corresponds to the user I want to delete
            if (!deleted && normalize(fileName) == inputName && normalize(codeFile) == inputCode) {
                // Mark that I deleted a user to avoid deleting more by mistake
                deleted = true;
                cout << "\nUser  deleted successfully!\n";
                // Do not copy this block to the temporary file (delete it)
            } else {
                // If it's not the user to delete, copy the complete block to the temporary file
                temp << completeBlock;
            }
        } else {
            // If the line is not part of a block, copy it as is
            temp << line << '\n';
        }
    }

    // Close both files before replacing
    file.close();
    temp.close();

    // Replace the original file with the temporary one (updated)
    remove("./documents/users.txt");
    rename("./documents/temp.txt", "./documents/users.txt");

    // If I didn't delete any user, inform the user
    if (!deleted) {
        cout << "\nNo user was found with that name and code. Nothing was deleted.\n";
    }

    cout << "\nPress Enter to continue...";
    cin.get(); // Pause for them to see the message
}

// Function that saves all the information of a new user in the usuarios.txt file
inline void saveUser (const string& name, const string& password, const string& code, const string& birthDate, const string& gender, const string& dui) {

    // Open the file in append mode to not erase previous data
    ofstream file("./documents/users.txt", ios::app);

    // Check that the file opened correctly
    if (file.is_open()) {

        // Write the header to identify a user block
        file << "====== User ======\n";

        // Save the received name
        file << "Name: " << name << "\n";

        // Save the received password
        file << "Password: " << password << "\n";

        // Save the generated recovery code
        file << "Code: " << code << "\n";

        // Save the birth date I received
        file << "Birthdate: " << birthDate << "\n";

        // Save the received gender (M/F/O)
        file << "Gender: " << gender << "\n";

        // Save the received DUI in valid format
        file << "DUI: " << dui << "\n";

        // Write a line to close the user block and leave space
        file << "=================\n\n";
    }
}

// Function that checks if someone is of legal age based on the given birth date (in DD/MM/YYYY format)
// Now with complete validation of ranges and months
inline bool isOfLegalAge(const string& birthDate) {

    // Declare variables to extract day, month, and year
    int day, month, year;

    // Try to extract the numbers using sscanf in the format DD/MM/YYYY
    // If I can't extract 3 numbers, I return false because the date is incorrectly written
    if (sscanf(birthDate.c_str(), "%d/%d/%d", &day, &month, &year) != 3)
        return false;

    // Validate that the year is in a reasonable range (for example, between 1900 and 2100)
    // If the year is out of range, return false because it's not valid
    if (year < 1900 || year > 2100)
        return false;

    // Validate that the month is between 1 and 12
    if (month < 1 || month > 12)
        return false;

    // Validate that the day is between 1 and 31
    if (day < 1 || day > 31)
        return false;

    // Now validate that the day is valid according to the specific month
    // For example, April, June, September, and November have a maximum of 30 days
    bool validDay = true; // variable to know if the day is correct

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        // If the day is greater than 30 in these months, it's invalid
        if (day > 30)
            validDay = false;
    }
    else if (month == 2) {
        // For February I must consider leap years
        // Leap year: divisible by 400 or divisible by 4 but not by 100
        bool isLeapYear = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);

        // Days that February can have depending on whether it's a leap year or not
        int febDays = isLeapYear ? 29 : 28;

        // If the day is greater than the allowed days in February, it's invalid
        if (day > febDays)
            validDay = false;
    }

    // If the day is not valid, return false
    if (!validDay)
        return false;

    // If I got here, the date has a valid format and range
    // Now I calculate the age to verify if they are of legal age

    // Get the current date with time and localtime
    time_t t = time(nullptr);
    tm* now = localtime(&t);

    // Extract current year, month, and day
    int currentYear = now->tm_year + 1900; // tm_year counts from 1900
    int currentMonth = now->tm_mon + 1;      // tm_mon goes from 0 to 11
    int currentDay = now->tm_mday;

    // Calculate the age as the difference between years
    int age = currentYear - year;

    // Adjust age if they haven't had their birthday this year
    if (currentMonth < month || (currentMonth == month && currentDay < day))
        age--;

    // Return true if they are 18 years or older, otherwise false
    return age >= 18;
}

// Function that checks if a DUI is already registered in the file
inline bool duiRepeated(const string& dui) {
    ifstream file("./documents/users.txt");
    string line;

    if (!file.is_open()) return false;

    while (getline(file, line)) {
        // Look for the line that contains the DUI
        if (line.rfind("DUI: ", 0) == 0) {  // If it starts with "DUI: "
            string duiFile = trim(line.substr(5)); // Extract the DUI value
            if (duiFile == dui) {
                file.close();
                return true; // The DUI already exists
            }
        }
    }

    file.close();
    return false; // The DUI was not found
}

// Function that validates correct format and that the DUI is not repeated
inline bool validDUI(const string& dui) {
    // Check format: length 10 and hyphen at position 8
    if (dui.length() != 10 || dui[8] != '-') return false;

    // Check that the first 8 and the last character are digits
    for (int i = 0; i < 8; ++i)
        if (!isdigit(dui[i])) return false;
    if (!isdigit(dui[9])) return false;

    // Check that it is not repeated in the file
    if (duiRepeated(dui)) {
        cout << "That DUI has already been registered.\n";
        return false;
    }

    return true; // Everything is fine
}

// Function that generates a random numeric code of given length (default 6 digits)
inline string generateRecoveryCode(int length = 6) {
    // Initialize an empty string for the code
    string code;

    // Loop from 0 to length-1
    for (int i = 0; i < length; ++i)
        // Add a random digit (0 to 9) to the code in string format
        code += to_string(rand() % 10);

    // Return the generated code
    return code;
}

// Function that registers a user by asking for all necessary data and validating them one by one
inline bool registerUser () {

    // Declare variables to temporarily store the data the user enters
    string name, password, birthDate, gender, dui;
    clearConsole(); // I use the function I already have to clear the screen before showing the registration
    // Show initial message for new registration
    cout << "\n=== New User Registration ===\n";

    // Ask and validate name: it must be valid and not already exist in the file
    do {
        cout << "Username: ";
        getline(cin, name);

        // Check that the name only has letters and spaces, otherwise notify and repeat
        if (!isNameValid(name)) {
            cout << "Invalid name. Only letters and spaces are allowed.\n";
            name.clear(); 
            continue;
        }

        // Check that the name is not already registered (normalize first)
        if (userExists(normalize(name))) {
            cout << "That name is already registered. Try another.\n";
            name.clear(); // Clear to repeat the cycle
            continue;
        }
    } while (name.empty()); // Repeat until the name is valid and not empty

    // Ask and validate birth date, also check that they are over 18
    do {
        cout << "Birth date (DD/MM/YYYY): ";
        getline(cin, birthDate);

        // If they are not of legal age, show a message and clear the variable to repeat
        if (!isOfLegalAge(birthDate)) {
            cout << "You must be over 18 years old to register.\n";
            birthDate.clear();
        }
    } while (birthDate.empty()); // Repeat until a valid date is entered

    // Ask and validate DUI, it must have the correct format and not be repeated
    do {
        cout << "DUI (format 12345678-9): ";
        getline(cin, dui);

        // If the DUI is not valid or is repeated, notify and clear to repeat
        if (!validDUI(dui)) {
            cout << "Invalid DUI or already registered. Try again.\n";
            dui.clear(); // This ensures the cycle repeats
        }
    } while (dui.empty()); // Repeat until a valid DUI is entered

    // Ask and validate gender, only accept M, F, or O (uppercase or lowercase)
    do {
        cout << "Gender (M/F/O): ";
        getline(cin, gender);

        if (gender != "M" && gender != "F" && gender != "O" &&
            gender != "m" && gender != "f" && gender != "o") {
            cout << "Invalid gender. Use M, F, or O.\n";
            gender.clear();
        }
    } while (gender.empty()); // Repeat until a valid gender is entered

    // Ask and validate password, minimum 8 characters
    do {
        cout << "Create a password (minimum 8 characters): ";
        getline(cin, password);

        if (password.length() < 8) {
            cout << "The password must be at least 8 characters long.\n";
            password.clear();
        }
    } while (password.empty()); // Repeat until a valid password is entered

    // Generate a random code for password recovery
    string code = generateRecoveryCode();

    // Save the user in the file with all their data
    saveUser (name, password, code, birthDate, gender, dui);

    // Confirm that the registration was successful and show the code for the user to keep
    cout << "Registration successful!\n";
    cout << "Your recovery code is: " << code << "\nKeep it safe.\n";

    // Return true because the registration was successful
    return true;
}

// Function that logs in by asking for username and password, validating in the users.txt file
inline bool logIn(string& player) {

    // Open the file for reading
    ifstream file("./documents/users.txt");

    // If it could not be opened, notify error and return false
    if (!file.is_open()) {
        cout << "Error opening user file.\n";
        return false;
    }

    // Variables to store entered username and password
    string enteredName, enteredPassword;
    clearConsole(); // Use the function I already have to clear the screen before showing the login
    // Show header for logging in
    cout << "\n=== Log In ===\n";
    cout << "Username: ";
    getline(cin, enteredName);
    cout << "Password: ";
    getline(cin, enteredPassword);

    // Normalize the entered name for comparison
    string normalizedEnteredName = normalize(enteredName);

    // Variable to read lines from the file
    string line;

    // Loop through line by line looking for the correct username and password
    while (getline(file, line)) {
        // When I find a user block
        if (line == "====== User ======") {
            // Read name and normalize
            getline(file, line);
            string fileName = normalize(trim(line.substr(6)));

            // Read password
            getline(file, line);
            string passwordFile = trim(line.substr(10));

            // Skip the code and closing lines that I don't need here
            getline(file, line);
            getline(file, line);

            // If the name and password match what was entered, log in
            if (fileName == normalizedEnteredName && passwordFile == enteredPassword) {
                // Store the original name without normalizing in player for later use
                player = enteredName;

                // Welcome the user
                cout << "Welcome, " << player << "!\n";
                cout << "==========================\n";

                // Return true because the login was successful
                return true;
            }
        }
    }

    // If I finished searching and found no matches, notify error
    cout << "Incorrect credentials.\n";

    // Clear the player variable because there is no valid user
    player.clear();

    // Return false because the login was not successful
    return false;
}

// Function that verifies if the recovery code and name match and if so returns the password
inline bool verifyRecoveryCode(const string& name, const string& code, string& password) {

    // Open file for reading
    ifstream file("./documents/users.txt");

    // If I can't open it, return false
    if (!file.is_open()) return false;

    // Normalize the name for comparison
    string normalizedName = normalize(name);

    // Variable to read lines
    string line;

    // Read line by line looking for matching user and code
    while (getline(file, line)) {
        if (line == "====== User ======") {

            // Read name and normalize
            getline(file, line);
            string fileName = normalize(trim(line.substr(6)));

            // Read password to store it if it matches
            getline(file, line);
            string passwordFile = trim(line.substr(10));

            // Read recovery code
            getline(file, line);
            string codeFile = trim(line.substr(6));

            // Skip empty line
            getline(file, line);

            // If the name and code match, store the password in the variable and return true
            if (fileName == normalizedName && codeFile == code) {
                password = passwordFile;
                return true;
            }
        }
    }

    // If I didn't find a match, return false
    return false;
}

// Function that updates a user's password in the usuarios.txt file
inline void updatePassword(const string& name, const string& newPassword) {

    // Open original file for reading
    ifstream file("./documents/users.txt");

    // Open temporary file for writing
    ofstream temp("./documents/temp.txt");

    // Variable to read lines
    string line;

    // Read the original file line by line
    while (getline(file, line)) {

        // When I find a user block
        if (line == "====== User ======") {

            // Copy the header to the temporary file
            temp << line << '\n';

            // Read name
            getline(file, line);
            string fileName = trim(line.substr(8));
            temp << "Name: " << fileName << '\n';

            // Read password (I will change it if it corresponds)
            getline(file, line);
            string passwordFile = trim(line.substr(13));

            // Read recovery code
            getline(file, line);
            string codeFile = trim(line.substr(8));

            // Read closing empty line
            getline(file, line);

            // If this is the user I want to update, write the new password
            if (fileName == name) {
                temp << "Password: " << newPassword << '\n';
            } else {
                // If not, write the original password
                temp << "Password: " << passwordFile << '\n';
            }

            // Write the original code and the closing line
            temp << "Code: " << codeFile << '\n';

        } else {
            // If it's not a user block line, copy the line normally
            temp << line << '\n';
        }
    }

    // Close files
    file.close();
    temp.close();

    // Replace the original file with the temporary one
    remove("./documents/users.txt");
    rename("./documents/temp.txt", "./documents/users.txt");
}

// Function that allows the user to recover their password using the recovery code
inline void recoverPassword() {

    // Variables for the data we will ask for
    string name, code, password;
    clearConsole(); // I use the function I already have to clear the screen before showing recovery
    // Initial message for recovery
    cout << "\n====== Recover Password ======\n";

    // Ask for username
    cout << "Username: ";
    getline(cin, name);

    // Ask for recovery code
    cout << "Enter your recovery code: ";
    getline(cin, code);

    // Clean spaces in inputs
    name = trim(name);
    code = trim(code);

    // Check if the code and name match in the file
    if (verifyRecoveryCode(name, code, password)) {

        // If correct, show the current password
        cout << "Correct code! Your current password is: " << password << "\n";

        // Variables for the new password and confirmation
        string newPassword, confirm;

        // Ask if they want to change the password
        cout << "\nDo you want to change your password? (y/n): ";
        string response;
        getline(cin, response);

        // If they respond yes (y or Y)
        if (response == "y" || response == "Y") {

            // Ask for new password
            cout << "New password: ";
            getline(cin, newPassword);

            // Ask for confirmation
            cout << "Confirm your new password: ";
            getline(cin, confirm);

            // Check that they match and are not empty
            if (newPassword == confirm && !newPassword.empty()) {

                // Update the password in the file
                updatePassword(name, newPassword);

                // Confirm update
                cout << "Password updated successfully!\n";
            } else {
                // If they don't match or are empty, notify that nothing was updated
                cout << "The passwords do not match or are empty. Nothing was updated.\n";
            }
        } else {
            // If they do not want to change, notify that they continue with the same password
            cout << "No changes were made. You can continue using your current password.\n";
        }

    } else {
        // If the code or name do not match, notify error
        cout << "User  or code incorrect.\n";
    }
}

#endif // USER_MANAGER_H