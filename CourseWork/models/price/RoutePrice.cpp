// routeprice.cpp

#include "routeprice.h"

RoutePrice::RoutePrice() : routeId(0), price(0.0) {}

RoutePrice::RoutePrice(int id, double price) : routeId(id), price(price) {}

int RoutePrice::getRouteId() const {
    return routeId;
}

double RoutePrice::getPrice() const {
    return price;
}

RoutePrice RoutePrice::fromSQLResult(const pqxx::row& row) {
    int id = row["route_id"].as<int>();
    double price = row["price"].as<double>();
    return RoutePrice(id, price);
}

RoutePrice RoutePrice::getTicketPrice(Database& db, int routeId) {
    pqxx::result result = db.executeQuery("SELECT route_id, price FROM RoutePrice WHERE route_id = " + std::to_string(routeId));
    if (!result.empty()) {
        return RoutePrice::fromSQLResult(result[0]);
    } else {
        throw std::runtime_error("No price found for the specified route.");
    }
}

void RoutePrice::displayTicketPrice(Database& db, int routeId) {
    try {
        RoutePrice routePrice = getTicketPrice(db, routeId);
        std::cout << "The price for the ticket on Route ID: " << routePrice.getRouteId()
                  << " is $" << routePrice.getPrice() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
