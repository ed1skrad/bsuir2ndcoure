// Stop.cpp

#include "Stop.h"

Stop::Stop(int stopId, const std::string& stopName, const std::string& stopAddress)
        : stopId(stopId),  stopName(stopName), address(stopAddress) {}

Stop::Stop() : stopId(0), stopName(""), address("") {
}

int Stop::getStopId() const {
    return stopId;
}

void Stop::setStopId(int stopId) {
    Stop::stopId = stopId;
}

const std::string &Stop::getStopName() const {
    return stopName;
}

void Stop::setStopName(const std::string &stopName) {
    Stop::stopName = stopName;
}

const std::string &Stop::getAddress() const {
    return address;
}

void Stop::setAddress(const std::string &address) {
    Stop::address = address;
}

std::vector<Stop> Stop::findAllStops(Database& db) {
    std::vector<Stop> stops;
    pqxx::result R = db.executeQuery("SELECT * FROM Stop;");
    for (auto row : R) {
        stops.emplace_back(row["stop_id"].as<int>(), row["stop_name"].as<std::string>(), row["address"].as<std::string>());
        std::cout << "Stop ID: " << row["stop_id"].as<int>() << ", Name: " << row["stop_name"].as<std::string>() << ", Address: " << row["address"].as<std::string>() << std::endl;
    }
    return stops;
}

std::optional<Stop> Stop::findStopById(Database& db, int stopId) {
    pqxx::result R = db.executeQuery("SELECT * FROM Stop WHERE stop_id = " + std::to_string(stopId) + ";");
    if (!R.empty()) {
        auto row = R[0];
        std::cout << "Found Stop: " << row["stop_name"].as<std::string>() << ", Address: " << row["address"].as<std::string>() << std::endl;
        return std::optional<Stop>(Stop(row["stop_id"].as<int>(), row["stop_name"].as<std::string>(), row["address"].as<std::string>()));
    } else {
        std::cout << "No stop found with ID: " << stopId << std::endl;
        return std::nullopt;
    }
}
