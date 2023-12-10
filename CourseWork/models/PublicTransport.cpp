#include "PublicTransport.h"
#include "Customer.h"
#include "price/RoutePrice.h"
#include "ticket/TransportTicket.h"
#include "ticket/TicketManager.h"
#include "../action/InputUtils.h"

PublicTransport::PublicTransport() : transportId(0), capacity(0) {}

PublicTransport::PublicTransport(int transportId, std::string brand, std::string model, std::string color, EngineType engineType, int capacity)
        : Transport(brand, model, color, engineType), transportId(transportId), capacity(capacity) {}

PublicTransport::PublicTransport(std::string brand, std::string model, std::string color, EngineType engineType, int capacity)
        : Transport(brand, model, color, engineType), transportId(0), capacity(capacity) {}

int PublicTransport::getTransportId() {
    return transportId;
}

void PublicTransport::setTransportId(int id) {
    transportId = id;
}

int PublicTransport::getCapacity() {
    return capacity;
}

void PublicTransport::setCapacity(int capacity) {
    this->capacity = capacity;
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

        int transportId = InputUtils::getPositiveInput<int>("Enter the " + transportTypeName + " ID: ");

        std::string checkTransportQuery = "SELECT EXISTS(SELECT 1 FROM " + transportTypeName + " WHERE " + transportTypeName + "_id = " + std::to_string(transportId) + ")";
        pqxx::result transportExistsResult = Db.executeQuery(checkTransportQuery);
        bool transportExists = transportExistsResult[0][0].as<bool>();
        if (!transportExists) {
            std::cout << "No " << transportTypeName << " with ID " << transportId << " found. Please enter a valid ID." << std::endl;
            return;
        }

        TransportTicket ticket;
        ticket.setTransportId(transportId);
        ticket.setCustomerId(customer.getCustomerId());
        ticket.setPrice(routePrice.getPrice());

        TicketManager ticketManager;
        int ticketId = ticketManager.insertTicket(ticket);

        std::cout << transportTypeName << " booked successfully! Ticket ID: " << ticketId << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

PublicTransport::~PublicTransport() {}

