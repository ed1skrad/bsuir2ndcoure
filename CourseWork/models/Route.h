#ifndef COURSEWORK_ROUTE_H
#define COURSEWORK_ROUTE_H

#include <iostream>
#include "Stop.h"
#include "../database/Database.h"
#include "PublicTransport.h"
#include "../contrainer/VectorOverload.h"
#include "../exception/Exception.h"

class Route {
private:
    int routeId;
    std::string routeName;
    MyVector<Stop> stops;

public:
    Route();
    Route(int routeId, const std::string& routeName, const MyVector<Stop>& routeStops);

    int getRouteId();
    std::string getRouteName();
    MyVector<Stop> getStops();

    void setRouteId(int routeId);
    void setRouteName(std::string routeName);
    void setStops(MyVector<Stop> stops);

    void getStopsForRoute(Database& db, int routeId);
    void getRoutesForTransport(Database& db, int transportId, PublicTransport::TransportType transportType);
    void displayAllRoutes(Database& db);
    void findRouteById(Database& db, int routeId);
    void findRouteByName(Database& db, const std::string& routeName);
};

#endif //COURSEWORK_ROUTE_H
