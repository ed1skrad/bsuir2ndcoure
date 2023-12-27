#include "Schedule.h"  // Include your own header file first
#include <iostream>

Schedule::Schedule(int scheduleId, int routeId, int stopId, TransportType transportType, int transportId, const std::string& arrivalTime)
        : scheduleId(scheduleId), routeId(routeId), stopId(stopId), transportType(transportType), transportId(transportId), arrivalTime(arrivalTime) {}

Schedule::Schedule()
        : scheduleId(0), routeId(0), stopId(0), transportType(TransportType::BUS), transportId(0), arrivalTime("") {}


int Schedule::getScheduleId() {
    return scheduleId;
}

void Schedule::setScheduleId(int scheduleId) {
    this->scheduleId = scheduleId;
}

int Schedule::getRouteId() {
    return routeId;
}

void Schedule::setRouteId(int routeId) {
    this->routeId = routeId;
}

int Schedule::getStopId() {
    return stopId;
}

void Schedule::setStopId(int stopId) {
    this->stopId = stopId;
}

TransportType Schedule::getTransportType() {
    return transportType;
}

void Schedule::setTransportType(TransportType transportType) {
    this->transportType = transportType;
}

int Schedule::getTransportId() {
    return transportId;
}

void Schedule::setTransportId(int transportId) {
    this->transportId = transportId;
}

std::string Schedule::getArrivalTime() {
    return arrivalTime;
}

void Schedule::setArrivalTime(std::string arrivalTime) {
    this->arrivalTime = arrivalTime;
}


/*
 * Функция emplace_back - это член класса std::vector в C++. Она используется для добавления нового элемента в конец вектора
 */
std::vector<Schedule> Schedule::getScheduleForRoute(Database& db, int routeId) {
    pqxx::result R = db.executeQuery("SELECT * FROM Schedule WHERE route_id = " + std::to_string(routeId) + ";");

    std::vector<Schedule> scheduleList;
    for (auto row: R) {
        scheduleList.emplace_back(row["schedule_id"].as<int>(),
                                  row["route_id"].as<int>(),
                                  row["stop_id"].as<int>(),
                                  static_cast<TransportType>(row["transport_type"].as<int>()),
                                  row["transport_id"].as<int>(),
                                  row["arrival_time"].as<std::string>());
    }
    return scheduleList;
}


//INNER JOIN
/*
 * JOIN StopRoute sr ON s.stop_id = sr.stop_id:
 * Этот JOIN объединяет таблицы Stop и StopRoute по столбцу stop_id.
 * Это означает, что для каждой остановки в таблице Stop будут выбраны
 * все соответствующие записи из таблицы StopRoute, где stop_id совпадает.

JOIN Schedule sch ON sr.route_id = sch.route_id AND sr.stop_id = sch.stop_id:
 Этот JOIN объединяет результат предыдущего JOIN с таблицей Schedule.
 Записи объединяются, когда route_id и stop_id в таблице StopRoute совпадают
 с route_id и stop_id в таблице Schedule.
 */
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
