#include <iostream>

#include "MusicStream.h"


void print_begin_test(std::string s) {
    std::cout << "============ BEGINNING OF TEST ============\n";
    std::cout << ">>>> Testing =" << s << "=..\n";
}

void print_end_test() {
    std::cout << "============ END OF TEST ============\n";
}


void test_add_profile() {
    print_begin_test("Add profile");
    MusicStream ms;

    ms.print();
    ms.addProfile("john@doe.com", "john_doe", free_of_charge);
    ms.print();
    print_end_test();
}

void test_follow_profile() {
    print_begin_test("Follow & Unfollow profile");
    MusicStream ms;

    std::cout << ">>>> Adding users `john_doe` and `harry_smith`\n";
    ms.addProfile("john@doe.com", "john_doe", free_of_charge);
    ms.addProfile("harry@smith.com", "harry_smith", free_of_charge);

    std::cout << ">>>> Make `john_doe` and `harry_smith` follow each other\n";
    ms.followProfile("john@doe.com", "harry@smith.com");
    ms.followProfile("harry@smith.com", "john@doe.com");
    ms.print();

    std::cout << ">>>> Make `john_doe` unfollow `harry_smith`\n";
    ms.unfollowProfile("john@doe.com", "harry@smith.com");    
    ms.print();
    print_end_test();
}

void test_delete_profile() {
    print_begin_test("Delete profile");
    MusicStream ms;

    std::cout << ">>>> Adding users `john_doe` and `harry_smith`\n";
    ms.addProfile("john@doe.com", "john_doe", free_of_charge);
    ms.addProfile("harry@smith.com", "harry_smith", free_of_charge);

    ms.followProfile("john@doe.com", "harry@smith.com");

    std::cout << ">>>> Delete user `john_doe`\n";
    ms.deleteProfile("john@doe.com");

    ms.print();
    print_end_test();
}

void test_follow_delete_profile() {
    print_begin_test("Add Follow Delete profile");
    MusicStream ms;

    std::cout << ">>>> Adding users `john_doe` and `harry_smith`\n";
    ms.addProfile("john@doe.com", "john_doe", free_of_charge);
    ms.addProfile("harry@smith.com", "harry_smith", free_of_charge);
    ms.addProfile("jane@doe.com", "jane_doe", free_of_charge);

    std::cout << ">>>> Make `john_doe` follow `harry_smith`\n";
    ms.followProfile("john@doe.com", "harry@smith.com");
    std::cout << ">>>> Make `john_doe` and `jane_doe` follow each other\n";
    ms.followProfile("john@doe.com", "jane@doe.com");
    ms.followProfile("jane@doe.com", "john@doe.com");
    std::cout << ">>>> Make `harry_smith` follow `jane_doe`\n";
    ms.followProfile("harry@smith.com", "jane@doe.com");
    ms.print();

    std::cout << ">>>> Deleting user `john_doe`\n";
    ms.deleteProfile("john@doe.com");
    ms.print();
    print_end_test();
}

void test_add_album() {
    print_begin_test("Adding 1 artist, 2 albums");
    MusicStream ms;

    std::cout << ">>>> Adding artist `The Beatles`\n";
    ms.addArtist("The Beatles");

    std::cout << ">>>> Adding 2 albums of `The Beatles`\n";
    ms.addAlbum("Please Please Me", 1);
    ms.addAlbum("A Hard Day's Knight", 1);

    std::cout << ">>>> Adding 2 songs of `The Beatles`\n";
    ms.addSong("I Saw Here Standing There", 175, 1);
    ms.addSong("Do You Want to Know a Secret", 116, 1);
    ms.print();
    print_end_test();
}

void test_add_song() {
    print_begin_test("Adding 1 artist, 2 albums and 2 songs");
    MusicStream ms;

    std::cout << ">>>> Adding artist `The Beatles`\n";
    ms.addArtist("The Beatles");

    std::cout << ">>>> Adding 2 albums of `The Beatles`\n";
    ms.addAlbum("Please Please Me", 2);
    ms.addAlbum("A Hard Day's Knight", 2);

    std::cout << ">>>> Adding 2 songs of `The Beatles`\n";
    ms.addSong("I Saw Here Standing There", 175, 3);
    ms.addSong("Do You Want to Know a Secret", 116, 3);
    ms.print();
    print_end_test();
}


void test_playlist() {
    print_begin_test("Creating a playlist");
    MusicStream ms;

    std::cout << ">>>> Adding user `john_doe`\n";
    ms.addProfile("john@doe.com", "john_doe", free_of_charge);

    std::cout << ">>>> Adding artist `The Beatles`\n";
    ms.addArtist("The Beatles");

    std::cout << ">>>> Adding 2 albums of `The Beatles`\n";
    ms.addAlbum("Please Please Me", 3);
    ms.addAlbum("A Hard Day's Knight", 3);

    std::cout << ">>>> Adding 2 songs of `The Beatles`\n";
    ms.addSong("I Saw Here Standing There", 175, 5);
    ms.addSong("Do You Want to Know a Secret", 116, 5);
    //ms.addSong("Some Redundant Song", 145, 1);

    std::cout << ">>>> Creating a playlist named `John's Playlist`\n";
    ms.createPlaylist("john@doe.com", "John's Playlist");

    std::cout << ">>>> Adding song with id 6 & 7 to the playlist\n";
    ms.addSongToPlaylist("john@doe.com", 6, 1);
    ms.addSongToPlaylist("john@doe.com", 7, 1);
    ms.print();

    std::cout << ">>>> Removing Song with id 6 from the playlist\n";
    ms.deleteSongFromPlaylist("john@doe.com", 6, 1);
    ms.print();

    std::cout << ">>>> Playing playlist\n";
    Playlist* johns_playlist = ms.getPlaylist("john@doe.com", 1); 
    LinkedList<Song *> johns_songs = ms.playPlaylist("john@doe.com", johns_playlist);
    johns_songs.print();

    std::cout << ">>>> Deleting playlist\n";
    ms.deletePlaylist("john@doe.com", 1);
    ms.print();

    print_end_test();
}

void test_share_playlist() {
    print_begin_test("Share & Unshare Playlist");
    MusicStream ms;

    std::cout << ">>>> Adding user `john_doe`\n";
    ms.addProfile("john@doe.com", "john_doe", free_of_charge);
    ms.addProfile("harry@smith.com", "harry_smith", free_of_charge);

    ms.followProfile("harry@smith.com", "john@doe.com");

    std::cout << ">>>> Adding artist `The Beatles`\n";
    ms.addArtist("The Beatles");

    std::cout << ">>>> Adding 2 albums of `The Beatles`\n";
    ms.addAlbum("Please Please Me", 4);
    ms.addAlbum("A Hard Day's Knight", 4);

    std::cout << ">>>> Adding 2 songs of `The Beatles`\n";
    ms.addSong("I Saw Here Standing There", 175, 7);
    ms.addSong("Do You Want to Know a Secret", 116, 7);

    std::cout << ">>>> Creating a playlist named `John's Playlist`\n";
    ms.createPlaylist("john@doe.com", "John's Playlist 2");

    std::cout << ">>>> Adding song with id 6 & 7 to the playlist\n";
    ms.addSongToPlaylist("john@doe.com", 8, 2);
    ms.addSongToPlaylist("john@doe.com", 9, 2);

    ms.print();

    std::cout << ">>>> Share Playlist with id 2\n";
    ms.sharePlaylist("john@doe.com", 2);
    ms.print();

    LinkedList<Playlist *> playlists = ms.getSharedPlaylists("harry@smith.com");
    std::cout << "pl size: " << playlists.getSize() << std::endl;

    std::cout << ">>>> Unshare Playlist with id 2\n";
    ms.unsharePlaylist("john@doe.com", 2);
    ms.print();
    
    print_end_test();
}


void test_subscription() {
    print_begin_test("Subscription Plans");
    MusicStream ms;

    std::cout << ">>>> Adding user `john_doe`\n";
    ms.addProfile("john@doe.com", "john_doe", free_of_charge);

    std::cout << ">>>> Subscribing premium\n";
    ms.subscribePremium("john@doe.com");
    ms.print();

    std::cout << ">>>> Unsubscribing premium\n";
    ms.unsubscribePremium("john@doe.com");
    ms.print();    
}


void test_case_7() {
    print_begin_test("Case 7 : Default constructor; addProfile; addArtist/addAlbum/addSong; createPlaylist; addSongToPlaylist; print.");
    MusicStream ms;

    std::cout << ">>>> Adding users\n";
    ms.addProfile("jack@sophia.com", "jack_sophia", free_of_charge);
    ms.addProfile("archie@rosie.com", "archie_rosie", premium);
    ms.addProfile("harry@isabella.com", "harry_isabella", free_of_charge);
    ms.addProfile("oscar@lily.com", "oscar_lily", premium);
    ms.addProfile("leo@ivy.com", "leo_ivy", free_of_charge);

    std::cout << ">>>> Adding artist `The Beatles`\n";
    ms.addArtist("The Beatles");

    std::cout << ">>>> Adding 2 albums of `The Beatles`\n";
    ms.addAlbum("Please Please Me", 1);
    ms.addAlbum("A Hard Day's Knight", 1);

    std::cout << ">>>> Adding 4 songs of `The Beatles`\n";
    ms.addSong("I Saw Here Standing There", 175, 1);
    ms.addSong("Do You Want to Know a Secret", 116, 1);
    ms.addSong("Things We Said Today", 155, 2);
    ms.addSong("You Can't Do That", 155, 2);

    std::cout << ">>>> Creating a playlist named `John's Playlist`\n";
    ms.createPlaylist("archie@rosie.com", "archie's favorites");
    ms.createPlaylist("oscar@lily.com", "oscar's goat");
    ms.createPlaylist("oscar@lily.com", "oscar's throwback playlist");

    ms.print();

    std::cout << ">>>> Adding song with id 2 to the playlist 3\n";
    ms.addSongToPlaylist("archie@rosie.com", 2, 1);
    ms.addSongToPlaylist("oscar@lily.com", 4, 2);
    ms.addSongToPlaylist("archie@rosie.com", 3, 1);
    ms.addSongToPlaylist("oscar@lily.com", 2, 3);

    ms.sharePlaylist("archie@rosie.com", 1);
    ms.sharePlaylist("oscar@lily.com", 2);
    ms.print();

    ms.followProfile("archie@rosie.com", "oscar@lily.com");
    ms.followProfile("oscar@lily.com", "archie@rosie.com");
    ms.followProfile("archie@rosie.com", "harry@isabella.com");
    ms.followProfile("jack@sophia.com", "harry@isabella.com")

    std::cout << "################################\n";
    LinkedList<Playlist *> shareds = ms.getSharedPlaylists("archie@rosie.com");
    shareds.print();
    std::cout << "################################\n";
    ms.print();

    print_end_test();
}


int main() {
    /*test_add_profile();
    test_follow_profile();  
    test_delete_profile();
    test_follow_delete_profile();  
    test_add_album();
    test_add_song();
    test_playlist();
    test_share_playlist();
    test_subscription();*/

    test_case_7();


    return 0;
}
