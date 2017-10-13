#include <string>

// function with error introduced
void parseStudentNameERROR(const string studentName, string& firstName, string& lastName, string& username) {
    // name length requirements
    const unsigned long LAST_LENGTH = 4;
    const unsigned long FIRST_LENGTH = 2;

    // empty studentName
    if (studentName.length() == 0) throw "Missing name/s";

    // parse studentName
    unsigned int spaceCount = 0; // space count in studentName
    for (int c = 0; c < studentName.length(); c++) {
        if (studentName[c] == ' ') spaceCount++; // found space
        else if (spaceCount == 0) firstName.push_back(studentName[c]); // build firstName
        else if (spaceCount == 1) lastName.push_back(studentName[c]); // build lastName
        else throw "Too many names"; // more than one space
    }

    // exceptions
    if (spaceCount == 0) throw "Missing name/s";
    if (lastName.length() == 0 || firstName.length() == 0) throw "Missing name/s";
    if (lastName.length() < LAST_LENGTH && firstName.length() < FIRST_LENGTH) throw "Both names are too short";

    // adjusted letter counts for CS username
    unsigned long userLastCount = LAST_LENGTH;
    unsigned long userFirstCount = FIRST_LENGTH;

    // recalculate CS name lengths
    if (lastName.length() < LAST_LENGTH) {
        userLastCount = lastName.length(); // add all characters from last name
        userFirstCount += (LAST_LENGTH - lastName.length()); // add more characters from first name
    }
    else if (firstName.length() < FIRST_LENGTH) {
        userFirstCount = firstName.length(); // add all characters from first name
        userLastCount += (FIRST_LENGTH - firstName.length()); // add more characters from last name
    }

    // create CS username
    for (int c = 0; c < userLastCount; c++) username.push_back(char(tolower(lastName[c]))); // add to lastName
    for (int c = 0; c < userFirstCount; c++) username.push_back(char(tolower(firstName[c]))); // add to FirstName
}