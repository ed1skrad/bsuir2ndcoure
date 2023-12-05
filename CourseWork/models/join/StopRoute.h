//
// Created by atema on 05.12.2023.
//

#ifndef COURSEWORK_STOPROUTE_H
#define COURSEWORK_STOPROUTE_H
#include <iostream>


class StopRoute {
public:
    int stop_id;
    int route_id;
    std::string transport_type;
    int transport_id;

    StopRoute(int sid, int rid, std::string ttype, int tid)
            : stop_id(sid), route_id(rid), transport_type(ttype), transport_id(tid) {}

    int getStopId() const {
        return stop_id;
    }

    void setStopId(int stopId) {
        stop_id = stopId;
    }

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



#endif //COURSEWORK_STOPROUTE_H
