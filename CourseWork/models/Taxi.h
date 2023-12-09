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

    int getCarId() const;
    void setCarId(int id);

    double getPricePerKil() const;
    void setPricePerKil(double pricePerKil);

    bool getHasDriver() const;
    void setHasDriver(bool hasDriver);

    bool getHasWiFi() const;
    void setHasWiFi(bool hasWiFi);

    bool getHasChildSeat() const;
    void setHasChildSeat(bool hasChildSeat);

    RentCarTypes getRentCarTypes() const;
    void setRentCarTypes(RentCarTypes rentCarTypes);

    ~Taxi();

    static RentCarTypes stringToRentCarTypes(const std::string& rentCarTypesStr);

    static void displayTaxiDetails(const pqxx::result::const_iterator& row);

    void displayAllTaxis(Database& Db);

    static void displayTaxiById(Database& Db, int taxiId);

    static void displayTaxisByBrand(Database& Db, const std::string& brand);

    static void displayTaxisByRentCarType(Database& Db, RentCarTypes rentCarType);
};

#endif // COURSEWORK_TAXI_H
