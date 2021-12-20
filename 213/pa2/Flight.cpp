#include "Flight.h"

Flight::Flight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity) {
    this->flightCode = flightCode;
    this->departureTime = departureTime;
    this->arrivalTime = arrivalTime;
    this->departureCity = departureCity;
    this->arrivalCity = arrivalCity;
    this->economyCapacity = economyCapacity;
    this->businessCapacity = businessCapacity;
    this->completed = false;
}

const std::string &Flight::getFlightCode() const {
    return flightCode;
}

const std::string &Flight::getDepartureTime() const {
    return departureTime;
}

const std::string &Flight::getArrivalTime() const {
    return arrivalTime;
}

const std::string &Flight::getDepartureCity() const {
    return departureCity;
}

const std::string &Flight::getArrivalCity() const {
    return arrivalCity;
}

int Flight::getEconomyCapacity() const {
    return economyCapacity;
}

int Flight::getBusinessCapacity() const {
    return businessCapacity;
}

bool Flight::isCompleted() const {
    return completed;
}

void Flight::setCompleted(bool completed) {
    this->completed = completed;
}

bool Flight::addTicket(const Ticket &ticket) {
    if (isCompleted()) 
        return false;
    TicketType type = ticket.getTicketType();

    int current_count = 0;
    for (int i = 0; i < tickets.size(); i++) {
        if (tickets[i].getTicketType() == type)
            current_count++;
    }

    if (type == economy && current_count < economyCapacity)
        tickets.push_back(ticket);
    else if (type == business && current_count < businessCapacity)
        tickets.push_back(ticket);
    else
        return false;

    if (tickets.size() == economyCapacity + businessCapacity)
        setCompleted(true);
    return true;
}

bool Flight::operator<(const Flight &rhs) const {
    return this->flightCode < rhs.getFlightCode();
}

bool Flight::operator>(const Flight &rhs) const {
    return rhs < *this;
}

bool Flight::operator==(const Flight &rhs) const {
    return flightCode == rhs.flightCode;
}

bool Flight::operator!=(const Flight &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Flight &flight) {
    os << "Flight(flightCode: " << flight.flightCode;
    os << ", departureTime: " << flight.departureTime;
    os << ", arrivalTime: " << flight.arrivalTime;
    os << ", departureCity: " << flight.departureCity;
    os << ", arrivalCity: " << flight.arrivalCity;
    os << ", economyCapacity: " << flight.economyCapacity;
    os << ", businessCapacity: " << flight.businessCapacity;
    os << ", completed: " << (flight.completed ? "yes" : "no");
    os << ", tickets: [";
    for (int i = 0 ; i < flight.tickets.size() ; ++i) {
        os << flight.tickets[i];
        if (i != (flight.tickets.size() - 1)) os << ", ";
    }
    os << "])";
    return os;
}
