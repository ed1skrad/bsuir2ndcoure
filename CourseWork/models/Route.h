//
// Created by atema on 03.12.2023.
//

#ifndef COURSEWORK_ROUTE_H
#define COURSEWORK_ROUTE_H
#include <iostream>
#include <vector>
#include "Stop.h"
#include "pqxx/pqxx"
#include "../database/Database.h"
#include "PublicTransport.h"

class Route {
private:
    int route_id;
    std::string route_name;
    int trolleybus_id;
    int bus_id;
    std::vector<Stop> stops;

public:
    Route() : route_id(0), trolleybus_id(0), bus_id(0) {}

    Route(int routeId, const std::string& routeName, int trolleybusId, int busId, const std::vector<Stop>& routeStops)
            : route_id(routeId), route_name(routeName), trolleybus_id(trolleybusId), bus_id(busId), stops(routeStops) {}

    int getRouteId() const { return route_id; }
    const std::string& getRouteName() const { return route_name; }
    int getTrolleybusId() const { return trolleybus_id; }
    int getBusId() const { return bus_id; }
    const std::vector<Stop>& getStops() const { return stops; }

    void setRouteId(int routeId) { route_id = routeId; }
    void setRouteName(const std::string& routeName) { route_name = routeName; }
    void setTrolleybusId(int trolleybusId) { trolleybus_id = trolleybusId; }
    void setBusId(int busId) { bus_id = busId; }
    void setStops(const std::vector<Stop>& routeStops) { stops = routeStops; }

    void getStopsForRoute(Database& db, int route_id) {
        std::cout << "Attempting to get stops for Route ID: " << route_id << std::endl;

        // Проверка наличия маршрута в таблице Route
        pqxx::result routeCheck = db.executeQuery("SELECT route_id FROM Route WHERE route_id = " + std::to_string(route_id));
        if (routeCheck.empty()) {
            std::cout << "Route ID: " << route_id << " does not exist in the Route table." << std::endl;
            return;
        }

        // Проверка наличия связей маршрута с остановками в таблице RouteStop
        pqxx::result routeStopCheck = db.executeQuery("SELECT stop_id FROM RouteStop WHERE route_id = " + std::to_string(route_id));
        if (routeStopCheck.empty()) {
            std::cout << "No stops are linked to Route ID: " << route_id << " in the RouteStop table." << std::endl;
            return;
        }

        try {
            pqxx::result result = db.executeQuery("SELECT s.stop_name, s.address "
                                                  "FROM Stop s "
                                                  "JOIN RouteStop rs ON s.stop_id = rs.stop_id "
                                                  "WHERE rs.route_id = " + std::to_string(route_id));

            if (!result.empty()) {
                for (const auto& row : result) {
                    std::cout << "Stop Name: " << row[0].as<std::string>() << ", Address: " << row[1].as<std::string>() << std::endl;
                }
            } else {
                std::cout << "No stops found for the specified route." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void getRoutesForTransport(Database& Db, int transportId, PublicTransport::TransportType transportType) {
        std::string transportTypeName = (transportType == PublicTransport::TransportType::BUS) ? "BUS" : "TROLLEYBUS";
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


#endif //COURSEWORK_ROUTE_H
