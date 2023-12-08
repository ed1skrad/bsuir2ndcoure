// TrolleyBus.h

#ifndef COURSEWORK_TROLLEYBUS_H
#define COURSEWORK_TROLLEYBUS_H

#include "PublicTransport.h"
#include "pqxx/pqxx"
#include "../database/Database.h"
#include "Transport.h"

class TrolleyBus : public PublicTransport {
private:
    bool hasSockets;

public:
    TrolleyBus();
    TrolleyBus(int transportId, std::string brand, std::string model, std::string color, EngineType engineType, int capacity, bool hasSockets);
    TrolleyBus(const std::string& brand, const std::string& model, const std::string& color, EngineType engineType, int capacity, bool hasSockets);

    bool getHasSockets() const;
    void setHasSockets(bool hasSockets);

    void displayTrolleyBusDetails(const pqxx::result::const_iterator& row);
    void displayAllTrolleyBuses(Database& db);
};

#endif // COURSEWORK_TROLLEYBUS_H
