// Schedule.h

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
    Schedule() = default;  // Default constructor

    Schedule(int scheduleId, int routeId, int stopId, TransportType transportType, int transportId, const std::string& arrivalTime);

    // Getters and setters for each field
    int getScheduleId() const;
    void setScheduleId(int scheduleId);

    int getRouteId() const;
    void setRouteId(int routeId);

    int getStopId() const;
    void setStopId(int stopId);

    TransportType getTransportType() const;
    void setTransportType(TransportType transportType);

    int getTransportId() const;
    void setTransportId(int transportId);

    const std::string& getArrivalTime() const;
    void setArrivalTime(const std::string& arrivalTime);

    // Static method to get the schedule for a specific route
    static std::vector<Schedule> getScheduleForRoute(Database& db, int routeId);
    // Вызов метода
    void printStopsForRoute(Database& db, int routeId);

};

#endif // SCHEDULE_H
