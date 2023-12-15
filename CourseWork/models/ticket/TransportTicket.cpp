// transportticket.cpp

#include "TransportTicket.h"

TransportTicket::TransportTicket()
        : ticketId(0), transportId(0), customerId(0), price(0.0), purchaseTime(""), transportType(TransportType::BUS) {}

TransportTicket::TransportTicket(int tId, int trId, int cId, double p, const std::string& pTime, TransportType tType)
        : ticketId(tId), transportId(trId), customerId(cId), price(p), purchaseTime(pTime), transportType(tType) {}

int TransportTicket::getTicketId() const {
    return ticketId;
}

int TransportTicket::getTransportId() const {
    return transportId;
}

int TransportTicket::getCustomerId() const {
    return customerId;
}

double TransportTicket::getPrice() const {
    return price;
}

std::string TransportTicket::getPurchaseTime() const {
    return purchaseTime;
}

TransportType TransportTicket::getTransportType() const {
    return transportType;
}

void TransportTicket::setCustomerId(int customerId) {
    this->customerId = customerId;
}

void TransportTicket::setTransportId(int transportId) {
    this->transportId = transportId;
}

void TransportTicket::setPrice(double price) {
    this->price = price;
}

void TransportTicket::displayTicketInfo() const {
    std::cout << "Ticket ID: " << getTicketId() << std::endl;
    std::cout << "Transport ID: " << getTransportId() << std::endl;
    std::cout << "Customer ID: " << getCustomerId() << std::endl;
    std::cout << "Price: " << getPrice() << std::endl;
    std::cout << "Purchase Time: " << getPurchaseTime() << std::endl;
    std::cout << "Transport Type: " << (getTransportType() == TransportType::BUS ? "Bus" : "Trolleybus") << std::endl;
    std::cout << std::endl;
}
