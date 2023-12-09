#include <string>
#include <iostream>
#include "pqxx/pqxx"
#include "../database/Database.h"
#include "../models/Taxi.h"
#include "../models/Order.h"
#include "../models/Bus.h"
#include "../models/Route.h"
#include "../models/ticket/TransportTicket.h"
#include "../models/ticket/TicketManager.h"
#include "../models/Trolleybus.h"
#include "../models/price/RoutePrice.h"
#include "../models/Customer.h"
#include "../admin/Admin.h"
#include "../models/schedule/Schedule.h"

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
            Customer customer;

            cout << "Enter your name: ";
            string name;
            cin >> name;
            customer.setName(name);

            cout << "Enter your surname: ";
            string surname;
            cin >> surname;
            customer.setSurname(surname);

            cout << "Enter your contact information: ";
            string contactInformation;
            cin >> contactInformation;
            customer.setContactInformation(contactInformation);

            string addCustomerQuery = "INSERT INTO customer (name, surname, contact_information) VALUES ('" +
                                      customer.getName() + "','" +
                                      customer.getSurname() + "','" +
                                      customer.getContactInformation() + "') RETURNING customer_id";
            pqxx::result customerIdResult = Db.executeQuery(addCustomerQuery);
            customer.setCustomerId(customerIdResult[0][0].as<int>());

            cout << "Enter the route ID: ";
            int routeId;
            cin >> routeId;

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
            ticket.setTransportId(transportId);
            ticket.setCustomerId(customer.getCustomerId());
            ticket.setPrice(routePrice.getPrice());

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

        Order order;
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

void handleTaxiSelect(Database& Db) {
    Taxi taxi;
    cout << "Choose an action:" << endl;
    cout << "1. View all taxis" << endl;
    cout << "2. Call taxi" << endl;
    cout << "3. Display taxi by ID" << endl;
    cout << "4. Display taxis by brand" << endl;
    cout << "5. Display taxis by RentCarType" << endl;

    int actionChoice;
    cin >> actionChoice;

    switch (actionChoice) {
        case 1: {
            taxi.displayAllTaxis(Db);
            break;
        }
        case 2: {
            orderTaxi(Db);
            break;
        }
        case 3: {
            int taxiId;
            cout << "Enter taxiId:";
            cin >> taxiId;
            taxi.displayTaxiById(Db, taxiId);
            break;
        }
        case 4: {
            string brand;
            cout << "Enter brand:";
            cin >> brand;
            taxi.displayTaxisByBrand(Db, brand);
            break;
        }
        case 5: {
            cout << "Choose RentCarType:" << endl;
            cout << "1. Economy" << endl;
            cout << "2. Comfort" << endl;
            cout << "3. Business" << endl;

            int rentCarTypeChoice;
            cin >> rentCarTypeChoice;

            RentCarTypes rentCarType;

            switch (rentCarTypeChoice) {
                case 1:
                    rentCarType = ECONOMY;
                    break;
                case 2:
                    rentCarType = COMFORT;
                    break;
                case 3:
                    rentCarType = BUSINESS;
                    break;
                default:
                    cout << "Invalid choice" << endl;
                    return;
            }

            taxi.displayTaxisByRentCarType(Db, rentCarType);
            break;
        }
        default: {
            cout << "Invalid choice" << endl;
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
    cout << "6. Stop case" << endl;
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
            route.displayAllRoutes(Db);
            break;
        }
        case 3: {
            cout << "Enter route id:";
            int busId;
            cin >> busId;
            Schedule transportSchedule;
            transportSchedule.printStopsForRoute(Db, busId);
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
        case 6:{
            Stop stop;
            stop.findAllStops(Db);
            cout << "Stop id:";
            int stopId;
            cin >> stopId;
            stop.findStopById(Db, stopId);
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
            Schedule transportSchedule;
            //transportSchedule.getScheduleForTransport(Db, trolleybusId, PublicTransport::TransportType::TROLLEYBUS);
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

void createAndAddBus(Database& Db, int isLogged) {
    Admin admin(Db, "admin_username", "admin_password");
    std::string brand, model, color;
    EngineType engineType;
    int capacity;
    bool has_contactless_payment;

    std::cout << "Enter bus brand: ";
    std::cin >> brand;
    std::cout << "Enter bus model: ";
    std::cin >> model;
    std::cout << "Enter bus color: ";
    std::cin >> color;
    std::cout << "Enter engine type (1 for DIESEL, 2 for PETROL, etc.): ";
    int engineTypeInput;
    std::cin >> engineTypeInput;
    engineType = static_cast<EngineType>(engineTypeInput);
    std::cout << "Enter bus capacity: ";
    std::cin >> capacity;
    std::cout << "Does the bus have contactless payment? (1 for YES, 0 for NO): ";
    int hasContactlessPaymentInput;
    std::cin >> hasContactlessPaymentInput;
    has_contactless_payment = hasContactlessPaymentInput != 0;

    admin.addBus(brand, model, color, engineType, capacity, has_contactless_payment, isLogged);
}

void createAndAddTrolleyBus(Database& Db, int isLogged) {
    Admin admin(Db, "admin_username", "admin_password");
    std::string brand, model, color;
    EngineType engineType;
    int capacity;
    bool has_sockets;

    std::cout << "Enter trolleybus brand: ";
    std::cin >> brand;
    std::cout << "Enter trolleybus model: ";
    std::cin >> model;
    std::cout << "Enter trolleybus color: ";
    std::cin >> color;
    std::cout << "Enter engine type (1 for DIESEL, 2 for PETROL, etc.): ";
    int engineTypeInput;
    std::cin >> engineTypeInput;
    engineType = static_cast<EngineType>(engineTypeInput);
    std::cout << "Enter trolleybus capacity: ";
    std::cin >> capacity;
    std::cout << "Does the trolleybus have electrical sockets? (1 for YES, 0 for NO): ";
    int hasSocketsInput;
    std::cin >> hasSocketsInput;
    has_sockets = hasSocketsInput != 0;

    admin.addTrolleyBus(brand, model, color, engineType, capacity, has_sockets, isLogged);
}

void createAndAddTaxi(Database& Db, int isLogged) {
    Admin admin(Db, "admin_username", "admin_password");
    std::string brand, model, color, engineType;
    double pricePerKilometer;
    bool hasDriver, hasWiFi, hasChildSeat;
    RentCarTypes carType;

    std::cout << "Enter taxi brand: ";
    std::cin >> brand;
    std::cout << "Enter taxi model: ";
    std::cin >> model;
    std::cout << "Enter taxi color: ";
    std::cin >> color;
    std::cout << "Enter engine type (e.g., DIESEL, PETROL): ";
    std::cin >> engineType;
    std::cout << "Enter price per kilometer: ";
    std::cin >> pricePerKilometer;
    std::cout << "Does the taxi have a driver? (1 for YES, 0 for NO): ";
    int hasDriverInput;
    std::cin >> hasDriverInput;
    hasDriver = hasDriverInput != 0;
    std::cout << "Does the taxi have WiFi? (1 for YES, 0 for NO): ";
    int hasWiFiInput;
    std::cin >> hasWiFiInput;
    hasWiFi = hasWiFiInput != 0;
    std::cout << "Does the taxi have a child seat? (1 for YES, 0 for NO): ";
    int hasChildSeatInput;
    std::cin >> hasChildSeatInput;
    hasChildSeat = hasChildSeatInput != 0;
    std::cout << "Enter car type (0 for ECONOMY, 1 for COMFORT, 2 for BUSINESS): ";
    int carTypeInput;
    std::cin >> carTypeInput;
    carType = static_cast<RentCarTypes>(carTypeInput);

    admin.addTaxi(brand, model, color, engineType, pricePerKilometer, hasDriver, hasWiFi, hasChildSeat, carType, isLogged);
}

void createAndAddStop(Database& Db, int isLogged) {
    Admin admin(Db, "admin_username", "admin_password");

    std::cout << "Enter stop name: ";
    std::string stopName;
    std::cin >> stopName;
    std::cout << "Enter address: ";
    std::string address;
    std::cin >> address;
    admin.addStop(stopName, address, isLogged);
}

void createAndAddRoute(Database& Db, int isLogged) {
    Admin admin(Db, "admin_username", "admin_password");

    std::string routeName;
    std::cout << "Enter route name:";
    std::cin >> routeName;
    admin.addRoute(routeName,  isLogged);
}

void createAndAddSchedule(Database& db, int isLogged) {
    Admin admin(db, "admin_username", "admin_password");
    int transport_id;
    std::string transport_type;
    int route_id;
    std::string arrival_time;

    std::cout << "Enter transport ID: ";
    std::cin >> transport_id;
    std::cout << "Enter transport type (BUS or TROLLEYBUS): ";
    std::cin >> transport_type; // Теперь transport_type - это строка
    std::cout << "Enter route ID: ";
    std::cin >> route_id;
    std::cout << "Enter arrival time (HH:MM:SS): ";
    std::cin >> arrival_time;

    // Вызов функции addSchedule с передачей параметров
    admin.addSchedule(db, route_id, transport_type, transport_id, isLogged);
}


void createAndSetRoutePrice(Database& db, int isLogged) {
    Admin admin(db, "admin_username", "admin_password");
    int route_id;
    double price;

    std::cout << "Enter route ID: ";
    std::cin >> route_id;
    std::cout << "Enter price: ";
    std::cin >> price;

    admin.setRoutePrice(db, route_id, price, isLogged);
}

void createAndLinkTransportToRoute(Database& db, int isLogged) {
    Admin admin(db, "admin_username", "admin_password");
    int route_id;
    Admin::TransportType transport_type;
    int transport_id;

    std::cout << "Enter route ID: ";
    std::cin >> route_id;
    std::cout << "Enter transport type (1 for BUS, 2 for TROLLEYBUS): ";
    int transport_type_input;
    std::cin >> transport_type_input;
    switch (transport_type_input) {
        case 1:
            transport_type = Admin::BUS;
            break;
        case 2:
            transport_type = Admin::TROLLEYBUS;
            break;
        default:
            std::cerr << "Invalid transport type selected." << std::endl;
            return;
    }
    std::cout << "Enter transport ID: ";
    std::cin >> transport_id;

    admin.linkTransportToRoute(db, route_id, transport_type, transport_id, isLogged);
}

void createAndLinkStopToRoute(Database& db, int isLogged) {
    Admin admin(db, "admin_username", "admin_password");
    int routeId, stopId;
    std::string transportType;

    std::cout << "Enter route ID: ";
    std::cin >> routeId;
    std::cout << "Enter stop ID: ";
    std::cin >> stopId;

    admin.linkStopToRoute(db, routeId, stopId, isLogged);
}


void handleAdminActions(Database& Db) {
    Admin admin(Db, "admin_username", "admin_password");
    std::cout << "1. Login\n2. Register\nChoose an option: ";
    int choice;
    std::cin >> choice;
    std::string username, password;
    int isLogged = 0;
    switch (choice) {
        case 1:
            std::cout << "Enter username: ";
            std::cin >> username;
            std::cout << "Enter password: ";
            std::cin >> password;
            if (admin.adminLogin(Db, username, password)) {
                std::cout << "Logged in successfully." << std::endl;
                isLogged = 1;
            } else {
                std::cout << "Login failed." << std::endl;
            }
            break;
        case 2:
            std::cout << "Enter username for registration: ";
            std::cin >> username;
            std::cout << "Enter password for registration: ";
            std::cin >> password;
            if (admin.registerAdmin(Db, username, password)) {
                std::cout << "Registered successfully." << std::endl;
                isLogged = 1;
            } else {
                std::cout << "Registration failed." << std::endl;
            }
            break;
        default:
            std::cout << "Invalid option selected." << std::endl;
            break;
    }
    while (isLogged == 1) {
        std::cout << "Select an action:\n"
                  << "1. Add Bus\n"
                  << "2. Add Trolleybus\n"
                  << "3. Add Taxi\n"
                  << "4. Set Stop\n"
                  << "5. Set Route\n"
                  << "6. Set Schedule\n"
                  << "7. Set Price\n"
                  << "8. Set link transport to route\n"
                  << "9. createAndLinkStopToRoute\n"
                  << "0. Logout\n"
                  << "Enter your choice: ";
        int action;
        std::cin >> action;
        switch (action) {
            case 1:
                createAndAddBus(Db, isLogged);
                break;
            case 2:
                createAndAddTrolleyBus(Db, isLogged);
                break;
            case 3:
                createAndAddTaxi(Db, isLogged);
                break;
            case 4:
                createAndAddStop(Db, isLogged);
                break;
            case 5:
                createAndAddRoute(Db, isLogged);
                break;
            case 6:
                createAndAddSchedule(Db, isLogged);
                break;
            case 7:
                createAndSetRoutePrice(Db, isLogged);
                break;
            case 8:
                createAndLinkTransportToRoute(Db, isLogged);
                break;
            case 9:
                createAndLinkStopToRoute(Db, isLogged);
                break;
            case 0:
                isLogged = false;
                std::cout << "Logged out successfully." << std::endl;
                break;
            default:
                std::cout << "Invalid action selected. Please try again." << std::endl;
                break;
        }
    }
}