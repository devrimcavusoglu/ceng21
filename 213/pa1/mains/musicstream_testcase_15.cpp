#include <iostream>

#include "../MusicStream.h"


/*
 * Case 15 : Profile::Profile(), Profile::followProfile(), Profile::createPlaylist(), Profile::addSongToPlaylist(), Profile::sharePlaylist(), Profile::unsharePlaylist(), Profile::shufflePlaylist(), Profile::getPlaylist(), Profile::getSharedPlaylists.
 */
int main() {
    std::cout << "-> Creating some profiles." << std::endl;

    Profile profile1("jack@sophia.com", "jack_sophia", free_of_charge);
    Profile profile2("archie@rosie.com", "archie_rosie", premium);
    Profile profile3("harry@isabella.com", "harry_isabella", free_of_charge);
    Profile profile4("oscar@lily.com", "oscar_lily", premium);
    Profile profile5("leo@ivy.com", "leo_ivy", free_of_charge);

    std::cout << "-> Making some profiles follow other profiles." << std::endl;

    profile1.followProfile(&profile2);
    profile1.followProfile(&profile5);
    profile3.followProfile(&profile2);
    profile3.followProfile(&profile4);
    profile4.followProfile(&profile3);

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
    profile2.addSongToPlaylist(&song3, 1);
    profile2.addSongToPlaylist(&song4, 1);
    profile4.addSongToPlaylist(&song3, 2);
    profile4.addSongToPlaylist(&song1, 3);
    profile4.addSongToPlaylist(&song4, 3);

    std::cout << "-> Printing profiles." << std::endl;

    std::cout << "[" << profile1 << "]" << std::endl;
    std::cout << "[" << profile2 << "]" << std::endl;
    std::cout << "[" << profile3 << "]" << std::endl;
    std::cout << "[" << profile4 << "]" << std::endl;
    std::cout << "[" << profile5 << "]" << std::endl;

    std::cout << "-> Marking some playlists as shared." << std::endl;

    profile2.sharePlaylist(1);
    profile4.sharePlaylist(2);
    profile4.sharePlaylist(3);

    std::cout << "-> Printing profiles." << std::endl;

    std::cout << "[" << profile1 << "]" << std::endl;
    std::cout << "[" << profile2 << "]" << std::endl;
    std::cout << "[" << profile3 << "]" << std::endl;
    std::cout << "[" << profile4 << "]" << std::endl;
    std::cout << "[" << profile5 << "]" << std::endl;

    std::cout << "-> Marking some playlists as unshared." << std::endl;

    profile4.unsharePlaylist(2);

    std::cout << "-> Printing profiles." << std::endl;

    std::cout << "[" << profile1 << "]" << std::endl;
    std::cout << "[" << profile2 << "]" << std::endl;
    std::cout << "[" << profile3 << "]" << std::endl;
    std::cout << "[" << profile4 << "]" << std::endl;
    std::cout << "[" << profile5 << "]" << std::endl;

    std::cout << "-> Shuffling the playlist with id 1 with seed 2." << std::endl;

    profile2.shufflePlaylist(1, 2);

    std::cout << "-> Printing profiles." << std::endl;

    std::cout << "[" << profile1 << "]" << std::endl;
    std::cout << "[" << profile2 << "]" << std::endl;
    std::cout << "[" << profile3 << "]" << std::endl;
    std::cout << "[" << profile4 << "]" << std::endl;
    std::cout << "[" << profile5 << "]" << std::endl;

    std::cout << "-> Getting the playlist with id 1." << std::endl;

    Playlist *playlist = profile2.getPlaylist(1);

    std::cout << "[" << *playlist << "]" << std::endl;

    std::cout << "-> Getting list of playlists shared with a profile." << std::endl;

    LinkedList<Playlist *> playlists = profile3.getSharedPlaylists();

    std::cout << "[";

    Node<Playlist *> *playlistNode = playlists.getFirstNode();
    if (playlistNode) {
        do {
            std::cout << *(playlistNode->data);
            if (playlistNode->next != playlists.getFirstNode()) std::cout << ", ";
            playlistNode = playlistNode->next;
        } while (playlistNode != playlists.getFirstNode());
    }
    std::cout << "]" << std::endl;

    std::cout << "-> Printing profiles." << std::endl;

    std::cout << "[" << profile1 << "]" << std::endl;
    std::cout << "[" << profile2 << "]" << std::endl;
    std::cout << "[" << profile3 << "]" << std::endl;
    std::cout << "[" << profile4 << "]" << std::endl;
    std::cout << "[" << profile5 << "]" << std::endl;

    return 0;
}
