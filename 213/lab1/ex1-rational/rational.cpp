#include <iostream>
#include "rational.hpp"

// Default (zero-argument) constructor
Rational::Rational()
{
    numer = denom = 0;
}

// Two argument constructor
Rational::Rational(int num, int den)
{
    numer = num;
    denom = den;
}

void Rational::setNumerator(int num)
{
    numer = num;
}

int Rational::getNumerator()
{
    return numer;
}

void Rational::setDenominator(int den)
{
    denom = den;
}

int Rational::getDenominator()
{
    return denom;
}

void Rational::print()
{
    if (denom == 1)
        std::cout << numer << "\n";
    else
        std::cout << numer << "/" << denom << "\n";
}

// Returns a + b
Rational Rational::add(Rational rhs)
{
    Rational result;
    
    /* TO-DO: fill add */
    
    // Simplify the result if possible. Note that we
    // are not passing "result" as an argument to
    // "simplify". Instead we are calling the "simplify"
    // function of the "result" object.

    result.setNumerator(numer * rhs.denom + rhs.numer * denom);
    result.setDenominator(denom * rhs.denom);

    result.simplify();

    return result;
}

// Returns a * b
Rational Rational::multiply(Rational rhs)
{
    Rational result;

    result.setNumerator(numer * rhs.numer);
    result.setDenominator(denom * rhs.denom);
    
    result.simplify();
    return result;
}

void Rational::simplify()
{
    int gcd_;
    gcd_ = gcd(numer, denom);
    numer = numer / gcd_;
    denom = denom / gcd_;
}

int Rational::gcd(int a, int b)
{
    int c;

    if(a<0)
        a = a * -1;
    if(b<0)
        b = b * -1;

    while (a != 0)
    {
        c = a;
        a = b % a;
        b = c;
    }

    return b;
}
