#include <string>
#include <iostream>
#include "pqxx/pqxx"
#include "models/Customer.h"
#include "database/Database.h"
#include "models/Taxi.h"
#include "models/Order.h"

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
                        isIdValid(carId, "taxi", &Db);
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
                // Block for displaying bus details
                displayAllBuses(Db);
                cout << "func";
                getRoutesForTransport(Db, 2, BUS);
                cout<<"WEEEEEEWEEEEEEE";
                getStopsForRoute(Db, 2);
                displayTicketPrice(Db, 1);
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

                        try {
                            isIdValid(busId, "bus", &Db);
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
                displayAllTrolleyBuses(Db);
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

                        try {
                            isIdValid(trolleybusId, "trolleybus", &Db);
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

