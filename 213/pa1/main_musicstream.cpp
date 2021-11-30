#include <iostream>

#include "MusicStream.h"


void print_begin_test(std::string s) {
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

    std::cout << "Adding users `john_doe` and `harry_smith`\n";
    ms.addProfile("john@doe.com", "john_doe", free_of_charge);
    ms.addProfile("harry@smith.com", "harry_smith", free_of_charge);

    std::cout << "Make `john_doe` follow `harry_smith`\n";
    ms.followProfile("john@doe.com", "harry@smith.com");
    ms.print();
    print_end_test();
}

int main() {

    
    test_add_profile();
    test_follow_profile();    


    /*ms.addArtist("The Beatles");

    ms.addAlbum("Please Please Me", 1);
    ms.addAlbum("A Hard Day's Knight", 1);

    ms.addSong("I Saw Here Standing There", 175, 1);
    ms.addSong("Do You Want to Know a Secret", 116, 1);*/
    //ms.deleteSongFromPlaylist("john@doe.com", 2, 1);
    /*ms.addSong("Things We Said Today", 155, 2);
    ms.addSong("You Can't Do That", 155, 2);*/

    return 0;
}
