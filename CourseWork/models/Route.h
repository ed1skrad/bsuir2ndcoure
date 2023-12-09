#ifndef COURSEWORK_ROUTE_H
#define COURSEWORK_ROUTE_H

#include <iostream>
#include <vector>
#include "Stop.h"
#include "../database/Database.h"
#include "PublicTransport.h"

class Route {
private:
    int routeId;
    std::string routeName;
    std::vector<Stop> stops;

public:
    Route();
    Route(int routeId, const std::string& routeName, const std::vector<Stop>& routeStops);

    int getRouteId() const;
    const std::string& getRouteName() const;
    const std::vector<Stop>& getStops() const;

    void setRouteId(int newRouteId);
    void setRouteName(const std::string& newRouteName);
    void setStops(const std::vector<Stop>& newRouteStops);

    void getStopsForRoute(Database& db, int routeId);
    void getRoutesForTransport(Database& db, int transportId, PublicTransport::TransportType transportType);
    void displayAllRoutes(Database& db);
};

#endif //COURSEWORK_ROUTE_H
