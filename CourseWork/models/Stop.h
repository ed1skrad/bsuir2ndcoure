//
// Created by atema on 03.12.2023.
//

#ifndef COURSEWORK_STOP_H
#define COURSEWORK_STOP_H

#include <iostream>

class Stop {
private:
    int stopId;
    int trolleybusId;
    int busId;
    std::string stopName;
    std::string address;

public:
    Stop(int stopId, int trolleybusId, int busId, const std::string& stopName, const std::string& stopAddress)
            : stopId(stopId), trolleybusId(trolleybusId), busId(busId), stopName(stopName), address(stopAddress) {}

    int getStopId() const {
        return stopId;
    }

    void setStopId(int stopId) {
        Stop::stopId = stopId;
    }

    int getTrolleybusId() const {
        return trolleybusId;
    }

    void setTrolleybusId(int trolleybusId) {
        Stop::trolleybusId = trolleybusId;
    }

    int getBusId() const {
        return busId;
    }

    void setBusId(int busId) {
        Stop::busId = busId;
    }

    const std::string &getStopName() const {
        return stopName;
    }

    void setStopName(const std::string &stopName) {
        Stop::stopName = stopName;
    }

    const std::string &getAddress() const {
        return address;
    }

    void setAddress(const std::string &address) {
        Stop::address = address;
    }
};

#endif //COURSEWORK_STOP_H
