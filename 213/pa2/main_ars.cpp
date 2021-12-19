#include <iostream>

#include "AirlineReservationSystem.h"


void print_test_begin(std::string test_name) {
    std::cout << "===== BEGIN " << test_name << " =====\n";
}

void print_test_end() {
    std::cout << "===== END OF TEST ======\n";
}

void ars_testcase2(AirlineReservationSystem &ars) {
    print_test_begin("Test functions on empty tree..");
    ars.addPassenger("jack", "sophia");
    ars.addPassenger("archie", "rosie");
    ars.addPassenger("harry", "isabella");
    ars.addPassenger("oscar", "lily");
    ars.addPassenger("leo", "ivy");
    ars.addPassenger("kate", "sophia");

    ars.print();
    print_test_end();
}


int main() {
    AirlineReservationSystem ars;
    ars.print();

    ars_testcase2(ars);


    return 0;
}
