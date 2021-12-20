#include <iostream>

#include "AirlineReservationSystem.h"


void print_test_begin(std::string test_name) {
    std::cout << "===== BEGIN " << test_name << " =====\n";
}

void print_test_end() {
    std::cout << "===== END OF TEST ======\n";
}

void ars_testcase2(AirlineReservationSystem ars) {
    print_test_begin("Test Case 2 | addPassenger, print.");
    ars.addPassenger("jack", "sophia");
    ars.addPassenger("archie", "rosie");
    ars.addPassenger("harry", "isabella");
    ars.addPassenger("oscar", "lily");
    ars.addPassenger("leo", "ivy");
    ars.addPassenger("kate", "sophia");

    ars.print();
    print_test_end();
}

void ars_testcase5(AirlineReservationSystem ars) {
    print_test_begin("Test Case 5 | addPassenger, addFlight, searchFlight, print");
    // addPassengers
    ars.addPassenger("jack", "sophia");
    ars.addPassenger("archie", "rosie");
    ars.addPassenger("harry", "isabella");
    ars.addPassenger("oscar", "lily");
    ars.addPassenger("leo", "ivy");
    ars.addPassenger("kate", "sophia");

    // addFlight
    ars.addFlight("19030", "2020/12/20 17:30:00", "2020/12/20 18:30:00", "ANKARA", "ISTANBUL", 70, 30);
    ars.addFlight("19040", "2020/12/20 17:30:00", "2020/12/20 18:30:00", "ANKARA", "IZMIR", 70, 30);
    ars.addFlight("19045", "2020/12/20 18:30:00", "2020/12/20 19:30:00", "ANKARA", "ISTANBUL", 70, 30);
    ars.addFlight("19050", "2020/12/20 17:30:00", "2020/12/20 18:45:00", "ISTANBUL", "ANTALYA", 60, 40);

    // searchFlight
    std::cout << "Selecting flights from ANKARA to ISTANBUL\n";
    std::vector<Flight *> s_flight = ars.searchFlight("ANKARA", "ISTANBUL");

    for (int i = 0; i < s_flight.size(); i++)
        std::cout << "selected flight (" << i << ") " << s_flight[i]->getFlightCode() << std::endl;
    ars.print();
    print_test_end();
}


void ars_testcase6(AirlineReservationSystem ars) {
    print_test_begin("Test Case 6 | addPassenger, addFlight, searchFlight, print");
    // addPassengers
    ars.addPassenger("jack", "sophia");
    ars.addPassenger("archie", "rosie");
    ars.addPassenger("harry", "isabella");
    ars.addPassenger("oscar", "lily");
    ars.addPassenger("leo", "ivy");
    ars.addPassenger("kate", "sophia");

    // addFlight
    ars.addFlight("19030", "2020/12/20 17:30:00", "2020/12/20 18:30:00", "ANKARA", "ISTANBUL", 70, 30);
    ars.addFlight("19040", "2020/12/20 17:30:00", "2020/12/20 18:30:00", "ANKARA", "IZMIR", 70, 30);
    ars.addFlight("19045", "2020/12/20 18:30:00", "2020/12/20 19:30:00", "ANKARA", "ISTANBUL", 70, 30);
    ars.addFlight("19050", "2020/12/20 17:30:00", "2020/12/20 18:45:00", "ISTANBUL", "ANTALYA", 60, 40);

    // issueTicket
    std::cout << "Issuing a ticket for 'no one' on 19030 (passenger not available)..\n";
    // (firstname, lastname, flightCode, ticketType)
    ars.issueTicket("no", "one", "19030", economy);
    std::cout << "Issuing a ticket for 'oscar lily' on 19030 (passenger available)..\n";
    ars.issueTicket("oscar", "lily", "19030", business);

    std::cout << "Issuing a ticket for 'leo ivy' on 19045 (passenger available)..\n";
    ars.issueTicket("leo", "ivy", "19045", economy);    
    ars.print();

    print_test_end();
}

void ars_testcase8(AirlineReservationSystem ars) {
    print_test_begin("Test Case 8 | addPassenger, addFlight, saveFreeTicketRequest; executeTheFlight; print");
    // addPassengers
    ars.addPassenger("jack", "sophia");
    ars.addPassenger("archie", "rosie");
    ars.addPassenger("harry", "isabella");
    ars.addPassenger("oscar", "lily");
    ars.addPassenger("leo", "ivy");
    ars.addPassenger("kate", "sophia");

    // addFlight
    ars.addFlight("DS7020", "20/12/2021 15:00", "20/12/2021 16:30", "Ankara", "London", 100, 5);
    ars.addFlight("DS7030", "20/12/2021 11:00", "20/12/2021 12:30", "Ankara", "Brussels", 200, 10);
    ars.addFlight("DS7040", "20/12/2021 13:00", "20/12/2021 14:30", "Ankara", "London", 200, 10);
    ars.addFlight("DS7050", "20/12/2021 10:00", "20/12/2021 11:30", "Ankara", "Istanbul", 200, 10);
    ars.addFlight("DS7060", "20/12/2021 14:00", "20/12/2021 15:30", "Ankara", "Rome", 200, 10);
    ars.addFlight("DS7070", "20/12/2021 12:00", "20/12/2021 13:30", "Ankara", "Amsterdam", 200, 10);
    ars.addFlight("DS7080", "20/12/2021 16:00", "20/12/2021 17:30", "Ankara", "London", 50, 0);

    // issueTicket
    //std::cout << "Issuing a ticket for 'oscar lily' on 19030 (passenger available)..\n";
    //ars.issueTicket("oscar", "lily", "19030", business);

    // saveFreeTicketRequest
    std::cout << "Free Ticket Request for 'no one' on 19030 (passenger not available)..\n";
    ars.saveFreeTicketRequest("jack", "sophia", "DS7050", economy);
    ars.saveFreeTicketRequest("archie", "rosie", "DS7040", economy);
    ars.saveFreeTicketRequest("harry", "isabella", "DS7040", economy);
    ars.saveFreeTicketRequest("oscar", "lily", "DS7080", economy);
    ars.saveFreeTicketRequest("leo", "ivy", "DS7080", economy);
    ars.saveFreeTicketRequest("kate", "sophia", "DS7080", business);

    // executeTheFlight
    std::cout << "Executing the flights\n";
    ars.executeTheFlight("DS7020");
    ars.executeTheFlight("DS7030");
    ars.executeTheFlight("DS7040");
    ars.executeTheFlight("DS7050");
    ars.executeTheFlight("DS7060");
    ars.executeTheFlight("DS7070");
    ars.executeTheFlight("DS7080");

    ars.print();

    print_test_end();
}

int main() {
    AirlineReservationSystem ars;
    ars.print();

    ars_testcase2(ars);
    ars_testcase5(ars);
    ars_testcase6(ars);
    ars_testcase8(ars);

    return 0;
}
