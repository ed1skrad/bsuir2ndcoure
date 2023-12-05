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
    int routeId;
    std::string routeName;
    int trolleybusId;
    int busId;
    std::vector<Stop> stops;

public:
    Route() : routeId(0), trolleybusId(0), busId(0) {}

    Route(int routeId, const std::string& routeName, int trolleybusId, int busId, const std::vector<Stop>& routeStops)
            : routeId(routeId), routeName(routeName), trolleybusId(trolleybusId), busId(busId), stops(routeStops) {}

    int getRouteId() const { return routeId; }
    const std::string& getRouteName() const { return routeName; }
    int getTrolleybusId() const { return trolleybusId; }
    int getBusId() const { return busId; }
    const std::vector<Stop>& getStops() const { return stops; }

    void setRouteId(int newRouteId) { routeId = newRouteId; }
    void setRouteName(const std::string& newRouteName) { routeName = newRouteName; }
    void setTrolleybusId(int newTrolleybusId) { trolleybusId = newTrolleybusId; }
    void setBusId(int newBusId) { busId = newBusId; }
    void setStops(const std::vector<Stop>& newRouteStops) { stops = newRouteStops; }

    void getStopsForRoute(Database& db, int routeId) {
        std::cout << "Attempting to get stops for Route ID: " << routeId << std::endl;

        // Проверка наличия маршрута в таблице Route
        pqxx::result routeCheck = db.executeQuery("SELECT route_id FROM Route WHERE route_id = " + std::to_string(routeId));
        if (routeCheck.empty()) {
            std::cout << "Route ID: " << routeId << " does not exist in the Route table." << std::endl;
            return;
        }

        // Проверка наличия связей маршрута с остановками в таблице RouteStop
        pqxx::result routeStopCheck = db.executeQuery("SELECT stop_id FROM RouteStop WHERE route_id = " + std::to_string(routeId));
        if (routeStopCheck.empty()) {
            std::cout << "No stops are linked to Route ID: " << routeId << " in the RouteStop table." << std::endl;
            return;
        }

        try {
            pqxx::result result = db.executeQuery("SELECT s.stop_name, s.address "
                                                  "FROM Stop s "
                                                  "JOIN RouteStop rs ON s.stop_id = rs.stop_id "
                                                  "WHERE rs.route_id = " + std::to_string(routeId));

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

    void getRoutesForTransport(Database& db, int transportId, PublicTransport::TransportType transportType) {
        std::string transportTypeName = (transportType == PublicTransport::TransportType::BUS) ? "BUS" : "TROLLEYBUS";
        std::cout << "Attempting to get routes for Transport: " << transportTypeName << " with ID: " << transportId << std::endl;

        try {
            pqxx::result result = db.executeQuery("SELECT r.route_id, r.route_name "
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
