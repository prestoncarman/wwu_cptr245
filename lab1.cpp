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
    return guess;
}


// Calculate what day of the week corresponds to the date.
// Absolute C++ Ch3 PP12
string dayOfTheWeek(int month, int day, int year);


// Find the student's Frist and Last Name and calculate the CS username
// Username criteria
//  - First 4 characters of Last Name
//  - If last name < 4, fill characters from first name.
//  - First 2 characters of First Name
//  - If first name < 2, fill characters from last name.
void parseStudentName(const string studentName, string& firstName, string& lastName, string& username);


// Tests...
TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( factorial(1) == 1 );
    REQUIRE( factorial(2) == 2 );
    REQUIRE( factorial(3) == 6 );
    REQUIRE( factorial(10) == 3628800 );
}

TEST_CASE("Square roots are computed", "[squareRoot]") {
    SECTION("Passed perfect square") {
        // requirements
        REQUIRE(squareRoot(4.0) == sqrt(4.0));
        REQUIRE(squareRoot(9.0) == sqrt(9.0));
        REQUIRE(squareRoot(16.0) == sqrt(16.0));
        REQUIRE(squareRoot(25.0) == sqrt(25.0));
        REQUIRE(squareRoot(36.0) == sqrt(36.0));
        REQUIRE(squareRoot(49.0) == sqrt(49.0));
        REQUIRE(squareRoot(64.0) == sqrt(64.0));
        REQUIRE(squareRoot(81.0) == sqrt(81.0));
        REQUIRE(squareRoot(100.0) == sqrt(100.0));
    }
    SECTION("Passed imperfect square") {
        // TODO: Check for proper testing/TDD form
        // test customizability
        const double PREC = 10; // number of decimal places to require accuracy of. default: 10
        const double INCR_X = 0.001; // x-value of y=x^3 where y is the val passed into squareRoot(). Default: 0.001
        const int TEST_NUM = 10000; // number of tests to run. Default: 10,000
        const double OFFSET = 0.0; // offset added to y to test different range of values in the same scope. Default: 0.0

        // requirements
        double roundPrec = pow(10, PREC);
        double val;
        for(double i = 0.0; i < INCR_X * TEST_NUM; i += INCR_X) {
            val = pow(i, 3) + OFFSET; // val=i^3 for better curve of values to test

            // require rounded values to be equal
            REQUIRE(round(squareRoot(val) * roundPrec) / roundPrec == round(sqrt(val) * roundPrec) / roundPrec);
        }
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