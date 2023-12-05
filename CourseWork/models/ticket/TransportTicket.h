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
    TransportTicket()
            : ticketId(0), transportId(0), customerId(0), price(0.0), purchaseTime(""), transportType(PublicTransport::TransportType::BUS) {}

    TransportTicket(int tId, int trId, int cId, double p, const std::string& pTime, PublicTransport::TransportType tType)
            : ticketId(tId), transportId(trId), customerId(cId), price(p), purchaseTime(pTime), transportType(tType) {}

    int getTicketId() const {
        return ticketId;
    }

    int getTransportId() const {
        return transportId;
    }

    int getCustomerId() const {
        return customerId;
    }

    double getPrice() const {
        return price;
    }

    std::string getPurchaseTime() const {
        return purchaseTime;
    }

    PublicTransport::TransportType getTransportType() const {
        return transportType;
    }

    void setCustomerId(int customerId) {
        this->customerId = customerId;
    }

    void setTransportId(int transportId) {
        this->transportId = transportId;
    }

    void setPrice(double price) {
        this->price = price;
    }

    void displayTicketInfo() const {
        std::cout << "Ticket ID: " << getTicketId() << std::endl;
        std::cout << "Transport ID: " << getTransportId() << std::endl;
        std::cout << "Customer ID: " << getCustomerId() << std::endl;
        std::cout << "Price: " << getPrice() << std::endl;
        std::cout << "Purchase Time: " << getPurchaseTime() << std::endl;
        std::cout << "Transport Type: " << (getTransportType() == PublicTransport::TransportType::BUS ? "Bus" : "Trolleybus") << std::endl;
        std::cout << std::endl;
    }
};

#endif //COURSEWORK_TRANSPORTTICKET_H
