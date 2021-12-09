#include <iostream>

#include "../MusicStream.h"


/*
 * Case 13 : Profile::Profile(), Profile::followProfile(), Profile::unfollowProfile().
 */
int main() {
    std::cout << "-> Creating some profiles." << std::endl;

    Profile profile1("jack@sophia.com", "jack_sophia", free_of_charge);
    Profile profile2("archie@rosie.com", "archie_rosie", premium);
    Profile profile3("harry@isabella.com", "harry_isabella", free_of_charge);
    Profile profile4("oscar@lily.com", "oscar_lily", premium);
    Profile profile5("leo@ivy.com", "leo_ivy", free_of_charge);

    std::cout << "-> Printing profiles." << std::endl;

    std::cout << "[" << profile1 << "]" << std::endl;
    std::cout << "[" << profile2 << "]" << std::endl;
    std::cout << "[" << profile3 << "]" << std::endl;
    std::cout << "[" << profile4 << "]" << std::endl;
    std::cout << "[" << profile5 << "]" << std::endl;

    std::cout << "-> Making some profiles follow other profiles." << std::endl;

    profile1.followProfile(&profile2);
    profile1.followProfile(&profile5);
    profile3.followProfile(&profile2);
    profile3.followProfile(&profile4);
    profile4.followProfile(&profile3);

    std::cout << "-> Printing profiles." << std::endl;

    std::cout << "[" << profile1 << "]" << std::endl;
    std::cout << "[" << profile2 << "]" << std::endl;
    std::cout << "[" << profile3 << "]" << std::endl;
    std::cout << "[" << profile4 << "]" << std::endl;
    std::cout << "[" << profile5 << "]" << std::endl;

    std::cout << "-> Making some profiles unfollow other profiles." << std::endl;

    profile1.unfollowProfile(&profile2);
    profile3.unfollowProfile(&profile2);
    profile4.unfollowProfile(&profile3);

    std::cout << "-> Printing profiles." << std::endl;

    std::cout << "[" << profile1 << "]" << std::endl;
    std::cout << "[" << profile2 << "]" << std::endl;
    std::cout << "[" << profile3 << "]" << std::endl;
    std::cout << "[" << profile4 << "]" << std::endl;
    std::cout << "[" << profile5 << "]" << std::endl;

    return 0;
}
