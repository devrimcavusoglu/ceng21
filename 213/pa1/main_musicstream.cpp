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
    print_begin_test("Follow profile");
    MusicStream ms;

    std::cout << ">>>> Adding users `john_doe` and `harry_smith`\n";
    ms.addProfile("john@doe.com", "john_doe", free_of_charge);
    ms.addProfile("harry@smith.com", "harry_smith", free_of_charge);

    std::cout << ">>>> Make `john_doe` follow `harry_smith`\n";
    ms.followProfile("john@doe.com", "harry@smith.com");
    ms.print();
    print_end_test();
}


void test_add_song() {
    print_begin_test("Adding 1 artist, 2 albums and 2 songs");
    MusicStream ms;

    std::cout << ">>>> Adding artist `The Beatles`\n";
    ms.addArtist("The Beatles");

    std::cout << ">>>> Adding 2 albums of `The Beatles`\n";
    ms.addAlbum("Please Please Me", 1);
    ms.addAlbum("A Hard Day's Knight", 1);

    std::cout << ">>>> Adding two songs of `The Beatles`\n";
    ms.addSong("I Saw Here Standing There", 175, 1);
    ms.addSong("Do You Want to Know a Secret", 116, 1);
    ms.print();
}


int main() {

    
    test_add_profile();
    test_follow_profile();    
    test_add_song();


    //ms.deleteSongFromPlaylist("john@doe.com", 2, 1);
    /*ms.addSong("Things We Said Today", 155, 2);
    ms.addSong("You Can't Do That", 155, 2);*/

    return 0;
}
