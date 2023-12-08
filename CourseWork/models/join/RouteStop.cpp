// routestop.cpp

#include "routestop.h"

RouteStop::RouteStop(int rid, int sid)
        : routeId(rid), stopId(sid) {}

int RouteStop::getRouteId() const {
    return routeId;
}

void RouteStop::setRouteId(int routeId) {
    this->routeId = routeId;
}

int RouteStop::getStopId() const {
    return stopId;
}

void RouteStop::setStopId(int stopId) {
    this->stopId = stopId;
}
