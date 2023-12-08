// routeprice.h

#ifndef COURSEWORK_ROUTEPRICE_H
#define COURSEWORK_ROUTEPRICE_H

#include "pqxx/pqxx"
#include "../../database/Database.h"

class RoutePrice {
private:
    int routeId;
    double price;

public:
    RoutePrice();

    RoutePrice(int id, double price);

    int getRouteId() const;
    double getPrice() const;

    static RoutePrice fromSQLResult(const pqxx::row& row);

    RoutePrice getTicketPrice(Database& db, int routeId);

    void displayTicketPrice(Database& db, int routeId);
};

#endif // COURSEWORK_ROUTEPRICE_H
