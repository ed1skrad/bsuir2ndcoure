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
    double rating;
    bool hasDriver;
    bool hasWiFi;
    bool hasChildSeat;
    RentCarTypes rentCarTypes;

public:
    Taxi(std::string brand, std::string model, std::string color, EngineType engineType, int carId, double pricePerKil, double rating, bool hasDriver, bool hasWiFi, bool hasChildSeat, RentCarTypes rentCarTypes);

    Taxi();

    int getCarId() const;
    void setCarId(int id);

    double getPricePerKil() const;
    void setPricePerKil(double pricePerKil);

    double getRating() const;
    void setRating(double rating);

    bool getHasDriver() const;
    void setHasDriver(bool hasDriver);

    bool getHasWiFi() const;
    void setHasWiFi(bool hasWiFi);

    bool getHasChildSeat() const;
    void setHasChildSeat(bool hasChildSeat);

    RentCarTypes getRentCarTypes() const;
    void setRentCarTypes(RentCarTypes rentCarTypes);

    ~Taxi();

    RentCarTypes stringToRentCarTypes(const std::string& rentCarTypesStr);

    void displayTaxiDetails(const pqxx::result::const_iterator& row);

    void displayAllTaxis(Database& Db);
};

#endif // COURSEWORK_TAXI_H
