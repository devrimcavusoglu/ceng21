#include <iostream>

#include "../MusicStream.h"


/*
 * Case 11 : Default constructor; addProfile; addArtist/addAlbum/addSong; createPlaylist; addSongToPlaylist; shufflePlaylist; getPlaylist; playPlaylist; print.
 */
int main() {
    std::cout << "-> Creating a music stream with default constructor." << std::endl;

    MusicStream mstream;

    std::cout << "-> Adding a profile to the music stream." << std::endl;

    mstream.addProfile("archie@rosie.com", "archie_rosie", premium);

    std::cout << "-> Adding an artist to the music stream." << std::endl;

    mstream.addArtist("The Beatles");

    std::cout << "-> Adding albums to the music stream." << std::endl;

    mstream.addAlbum("Please Please Me", 1);
    mstream.addAlbum("A Hard Day's Night", 1);

    std::cout << "-> Adding songs to the music stream." << std::endl;

    mstream.addSong("I Saw Here Standing There", 175, 1);
    mstream.addSong("Do You Want to Know a Secret", 116, 1);
    mstream.addSong("Twist and Shout", 152, 1);
    mstream.addSong("Things We Said Today", 155, 2);
    mstream.addSong("You Can't Do That", 155, 2);
    mstream.addSong("I Should Have Known Better", 166, 2);

    std::cout << "-> Creating a playlist." << std::endl;

    mstream.createPlaylist("archie@rosie.com", "archie's favorites");

    std::cout << "-> Adding some songs to the playlists." << std::endl;

    mstream.addSongToPlaylist("archie@rosie.com", 2, 1);
    mstream.addSongToPlaylist("archie@rosie.com", 3, 1);
    mstream.addSongToPlaylist("archie@rosie.com", 4, 1);
    mstream.addSongToPlaylist("archie@rosie.com", 5, 1);
    mstream.addSongToPlaylist("archie@rosie.com", 6, 1);
    mstream.addSongToPlaylist("archie@rosie.com", 7, 1);

    std::cout << "-> Printing the music stream." << std::endl;

    mstream.print();

    for (int i = 2; i <= 4; ++i) {
        std::cout << "-> Shuffling the playlist with id 1 with seed " << i << "." << std::endl;

        mstream.shufflePlaylist("archie@rosie.com", 1, i);

        std::cout << "-> Getting and playing the playlist." << std::endl;

        Playlist *playlist = mstream.getPlaylist("archie@rosie.com", 1);

        LinkedList<Song *> songs = mstream.playPlaylist("archie@rosie.com", playlist);

        std::cout << "list of songs in the playlist is [";

        Node<Song *> *songNode = songs.getFirstNode();
        if (songNode) {
            do {
                std::cout << *songNode->data;
                if (songNode->next != songs.getFirstNode()) std::cout << ", ";
                songNode = songNode->next;
            } while (songNode != songs.getFirstNode());
        }
        std::cout << "]." << std::endl;
    }

    std::cout << "-> Printing the music stream." << std::endl;

    mstream.print();

    return 0;
}
