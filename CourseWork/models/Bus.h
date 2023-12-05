#ifndef COURSEWORK_BUS_H
#define COURSEWORK_BUS_H

#include <iostream>
#include <string>
#include "PublicTransport.h"
#include "pqxx/pqxx"

class Bus : public PublicTransport {
private:
    bool hasContactlessPayment;

public:
    Bus() : PublicTransport(0, "", "", "", EngineType::DIESEL, 0), hasContactlessPayment(false) {}

    Bus(const std::string& brand, const std::string& model, const std::string& color, EngineType engineType, int capacity, bool hasContactlessPayment)
            : PublicTransport(brand, model, color, engineType, capacity), hasContactlessPayment(hasContactlessPayment) {}

    Bus(int transportId, std::string brand, std::string model, std::string color, EngineType engineType, int capacity, bool hasContactlessPayment)
            : PublicTransport(transportId, brand, model, color, engineType, capacity), hasContactlessPayment(hasContactlessPayment) {}

    bool isHasContactlessPayment() const {
        return hasContactlessPayment;
    }

    void setHasContactlessPayment(bool hasContactlessPayment) {
        hasContactlessPayment = hasContactlessPayment;
    }

    void displayBusDetails(const pqxx::result::const_iterator& row) {
        int transportId = row["bus_id"].as<int>();
        int capacity = row["capacity"].as<int>();
        std::string brand = row["brand"].as<std::string>();
        std::string model = row["model"].as<std::string>();
        std::string color = row["color"].as<std::string>();
        EngineType engineType = stringToEngineType(row["engineType"].as<std::string>());
        bool hasContactlessPayment = row["has_contactless_payment"].as<bool>();

        std::unique_ptr<Bus> bus = std::make_unique<Bus>(
                transportId, brand, model, color,
                static_cast<EngineType>(engineType),
                capacity,
                hasContactlessPayment
        );

        std::cout << "Bus Details:" << std::endl;
        std::cout << "Transport ID: " << bus->getTransportId() << std::endl;
        std::cout << "Brand: " << bus->getBrand() << std::endl;
        std::cout << "Model: " << bus->getModel() << std::endl;
        std::cout << "Color: " << bus->getColor() << std::endl;
        std::cout << "Engine Type: " << bus->getEngineTypeString() << std::endl;
        std::cout << "Capacity: " << bus->getCapacity() << std::endl;
        std::cout << "Has Contactless Payment: " << (bus->isHasContactlessPayment() ? "Yes" : "No") << std::endl;
        std::cout << std::endl;
    }

    void displayAllBuses(Database& Db) {
        try {
            pqxx::result busResult = Db.executeQuery("SELECT * FROM bus");
            std::cout << "Displaying Bus Details:" << std::endl;
            for (const auto& row : busResult) {
                displayBusDetails(row);
            }
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
};

#endif //COURSEWORK_BUS_H
