#include <iostream>

#include "../MusicStream.h"


/*
 * Case 7 : Default constructor; addProfile; addArtist/addAlbum/addSong; createPlaylist; addSongToPlaylist; print.
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

    std::cout << "-> Creating some playlists." << std::endl;

    mstream.createPlaylist("archie@rosie.com", "archie's favorites");
    mstream.createPlaylist("oscar@lily.com", "oscar's goat");
    mstream.createPlaylist("oscar@lily.com", "oscar's throwback playlist");

    std::cout << "-> Printing the music stream." << std::endl;

    mstream.print();

    std::cout << "-> Adding some songs to some playlists." << std::endl;

    mstream.addSongToPlaylist("archie@rosie.com", 2, 1);
    mstream.addSongToPlaylist("archie@rosie.com", 3, 1);
    mstream.addSongToPlaylist("oscar@lily.com", 4, 2);
    mstream.addSongToPlaylist("oscar@lily.com", 2, 3);
    mstream.addSongToPlaylist("oscar@lily.com", 5, 3);

    std::cout << "-> Printing the music stream." << std::endl;

    mstream.print();

    return 0;
}
