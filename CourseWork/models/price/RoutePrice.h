//
// Created by atema on 03.12.2023.
//

#ifndef COURSEWORK_ROUTEPRICE_H
#define COURSEWORK_ROUTEPRICE_H
#include "pqxx/pqxx"
#include "../../database/Database.h"

class RoutePrice {
private:
    int route_id;
    double price;

public:
    RoutePrice(int id, double price) : route_id(id), price(price) {}

    int getRouteId() const { return route_id; }
    double getPrice() const { return price; }

    static RoutePrice fromSQLResult(const pqxx::row& row) {
        int id = row["route_id"].as<int>();
        double price = row["price"].as<double>();
        return RoutePrice(id, price);
    }

    RoutePrice getTicketPrice(Database& db, int route_id) {
        pqxx::result result = db.executeQuery("SELECT route_id, price FROM RoutePrice WHERE route_id = " + std::to_string(route_id));
        if (!result.empty()) {
            return RoutePrice::fromSQLResult(result[0]);
        } else {
            throw std::runtime_error("No price found for the specified route.");
        }
    }

    void displayTicketPrice(Database& db, int route_id) {
        try {
            RoutePrice routePrice = getTicketPrice(db, route_id);
            std::cout << "The price for the ticket on Route ID: " << routePrice.getRouteId()
                      << " is $" << routePrice.getPrice() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

};


#endif //COURSEWORK_ROUTEPRICE_H
