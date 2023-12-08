// routestop.h

#ifndef COURSEWORK_ROUTESTOP_H
#define COURSEWORK_ROUTESTOP_H

class RouteStop {
public:
    int routeId;
    int stopId;

    RouteStop(int rid, int sid);

    int getRouteId() const;

    void setRouteId(int routeId);

    int getStopId() const;

    void setStopId(int stopId);
};

#endif // COURSEWORK_ROUTESTOP_H
