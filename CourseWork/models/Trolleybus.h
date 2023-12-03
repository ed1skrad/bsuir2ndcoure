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
    TrolleyBus(int transport_id, std::string brand, std::string model, std::string color, EngineType engineType, int capacity, std::string from, std::string to, std::string frequency, bool has_sockets)
            : PublicTransport(transport_id, brand, model, color, engineType, capacity, from, to, frequency), has_sockets(has_sockets) {}


    bool gethas_sockets() const { return has_sockets; }
    void sethas_sockets(bool has_sockets) { this->has_sockets = has_sockets; }
    void displayTrolleyBusDetails(const pqxx::result::const_iterator& row) {
        int transport_id = row["trolleybus_id"].as<int>();
        int capacity = row["capacity"].as<int>();
        std::string brand = row["brand"].as<std::string>();
        std::string model = row["model"].as<std::string>();
        std::string color = row["color"].as<std::string>();
        EngineType engineType = stringToEngineType(row["engineType"].as<std::string>());
        std::string from = row["from_location"].as<std::string>();
        std::string to = row["to_location"].as<std::string>();
        std::string frequency = row["frequency"].as<std::string>();
        bool has_sockets = row["has_sockets"].as<bool>();

        std::unique_ptr<TrolleyBus> trolleyBus = make_unique<TrolleyBus>(
                transport_id, brand, model, color,
                static_cast<EngineType>(engineType),
                capacity, from, to, frequency,
                has_sockets
        );

        std::cout << "TrolleyBus Details:" << std::endl;
        std::cout << "Transport ID: " << trolleyBus->gettransport_id() << std::endl;
        std::cout << "Brand: " << trolleyBus->getBrand() << std::endl;
        std::cout << "Model: " << trolleyBus->getModel() << std::endl;
        std::cout << "Color: " << trolleyBus->getColor() << std::endl;
        std::cout << "Engine Type: " << trolleyBus->getEngineTypeString() << std::endl;
        std::cout << "Capacity: " << trolleyBus->getCapacity() << std::endl;
        std::cout << "From: " << trolleyBus->getFrom() << std::endl;
        std::cout << "To: " << trolleyBus->getTo() << std::endl;
        std::cout << "Frequency: " << trolleyBus->getFrequency() << std::endl;
        std::cout << "Has Sockets: " << (trolleyBus->gethas_sockets() ? "Yes" : "No") << std::endl;
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
