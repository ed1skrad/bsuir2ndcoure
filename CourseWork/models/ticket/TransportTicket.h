//
// Created by atema on 02.12.2023.
//

#ifndef COURSEWORK_TRANSPORTTICKET_H
#define COURSEWORK_TRANSPORTTICKET_H
#include <iostream>
#include <chrono>
#include <sstream>
#include "../PublicTransport.h"

class TransportTicket : public PublicTransport {
private:
    int ticket_id;
    int transport_id;
    int customerId;
    double price;
    std::string purchaseTime;
    TransportType transportType;

public:
    // Измененный конструктор с 6 параметрами в указанном порядке
    TransportTicket(int ticket_id, int transport_id, int customerId, double price,
                    std::string purchaseTime, TransportType transportType)
            : PublicTransport(transport_id), // Предполагаем, что transport_id используется для идентификации в базовом классе
              ticket_id(ticket_id), transport_id(transport_id), customerId(customerId),
              price(price), purchaseTime(purchaseTime), transportType(transportType) {
        // Тело конструктора
    }

    TransportTicket(int transportId, std::string brand, std::string model, std::string color, EngineType engineType,
                    int capacity, std::string from, std::string to, std::string frequency) : PublicTransport(
            transportId, brand, model, color, engineType, capacity, from, to, frequency), ticket_id(0), transport_id(0),
                                                                                             customerId(0), price(0.0),
                                                                                             purchaseTime(""),
                                                                                             transportType(
                                                                                                     TransportType::BUS) {}


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

    TransportType getTransportType() const {
        return transportType;
    }

    void setCustomerId(int customerId) {
        TransportTicket::customerId = customerId;
    }

    void settransport_id(int transport_id) {
        TransportTicket::transport_id = transport_id;
    }

    void displayTicketInfo() const {
        std::cout << "Ticket ID: " << getticket_id() << std::endl;
        std::cout << "Transport ID: " << gettransport_id() << std::endl;
        std::cout << "Customer ID: " << getCustomerId() << std::endl;
        std::cout << "Price: " << getPrice() << std::endl;
        std::cout << "Purchase Time: " << getPurchaseTime() << std::endl;
        std::cout << "Transport Type: " << (getTransportType() == TransportType::BUS ? "Bus" : "Trolleybus") << std::endl;
        std::cout << std::endl;
    }
};


#endif //COURSEWORK_TRANSPORTTICKET_H
