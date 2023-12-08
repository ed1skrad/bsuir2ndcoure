// stoproute.h

#ifndef COURSEWORK_STOPROUTE_H
#define COURSEWORK_STOPROUTE_H

#include <iostream>

class StopRoute {
public:
    int stopId;
    int routeId;
    std::string transportType;
    int transportId;

    StopRoute(int sid, int rid, std::string ttype, int tid);

    int getStopId() const;

    void setStopId(int stopId);

    int getRouteId() const;

    void setRouteId(int routeId);

    const std::string &getTransportType() const;

    void setTransportType(const std::string &transportType);

    int getTransportId() const;

    void setTransportId(int transportId);
};

#endif // COURSEWORK_STOPROUTE_H
