// Schedule.cpp

#include "Schedule.h"  // Include your own header file first
#include <iostream>

Schedule::Schedule(int scheduleId, int routeId, int stopId, TransportType transportType, int transportId, const std::string& arrivalTime)
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

TransportType Schedule::getTransportType() const {
    return transportType;
}

void Schedule::setTransportType(TransportType transportType) {
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
    for (auto row: R) {
        scheduleList.emplace_back(row["schedule_id"].as<int>(),
                                  row["route_id"].as<int>(),
                                  row["stop_id"].as<int>(),
                                  static_cast<TransportType>(row["transport_type"].as<int>()), // Assuming transport_type is stored as an integer in the database
                                  row["transport_id"].as<int>(),
                                  row["arrival_time"].as<std::string>());
    }
    return scheduleList;
}

void Schedule::printStopsForRoute(Database& db, int routeId) {
    pqxx::result R = db.executeQuery("SELECT s.stop_id, s.stop_name, s.address, sch.arrival_time "
                                     "FROM Stop s "
                                     "JOIN StopRoute sr ON s.stop_id = sr.stop_id "
                                     "JOIN Schedule sch ON sr.route_id = sch.route_id AND sr.stop_id = sch.stop_id "
                                     "WHERE sr.route_id = " + std::to_string(routeId) + " "
                                                                                        "ORDER BY sr.stop_id;");

    std::cout << "Stops for route ID " << routeId << ":" << std::endl;
    for (auto row : R) {
        std::cout << "Stop ID: " << row["stop_id"].as<int>() << ", Stop Name: " << row["stop_name"].as<std::string>()
                  << ", Address: " << row["address"].as<std::string>() << ", Arrival Time: " << row["arrival_time"].as<std::string>() << std::endl;
    }
}
