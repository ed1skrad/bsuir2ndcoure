//
// Created by atema on 03.12.2023.
//

#ifndef COURSEWORK_TICKETMANAGER_H
#define COURSEWORK_TICKETMANAGER_H
#include <iostream>
#include <chrono>
#include <sstream>
#include "../PublicTransport.h"
#include "pqxx/pqxx"
#include "TransportTicket.h"

class TicketManager {
private:
    pqxx::connection C;

public:
    TicketManager() : C("dbname=CourseWorkDb user=postgres password=aboba hostaddr=127.0.0.1 port=5432") {
        if (C.is_open()) {
            std::cout << "Opened database successfully: " << C.dbname() << std::endl;
        } else {
            std::cout << "Can't open database" << std::endl;
            throw std::runtime_error("Failed to open database");
        }
    }

    ~TicketManager() {
    }

    pqxx::result executeQuery(const std::string& query) {
        pqxx::nontransaction N(C);
        return N.exec(query);
    }

    std::string getCurrentTimestampAsString() {
        auto now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::ctime(&currentTime);
        return ss.str();
    }

    int insertTicket(const TransportTicket& ticket) {
        try {
            pqxx::work W(C);

            std::string currentTimestamp = getCurrentTimestampAsString();

            std::string insertQuery = "INSERT INTO ticket (transport_id, customer_id, price, purchase_time, transport_type) VALUES ("
                                      + std::to_string(ticket.gettransport_id()) + ", "
                                      + std::to_string(ticket.getCustomerId()) + ", "
                                      + std::to_string(ticket.getPrice()) + ", '"
                                      + currentTimestamp + "', '"
                                      + (ticket.getTransportType() == PublicTransport::TransportType::BUS ? "BUS" : "TROLLEYBUS") + "') RETURNING ticket_id";

            pqxx::result ticket_idResult = W.exec(insertQuery);
            int ticket_id = ticket_idResult[0]["ticket_id"].as<int>();

            W.commit();

            return ticket_id;
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            throw std::runtime_error("Failed to insert ticket into the database");
        }
    }


    void displayAllTickets() {
        try {
            pqxx::result R = executeQuery("SELECT * FROM ticket");

            for (const auto& row : R) {
                displayTicketDetails(row);
            }
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            throw std::runtime_error("Failed to display tickets from the database");
        }
    }

private:
    void displayTicketDetails(const pqxx::result::const_iterator& row) {
        int ticket_id = row["ticket_id"].as<int>();
        int transport_id = row["transport_id"].as<int>();
        int customerId = row["customer_id"].as<int>();
        double price = row["price"].as<double>();
        std::string purchaseTime = row["purchase_time"].as<std::string>();
        std::string transportTypeStr = row["transport_type"].as<std::string>();

        PublicTransport::TransportType transportType;
        if (transportTypeStr == "BUS") {
            transportType = PublicTransport::TransportType::BUS;
        } else if (transportTypeStr == "TROLLEYBUS") {
            transportType = PublicTransport::TransportType::TROLLEYBUS;
        } else {
            throw std::runtime_error("Invalid transport type in the database");
        }

        TransportTicket ticket(ticket_id, transport_id, customerId, price, purchaseTime, transportType);
        ticket.displayTicketInfo();
    }
};



#endif //COURSEWORK_TICKETMANAGER_H
