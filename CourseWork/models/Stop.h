// Stop.h

#ifndef COURSEWORK_STOP_H
#define COURSEWORK_STOP_H

#include <iostream>
#include "../database/Database.h"

class Stop {
private:
    int stopId;
    std::string stopName;
    std::string address;

public:
    Stop(int stopId, const std::string& stopName, const std::string& stopAddress);
    Stop();
    int getStopId() const;
    void setStopId(int stopId);

    const std::string &getStopName() const;
    void setStopName(const std::string &stopName);

    const std::string &getAddress() const;
    void setAddress(const std::string &address);

    static std::vector<Stop> findAllStops(Database& db);

    static std::optional<Stop> findStopById(Database& db, int stopId);
};

#endif // COURSEWORK_STOP_H
