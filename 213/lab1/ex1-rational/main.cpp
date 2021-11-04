#include <iostream>
#include "rational.hpp"

int main()
{
    std::cout << "Hello Rational!" << std::endl;
    
    Rational a(1, 2); // initialized by the 2-argument constructor
    Rational b(3, 4); // initialized by the 2-argument constructor
    Rational c;       // initialized by the 0-argument constructor

    c = a.add(b);
    
    c.print();

    return 0;
}
