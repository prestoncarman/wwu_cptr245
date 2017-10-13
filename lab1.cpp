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
