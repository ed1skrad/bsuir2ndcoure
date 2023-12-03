//
// Created by atema on 02.12.2023.
//

#ifndef COURSEWORK_TRANSPORT_H
#define COURSEWORK_TRANSPORT_H
#include "../database/Database.h"
#include "PublicTransport.h"
#include <iostream>


enum EngineType
{
    PETROL,
    DIESEL,
    HYBRID,
    ELECTRIC
};

class Transport{
private:
    std::string brand;
    std::string model;
    std::string color;
    EngineType engineType;

public:
    Transport(std::string brand, std::string model, std::string color, EngineType engineType) : brand(brand), model(model), color(color), engineType(engineType) {}
    ~Transport() {}

    std::string getBrand() { return brand; }
    void setBrand(std::string brand) { this->brand = brand; }

    std::string getModel() { return model; }
    void setModel(std::string model) { this->model = model; }

    std::string getColor() { return color; }
    void setColor(std::string color) { this->color = color; }

    EngineType getEngineType() { return engineType; }
    void setEngineType(EngineType engineType) { this->engineType = engineType; }

    std::string getEngineTypeString() {
        switch (engineType) {
            case EngineType::PETROL:
                return "PETROL";
            case EngineType::DIESEL:
                return "DIESEL";
            case EngineType::HYBRID:
                return "HYBRID";
            case EngineType::ELECTRIC:
                return "ELECTRIC";
            default:
                return "Unknown";
        }
    }
    EngineType stringToEngineType(const std::string& engineTypeStr) {
        if (engineTypeStr == "PETROL") {
            return EngineType::PETROL;
        } else if (engineTypeStr == "DIESEL") {
            return EngineType::DIESEL;
        } else if (engineTypeStr == "HYBRID") {
            return EngineType::HYBRID;
        } else if (engineTypeStr == "ELECTRIC") {
            return EngineType::ELECTRIC;
        } else {
            throw std::runtime_error("Invalid engine type: " + engineTypeStr);
        }
    }

    void isIdValid(int& id, const std::string& transportName, Database* Db) {
        while (true) {
            try {
                std::cout << "Enter the " << transportName << " ID: ";
                std::cin >> id;

                std::string checkQuery = "SELECT * FROM " + transportName + " WHERE " + transportName + "_id = " + std::to_string(id);
                pqxx::result result = Db->executeQuery(checkQuery);

                if (!result.empty()) {
                    return;
                } else {
                    std::cerr << transportName << " with entered value does not exist. Try again." << std::endl;
                }
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }
    void getRoutesForTransport(Database& Db, int transportId, PublicTransport::TransportType transportType) {
        std::string transportTypeName = (transportType == TransportType::BUS) ? "BUS" : "TROLLEYBUS";
        std::cout << "Attempting to get routes for Transport: " << transportTypeName << " with ID: " << transportId << std::endl;

        try {
            pqxx::result result = Db.executeQuery("SELECT r.route_id, r.route_name "
                                                  "FROM Route r "
                                                  "JOIN (SELECT route_id FROM TransportRoute WHERE transport_id = " +
                                                  std::to_string(transportId) +
                                                  " AND transport_type = '" + transportTypeName + "') tr ON r.route_id = tr.route_id");

            if (!result.empty()) {
                for (const auto& row : result) {
                    std::cout << "Route ID: " << row[0].as<int>() << ", Route Name: " << row[1].as<std::string>() << std::endl;
                }
            } else {
                std::cout << "No routes found for the specified transport." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
};
#endif //COURSEWORK_TRANSPORT_H
