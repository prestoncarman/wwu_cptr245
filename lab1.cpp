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
#include <cmath>

using namespace std;

// Factorial
unsigned int factorial( unsigned int number ) {
    return number <= 1 ? number : factorial(number - 1) * number;
}

// Quadratic equation.
// While the quadratic equation has a plus or minus, only consider the plus case.
double quadratic(int a, int b, int c) {
    // discriminant is negative exception
    if(pow(b, 2) - 4 * a * c < 0) throw "Discriminant is negative";

    // answer is undefined exception
    if(!a) throw "Answer is undefined";

    // calculation
    const int PRECISION = 15; // decimal precision of answer
    return trunc((-1 * b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a) * pow(10, PRECISION)) / pow(10, PRECISION);
}


// Greatest Common Divisor (GCD).
double gcd(int number1, int number2) {
    return number2 == 0 ? number1 : gcd(number2, number1 % number2);
}


// Babylonian Algorithm for square root.
// Absolute C++ Ch3 PP14
double squareRoot(double value) {
    // bad value exception
    if(value < 0) throw "Passed bad value";
    if(value == 0) return 0.0;

    // babylonian algorithm
    double guess = value / 2;
    double oldGuess;
    double r;
    while(guess - oldGuess != 0.0) {
        oldGuess = guess;
        r = value / guess;
        guess = (guess + r) / 2;
    }
    return trunc(guess*pow(10,15))/pow(10,15);  //Truncate at 15 decimal places
}


// Calculate what day of the week corresponds to the date.
// Absolute C++ Ch3 PP12
string dayOfTheWeek(int month, int day, int year) {
    static int const_factor[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4}; //factors needed for conversion
    year -= month < 3;
    int dayOfWeek = (year + year/4 - year/100 + year/400 + const_factor[month-1] + day) % 7; //returns number from 0-6
    static string days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    return days[dayOfWeek];
}


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
    if (lastName.length() == 0 || firstName.length() == 0) throw "Missing name/s";

    // adjusted letter counts for username
    unsigned long userLastCount = min(lastName.length(), LAST_LENGTH);
    unsigned long userFirstCount = min(firstName.length(), FIRST_LENGTH);

    // add more characters from first name
    if(userLastCount < LAST_LENGTH && userFirstCount >= FIRST_LENGTH) {
        userFirstCount += LAST_LENGTH - userLastCount;
    }
    // add more characters from last name
    else if(userFirstCount < FIRST_LENGTH && userLastCount >= LAST_LENGTH) {
        userLastCount += FIRST_LENGTH - userFirstCount;
    }

    // add last name characters to username
    for(int c = 0; c < userLastCount; c++) {
        username.push_back(char(tolower(lastName[c])));
    }
    // add first name characters to username
    for(int c = 0; c < userFirstCount; c++) {
        username.push_back(char(tolower(firstName[c])));
    }

    // fill all remaining spots with '_'
    double usrLngth = username.length();
    for(int c = 0; c < LAST_LENGTH + FIRST_LENGTH - usrLngth; c++) {
        username.push_back('_');
    }
}


// FACTORIAL TESTS
TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( factorial(1) == 1 );
    REQUIRE( factorial(2) == 2 );
    REQUIRE( factorial(3) == 6 );
    REQUIRE( factorial(10) == 3628800 );
}

// QUADRATIC TESTS
TEST_CASE("Quadratic value is computed", "[quadratic]") {
    SECTION("Discriminant is positive") {
        REQUIRE(quadratic(1, 2, -3) == 1.0);
        REQUIRE(quadratic(4, 2, -2) == 0.5);
        REQUIRE(quadratic(2, 2, -6) == 1.302775637731994);
    }
    REQUIRE_THROWS_WITH(quadratic(1, 2, 3), "Discriminant is negative");
    REQUIRE_THROWS_WITH(quadratic(0, 1, 2), "Answer is undefined");
}

// PARSE STUDENT NAME TESTS
TEST_CASE("Student names are parsed", "[parseStudentName]") {
    // output values declarations
    string lastName;
    string firstName;
    string userName;

    SECTION("Name length testing") {
        SECTION("Last name >= 4 && First name >= 2") {
            // parse student name
            parseStudentName("Sheldon Woodward", firstName, lastName, userName);

            // requirements
            REQUIRE(lastName == "Woodward");
            REQUIRE(firstName == "Sheldon");
            REQUIRE(userName == "woodsh");
        }
        SECTION("Last name >= 4 && First name < 2") {
            // parse student name
            parseStudentName("U Woodward", firstName, lastName, userName);

            // requirements
            REQUIRE(lastName == "Woodward");
            REQUIRE(firstName == "U");
            REQUIRE(userName == "woodwu");
        }
        SECTION("Last name < 4 && First name >= 2") {
            // parse student name
            parseStudentName("Sheldon Yip", firstName, lastName, userName);

            // requirements
            REQUIRE(lastName == "Yip");
            REQUIRE(firstName == "Sheldon");
            REQUIRE(userName == "yipshe");
        }
        SECTION("Last name < 4 && First name < 2") {
            // parse student name
            parseStudentName("U Yip", firstName, lastName, userName);

            // requirements
            REQUIRE(lastName == "Yip");
            REQUIRE(firstName == "U");
            REQUIRE(userName == "yipu__");
        }
    }
    SECTION("Too many names") {
        // requirements
        REQUIRE_THROWS_WITH(parseStudentName("Sheldon Kent Woodward", firstName, lastName, userName), "Too many names");
    }
    SECTION("Missing name/s") {
        // requirements
        REQUIRE_THROWS_WITH(parseStudentName("", firstName, lastName, userName), "Missing name/s");
        REQUIRE_THROWS_WITH(parseStudentName(" ", firstName, lastName, userName), "Missing name/s");
        REQUIRE_THROWS_WITH(parseStudentName("Sheldon ", firstName, lastName, userName), "Missing name/s");
        REQUIRE_THROWS_WITH(parseStudentName(" Woodward", firstName, lastName, userName), "Missing name/s");
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
TEST_CASE("Square roots are computed", "[squareRoot]") {
    SECTION("Passed perfect square") {
        // requirements
        REQUIRE(squareRoot(4.0) == sqrt(4.0));
        REQUIRE(squareRoot(100.0) == sqrt(100.0));
        REQUIRE(squareRoot(11.56) == trunc(sqrt(11.56)*pow(10,15))/pow(10,15));
        REQUIRE(squareRoot(133.6336) == trunc(sqrt(133.6336)*pow(10,15))/pow(10,15));
    }
    SECTION("Passed imperfect square") {
        const double PREC = 15; // number of decimal places to require accuracy of. default: 15

        // requirements
        double truncPrec = pow(10, -PREC);

        REQUIRE(abs(squareRoot(2.0) - sqrt(2.0)) < truncPrec);
        REQUIRE(abs(squareRoot(27.0) - sqrt(27.0)) < truncPrec);
        REQUIRE(abs(squareRoot(7925.0) - sqrt(7925)) < truncPrec);
    }
    SECTION("Passed negative value") {
        //requirements
        REQUIRE_THROWS_WITH(squareRoot(-1.0), "Passed bad value");
    }
    SECTION("Passed zero") {
        // requirements
        REQUIRE(squareRoot(0.0) == 0.0);
    }
}

TEST_CASE("GCD is computed", "[gcd]") {
    REQUIRE(gcd(3, 6) == 3);
    REQUIRE(gcd(12, 12) == 12);
    REQUIRE(gcd(41, 400) == 1);
    REQUIRE(gcd(48, 120) == 24);
}

TEST_CASE( "Day of Week is computed", "[dayOfTheWeek]") {
    REQUIRE( dayOfTheWeek(10, 15, 2017) == "Sunday" );
    REQUIRE( dayOfTheWeek(12, 4, 456) == "Monday" );
    REQUIRE( dayOfTheWeek(7, 22, 1073) == "Tuesday" );
    REQUIRE( dayOfTheWeek(8, 25, 2990) == "Wednesday" );
    REQUIRE( dayOfTheWeek(2, 12, 1920) == "Thursday" );
    REQUIRE( dayOfTheWeek(11, 6, 843) == "Friday" );
    REQUIRE( dayOfTheWeek(4, 14, 1) == "Saturday" );
}
