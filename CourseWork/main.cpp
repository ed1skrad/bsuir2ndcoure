#include <string>
#include <iostream>
#include "pqxx/pqxx"

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
};

class PublicTransport : public Transport{
private:
    int capacity;
    std::string from;
    std::string to;
    std::string frequency;

public:
    PublicTransport(std::string brand, std::string model, std::string color, EngineType engineType, int capacity, std::string from, std::string to, std::string frequency)
            : Transport(brand, model, color, engineType), capacity(capacity), from(from), to(to), frequency(frequency) {}
    ~PublicTransport() {}

    int getCapacity() { return capacity; }
    void setCapacity(int capacity) { this->capacity = capacity; }

    std::string getFrom() { return from; }
    void setFrom(std::string from) { this->from = from; }

    std::string getTo() { return to; }
    void setTo(std::string to) { this->to = to; }

    std::string getFrequency() { return frequency; }
    void setFrequency(std::string frequency) { this->frequency = frequency; }
};

class Bus : public PublicTransport{
private:
    bool hasContactlessPayment;

public:
    Bus(std::string brand, std::string model, std::string color, EngineType engineType, int capacity, std::string from, std::string to, std::string frequency, bool hasContactlessPayment)
            : PublicTransport(brand, model, color, engineType, capacity, from, to, frequency), hasContactlessPayment(hasContactlessPayment) {}

    bool getHasContactlessPayment() { return hasContactlessPayment; }
    void setHasContactlessPayment(bool hasContactlessPayment) { this->hasContactlessPayment = hasContactlessPayment; }
};

class TrolleyBus : public PublicTransport{
private:
    bool hasSockets;

public:
    TrolleyBus(std::string brand, std::string model, std::string color, EngineType engineType, int capacity, std::string from, std::string to, std::string frequency, bool hasSockets)
            : PublicTransport(brand, model, color, engineType, capacity, from, to, frequency), hasSockets(hasSockets) {}

    bool getHasSockets() { return hasSockets; }
    void setHasSockets(bool hasSockets) { this->hasSockets = hasSockets; }
};

enum RentCarTypes{
    ECONOMY,
    COMFORT,
    BUSINESS
};

class Taxi : public Transport{
private:
    double pricePerKil;
    double rating;
    bool hasDriver;
    bool hasWiFi;
    bool hasChildSeat;
    RentCarTypes rentCarTypes;

public:
    Taxi(std::string brand, std::string model, std::string color, EngineType engineType, double pricePerKil, double rating, bool hasDriver, bool hasWiFi, bool hasChildSeat, RentCarTypes rentCarTypes)
            : Transport(brand, model, color, engineType), pricePerKil(pricePerKil), rating(rating), hasDriver(hasDriver), hasWiFi(hasWiFi), hasChildSeat(hasChildSeat), rentCarTypes(rentCarTypes) {}

    double getPricePerKil() { return pricePerKil; }
    void setPricePerKil(double pricePerKil) { this->pricePerKil = pricePerKil; }

    double getRating() { return rating; }
    void setRating(double rating) { this->rating = rating; }

    bool getHasDriver() { return hasDriver; }
    void setHasDriver(bool hasDriver) { this->hasDriver = hasDriver; }

    bool getHasWiFi() { return hasWiFi; }
    void setHasWiFi(bool hasWiFi) { this->hasWiFi = hasWiFi; }

    bool getHasChildSeat() { return hasChildSeat; }
    void setHasChildSeat(bool hasChildSeat) { this->hasChildSeat = hasChildSeat; }

    RentCarTypes getRentCarTypes() { return rentCarTypes; }
    void setRentCarTypes(RentCarTypes rentCarTypes) { this->rentCarTypes = rentCarTypes; }
};

class CarSharing : public Transport{
private:
    double pricePerMinute;
    bool hasInsurance;
    bool hasADS;

public:
    CarSharing(std::string brand, std::string model, std::string color, EngineType engineType, double pricePerMinute, bool hasInsurance, bool hasADS)
            : Transport(brand, model, color, engineType), pricePerMinute(pricePerMinute), hasInsurance(hasInsurance), hasADS(hasADS) {}

    double getPricePerMinute() { return pricePerMinute; }
    void setPricePerMinute(double pricePerMinute) { this->pricePerMinute = pricePerMinute; }

    bool getHasInsurance() { return hasInsurance; }
    void setHasInsurance(bool hasInsurance) { this->hasInsurance = hasInsurance; }

    bool getHasADS() { return hasADS; }
    void setHasADS(bool hasADS) { this->hasADS = hasADS; }
};


int main() {
    try {
        pqxx::connection conn("your_connection_string_here");

        int choice;
        while (true) {
            std::cout << "Выберите тип транспорта:" << std::endl;
            std::cout << "1 - Bus" << std::endl;
            std::cout << "2 - Trolleybus" << std::endl;
            std::cout << "3 - Taxi" << std::endl;
            std::cout << "4 - Car Sharing" << std::endl;
            std::cout << "0 - Выход" << std::endl;
            std::cout << "Ваш выбор: ";
            std::cin >> choice;

            if (choice == 0) {
                break;
            }

            pqxx::work txn(conn);
            pqxx::result result;

            switch (choice) {
                case 1:
                    result = txn.exec("SELECT * FROM bus");
                    break;
                case 2:
                    result = txn.exec("SELECT * FROM trolleybus");
                    break;
                case 3:
                    result = txn.exec("SELECT * FROM taxi");
                    break;
                case 4:
                    result = txn.exec("SELECT * FROM car_sharing");
                    break;
                default:
                    std::cout << "Incorrect input." << std::endl;
                    continue;
            }

            txn.commit();

            for (pqxx::result::size_type i = 0; i < result.size(); ++i) {
                std::string brand = result[i]["brand"].as<std::string>();
                std::string model = result[i]["model"].as<std::string>();
                std::string color = result[i]["color"].as<std::string>();
                EngineType engineType = static_cast<EngineType>(result[i]["engineType"].as<int>());

                if (choice == 1) {
                    int capacity = result[i]["capacity"].as<int>();
                    std::string from = result[i]["from_location"].as<std::string>();
                    std::string to = result[i]["to_location"].as<std::string>();
                    std::string frequency = result[i]["frequency"].as<std::string>();
                    bool hasContactlessPayment = result[i]["has_contactless_payment"].as<bool>();

                    Bus bus(brand, model, color, engineType, capacity, from, to, frequency, hasContactlessPayment);

                }
                else if (choice == 2) {
                    int capacity = result[i]["capacity"].as<int>();
                    std::string from = result[i]["from_location"].as<std::string>();
                    std::string to = result[i]["to_location"].as<std::string>();
                    std::string frequency = result[i]["frequency"].as<std::string>();
                    bool hasSockets = result[i]["has_sockets"].as<bool>();

                    TrolleyBus trolleybus(brand, model, color, engineType, capacity, from, to, frequency, hasSockets);
                }
                else if (choice == 3) {
                    double pricePerKil = result[i]["price_per_kil"].as<double>();
                    double rating = result[i]["rating"].as<double>();
                    bool hasDriver = result[i]["has_driver"].as<bool>();
                    bool hasWiFi = result[i]["has_wifi"].as<bool>();
                    bool hasChildSeat = result[i]["has_child_seat"].as<bool>();
                    RentCarTypes rentCarType = static_cast<RentCarTypes>(result[i]["rent_car_type"].as<int>());

                    Taxi taxi(brand, model, color, engineType, pricePerKil, rating, hasDriver, hasWiFi, hasChildSeat, rentCarType);

                }
                else if (choice == 4) {
                    double pricePerMinute = result[i]["price_per_minute"].as<double>();
                    bool hasInsurance = result[i]["has_insurance"].as<bool>();
                    bool hasADS = result[i]["has_ads"].as<bool>();

                    CarSharing carSharing(brand, model, color, engineType, pricePerMinute, hasInsurance, hasADS);

                }
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
