// stoproute.cpp

#include "stoproute.h"

StopRoute::StopRoute(int sid, int rid, std::string ttype, int tid)
        : stopId(sid), routeId(rid), transportType(ttype), transportId(tid) {}

int StopRoute::getStopId() const {
    return stopId;
}

void StopRoute::setStopId(int stopId) {
    this->stopId = stopId;
}

int StopRoute::getRouteId() const {
    return routeId;
}

void StopRoute::setRouteId(int routeId) {
    this->routeId = routeId;
}

const std::string &StopRoute::getTransportType() const {
    return transportType;
}

void StopRoute::setTransportType(const std::string &transportType) {
    this->transportType = transportType;
}

int StopRoute::getTransportId() const {
    return transportId;
}

void StopRoute::setTransportId(int transportId) {
    this->transportId = transportId;
}
