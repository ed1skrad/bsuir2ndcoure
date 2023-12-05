//
// Created by atema on 03.12.2023.
//

#ifndef COURSEWORK_ROUTESTOP_H
#define COURSEWORK_ROUTESTOP_H


class RouteStop {
private:
    int routeId;
    int stopId;

public:
    RouteStop(int route, int stop) : routeId(route), stopId(stop) {}

    int getRouteId() const {
        return routeId;
    }

    int getStopId() const {
        return stopId;
    }

    void setRouteId(int route) {
        routeId = route;
    }

    void setStopId(int stop) {
        stopId = stop;
    }
};


#endif //COURSEWORK_ROUTESTOP_H
