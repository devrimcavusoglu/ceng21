#include <iostream>

#include "../MusicStream.h"


/*
 * Case 1 : Default constructor; print.
 */
int main() {
    std::cout << "-> Creating a music stream with default constructor." << std::endl;

    MusicStream mstream;

    std::cout << "-> Printing the music stream." << std::endl;

    mstream.print();

    return 0;
}
