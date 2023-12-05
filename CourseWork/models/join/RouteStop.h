//
// Created by atema on 05.12.2023.
//

#ifndef COURSEWORK_ROUTESTOP_H
#define COURSEWORK_ROUTESTOP_H

class RouteStop {
public:
    int route_id;
    int stop_id;

    RouteStop(int rid, int sid)
            : route_id(rid), stop_id(sid) {}


    int getRouteId() const {
        return route_id;
    }

    void setRouteId(int routeId) {
        route_id = routeId;
    }

    int getStopId() const {
        return stop_id;
    }

    void setStopId(int stopId) {
        stop_id = stopId;
    }
};


#endif //COURSEWORK_ROUTESTOP_H
