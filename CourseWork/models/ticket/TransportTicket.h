// transportticket.h

#ifndef COURSEWORK_TRANSPORTTICKET_H
#define COURSEWORK_TRANSPORTTICKET_H

#include <iostream>
#include <chrono>
#include <sstream>
#include "../PublicTransport.h"

class TransportTicket {
private:
    int ticketId;
    int transportId;
    int customerId;
    double price;
    std::string purchaseTime;
    PublicTransport::TransportType transportType;

public:
    TransportTicket();

    TransportTicket(int tId, int trId, int cId, double p, const std::string& pTime, PublicTransport::TransportType tType);

    int getTicketId() const;
    int getTransportId() const;
    int getCustomerId() const;
    double getPrice() const;
    std::string getPurchaseTime() const;
    PublicTransport::TransportType getTransportType() const;

    void setCustomerId(int customerId);
    void setTransportId(int transportId);
    void setPrice(double price);

    void displayTicketInfo() const;
};

#endif // COURSEWORK_TRANSPORTTICKET_H
