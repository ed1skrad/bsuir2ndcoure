// transportroute.h

#ifndef COURSEWORK_TRANSPORTROUTE_H
#define COURSEWORK_TRANSPORTROUTE_H

#include <iostream>

class TransportRoute {
public:
    int routeId;
    std::string transportType;
    int transportId;

    TransportRoute(int rid, std::string ttype, int tid);

    int getRouteId() const;

    void setRouteId(int routeId);

    const std::string &getTransportType() const;

    void setTransportType(const std::string &transportType);

    int getTransportId() const;

    void setTransportId(int transportId);
};

#endif // COURSEWORK_TRANSPORTROUTE_H
