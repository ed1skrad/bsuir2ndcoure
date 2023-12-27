#include "TransportTicket.h"

TransportTicket::TransportTicket()
        : ticketId(0), transportId(0), customerId(0), price(0.0), purchaseTime(""), transportType(TransportType::BUS) {}

TransportTicket::TransportTicket(int ticketId, int transportId, int customerId, double price, const std::string& purchaseTime, TransportType transportType)
        : ticketId(ticketId), transportId(transportId), customerId(customerId), price(price), purchaseTime(purchaseTime), transportType(transportType) {}

int TransportTicket::getTicketId() {
    return ticketId;
}

int TransportTicket::getTransportId(){
    return transportId;
}

int TransportTicket::getCustomerId(){
    return customerId;
}

double TransportTicket::getPrice(){
    return price;
}

std::string TransportTicket::getPurchaseTime(){
    return purchaseTime;
}

TransportType TransportTicket::getTransportType(){
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

void TransportTicket::displayTicketInfo() {
    std::cout << "Ticket ID: " << getTicketId() << std::endl;
    std::cout << "Transport ID: " << getTransportId() << std::endl;
    std::cout << "Customer ID: " << getCustomerId() << std::endl;
    std::cout << "Price: " << getPrice() << std::endl;
    std::cout << "Purchase Time: " << getPurchaseTime() << std::endl;
    std::cout << "Transport Type: " << (getTransportType() == TransportType::BUS ? "Bus" : "Trolleybus") << std::endl;
    std::cout << std::endl;
}
