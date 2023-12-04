#include <string>
#include <iostream>
#include "pqxx/pqxx"
#include "database/Database.h"
#include "models/Taxi.h"
#include "models/Order.h"
#include "models/Bus.h"
#include "models/Route.h"
#include "models/schedule/TransportSchedule.h"
#include "models/ticket/TransportTicket.h"
#include "models/ticket/TicketManager.h"
#include "models/Trolleybus.h"
#include "models/price/RoutePrice.h"
#include "models/Customer.h"
#include "admin/Admin.h"

using namespace std;

void displayMenu() {
    cout << "Choose the type of transport:" << endl;
    cout << "1. Taxi" << endl;
    cout << "2. Bus" << endl;
    cout << "3. Trolleybus" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice (1/2/3/0): ";
}

void bookTransport(Database& Db, PublicTransport::TransportType transportType) {
    string transportTypeName = (transportType == PublicTransport::BUS) ? "bus" : "trolleybus";
    cout << "Do you want to book a " << transportTypeName << "? (yes/no): ";
    string bookChoice;
    cin >> bookChoice;

    if (bookChoice == "yes" || bookChoice == "Yes") {
        try {
            Customer customer; // Создание объекта класса Customer

            cout << "Enter your name: ";
            string name;
            cin >> name;
            customer.setName(name); // Установка имени через setter

            cout << "Enter your surname: ";
            string surname;
            cin >> surname;
            customer.setSurname(surname); // Установка фамилии через setter

            cout << "Enter your contact information: ";
            string contactInformation;
            cin >> contactInformation;
            customer.setContactInformation(contactInformation); // Установка контактной информации через setter

            // Добавление информации о клиенте в базу данных и получение customer_id
            string addCustomerQuery = "INSERT INTO customer (name, surname, contact_information) VALUES ('" +
                                      customer.getName() + "','" +
                                      customer.getSurname() + "','" +
                                      customer.getContactInformation() + "') RETURNING customer_id";
            pqxx::result customerIdResult = Db.executeQuery(addCustomerQuery);
            customer.setCustomerId(customerIdResult[0][0].as<int>());

            cout << "Enter the route ID: ";
            int routeId;
            cin >> routeId;

            // Получение цены маршрута
            RoutePrice routePrice;
            try {
                routePrice = RoutePrice().getTicketPrice(Db, routeId);
                cout << "The price for the ticket on Route ID: " << routeId
                     << " is $" << routePrice.getPrice() << std::endl;
            } catch (const std::exception& e) {
                cerr << "Error: " << e.what() << endl;
                return;
            }

            cout << "Enter the " << transportTypeName << " ID: ";
            int transportId;
            cin >> transportId;

            string checkTransportQuery = "SELECT EXISTS(SELECT 1 FROM " + transportTypeName + " WHERE " + transportTypeName + "_id = " + std::to_string(transportId) + ")";
            pqxx::result transportExistsResult = Db.executeQuery(checkTransportQuery);
            bool transportExists = transportExistsResult[0][0].as<bool>();
            if (!transportExists) {
                cout << "No " << transportTypeName << " with ID " << transportId << " found. Please enter a valid ID." << endl;
                return;
            }

            TransportTicket ticket;
            ticket.settransport_id(transportId);
            ticket.setCustomerId(customer.getCustomerId());
            ticket.setPrice(routePrice.getPrice()); // Установка цены билета

            TicketManager ticketManager;
            int ticket_id = ticketManager.insertTicket(ticket);

            cout << transportTypeName << " booked successfully! Ticket ID: " << ticket_id << endl;
        } catch (const std::exception& e) {
            cerr << e.what() << endl;
        }
    }
}

void orderTaxi(Database& Db) {
    cout << "Do you want to order a taxi? (yes/no): ";
    string orderChoice;
    cin >> orderChoice;

    if (orderChoice == "yes" || orderChoice == "Yes") {
        cout << "Enter the car ID: ";
        int carId;
        cin >> carId;

        // Проверка наличия такси с таким идентификатором в базе данных
        pqxx::result taxiExistsResult = Db.executeQuery("SELECT EXISTS(SELECT 1 FROM taxi WHERE taxi_id = " + to_string(carId) + ")");
        bool taxiExists = taxiExistsResult[0][0].as<bool>();
        if (!taxiExists) {
            cout << "Taxi with ID " << carId << " does not exist. Please enter a valid taxi ID." << endl;
            return;
        }

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

        Orders order;
        order.setCustomerId(customerId);
        order.setCarId(carId);

        string addOrderQuery = "INSERT INTO orders (customer_id, car_id, order_time) VALUES (" +
                               to_string(customerId) + "," +
                               to_string(carId) + ",'" +
                               order.getOrderTime() + "')";
        Db.executeQuery(addOrderQuery);

        cout << "Order placed successfully! Your taxi ID is " << carId << "." << endl;
    }
}

void handleTaxiSelect(Database& Db){
    cout << "Choose an action:" << endl;
    cout << "1. View all taxis" << endl;
    cout << "2. Call taxi" << endl;
    int actionChoice;
    cin >> actionChoice;

    switch (actionChoice) {
        case 1: {
            Taxi taxi;
            taxi.displayAllTaxis(Db);
            break;
        }
        case 2: {
            orderTaxi(Db);
            break;
        }
    }
}


void handleBusSelect(Database& Db) {
    cout << "Choose an action:" << endl;
    cout << "1. View all buses" << endl;
    cout << "2. View all routes" << endl;
    cout << "3. View schedule" << endl;
    cout << "4. Get ticket price for a route" << endl;
    cout << "5. Book a ticket" << endl;
    cout << "Enter your choice (1/2/3/4/5): ";

    int actionChoice;
    cin >> actionChoice;

    switch (actionChoice) {
        case 1: {
            Bus bus;
            bus.displayAllBuses(Db);
            break;
        }
        case 2: {
            cout << "Enter bus id to find linked routes:";
            int busId;
            cin >> busId;
            Route route;
            route.getRoutesForTransport(Db, busId, PublicTransport::BUS);
            break;
        }
        case 3: {
            cout << "Enter bus id to find schedule:";
            int busId;
            cin >> busId;
            TransportSchedule transportSchedule;
            transportSchedule.getScheduleForTransport(Db, busId, PublicTransport::TransportType::BUS);
            break;
        }
        case 4: {
            int routeId;
            cout << "Enter the route ID to get the ticket price: ";
            cin >> routeId;
            RoutePrice routePrice;
            routePrice.displayTicketPrice(Db, routeId);
            break;
        }
        case 5: {
            bookTransport(Db,PublicTransport::BUS);
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
}

void handleTrolleyBusSelect(Database& Db) {
    cout << "Choose an action:" << endl;
    cout << "1. View all trolleybuses" << endl;
    cout << "2. View all routes" << endl;
    cout << "3. View schedule" << endl;
    cout << "4. Get ticket price for a route" << endl;
    cout << "5. Book a ticket" << endl;
    cout << "Enter your choice (1/2/3/4/5): ";

    int actionChoice;
    cin >> actionChoice;

    switch (actionChoice) {
        case 1: {
            TrolleyBus trolleyBus;
            trolleyBus.displayAllTrolleyBuses(Db);
            break;
        }
        case 2: {
            cout << "Enter trolleybus id to find linked routes:";
            int trolleybusId;
            cin >> trolleybusId;
            Route route;
            route.getRoutesForTransport(Db, trolleybusId, PublicTransport::TROLLEYBUS);
            break;
        }
        case 3: {
            cout << "Enter trolleybus id to find schedule:";
            int trolleybusId;
            cin >> trolleybusId;
            TransportSchedule transportSchedule;
            transportSchedule.getScheduleForTransport(Db, trolleybusId, PublicTransport::TransportType::TROLLEYBUS);
            break;
        }
        case 4: {
            int routeId;
            cout << "Enter the route ID to get the ticket price: ";
            cin >> routeId;
            RoutePrice routePrice;
            routePrice.displayTicketPrice(Db, routeId);
            break;
        }
        case 5: {
            bookTransport(Db, PublicTransport::TROLLEYBUS);
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
    }
}

void handleAdminActions(Database& Db) {
    // Создаем объект Admin
    Admin admin(Db, "admin_username", "admin_password");
    std::cout << "1. Login\n2. Register\nChoose an option: ";
    int choice;
    std::cin >> choice;
    std::string username, password;
    switch (choice) {
        case 1: // Логин
            std::cout << "Enter username: ";
            std::cin >> username;
            std::cout << "Enter password: ";
            std::cin >> password;
            if (admin.adminLogin(Db, username, password)) {
                std::cout << "Logged in successfully." << std::endl;
                // Дальнейшие действия администратора
            } else {
                std::cout << "Login failed." << std::endl;
            }
            break;
        case 2: // Регистрация
            std::cout << "Enter username for registration: ";
            std::cin >> username;
            std::cout << "Enter password for registration: ";
            std::cin >> password;
            if (admin.registerAdmin(Db, username, password)) {
                std::cout << "Registered successfully." << std::endl;
            } else {
                std::cout << "Registration failed." << std::endl;
            }
            break;
        default:
            std::cout << "Invalid option selected." << std::endl;
            break;
    }
}

int main() {
    Database Db;
    bool isRunning = true;
    while (isRunning) {
        displayMenu();
        int actionChoice;
        std::cin >> actionChoice;
        switch (actionChoice) {
            case 1:
                handleTaxiSelect(Db);
                break;
            case 2:
                handleBusSelect(Db);
                break;
            case 3:
                handleTrolleyBusSelect(Db);
                break;
            case 4:
                handleAdminActions(Db);
                break;
            case 0:
                isRunning = false;
                std::cout << "Exiting the program." << std::endl;
                break;
            default:
                std::cout << "Invalid option selected. Please try again." << std::endl;
                break;
        }
    }
    return 0;
}


