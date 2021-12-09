#include <iostream>

#include "../MusicStream.h"


/*
 * Case 10 : Default constructor; addProfile; addArtist/addAlbum/addSong; createPlaylist; addSongToPlaylist; subscribePremium; unsubscribePremium; getPlaylist; playPlaylist; print.
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

    std::cout << "-> Toggling subscription plans of some profiles (free_of_charge -> premium, premium -> free_of_charge)." << std::endl;

    mstream.subscribePremium("jack@sophia.com");
    mstream.unsubscribePremium("archie@rosie.com");
    mstream.subscribePremium("harry@isabella.com");
//    mstream.unsubscribePremium("oscar@lily.com");
    mstream.subscribePremium("leo@ivy.com");

    std::cout << "-> Printing the music stream." << std::endl;

    mstream.print();

    // free_of_charge.
    std::cout << "-> Getting a playlist." << std::endl;

    Playlist *playlist = mstream.getPlaylist("archie@rosie.com", 1);

    std::cout << "id must be " << 1 << ". it is " << playlist->getPlaylistId() << "." << std::endl;
    std::cout << "name must be " << "archie's favorites" << ". it is " << playlist->getName() << "." << std::endl;

    std::cout << "-> Playing the playlist." << std::endl;

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
    std::cout << "]" << std::endl;

    // premium.
    std::cout << "-> Getting another playlist." << std::endl;

    playlist = mstream.getPlaylist("oscar@lily.com", 3);

    std::cout << "id must be " << 2 << ". it is " << playlist->getPlaylistId() << "." << std::endl;
    std::cout << "name must be " << "oscar's throwback playlist" << ". it is " << playlist->getName() << "." << std::endl;

    std::cout << "-> Playing the playlist." << std::endl;

    songs = mstream.playPlaylist("oscar@lily.com", playlist);

    std::cout << "list of songs in the playlist is [";

    songNode = songs.getFirstNode();
    if (songNode) {
        do {
            std::cout << *songNode->data;
            if (songNode->next != songs.getFirstNode()) std::cout << ", ";
            songNode = songNode->next;
        } while (songNode != songs.getFirstNode());
    }
    std::cout << "]" << std::endl;

    std::cout << "-> Printing the music stream." << std::endl;

    mstream.print();

    return 0;
}
