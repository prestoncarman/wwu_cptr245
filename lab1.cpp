//=======================================================
// Name: lab1.cpp
// Author: PatrickDunphy NickPerry
// Course: CPTR245
// Assignment: Lab 1
// Description: Write the test cases and math expressions.
//=======================================================

// catch documentation: https://github.com/philsquared/Catch
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Factorial
unsigned int factorial( unsigned int number ) {
    return number <= 1 ? number : factorial(number - 1) * number;
}

// Quadratic equation. Plus only.
double quadratic(int a, int b, int c)
{
    if (b*b < 4*a*c)
        throw invalid_argument("Invalid Inputs");
    if (a == 0)
        throw invalid_argument("'a' can't be zero")
    return ((-b + sqrt(b*b-4*a*c))/(2*a));
}

// Greatest Common Divisor (GCD).
double gcd(int number1, int number2)
{//For the sake of time, we are using code partially written by an outside source, and will write tests for that.
 //Source is: https://codereview.stackexchange.com/questions/66711/greatest-common-divisor
   double gcd;
     if (number1 < 0)
        number1 = 0 - number1;
     if (number2 < 0)
        number2 = 0 - number2;
   for(double i=1;i<=number1&&i<=number2;i++){
    if(number1%i==0 && number2%i == 0 )
        gcd=i;
   }
   return gcd;
}

// Babylonian Algorithm for square root.
// Absolute C++ Ch3 PP14
double squareRoot(double value);
{
    if (value < 0)
        throw invalid_argument("Can't square root a negative");
    double guess = 1;
    double ans;
    while (true)
    {
        ans = (guess + (value / guess)) / 2;
        if (ans >= guess-.0000000001 && ans <= guess+.0000000001)
            return ans;
        guess = ans;
    }
    
}

// GCD TESTS
TEST_CASE("GCD is computed", "[gcd]") {
    REQUIRE(gcd(0, 0) == 0);
    REQUIRE(gcd(0, -1) == 1);
    REQUIRE(gcd(-5, -8) == 1);
    REQUIRE(gcd(-5, -15) == 5);
    REQUIRE(gcd(-12, -14) == 2);
    REQUIRE(gcd(3, 6) == 3);
    REQUIRE(gcd(12, 12) == 12);
    REQUIRE(gcd(41, 400) == 1);
    REQUIRE(gcd(48, 120) == 24);
    REQUIRE(gcd(-5, 5) == 5);
}

// DAY OF THE WEEK TESTS
TEST_CASE( "Day of Week is computed", "[dayOfTheWeek]") {
    REQUIRE( dayOfTheWeek(10, 15, 2017) == "Sunday" );
    REQUIRE( dayOfTheWeek(12, 4, 456) == "Monday" );
    REQUIRE( dayOfTheWeek(7, 22, 1073) == "Tuesday" );
    REQUIRE( dayOfTheWeek(8, 25, 2990) == "Wednesday" );
    REQUIRE( dayOfTheWeek(2, 12, 1920) == "Thursday" );
    REQUIRE( dayOfTheWeek(11, 6, 843) == "Friday" );
    REQUIRE( dayOfTheWeek(4, 14, 1) == "Saturday" );
}


// SQUARE ROOT TESTS
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
