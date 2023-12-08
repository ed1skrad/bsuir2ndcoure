// transportschedule.h

#ifndef COURSEWORK_TRANSPORTSCHEDULE_H
#define COURSEWORK_TRANSPORTSCHEDULE_H

#include <iostream>
#include "../PublicTransport.h"
#include "pqxx/pqxx"

class TransportSchedule {
public:
    int scheduleId;
    PublicTransport::TransportType transportType;
    int transportId;
    int routeId;
    int stopId;
    std::string arrivalTime;

    TransportSchedule();

    TransportSchedule(int schedId, PublicTransport::TransportType transType, int transId, int rtId, int stId, std::string arrTime);

    void print();

    void getScheduleForTransport(Database& Db, int transportId, PublicTransport::TransportType transportType);
};

#endif // COURSEWORK_TRANSPORTSCHEDULE_H
