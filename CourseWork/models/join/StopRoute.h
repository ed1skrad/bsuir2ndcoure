#ifndef COURSEWORK_STOPROUTE_H
#define COURSEWORK_STOPROUTE_H

#include <iostream>

class StopRoute {
public:
    int stopId;
    int routeId;
    std::string transportType;
    int transportId;

    StopRoute(int sid, int rid, std::string ttype, int tid)
            : stopId(sid), routeId(rid), transportType(ttype), transportId(tid) {}

    int getStopId() const {
        return stopId;
    }

    void setStopId(int stopId) {
        stopId = stopId;
    }

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
        StopRoute::transportType = transportType;
    }

    int getTransportId() const {
        return transportId;
    }

    void setTransportId(int transportId) {
        transportId = transportId;
    }
};

#endif //COURSEWORK_STOPROUTE_H
