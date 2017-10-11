//=======================================================
// Name: lab1.cpp
// Author: ?
// Course: CPTR245
// Assignment: Lab 1
// Description: Write the test cases and math expressions.
//=======================================================

// catch documentation: https://github.com/philsquared/Catch
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>

using namespace std;

// Factorial
unsigned int factorial( unsigned int number ) {
    return number <= 1 ? number : factorial(number - 1) * number;
}

// Quadratic equation.
double quadratic(int a, int b, int c);


// Greatest Common Divisor (GCD).
double gcd(int number1, int number2);


// Babylonian Algorithm for square root.
// Absolute C++ Ch3 PP14
double squareRoot(double value);


// Calculate what day of the week corresponds to the date.
// Absolute C++ Ch3 PP12
string dayOfTheWeek(int month, int day, int year);


// Find the student's First and Last Name and calculate the CS username
// Username criteria
//  - First 4 characters of Last Name
//  - If last name < 4, fill characters from first name.
//  - First 2 characters of First Name
//  - If first name < 2, fill characters from last name.
void parseStudentName(const string studentName, string& firstName, string& lastName, string& username) {
    // name length requirements
    const unsigned long LAST_LENGTH = 4;
    const unsigned long FIRST_LENGTH = 2;

    // clear pass by reference values
    lastName.clear();
    firstName.clear();
    username.clear();

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


// Tests...
TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( factorial(1) == 1 );
    REQUIRE( factorial(2) == 2 );
    REQUIRE( factorial(3) == 6 );
    REQUIRE( factorial(10) == 3628800 );
}

// PARSE STUDENT NAME TESTS
TEST_CASE("Student names are parsed", "[parseStudentName]") {
    // output values declarations
    string lastName;
    string firstName;
    string userName;

    // minimum length requirements
    const unsigned long LAST_LENGTH = 4;
    const unsigned long FIRST_LENGTH = 2;

    SECTION("Last name >= 4 && First name >= 2") {
        // parse student name
        parseStudentName("Sheldon Woodward", firstName, lastName, userName);

        // requirements
        REQUIRE(lastName.length() >= LAST_LENGTH);
        REQUIRE(firstName.length() >= FIRST_LENGTH);
        REQUIRE(lastName == "Woodward");
        REQUIRE(firstName == "Sheldon");
        REQUIRE(userName == "woodsh");
    }
    SECTION("Last name < 4 && First name >= 2") {
        // parse student name
        parseStudentName("Sheldon Yip", firstName, lastName, userName);

        // requirements
        REQUIRE(lastName.length() < LAST_LENGTH);
        REQUIRE(firstName.length() >= FIRST_LENGTH);
        REQUIRE(lastName == "Yip");
        REQUIRE(firstName == "Sheldon");
        REQUIRE(userName == "yipshe");
    }
    SECTION("Last name >= 4 && First name < 2") {
        // parse student name
        parseStudentName("U Woodward", firstName, lastName, userName);

        // requirements
        REQUIRE(lastName.length() >= LAST_LENGTH);
        REQUIRE(firstName.length() < FIRST_LENGTH);
        REQUIRE(lastName == "Woodward");
        REQUIRE(firstName == "U");
        REQUIRE(userName == "woodwu");
    }
    SECTION("Last name < 4 && First name < 2") {
        // requirements
        REQUIRE_THROWS_WITH(parseStudentName("U Yip", firstName, lastName, userName), "Both names are too short");
        REQUIRE(lastName.length() < LAST_LENGTH);
        REQUIRE(firstName.length() < FIRST_LENGTH);
    }
    SECTION("Too many names") {
        // requirements
        REQUIRE_THROWS_WITH(parseStudentName("Sheldon Kent Woodward", firstName, lastName, userName), "Too many names");
    }
    SECTION("Missing name/s") {
        SECTION("Empty name string") {
            // requirements
            REQUIRE_THROWS_WITH(parseStudentName("", firstName, lastName, userName), "Missing name/s");
        }
        SECTION("No names in string") {
            // requirements
            REQUIRE_THROWS_WITH(parseStudentName(" ", firstName, lastName, userName), "Missing name/s");
        }
        SECTION("No last name in string") {
            // requirements
            REQUIRE_THROWS_WITH(parseStudentName("Sheldon ", firstName, lastName, userName), "Missing name/s");
        }
        SECTION("No first name in string") {
            // requirements
            REQUIRE_THROWS_WITH(parseStudentName(" Woodward", firstName, lastName, userName), "Missing name/s");
        }
    }
    SECTION("Pass by reference values not empty strings") {
        // assign values
        lastName = "Bob";
        firstName = "Joe";
        userName = "bobjoe";

        // parse student name
        parseStudentName("Sheldon Woodward", firstName, lastName, userName);

        // requirements
        REQUIRE(lastName == "Woodward");
        REQUIRE(firstName == "Sheldon");
        REQUIRE(userName == "woodsh");
    }
}