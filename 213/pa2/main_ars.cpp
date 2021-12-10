#include <iostream>

#include "AirlineReservationSystem.h"

int main() {
    AirlineReservationSystem ars;

    ars.print();

    ars.addPassenger("jack", "sophia");
    ars.addPassenger("archie", "rosie");
    ars.addPassenger("harry", "isabella");
    ars.addPassenger("oscar", "lily");
    ars.addPassenger("leo", "ivy");
    ars.addPassenger("kate", "sophia");

    ars.print();

    return 0;
}
