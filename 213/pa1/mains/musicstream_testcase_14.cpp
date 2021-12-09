#include <iostream>

#include "../MusicStream.h"


/*
 * Case 14 : Profile::Profile(), Profile::createPlaylist(), Profile::addSongToPlaylist(), Profile::deletePlaylist(), Profile::deleteSongFromPlaylist().
 */
int main() {
    std::cout << "-> Creating some profiles." << std::endl;

    Profile profile1("jack@sophia.com", "jack_sophia", free_of_charge);
    Profile profile2("archie@rosie.com", "archie_rosie", premium);
    Profile profile3("harry@isabella.com", "harry_isabella", free_of_charge);
    Profile profile4("oscar@lily.com", "oscar_lily", premium);
    Profile profile5("leo@ivy.com", "leo_ivy", free_of_charge);

    std::cout << "-> Creating some playlists." << std::endl;

    profile2.createPlaylist("archie's favorites");
    profile4.createPlaylist("oscar's goat");
    profile4.createPlaylist("oscar's throwback playlist");

    std::cout << "-> Adding some songs to some playlists." << std::endl;

    Song song1("I Saw Here Standing There", 175);
    Song song2("Do You Want to Know a Secret", 116);
    Song song3("Things We Said Today", 155);
    Song song4("You Can't Do That", 155);

    profile2.addSongToPlaylist(&song1, 1);
    profile2.addSongToPlaylist(&song2, 1);
    profile4.addSongToPlaylist(&song3, 2);
    profile4.addSongToPlaylist(&song1, 3);
    profile4.addSongToPlaylist(&song4, 3);

    std::cout << "-> Printing profiles." << std::endl;

    std::cout << "[" << profile1 << "]" << std::endl;
    std::cout << "[" << profile2 << "]" << std::endl;
    std::cout << "[" << profile3 << "]" << std::endl;
    std::cout << "[" << profile4 << "]" << std::endl;
    std::cout << "[" << profile5 << "]" << std::endl;

    std::cout << "-> Deleting some playlists." << std::endl;

    profile4.deletePlaylist(2);

    std::cout << "-> Printing profiles." << std::endl;

    std::cout << "[" << profile1 << "]" << std::endl;
    std::cout << "[" << profile2 << "]" << std::endl;
    std::cout << "[" << profile3 << "]" << std::endl;
    std::cout << "[" << profile4 << "]" << std::endl;
    std::cout << "[" << profile5 << "]" << std::endl;

    std::cout << "-> Deleting some songs from some playlists." << std::endl;

    profile2.deleteSongFromPlaylist(&song1, 1);
    profile4.deleteSongFromPlaylist(&song4, 3);

    std::cout << "-> Printing profiles." << std::endl;

    std::cout << "[" << profile1 << "]" << std::endl;
    std::cout << "[" << profile2 << "]" << std::endl;
    std::cout << "[" << profile3 << "]" << std::endl;
    std::cout << "[" << profile4 << "]" << std::endl;
    std::cout << "[" << profile5 << "]" << std::endl;

    return 0;
}
