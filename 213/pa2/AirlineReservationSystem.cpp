#include "AirlineReservationSystem.h"

void AirlineReservationSystem::addPassenger(const std::string &firstname, const std::string &lastname) {
    Passenger p = Passenger(firstname, lastname);
    passengers.insert(p);
}

Passenger *AirlineReservationSystem::searchPassenger(const std::string &firstname, const std::string &lastname) {
    Passenger p = Passenger(firstname, lastname);
    Passenger *p_node = &passengers.search(p)->data;
    return p_node;
}

void AirlineReservationSystem::addFlight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity) {
    Flight f = Flight(flightCode, departureTime, arrivalTime, departureCity, arrivalCity, economyCapacity, businessCapacity);
    flights.insert(f);
}

std::vector<Flight *> AirlineReservationSystem::searchFlight(const std::string &departureCity, const std::string &arrivalCity) {
    std::vector<Flight *> selected_flights;
    BSTNode<Flight> *current = flights.getSuccessor(NULL, preorder);
    while (current) {
        if (current->data.getDepartureCity() == departureCity && current->data.getArrivalCity() == arrivalCity) 
            selected_flights.push_back(&current->data);
        current = flights.getSuccessor(current, preorder);
    }
    return selected_flights;
}

void AirlineReservationSystem::issueTicket(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {

    Passenger *p = searchPassenger(firstname, lastname);
    Flight *f = searchFlight(flightCode);
    if (!f or !p)
        return;

    Ticket t = Ticket(p, f, ticketType);
    f->addTicket(t);
}

void AirlineReservationSystem::saveFreeTicketRequest(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    Passenger *p = searchPassenger(firstname, lastname);
    Flight *f = searchFlight(flightCode);

    if (!f or !p)
        return;

    Ticket t = Ticket(p, f, ticketType);
    freeTicketRequests.enqueue(t);
}

void AirlineReservationSystem::executeTheFlight(const std::string &flightCode) {
    Flight *f = searchFlight(flightCode);

    if (!f or f->isCompleted())
        return;

    const int q_size = freeTicketRequests.size();
    Ticket t;
    bool ticket_added;
    for (int i = 0; i < q_size; i++) {
        t = freeTicketRequests.dequeue();
        if (t.getFlight()->getFlightCode() == flightCode) {
            ticket_added = f->addTicket(t);
            if (!ticket_added)
                freeTicketRequests.enqueue(t);    
        }
        else 
            freeTicketRequests.enqueue(t);
    }

    f->setCompleted(true);
}

Flight *AirlineReservationSystem::searchFlight(const std::string &flightCode) {
    BSTNode<Flight> *current = flights.getSuccessor(NULL, preorder);
    while (current != NULL) {
        if (current->data.getFlightCode() == flightCode)
            return &current->data;
        current = flights.getSuccessor(current, preorder);         
    }
}

void AirlineReservationSystem::print() const {
    std::cout << "# Printing the airline reservation system ..." << std::endl;

    std::cout << "# Passengers:" << std::endl;
    passengers.print(inorder);

    std::cout << "# Flights:" << std::endl;
    flights.print(inorder);

    std::cout << "# Free ticket requests:" << std::endl;
    freeTicketRequests.print();

    std::cout << "# Printing is done." << std::endl;
}
