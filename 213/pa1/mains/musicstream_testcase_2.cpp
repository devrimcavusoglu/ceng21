#include <iostream>

#include "../MusicStream.h"


/*
 * Case 2 : Default constructor; addProfile; print.
 */
int main() {
    std::cout << "-> Creating a music stream with default constructor." << std::endl;

    MusicStream mstream;

    std::cout << "-> Adding profiles to the music stream." << std::endl;

    mstream.addProfile("jack@sophia.com", "jack_sophia", free_of_charge);
    mstream.addProfile("archie@rosie.com", "archie_rosie", premium);
    mstream.addProfile("harry@isabella.com", "harry_isabella", free_of_charge);
    mstream.addProfile("oscar@lily.com", "oscar_lily", premium);
    mstream.addProfile("leo@ivy.com", "leo_ivy", free_of_charge);

    std::cout << "-> Printing the music stream." << std::endl;

    mstream.print();

    return 0;
}
