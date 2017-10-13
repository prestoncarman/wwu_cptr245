//=======================================================
// Name: lab1.cpp
// Author: Sheldon Woodward and Ethan Beaver
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
    number1 = abs(number1);
    number2 = abs(number2);
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
    if(lastName.length() + firstName.length() < LAST_LENGTH + FIRST_LENGTH) {
        for (int c = 0; c < LAST_LENGTH - userLastCount; c++) {
            username.push_back('_');
        }
    }
    // add first name characters to username
    for(int c = 0; c < userFirstCount; c++) {
        username.push_back(char(tolower(firstName[c])));
    }
    if(lastName.length() + firstName.length() < LAST_LENGTH + FIRST_LENGTH) {
        for (int c = 0; c < FIRST_LENGTH - userFirstCount; c++) {
            username.push_back('_');
        }
    }
}


// Tests...
TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( factorial(1) == 1 );
    REQUIRE( factorial(2) == 2 );
    REQUIRE( factorial(3) == 6 );
    REQUIRE( factorial(10) == 3628800 );
}

TEST_CASE( "Should compute quadratic", "[quadratic]" ) {
  REQUIRE( quadratic(2, 4, 2) == -1.0);
}

TEST_CASE( "When a is zero should throw floating point exception", "[quadratic]") {
  REQUIRE_THROWS_AS( quadratic(0, 20, -10), Float_exception e);
}

TEST_CASE( "If a, b, and c are specific values that create imaginary number throw imaginary_exception", "[quadratic]") {
  REQUIRE_THROWS_AS( quadratic(-1, -1, -1), Imaginary_exception e);
}

TEST_CASE( "If a or b is 0 return 0", "[gcd]") {
  REQUIRE( gcd(0, 20) == 0);
}

TEST_CASE( "It should compute the greatest common deviser", "[gcd]") {
  REQUIRE( gcd(10, 25) == 5);
}

TEST_CASE( "Should throw imaginary exception when given a negative number", "[squareRoot]") {
  REQUIRE_THROWS_AS( squareRoot(-4.00), Imaginary_exception e);
}

TEST_CASE( "Should return zero if given zero", "[squareRoot]") {
  REQUIRE( squareRoot(0.00) == 0.00);
}

TEST_CASE( "Should calculate square root of a positive double", "[squareRoot]") {
  REQUIRE( squareRoot(5) == Approx(2.2361));
}

TEST_CASE( "Should calculate leapYear", "[dayOfTheWeek]") {
  REQUIRE( getLeapYear(2017) == false);
  REQUIRE( getLeapYear(2016));
}

TEST_CASE( "Should calculate CenturyValue", "[dayOfTheWeek]") {
  REQUIRE( getCenturyValue(2016) == 6);
} 

TEST_CASE( "Should calculate MonthValue", "[dayOfTheWeek]") {
  REQUIRE( getMonthValue(2, true) == 2);
  REQUIRE( getMonthValue(2, false) == 3);
  REQUIRE( getMonthValue(5, false) == 1);
}

TEST_CASE( "Should check if the day is allowed in that month", "[dayOfTheWeek]") {
  REQUIRE( dayAllowed(31, 5, true));
  REQUIRE( dayAllowed(30, 4, false));
  REQUIRE( dayAllowed(29, 2, true));
  REQUIRE( dayAllowed(28, 2, false));
}

TEST_CASE( "It should return OutOfRange_exception if year is less than 1", "[dayOfTheWeek]") {
  REQUIRE_THROWS_AS(dayOfTheWeek(12, 5, -1000), OutOfRange_exception e);
}

TEST_CASE( "It should return OutOfRange_exception if month is less than 1", "[dayOfTheWeek]") {
  REQUIRE_THROWS_AS(dayOfTheWeek(-5, 5, 1000), OutOfRange_exception e);
}

TEST_CASE( "It should return OutOfRange_exception if day is less than 1", "[dayOfTheWeek]") {
  REQUIRE_THROWS_AS(dayOfTheWeek(12, 0, 1000), OutOfRange_exception e);
}

TEST_CASE( "It should return an OutOfRange_exception if month is greater than 12", "[dayOfTheWeek]") {
  REQUIRE_THROWS_AS( dayOfTheWeek(13, 1, 2008), OutOfRange_exception e);
}

TEST_CASE( "It should calculate the day of the week given the day, month and year", "[dayOfTheWeek]") {
  REQUIRE( dayOfTheWeek(10, 9, 2017) == "Monday");
}

TEST_CASE( "It should return an OutOfRange_exception if the day does not exist in that month", "[dayOfTheWeek]") {
  REQUIRE_THROWS_AS( dayOfTheWeek(10, 32, 2017), OutOfRange_exception e);
}


TEST_CASE( "Test for RemoveSpaces() function. It should remove all spaces and reconcatonate the strings.", "[parseStudentName]") {
  string str = "Norris, chu ck";
  string res = "Norris,chuck";
  REQUIRE(removeSpaces(str) == res);
}

TEST_CASE( "Should split the string on a delimiter, and return the parts as a vector", "[parseStudentName]") {
  string str = "howlett,james";
  vector<string> res;
  res.push_back("howlett");
  res.push_back("james");
  REQUIRE(tokenizeString(str,',') == res);
}

TEST_CASE( "Should change all characters to lowercase in string", "[parseStudentName]") {
  string str = "HeLLo WorLd";
  REQUIRE(stringToLower(str) == "hello world");
}
