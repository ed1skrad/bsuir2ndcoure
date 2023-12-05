#ifndef COURSEWORK_ROUTESTOP_H
#define COURSEWORK_ROUTESTOP_H

class RouteStop {
public:
    int routeId;
    int stopId;

    RouteStop(int rid, int sid)
            : routeId(rid), stopId(sid) {}


    int getRouteId() const {
        return routeId;
    }

    void setRouteId(int routeId) {
        routeId = routeId;
    }

    int getStopId() const {
        return stopId;
    }

    void setStopId(int stopId) {
        stopId = stopId;
    }
};

#endif //COURSEWORK_ROUTESTOP_H
