// Schedule.cpp

#include "Schedule.h"

// Implementation of the Schedule class methods

Schedule::Schedule(int scheduleId, int routeId, int stopId, const std::string& transportType, int transportId, const std::string& arrivalTime)
        : scheduleId(scheduleId), routeId(routeId), stopId(stopId), transportType(transportType), transportId(transportId), arrivalTime(arrivalTime) {}

int Schedule::getScheduleId() const {
    return scheduleId;
}

void Schedule::setScheduleId(int scheduleId) {
    this->scheduleId = scheduleId;
}

int Schedule::getRouteId() const {
    return routeId;
}

void Schedule::setRouteId(int routeId) {
    this->routeId = routeId;
}

int Schedule::getStopId() const {
    return stopId;
}

void Schedule::setStopId(int stopId) {
    this->stopId = stopId;
}

const std::string& Schedule::getTransportType() const {
    return transportType;
}

void Schedule::setTransportType(const std::string& transportType) {
    this->transportType = transportType;
}

int Schedule::getTransportId() const {
    return transportId;
}

void Schedule::setTransportId(int transportId) {
    this->transportId = transportId;
}

const std::string& Schedule::getArrivalTime() const {
    return arrivalTime;
}

void Schedule::setArrivalTime(const std::string& arrivalTime) {
    this->arrivalTime = arrivalTime;
}

std::vector<Schedule> Schedule::getScheduleForRoute(Database& db, int routeId) {
    pqxx::result R = db.executeQuery("SELECT * FROM Schedule WHERE route_id = " + std::to_string(routeId) + ";");

    std::vector<Schedule> scheduleList;
    for (auto row : R) {
        scheduleList.emplace_back(row["schedule_id"].as<int>(),
                                  row["route_id"].as<int>(),
                                  row["stop_id"].as<int>(),
                                  row["transport_type"].as<std::string>(),
                                  row["transport_id"].as<int>(),
                                  row["arrival_time"].as<std::string>());
    }
    return scheduleList;
}
