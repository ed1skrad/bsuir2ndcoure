// transportroute.cpp

#include "transportroute.h"

TransportRoute::TransportRoute(int rid, std::string ttype, int tid)
        : routeId(rid), transportType(ttype), transportId(tid) {}

int TransportRoute::getRouteId() const {
    return routeId;
}

void TransportRoute::setRouteId(int routeId) {
    this->routeId = routeId;
}

const std::string &TransportRoute::getTransportType() const {
    return transportType;
}

void TransportRoute::setTransportType(const std::string &transportType) {
    this->transportType = transportType;
}

int TransportRoute::getTransportId() const {
    return transportId;
}

void TransportRoute::setTransportId(int transportId) {
    this->transportId = transportId;
}
