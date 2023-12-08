#ifndef COURSEWORK_TICKETMANAGER_H
#define COURSEWORK_TICKETMANAGER_H

#include <iostream>
#include <chrono>
#include <sstream>
#include "../PublicTransport.h"
#include "pqxx/pqxx"
#include "TransportTicket.h"

class TicketManager {
private:
    pqxx::connection C;

public:
    TicketManager();

    ~TicketManager();

    pqxx::result executeQuery(const std::string& query);

    std::string getCurrentTimestampAsString();

    int insertTicket(const TransportTicket& ticket);

    //void displayAllTickets();

    //void displayTicketDetails(const pqxx::result::const_iterator& row);
};

#endif // COURSEWORK_TICKETMANAGER_H
