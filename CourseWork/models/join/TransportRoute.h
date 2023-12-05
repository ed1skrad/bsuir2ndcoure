//
// Created by atema on 05.12.2023.
//

#ifndef COURSEWORK_TRANSPORTROUTE_H
#define COURSEWORK_TRANSPORTROUTE_H
#include <iostream>

class TransportRoute {
public:
    int route_id;
    std::string transport_type;
    int transport_id;

    TransportRoute(int rid, std::string ttype, int tid)
            : route_id(rid), transport_type(ttype), transport_id(tid) {}

    int getRouteId() const {
        return route_id;
    }

    void setRouteId(int routeId) {
        route_id = routeId;
    }

    const std::string &getTransportType() const {
        return transport_type;
    }

    void setTransportType(const std::string &transportType) {
        transport_type = transportType;
    }

    int getTransportId() const {
        return transport_id;
    }

    void setTransportId(int transportId) {
        transport_id = transportId;
    }
};


#endif //COURSEWORK_TRANSPORTROUTE_H
