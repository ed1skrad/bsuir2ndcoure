// transportschedule.cpp

#include "transportschedule.h"

TransportSchedule::TransportSchedule() : scheduleId(0), transportType(PublicTransport::TransportType::BUS), transportId(0), routeId(0), stopId(0) {}

TransportSchedule::TransportSchedule(int schedId, PublicTransport::TransportType transType, int transId, int rtId, int stId, std::string arrTime)
        : scheduleId(schedId), transportType(transType), transportId(transId), routeId(rtId), stopId(stId), arrivalTime(arrTime) {}

void TransportSchedule::print() {
    std::string type = (transportType == PublicTransport::TransportType::BUS) ? "BUS" : "TROLLEYBUS";
    std::cout << "Schedule ID: " << scheduleId
              << ", Transport Type: " << type
              << ", Transport ID: " << transportId
              << ", Route ID: " << routeId
              << ", Stop ID: " << stopId
              << ", Arrival Time: " << arrivalTime << std::endl;
}

void TransportSchedule::getScheduleForTransport(Database& Db, int transportId, PublicTransport::TransportType transportType) {
    try {
        std::string transportTypeName = (transportType == PublicTransport::TransportType::BUS) ? "BUS" : "TROLLEYBUS";
        std::string query = "SELECT ts.schedule_id, ts.transport_id, ts.route_id, ts.stop_id, ts.arrival_time "
                            "FROM TransportSchedule ts "
                            "WHERE ts.transport_id = " + std::to_string(transportId) + " AND ts.transport_type = '" + transportTypeName + "'";
        pqxx::result result = Db.executeQuery(query);

        if (result.empty()) {
            std::cout << "Bus with ID " << transportId << " not found." << std::endl;
        } else {
            for (const auto& row : result) {
                TransportSchedule schedule(row[0].as<int>(), transportType, row[1].as<int>(), row[2].as<int>(), row[3].as<int>(), row[4].as<std::string>());
                schedule.print();
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
