#ifndef COURSEWORK_ADMIN_H
#define COURSEWORK_ADMIN_H

#include <iostream>
#include <pqxx/pqxx>
#include <stdexcept>
#include "../database/Database.h"
#include "../models/Taxi.h"
#include "../models/Bus.h"
#include "../models/Trolleybus.h"

class Admin {
private:
    int adminId;
    std::string username;
    std::string hashedPassword;
    Database &db;

    std::string hashPassword(const std::string &password);

public:
    Admin(Database &db, const std::string &username, const std::string &password);

    enum TransportType {
        BUS,
        TROLLEYBUS,
    };

    bool login();

    bool isValidTransportID(Database &db, int transportId, const std::string &transportType);

    bool isValidRouteID(Database &db, int routeId);

    bool isValidStopID(Database &db, int stopId);

    std::string engineTypeToString(EngineType engineType);

    bool registerAdmin(Database &db, const std::string &username, const std::string &password);

    void addBus(const std::string &brand, const std::string &model, const std::string &color, EngineType engineType,
                int capacity, bool hasContactlessPayment, int isLogged);

    void addTrolleyBus(const std::string &brand, const std::string &model, const std::string &color,
                       EngineType engineType, int capacity, bool hasSockets, int isLogged);

    void addTaxi(const std::string &brand, const std::string &model, const std::string &color,
                 const std::string &engineType, double pricePerKilometer, bool hasDriver, bool hasWiFi,
                 bool hasChildSeat, RentCarTypes rentCarTypes, int isLogged);

    void addStop(const std::string &stopName, const std::string &address, int isLogged);

    void addRoute(const std::string &routeName, int isLogged);

    void addSchedule(Database& db, int routeId, const std::string& transportType, int transportId, int isLogged);

    void setRoutePrice(Database &Db, int routeId, double price, int isLogged);

    void linkTransportToRoute(Database &Db, int route_id, TransportType transport_type, int transport_id, int isLogged);

    void linkStopToRoute(Database &db, int routeId, int stopId, int isLoggedIn);

    bool checkTransportExists(Database &Db, TransportType transportType, int transportId);

    bool adminLogin(Database &db, const std::string &username, const std::string &password);

    TransportType stringToTransportType(const std::string &typeStr);
};

#endif
