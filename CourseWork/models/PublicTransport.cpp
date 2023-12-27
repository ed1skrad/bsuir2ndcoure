#include "PublicTransport.h"
#include "Customer.h"
#include "price/RoutePrice.h"
#include "ticket/TransportTicket.h"
#include "../action/InputUtils.h"

PublicTransport::PublicTransport() : transportId(0), capacity(0) {}

PublicTransport::PublicTransport(int transportId, std::string brand, std::string model, std::string color, EngineType engineType, int capacity)
        : Transport(brand, model, color, engineType), transportId(transportId), capacity(capacity) {}

PublicTransport::PublicTransport(std::string brand, std::string model, std::string color, EngineType engineType, int capacity)
        : Transport(brand, model, color, engineType), transportId(0), capacity(capacity) {}

int PublicTransport::getTransportId() {
    return transportId;
}

void PublicTransport::setTransportId(int transporId) {
    this->transportId = transporId;
}

int PublicTransport::getCapacity() {
    return capacity;
}

void PublicTransport::setCapacity(int capacity) {
    this->capacity = capacity;
}

std::string PublicTransport::getCurrentTimestampAsString() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::ctime(&currentTime);
    return ss.str();
}

int PublicTransport::insertTicket(Database& db, TransportTicket ticket) {
    try {
        std::string currentTimestamp = getCurrentTimestampAsString();

        std::string insertQuery = "INSERT INTO ticket (transport_id, customer_id, price, purchase_time, transport_type) VALUES ("
                                  + std::to_string(ticket.getTransportId()) + ", "
                                  + std::to_string(ticket.getCustomerId()) + ", "
                                  + std::to_string(ticket.getPrice()) + ", '"
                                  + currentTimestamp + "', '"
                                  + (ticket.getTransportType() == TransportType::BUS ? "BUS" : "TROLLEYBUS") + "') RETURNING ticket_id";

        pqxx::result ticketIdResult = db.executeQuery(insertQuery);
        int ticketId = ticketIdResult[0]["ticket_id"].as<int>();

        return ticketId;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw std::runtime_error("Failed to insert ticket into the database");
    }
}

void PublicTransport::bookTransport(Database& Db, PublicTransport::TransportType transportType) {
    std::string transportTypeName = (transportType == PublicTransport::BUS) ? "bus" : "trolleybus";

    try {
        Customer customer;

        customer.setName(InputUtils::getStringInput("Enter your name: "));
        customer.setSurname(InputUtils::getStringInput("Enter your surname: "));
        customer.setContactInformation(InputUtils::getStringInput("Enter your contact information: "));

        std::string addCustomerQuery = "INSERT INTO customer (name, surname, contact_information) VALUES ('" +
                                       customer.getName() + "','" +
                                       customer.getSurname() + "','" +
                                       customer.getContactInformation() + "') RETURNING customer_id";
        pqxx::result customerIdResult = Db.executeQuery(addCustomerQuery);
        customer.setCustomerId(customerIdResult[0][0].as<int>());

        int routeId = InputUtils::getPositiveInput<int>("Enter the route ID: ");

        RoutePrice routePrice;
        try {
            routePrice = RoutePrice().getTicketPrice(Db, routeId);
            std::cout << "The price for the ticket on Route ID: " << routeId
                      << " is $" << routePrice.getPrice() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return;
        }

        TransportTicket ticket;
        ticket.setTransportId(transportId);
        ticket.setCustomerId(customer.getCustomerId());
        ticket.setPrice(routePrice.getPrice());

        int ticketId = insertTicket(Db, ticket);

        std::cout << transportTypeName << " booked successfully! Ticket ID: " << ticketId << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

PublicTransport::~PublicTransport() {}
