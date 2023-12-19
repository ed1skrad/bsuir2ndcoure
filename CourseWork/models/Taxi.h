// Taxi.h

#ifndef COURSEWORK_TAXI_H
#define COURSEWORK_TAXI_H

#include "Transport.h"
#include "pqxx/pqxx"
#include "../database/Database.h"

enum RentCarTypes {
    ECONOMY,
    COMFORT,
    BUSINESS
};

class Taxi : public Transport {
private:
    int carId;
    double pricePerKil;
    bool hasDriver;
    bool hasWiFi;
    bool hasChildSeat;
    RentCarTypes rentCarTypes;

public:
    Taxi(std::string brand, std::string model, std::string color, EngineType engineType, int carId, double pricePerKil, bool hasDriver, bool hasWiFi, bool hasChildSeat, RentCarTypes rentCarTypes);

    Taxi();

    int getCarId();
    void setCarId(int carId);

    double getPricePerKil();
    void setPricePerKil(double pricePerKil);

    bool getHasDriver();
    void setHasDriver(bool hasDriver);

    bool getHasWiFi();
    void setHasWiFi(bool hasWiFi);

    bool getHasChildSeat();
    void setHasChildSeat(bool hasChildSeat);

    RentCarTypes getRentCarTypes();
    void setRentCarTypes(RentCarTypes rentCarTypes);

    ~Taxi();

    static RentCarTypes stringToRentCarTypes(const std::string& rentCarTypesStr);

    static void displayTaxiDetails(const pqxx::result::const_iterator& row);

    void displayAllTaxis(Database& Db);

    static void displayTaxiById(Database& Db, int taxiId);

    static void displayTaxisByBrand(Database& Db, const std::string& brand);

    static void displayTaxisByRentCarType(Database& Db, RentCarTypes rentCarType);

    std::string to_string(const int value);

    void orderTaxi(Database& Db);
};

#endif // COURSEWORK_TAXI_H
