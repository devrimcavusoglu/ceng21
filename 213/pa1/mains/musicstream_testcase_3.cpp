#include <iostream>

#include "../MusicStream.h"


/*
 * Case 3 : Default constructor; addArtist/addAlbum/addSong; print.
 */
int main() {
    std::cout << "-> Creating a music stream with default constructor." << std::endl;

    MusicStream mstream;

    std::cout << "-> Adding artists to the music stream." << std::endl;

    mstream.addArtist("The Beatles");

    std::cout << "-> Adding albums to the music stream." << std::endl;

    mstream.addAlbum("Please Please Me", 1);
    mstream.addAlbum("A Hard Day's Night", 1);

    std::cout << "-> Adding songs to the music stream." << std::endl;

    mstream.addSong("I Saw Here Standing There", 175, 1);
    mstream.addSong("Do You Want to Know a Secret", 116, 1);
    mstream.addSong("Things We Said Today", 155, 2);
    mstream.addSong("You Can't Do That", 155, 2);

    std::cout << "-> Printing the music stream." << std::endl;

    mstream.print();

    return 0;
}
