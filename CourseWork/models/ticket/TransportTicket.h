//
// Created by atema on 02.12.2023.
//

#ifndef COURSEWORK_TRANSPORTTICKET_H
#define COURSEWORK_TRANSPORTTICKET_H
#include <iostream>
#include <chrono>
#include <sstream>
#include "../PublicTransport.h"

class TransportTicket{
private:
    int ticket_id;
    int transport_id;
    int customerId;
    double price;
    std::string purchaseTime;
    PublicTransport::TransportType transportType;

public:
    TransportTicket()
            : ticket_id(0), transport_id(0), customerId(0), price(0.0), purchaseTime(""), transportType(PublicTransport::TransportType::BUS) {}

    TransportTicket(int t_id, int tr_id, int c_id, double p, const std::string& pTime, PublicTransport::TransportType tType)
            : ticket_id(t_id), transport_id(tr_id), customerId(c_id), price(p), purchaseTime(pTime), transportType(tType) {}


    int getticket_id() const {
        return ticket_id;
    }

    int gettransport_id() const {
        return transport_id;
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
        TransportTicket::customerId = customerId;
    }

    void settransport_id(int transport_id) {
        TransportTicket::transport_id = transport_id;
    }

    void setPrice(double price) {
        TransportTicket::price = price;
    }

    void displayTicketInfo() const {
        std::cout << "Ticket ID: " << getticket_id() << std::endl;
        std::cout << "Transport ID: " << gettransport_id() << std::endl;
        std::cout << "Customer ID: " << getCustomerId() << std::endl;
        std::cout << "Price: " << getPrice() << std::endl;
        std::cout << "Purchase Time: " << getPurchaseTime() << std::endl;
        std::cout << "Transport Type: " << (getTransportType() == PublicTransport::TransportType::BUS ? "Bus" : "Trolleybus") << std::endl;
        std::cout << std::endl;
    }
};


#endif //COURSEWORK_TRANSPORTTICKET_H
