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
    Bus();

    Bus(const std::string& brand, const std::string& model, const std::string& color, EngineType engineType, int capacity, bool hasContactlessPayment);

    Bus(int transportId, std::string brand, std::string model, std::string color, EngineType engineType, int capacity, bool hasContactlessPayment);

    bool isHasContactlessPayment();

    void setHasContactlessPayment(bool hasContactlessPayment);

    void displayBusDetails(const pqxx::result::const_iterator& row);

    void displayAllBuses(Database& Db);
};

#endif // COURSEWORK_BUS_H
