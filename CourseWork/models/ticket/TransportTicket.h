// transportticket.h

#ifndef COURSEWORK_TRANSPORTTICKET_H
#define COURSEWORK_TRANSPORTTICKET_H

#include <iostream>
#include <chrono>
#include <sstream>
#include "../../database/Database.h"

enum TransportType{
    BUS,
    TROLLEYBUS
};

class TransportTicket {
private:
    int ticketId;
    int transportId;
    int customerId;
    double price;
    std::string purchaseTime;
    TransportType transportType;
    Database* db;

public:
    TransportTicket();

    TransportTicket(int ticketId, int transportId, int customerId, double price, const std::string& purchaseTime, TransportType transportType);

    TransportTicket(Database* db) : db(db) {}
    int getTicketId();
    int getTransportId();
    int getCustomerId();
    double getPrice();
    std::string getPurchaseTime();
    TransportType getTransportType();

    void setCustomerId(int customerId);
    void setTransportId(int transportId);
    void setPrice(double price);

    void displayTicketInfo();
};

#endif // COURSEWORK_TRANSPORTTICKET_H
