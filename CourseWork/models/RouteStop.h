//
// Created by atema on 03.12.2023.
//

#ifndef COURSEWORK_ROUTESTOP_H
#define COURSEWORK_ROUTESTOP_H


class RouteStop {
private:
    int route_id;
    int stop_id;

public:
    RouteStop(int routeId, int stopId) : route_id(routeId), stop_id(stopId) {}

    int getRouteId() const { return route_id; }
    int getStopId() const { return stop_id; }

    void setRouteId(int routeId) { route_id = routeId; }
    void setStopId(int stopId) { stop_id = stopId; }
};

#endif //COURSEWORK_ROUTESTOP_H
