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
double quadratic(int a, int b, int c);


// Greatest Common Divisor (GCD).
double gcd(int number1, int number2) {
    return number2 == 0 ? number1 : gcd(number2, number1 % number2);
}


// Babylonian Algorithm for square root.
// Absolute C++ Ch3 PP14
double squareRoot(double value);


// Calculate what day of the week corresponds to the date.
// Absolute C++ Ch3 PP12
string dayOfTheWeek(int month, int day, int year) {
    static int const_factor[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4}; //factors needed for conversion
    year -= month < 3;
    int dayOfWeek = (year + year/4 - year/100 + year/400 + const_factor[month-1] + day) % 7; //returns number from 0-6
    static string days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    return days[dayOfWeek];
}


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
