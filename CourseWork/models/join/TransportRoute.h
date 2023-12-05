#ifndef COURSEWORK_TRANSPORTROUTE_H
#define COURSEWORK_TRANSPORTROUTE_H

#include <iostream>

class TransportRoute {
public:
    int routeId;
    std::string transportType;
    int transportId;

    TransportRoute(int rid, std::string ttype, int tid)
            : routeId(rid), transportType(ttype), transportId(tid) {}

    int getRouteId() const {
        return routeId;
    }

    void setRouteId(int routeId) {
        routeId = routeId;
    }

    const std::string &getTransportType() const {
        return transportType;
    }

    void setTransportType(const std::string &transportType) {
        TransportRoute::transportType = transportType;
    }

    int getTransportId() const {
        return transportId;
    }

    void setTransportId(int transportId) {
        transportId = transportId;
    }
};

#endif //COURSEWORK_TRANSPORTROUTE_H
