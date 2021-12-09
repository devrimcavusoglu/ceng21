#include <iostream>

#include "../MusicStream.h"


/*
 * Case 12 : Default constructor; addProfile; addArtist/addAlbum/addSong; createPlaylist; addSongToPlaylist; sharePlaylist, unsharePlaylist, getSharedPlaylists; print.
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

    std::cout << "-> Making some profiles follow other profiles." << std::endl;

    mstream.followProfile("jack@sophia.com", "harry@isabella.com");
    mstream.followProfile("archie@rosie.com", "oscar@lily.com");
    mstream.followProfile("oscar@lily.com", "archie@rosie.com");
    mstream.followProfile("archie@rosie.com", "harry@isabella.com");

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

    std::cout << "-> Creating some playlists." << std::endl;

    mstream.createPlaylist("archie@rosie.com", "archie's favorites");
    mstream.createPlaylist("oscar@lily.com", "oscar's goat");
    mstream.createPlaylist("oscar@lily.com", "oscar's throwback playlist");

    std::cout << "-> Adding some songs to some playlists." << std::endl;

    mstream.addSongToPlaylist("archie@rosie.com", 2, 1);
    mstream.addSongToPlaylist("archie@rosie.com", 3, 1);
    mstream.addSongToPlaylist("oscar@lily.com", 4, 2);
    mstream.addSongToPlaylist("oscar@lily.com", 2, 3);
    mstream.addSongToPlaylist("oscar@lily.com", 5, 3);

    std::cout << "-> Printing the music stream." << std::endl;

    mstream.print();

    std::cout << "-> Marking some playlists as shared." << std::endl;

    mstream.sharePlaylist("archie@rosie.com", 1);
    mstream.sharePlaylist("oscar@lily.com", 2);
    mstream.sharePlaylist("oscar@lily.com", 3);

    std::cout << "-> Printing the music stream." << std::endl;

    mstream.print();

    std::cout << "-> Marking some playlists as unshared." << std::endl;

    mstream.unsharePlaylist("archie@rosie.com", 1);

    std::cout << "-> Printing the music stream." << std::endl;

    mstream.print();

    std::cout << "-> Getting list of playlists shared with a profile." << std::endl;

    LinkedList<Playlist *> playlists = mstream.getSharedPlaylists("archie@rosie.com");

    std::cout << "list of playlists is [";

    Node<Playlist *> *playlistNode = playlists.getFirstNode();
    if (playlistNode) {
        do {
            std::cout << *playlistNode->data;
            if (playlistNode->next != playlists.getFirstNode()) std::cout << ", ";
            playlistNode = playlistNode->next;
        } while (playlistNode != playlists.getFirstNode());
    }
    std::cout << "]." << std::endl;

    std::cout << "-> Printing the music stream." << std::endl;

    mstream.print();

    return 0;
}
