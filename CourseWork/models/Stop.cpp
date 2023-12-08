// Stop.cpp

#include "Stop.h"

Stop::Stop(int stopId, int trolleybusId, int busId, const std::string& stopName, const std::string& stopAddress)
        : stopId(stopId), trolleybusId(trolleybusId), busId(busId), stopName(stopName), address(stopAddress) {}

int Stop::getStopId() const {
    return stopId;
}

void Stop::setStopId(int stopId) {
    Stop::stopId = stopId;
}

int Stop::getTrolleybusId() const {
    return trolleybusId;
}

void Stop::setTrolleybusId(int trolleybusId) {
    Stop::trolleybusId = trolleybusId;
}

int Stop::getBusId() const {
    return busId;
}

void Stop::setBusId(int busId) {
    Stop::busId = busId;
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
