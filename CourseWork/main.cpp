#include <string>
#include <iostream>
#include "pqxx/pqxx"
#include "database/Database.h"
#include "models/Transport.h"
#include "models/Taxi.h"
#include "models/Order.h"
#include "models/Bus.h"
#include "models/Route.h"
#include "models/schedule/TransportSchedule.h"
#include "models/ticket/TransportTicket.h"
#include "models/ticket/TicketManager.h"
#include "models/Trolleybus.h"

using namespace std;

int main() {
    try {
        Database Db;

        cout << "Choose the type of transport:" << endl;
        cout << "1. Taxi" << endl;
        cout << "2. Bus" << endl;
        cout << "3. Trolleybus" << endl;
        cout << "Enter your choice (1/2/3): ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                Taxi taxi;
                taxi.displayAllTaxis(Db);
                cout << "Do you want to order a taxi? (yes/no): ";
                string orderChoice;
                cin >> orderChoice;

                if (orderChoice == "yes" || orderChoice == "Yes") {

                    cout << "Taxi order placed successfully!" << endl;

                    string name, surname, contactInformation;

                    cout << "Enter your name: ";
                    cin >> name;

                    cout << "Enter your surname: ";
                    cin >> surname;

                    cout << "Enter your contact information: ";
                    cin >> contactInformation;

                    string addCustomerQuery = "INSERT INTO customer (name, surname, contact_information) VALUES ('" +
                                              name + "','" +
                                              surname + "','" +
                                              contactInformation + "')";
                    Db.executeQuery(addCustomerQuery);

                    pqxx::result customerIdResult = Db.executeQuery("SELECT MAX(customer_id) FROM customer");
                    int customerId = customerIdResult[0][0].as<int>();

                    int carId;
                    Orders order;

                    try {
                        taxi.isIdValid(carId, "taxi", &Db);
                    } catch (const std::runtime_error& e) {
                        std::cerr << "Error: " << e.what() << std::endl;
                    }

                    order.setCustomerId(customerId);
                    order.setCarId(carId);

                    string addOrderQuery = "INSERT INTO orders (customer_id, car_id, order_time) VALUES (" +
                                           to_string(order.getCustomerId()) + "," +
                                           to_string(order.getCarId()) + ",'" +
                                           order.getOrderTime() + "')";
                    Db.executeQuery(addOrderQuery);

                    cout << "Order placed successfully!" << endl;
                }
                break;
            }
            case 2: {
                Bus bus;
                bus.displayAllBuses(Db);
                cout << "func";
                Route route;
                route.getRoutesForTransport(Db, 2, PublicTransport::BUS);
                cout << "schedule";
                TransportSchedule transportSchedule;
                transportSchedule.getScheduleForTransport(Db, 1, PublicTransport::TransportType::BUS);
                cout << "Do you want to book a bus? (yes/no): ";
                string bookChoice;
                cin >> bookChoice;

                if (bookChoice == "yes" || bookChoice == "Yes") {
                    try {
                        cout << "Bus booked successfully!" << endl;

                        string name, surname, contactInformation;

                        cout << "Enter your name: ";
                        cin >> name;

                        cout << "Enter your surname: ";
                        cin >> surname;

                        cout << "Enter your contact information: ";
                        cin >> contactInformation;

                        string addCustomerQuery = "INSERT INTO customer (name, surname, contact_information) VALUES ('" +
                                                  name + "','" +
                                                  surname + "','" +
                                                  contactInformation + "') RETURNING customer_id";
                        pqxx::result customerIdResult = Db.executeQuery(addCustomerQuery);
                        int customerId = customerIdResult[0][0].as<int>();

                        int busId;
                        TransportTicket ticket;
                        Transport transport;
                        try {
                            transport.isIdValid(busId, "bus", &Db);
                        } catch (const std::runtime_error& e) {
                            std::cerr << "Error: " << e.what() << std::endl;
                        }


                        ticket.settransport_id(busId);
                        ticket.setCustomerId(customerId);

                        TicketManager ticketManager;
                        int ticket_id = ticketManager.insertTicket(ticket);

                        cout << "Bus booked successfully! Ticket ID: " << ticket_id << endl;
                    } catch (const std::exception& e) {
                        cerr << e.what() << std::endl;
                    }
                }
                break;
            }
            case 3: {
                TrolleyBus trolleyBus;
                trolleyBus.displayAllTrolleyBuses(Db);
                cout << "Do you want to book a trolleybus? (yes/no): ";
                string bookChoice;
                cin >> bookChoice;

                if (bookChoice == "yes" || bookChoice == "Yes") {
                    try {
                        cout << "Trolleybus booked successfully!" << endl;

                        string name, surname, contactInformation;

                        cout << "Enter your name: ";
                        cin >> name;

                        cout << "Enter your surname: ";
                        cin >> surname;

                        cout << "Enter your contact information: ";
                        cin >> contactInformation;

                        string addCustomerQuery = "INSERT INTO customer (name, surname, contact_information) VALUES ('" +
                                                  name + "','" +
                                                  surname + "','" +
                                                  contactInformation + "') RETURNING customer_id";
                        pqxx::result customerIdResult = Db.executeQuery(addCustomerQuery);
                        int customerId = customerIdResult[0][0].as<int>();

                        int trolleybusId;
                        TransportTicket ticket;
                        Transport transport;
                        try {
                            transport.isIdValid(trolleybusId, "trolleybus", &Db);
                        } catch (const std::runtime_error& e) {
                            std::cerr << "Error: " << e.what() << std::endl;
                        }

                        ticket.settransport_id(trolleybusId);
                        ticket.setCustomerId(customerId);

                        TicketManager ticketManager;
                        int ticket_id = ticketManager.insertTicket(ticket);

                        cout << "Trolleybus booked successfully! Ticket ID: " << ticket_id << endl;
                    } catch (const std::exception& e) {
                        cerr << e.what() << std::endl;
                    }
                }
                break;
            }
            default:
                cout << "Invalid choice. Exiting." << endl;
        }
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}

void displayMenu() {
    cout << "Choose the type of transport:" << endl;
    cout << "1. Taxi" << endl;
    cout << "2. Bus" << endl;
    cout << "3. Trolleybus" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice (1/2/3/0): ";
}

void handleTaxi(Database& Db) {
    // Ваш код для обработки заказа такси
}

void handleBus(Database& Db) {
    // Ваш код для обработки заказа автобуса
}

void handleTrolleyBus(Database& Db) {
    // Ваш код для обработки заказа троллейбуса
}