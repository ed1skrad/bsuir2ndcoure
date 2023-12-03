//
// Created by atema on 03.12.2023.
//

#ifndef COURSEWORK_STOP_H
#define COURSEWORK_STOP_H
#include <iostream>

class Stop {
private:
    int stop_id;
    int trolleybus_id;
    int bus_id;
    std::string stop_name;
    std::string address;

public:
    Stop(int stopId, int trolleybusId, int busId, const std::string& stopName, const std::string& stopAddress)
            : stop_id(stopId), trolleybus_id(trolleybusId), bus_id(busId), stop_name(stopName), address(stopAddress) {}

    int getStopId() const { return stop_id; }
    int getTrolleybusId() const { return trolleybus_id; }
    int getBusId() const { return bus_id; }
    const std::string& getStopName() const { return stop_name; }
    const std::string& getAddress() const { return address; }

    void setStopId(int stopId) { stop_id = stopId; }
    void setTrolleybusId(int trolleybusId) { trolleybus_id = trolleybusId; }
    void setBusId(int busId) { bus_id = busId; }
    void setStopName(const std::string& stopName) { stop_name = stopName; }
    void setAddress(const std::string& stopAddress) { address = stopAddress; }
};


#endif //COURSEWORK_STOP_H
