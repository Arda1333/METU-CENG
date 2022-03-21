#include "AirlineReservationSystem.h"

void AirlineReservationSystem::searchFlightHelper(BSTNode<Flight> *root, std::vector<Flight *> &v, const std::string &departureCity, const std::string &arrivalCity)
{
    if(root == NULL) return;

    if(root -> data.getDepartureCity() == departureCity && root -> data.getArrivalCity() == arrivalCity) v.push_back(&(root -> data));

    searchFlightHelper(root -> left, v, departureCity, arrivalCity);
    searchFlightHelper(root -> right, v, departureCity, arrivalCity);
}

void AirlineReservationSystem::addPassenger(const std::string &firstname, const std::string &lastname) {
    /* TODO */
    Passenger passenger(firstname, lastname);

    if(this -> passengers.search(passenger)) return;

    else this -> passengers.insert(passenger);
}

Passenger *AirlineReservationSystem::searchPassenger(const std::string &firstname, const std::string &lastname) {
    /* TODO */
    Passenger passenger(firstname, lastname);
    BSTNode<Passenger> *passengerP;

    passengerP = this -> passengers.search(passenger);

    if(passengerP == NULL) return NULL;

    else return &(passengerP -> data);
}

void AirlineReservationSystem::addFlight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity) {
    /* TODO */
    Flight flight(flightCode, departureTime, arrivalTime, departureCity, arrivalCity, economyCapacity, businessCapacity);

    if(this -> flights.search(flight)) return;

    else this -> flights.insert(flight);
}

std::vector<Flight *> AirlineReservationSystem::searchFlight(const std::string &departureCity, const std::string &arrivalCity) {
    /* TODO */
    std::vector<Flight *> flightRoutes;
    BSTNode<Flight> *root = flights.getRoot();

    AirlineReservationSystem::searchFlightHelper(root, flightRoutes, departureCity, arrivalCity);

    return flightRoutes;
}

void AirlineReservationSystem::issueTicket(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    /* TODO */
    Passenger passenger(firstname, lastname);
    std::string ph1 = "", ph2 = "", ph3 = "", ph4 = "";
    Flight flight(flightCode, ph1, ph2, ph3, ph4, 0, 0);
    BSTNode<Flight> *flightP;
    BSTNode<Passenger> *passengerP;

    flightP = this -> flights.search(flight);
    passengerP = this -> passengers.search(passenger);

    if(passengerP == NULL || flightP == NULL) return;

    else if((ticketType == economy && flightP -> data.getEconomyCapacity() == 0) || (ticketType == business && flightP -> data.getBusinessCapacity() == 0)) return;

    Ticket ticket(&(passengerP -> data), &(flightP -> data), ticketType);

    flightP -> data.addTicket(ticket);
}

void AirlineReservationSystem::saveFreeTicketRequest(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    /* TODO */
    Passenger passenger(firstname, lastname);
    std::string ph1 = "", ph2 = "", ph3 = "", ph4 = "";
    Flight flight(flightCode, ph1, ph2, ph3, ph4, 0, 0);
    BSTNode<Flight> *flightP;
    BSTNode<Passenger> *passengerP;

    flightP = this -> flights.search(flight);
    passengerP = this -> passengers.search(passenger);

    if(passengerP == NULL || flightP == NULL) return;

    Ticket ticket(&(passengerP -> data), &(flightP -> data), ticketType);

    freeTicketRequests.enqueue(ticket);
}

void AirlineReservationSystem::executeTheFlight(const std::string &flightCode) {
    /* TODO */
    std::string ph1 = "", ph2 = "", ph3 = "", ph4 = "";
    Flight flight(flightCode, ph1, ph2, ph3, ph4, 0, 0);
    Queue<Ticket> placeholder;
    BSTNode<Flight> *flightP;

    flightP = this -> flights.search(flight);

    if(flightP == NULL) return;

    while(!(this -> freeTicketRequests.isEmpty()))
    {
        if((this -> freeTicketRequests.peek()).getFlight() == &(flightP -> data))
        {
            if(flightP -> data.addTicket(this -> freeTicketRequests.peek())) this -> freeTicketRequests.dequeue();

            else placeholder.enqueue(this -> freeTicketRequests.dequeue());
        }

        else placeholder.enqueue(this -> freeTicketRequests.dequeue());
    }

    while(!(placeholder.isEmpty())) this -> freeTicketRequests.enqueue(placeholder.dequeue());

    flightP -> data.setCompleted(true);
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

