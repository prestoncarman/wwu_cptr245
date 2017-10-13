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
double gcd(int number1, int number2);


// Babylonian Algorithm for square root.
// Absolute C++ Ch3 PP14
double squareRoot(double value);


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