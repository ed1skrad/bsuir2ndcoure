// Stop.h

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
    Stop(int stopId, int trolleybusId, int busId, const std::string& stopName, const std::string& stopAddress);

    int getStopId() const;
    void setStopId(int stopId);

    int getTrolleybusId() const;
    void setTrolleybusId(int trolleybusId);

    int getBusId() const;
    void setBusId(int busId);

    const std::string &getStopName() const;
    void setStopName(const std::string &stopName);

    const std::string &getAddress() const;
    void setAddress(const std::string &address);
};

#endif // COURSEWORK_STOP_H
