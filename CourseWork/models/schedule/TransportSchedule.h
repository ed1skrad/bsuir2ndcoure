//
// Created by atema on 04.12.2023.
//

#ifndef COURSEWORK_TRANSPORTSCHEDULE_H
#define COURSEWORK_TRANSPORTSCHEDULE_H
#include <iostream>
#include "../PublicTransport.h"

class TransportSchedule {
public:
    int schedule_id;
    PublicTransport::TransportType transport_type;
    int transport_id;
    int route_id;
    int stop_id;
    std::string arrival_time;
    TransportSchedule() : schedule_id(0), transport_type(PublicTransport::TransportType::BUS), transport_id(0), route_id(0), stop_id(0) {}


    TransportSchedule(int sched_id, PublicTransport::TransportType trans_type, int trans_id, int rt_id, int st_id, std::string arr_time)
            : schedule_id(sched_id), transport_type(trans_type), transport_id(trans_id), route_id(rt_id), stop_id(st_id), arrival_time(arr_time) {}

    void print() {
        std::string type = (transport_type == PublicTransport::TransportType::BUS) ? "BUS" : "TROLLEYBUS";
        std::cout << "Schedule ID: " << schedule_id
                  << ", Transport Type: " << type
                  << ", Transport ID: " << transport_id
                  << ", Route ID: " << route_id
                  << ", Stop ID: " << stop_id
                  << ", Arrival Time: " << arrival_time << std::endl;
    }

    void getScheduleForTransport(Database& Db, int transportId, PublicTransport::TransportType transportType) {
        try {
            std::string transportTypeName = (transportType == PublicTransport::TransportType::BUS) ? "BUS" : "TROLLEYBUS";
            std::string query = "SELECT ts.schedule_id, ts.transport_id, ts.route_id, ts.stop_id, ts.arrival_time "
                                "FROM TransportSchedule ts "
                                "WHERE ts.transport_id = " + std::to_string(transportId) + " AND ts.transport_type = '" + transportTypeName + "'";
            pqxx::result result = Db.executeQuery(query);

            for (const auto& row : result) {
                TransportSchedule schedule(row[0].as<int>(), transportType, row[1].as<int>(), row[2].as<int>(), row[3].as<int>(), row[4].as<std::string>());
                schedule.print();
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
};



#endif //COURSEWORK_TRANSPORTSCHEDULE_H
