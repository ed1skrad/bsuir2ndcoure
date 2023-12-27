#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <vector>
#include <string>
#include "../../database/Database.h"
#include "../PublicTransport.h"

class Schedule {
private:
    int scheduleId;
    int routeId;
    int stopId;
    TransportType transportType;
    int transportId;
    std::string arrivalTime;

public:
    Schedule();

    Schedule(int scheduleId, int routeId, int stopId, TransportType transportType, int transportId, const std::string& arrivalTime);

    int getScheduleId();
    void setScheduleId(int scheduleId);

    int getRouteId();
    void setRouteId(int routeId);

    int getStopId();
    void setStopId(int stopId);

    TransportType getTransportType();
    void setTransportType(TransportType transportType);

    int getTransportId();
    void setTransportId(int transportId);

    std::string getArrivalTime();
    void setArrivalTime(std::string arrivalTime);

    static std::vector<Schedule> getScheduleForRoute(Database& db, int routeId);

    void printStopsForRoute(Database& db, int routeId);

};

#endif // SCHEDULE_H
