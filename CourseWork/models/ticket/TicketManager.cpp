// ticketmanager.cpp

#include "ticketmanager.h"

TicketManager::TicketManager() : C("dbname=CourseWorkDb user=postgres password=aboba hostaddr=127.0.0.1 port=5432") {
    if (C.is_open()) {
        std::cout << "Opened database successfully: " << C.dbname() << std::endl;
    } else {
        std::cout << "Can't open database" << std::endl;
        throw std::runtime_error("Failed to open database");
    }
}

TicketManager::~TicketManager() {
}

pqxx::result TicketManager::executeQuery(const std::string& query) {
    pqxx::nontransaction N(C);
    return N.exec(query);
}

std::string TicketManager::getCurrentTimestampAsString() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::ctime(&currentTime);
    return ss.str();
}

int TicketManager::insertTicket(const TransportTicket& ticket) {
    try {
        pqxx::work W(C);

        std::string currentTimestamp = getCurrentTimestampAsString();

        std::string insertQuery = "INSERT INTO ticket (transport_id, customer_id, price, purchase_time, transport_type) VALUES ("
                                  + std::to_string(ticket.getTransportId()) + ", "
                                  + std::to_string(ticket.getCustomerId()) + ", "
                                  + std::to_string(ticket.getPrice()) + ", '"
                                  + currentTimestamp + "', '"
                                  + (ticket.getTransportType() == PublicTransport::TransportType::BUS ? "BUS" : "TROLLEYBUS") + "') RETURNING ticket_id";

        pqxx::result ticketIdResult = W.exec(insertQuery);
        int ticketId = ticketIdResult[0]["ticket_id"].as<int>();

        W.commit();

        return ticketId;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw std::runtime_error("Failed to insert ticket into the database");
    }
}
/*
void TicketManager::displayAllTickets() {
    try {
        pqxx::result R = executeQuery("SELECT * FROM ticket");

        for (const auto& row : R) {
            TicketManager::displayTicketDetails(row);
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw std::runtime_error("Failed to display tickets from the database");
    }
}
 */

