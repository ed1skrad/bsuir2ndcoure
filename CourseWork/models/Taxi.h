//
// Created by atema on 02.12.2023.
//

#ifndef COURSEWORK_TAXI_H
#define COURSEWORK_TAXI_H
#include "Transport.h"
#include "pqxx/pqxx"
#include "../database/Database.h"

enum RentCarTypes{
    ECONOMY,
    COMFORT,
    BUSINESS
};

class Taxi : public Transport {
private:
    int carId;
    double pricePerKil;
    double rating;
    bool hasDriver;
    bool hasWiFi;
    bool hasChildSeat;
    RentCarTypes rentCarTypes;

public:
    Taxi(std::string brand, std::string model, std::string color, EngineType engineType, int carId, double pricePerKil, double rating, bool hasDriver, bool hasWiFi, bool hasChildSeat, RentCarTypes rentCarTypes)
            : Transport(brand, model, color, engineType), carId(carId), pricePerKil(pricePerKil), rating(rating), hasDriver(hasDriver), hasWiFi(hasWiFi), hasChildSeat(hasChildSeat), rentCarTypes(rentCarTypes) {}

    Taxi() : Transport("", "", "", EngineType::PETROL), carId(0), pricePerKil(0.0), rating(0.0), hasDriver(false), hasWiFi(false), hasChildSeat(false), rentCarTypes(RentCarTypes::ECONOMY) {}
    int getCarId() const { return carId; }
    void setCarId(int id) { carId = id; }

    double getPricePerKil() const { return pricePerKil; }
    void setPricePerKil(double pricePerKil) { this->pricePerKil = pricePerKil; }

    double getRating() const { return rating; }
    void setRating(double rating) { this->rating = rating; }

    bool getHasDriver() const { return hasDriver; }
    void setHasDriver(bool hasDriver) { this->hasDriver = hasDriver; }

    bool getHasWiFi() const { return hasWiFi; }
    void setHasWiFi(bool hasWiFi) { this->hasWiFi = hasWiFi; }

    bool getHasChildSeat() const { return hasChildSeat; }
    void setHasChildSeat(bool hasChildSeat) { this->hasChildSeat = hasChildSeat; }

    RentCarTypes getRentCarTypes() const { return rentCarTypes; }
    void setRentCarTypes(RentCarTypes rentCarTypes) { this->rentCarTypes = rentCarTypes; }

    ~Taxi() {
    }

    RentCarTypes stringToRentCarTypes(const std::string& rentCarTypesStr) {
        if (rentCarTypesStr == "ECONOMY") {
            return RentCarTypes::ECONOMY;
        } else if (rentCarTypesStr == "COMFORT") {
            return RentCarTypes::COMFORT;
        } else if (rentCarTypesStr == "BUSINESS") {
            return RentCarTypes::BUSINESS;
        } else {
            std::cerr << "Error: Invalid rent car type - unknown value: " << rentCarTypesStr << std::endl;
            throw std::runtime_error("Invalid rent car type: " + rentCarTypesStr);
        }
    }

    void displayTaxiDetails(const pqxx::result::const_iterator& row) {
        try {
            int carId = row[0].as<int>();
            std::string brand = row[1].as<std::string>();
            std::string model = row[2].as<std::string>();
            std::string color = row[3].as<std::string>();
            EngineType engineType = stringToEngineType(row["engineType"].as<std::string>());
            double pricePerKil = row[5].as<double>();
            bool hasDriver = row[6].as<bool>();
            bool hasWiFi = row[7].as<bool>();
            bool hasChildSeat = row[8].as<bool>();
            RentCarTypes rentCarTypes = stringToRentCarTypes(row["rent_car_type"].as<std::string>());

            // Создание объекта Taxi с использованием полученных значений
            std::unique_ptr<Taxi> taxi = std::make_unique<Taxi>(
                    brand, model, color,
                    engineType,
                    carId, pricePerKil, rating,
                    hasDriver, hasWiFi, hasChildSeat,
                    rentCarTypes
            );

            // Вывод деталей такси
            std::cout << "Taxi Details:" << std::endl;
            std::cout << "Car ID: " << taxi->getCarId() << std::endl;
            std::cout << "Brand: " << taxi->getBrand() << std::endl;
            std::cout << "Model: " << taxi->getModel() << std::endl;
            std::cout << "Color: " << taxi->getColor() << std::endl;
            std::cout << "Engine Type: " << taxi->getEngineTypeString() << std::endl;
            std::cout << "Price per Kilometer: " << taxi->getPricePerKil() << std::endl;
            std::cout << "Rating: " << taxi->getRating() << std::endl;
            std::cout << "Has Driver: " << (hasDriver ? "Yes" : "No") << std::endl;
            std::cout << "Has WiFi: " << (hasWiFi ? "Yes" : "No") << std::endl;
            std::cout << "Has Child Seat: " << (hasChildSeat ? "Yes" : "No") << std::endl;
            std::cout << "Rent Car Type: " << taxi->getRentCarTypes() << std::endl;
            std::cout << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "Error displaying taxi details: " << e.what() << std::endl;
        }
    }



    void displayAllTaxis(Database& Db) {
        try {
            pqxx::result R = Db.executeQuery("SELECT * FROM taxi");

            std::cout << "Printing query result:" << std::endl;
            for (const auto& row : R) {
                for (const auto& field : row) {
                    std::cout << field.name() << ": " << field.c_str() << "\t";
                }
                std::cout << std::endl;
            }

            for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
                displayTaxiDetails(c);
            }
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

};


#endif //COURSEWORK_TAXI_H
