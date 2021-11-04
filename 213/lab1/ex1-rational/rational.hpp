#ifndef __rational_v1_hpp__
#define __rational_v1_hpp__

class Rational
{
    public:
        // Constructors are used to initialize the data
        // members during the creating of an object
        Rational();
        Rational(int num, int den);

        // public member functions
        Rational add(Rational rhs);
        Rational multiply(Rational rhs);

        // set/get functions can be used to access
        // and modify private variables
        void setNumerator(int num);
        int getNumerator();
        void setDenominator(int den);
        int getDenominator();

        void print();

    private:
        // private member functions
        void simplify();
        int gcd(int a, int b);

        // private data members
        int numer;
        int denom;
};

#endif // __rational_v1_hpp__