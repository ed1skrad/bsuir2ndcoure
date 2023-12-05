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
    Bus() : PublicTransport(0, "", "", "", EngineType::DIESEL, 0), has_contactless_payment(false) {}


    Bus(const std::string& brand, const std::string& model, const std::string& color, EngineType engineType, int capacity, bool has_contactless_payment)
            : PublicTransport(brand, model, color, engineType, capacity), has_contactless_payment(has_contactless_payment) {}

    Bus(int transport_id, std::string brand, std::string model, std::string color, EngineType engineType, int capacity, bool has_contactless_payment)
            : PublicTransport(transport_id, brand, model, color, engineType, capacity), has_contactless_payment(has_contactless_payment) {}


    bool isHasContactlessPayment() const {
        return has_contactless_payment;
    }

    void setHasContactlessPayment(bool hasContactlessPayment) {
        has_contactless_payment = hasContactlessPayment;
    }



    void displayBusDetails(const pqxx::result::const_iterator& row) {
        int transport_id = row["bus_id"].as<int>();
        int capacity = row["capacity"].as<int>();
        std::string brand = row["brand"].as<std::string>();
        std::string model = row["model"].as<std::string>();
        std::string color = row["color"].as<std::string>();
        EngineType engineType = stringToEngineType(row["engineType"].as<std::string>());
        bool has_contactless_payment = row["has_contactless_payment"].as<bool>();

        std::unique_ptr<Bus> bus = make_unique<Bus>(
                transport_id, brand, model, color,
                static_cast<EngineType>(engineType),
                capacity,
                has_contactless_payment
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
