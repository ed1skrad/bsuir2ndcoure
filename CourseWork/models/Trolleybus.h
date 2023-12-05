//
// Created by atema on 02.12.2023.
//

#ifndef COURSEWORK_TROLLEYBUS_H
#define COURSEWORK_TROLLEYBUS_H
#include "PublicTransport.h"
#include "pqxx/pqxx"
#include "../database/Database.h"
#include "Transport.h"

class TrolleyBus : public PublicTransport {
private:
    bool has_sockets;

public:
    TrolleyBus() : PublicTransport(), has_sockets(false) {}


    TrolleyBus(int transport_id, std::string brand, std::string model, std::string color, EngineType engineType, int capacity, bool has_sockets)
            : PublicTransport(transport_id, brand, model, color, engineType, capacity), has_sockets(has_sockets) {}


    TrolleyBus(const std::string& brand, const std::string& model, const std::string& color, EngineType engineType, int capacity, bool has_sockets)
            : PublicTransport(brand, model, color, engineType, capacity), has_sockets(has_sockets) {}

    bool isHasSockets() const {
        return has_sockets;
    }

    void setHasSockets(bool hasSockets) {
        has_sockets = hasSockets;
    }

    void displayTrolleyBusDetails(const pqxx::result::const_iterator& row) {
        int transport_id = row["trolleybus_id"].as<int>();
        int capacity = row["capacity"].as<int>();
        std::string brand = row["brand"].as<std::string>();
        std::string model = row["model"].as<std::string>();
        std::string color = row["color"].as<std::string>();
        EngineType engineType = stringToEngineType(row["engineType"].as<std::string>());
        bool has_sockets = row["has_sockets"].as<bool>();

        std::unique_ptr<TrolleyBus> trolleyBus = make_unique<TrolleyBus>(
                transport_id, brand, model, color,
                static_cast<EngineType>(engineType),
                capacity,
                has_sockets
        );

        std::cout << "TrolleyBus Details:" << std::endl;
        std::cout << "Transport ID: " << trolleyBus->getTransportId() << std::endl;
        std::cout << "Brand: " << trolleyBus->getBrand() << std::endl;
        std::cout << "Model: " << trolleyBus->getModel() << std::endl;
        std::cout << "Color: " << trolleyBus->getColor() << std::endl;
        std::cout << "Engine Type: " << trolleyBus->getEngineTypeString() << std::endl;
        std::cout << "Capacity: " << trolleyBus->getCapacity() << std::endl;
        std::cout << "Has Sockets: " << (trolleyBus->isHasSockets() ? "Yes" : "No") << std::endl;
        std::cout << std::endl;
    }

    void displayAllTrolleyBuses(Database& Db) {
        try {
            pqxx::result trolleyBusResult = Db.executeQuery("SELECT * FROM trolleybus");
            std::cout << "Displaying TrolleyBus Details:" << std::endl;
            for (const auto& row : trolleyBusResult) {
                displayTrolleyBusDetails(row);
            }
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
};



#endif //COURSEWORK_TROLLEYBUS_H
