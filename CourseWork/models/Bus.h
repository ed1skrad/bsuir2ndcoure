//
// Created by atema on 02.12.2023.
//

#ifndef COURSEWORK_BUS_H
#define COURSEWORK_BUS_H
#include <iostream>
#include <string>
#include "PublicTransport.h"
#include "pqxx/pqxx"

class Bus : public PublicTransport {
private:

    bool has_contactless_payment;

public:
    Bus(int transport_id, std::string brand, std::string model, std::string color, EngineType engineType, int capacity, std::string from, std::string to, std::string frequency, bool has_contactless_payment)
            : PublicTransport(transport_id, brand, model, color, engineType, capacity, from, to, frequency), has_contactless_payment(has_contactless_payment) {}


    bool gethas_contactless_payment() const { return has_contactless_payment; }
    void sethas_contactless_payment(bool has_contactless_payment) { this->has_contactless_payment = has_contactless_payment; }

    void displayBusDetails(const pqxx::result::const_iterator& row) {
        int transport_id = row["bus_id"].as<int>();
        int capacity = row["capacity"].as<int>();
        std::string brand = row["brand"].as<std::string>();
        std::string model = row["model"].as<std::string>();
        std::string color = row["color"].as<std::string>();
        EngineType engineType = stringToEngineType(row["engineType"].as<std::string>());
        std::string from = row["from_location"].as<std::string>();
        std::string to = row["to_location"].as<std::string>();
        std::string frequency = row["frequency"].as<std::string>();
        bool has_contactless_payment = row["has_contactless_payment"].as<bool>();

        std::unique_ptr<Bus> bus = make_unique<Bus>(
                transport_id, brand, model, color,
                static_cast<EngineType>(engineType),
                capacity, from, to, frequency,
                has_contactless_payment
        );

        std::cout << "Bus Details:" << std::endl;
        std::cout << "Transport ID: " << bus->gettransport_id() << std::endl;
        std::cout << "Brand: " << bus->getBrand() << std::endl;
        std::cout << "Model: " << bus->getModel() << std::endl;
        std::cout << "Color: " << bus->getColor() << std::endl;
        std::cout << "Engine Type: " << bus->getEngineTypeString() << std::endl;
        std::cout << "Capacity: " << bus->getCapacity() << std::endl;
        std::cout << "From: " << bus->getFrom() << std::endl;
        std::cout << "To: " << bus->getTo() << std::endl;
        std::cout << "Frequency: " << bus->getFrequency() << std::endl;
        std::cout << "Has Contactless Payment: " << (bus->gethas_contactless_payment() ? "Yes" : "No") << std::endl;
        std::cout << std::endl;
    }


};



#endif //COURSEWORK_BUS_H
