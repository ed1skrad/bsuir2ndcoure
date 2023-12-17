#include <string>
#include <iostream>
#include "pqxx/pqxx"
#include "../database/Database.h"
#include "../models/Taxi.h"
#include "../models/Order.h"
#include "../models/Bus.h"
#include "../models/Route.h"
#include "../models/Trolleybus.h"
#include "../models/price/RoutePrice.h"
#include "../admin/Admin.h"
#include "../models/schedule/Schedule.h"
#include "InputUtils.h"

using namespace std;

void displayMenu() {
    cout << "Choose the type of transport:" << endl;
    cout << "1. Taxi" << endl;
    cout << "2. Bus" << endl;
    cout << "3. Trolleybus" << endl;
    cout << "4. Admin panel" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice (1/2/3/4/0): ";
}

RentCarTypes parseEnumRentCarType(int rentCarTypeInput) {
    RentCarTypes rentCarTypes;
    switch (rentCarTypeInput) {
        case 1:
            rentCarTypes = ECONOMY;
            break;
        case 2:
            rentCarTypes = COMFORT;
            break;
        case 3:
            rentCarTypes = BUSINESS;
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
    }
    return rentCarTypes;
}

EngineType parseEnumEngineType(int engineTypeInput) {
    EngineType engineType;
    switch (engineTypeInput) {
        case 1:
            engineType = DIESEL;
            break;
        case 2:
            engineType = PETROL;
            break;
        case 3:
            engineType = HYBRID;
            break;
        case 4:
            engineType = ELECTRIC;
            break;
        default:
            std::cerr << "Invalid engine type selected." << std::endl;
            break;
    }
    return engineType;
}


void handleTaxiSelect(Database& Db) {
    bool exitMenu = false;
    while (!exitMenu) {
        Taxi taxi;
        cout << "Choose an action:" << endl;
        cout << "1. View all taxis" << endl;
        cout << "2. Call taxi" << endl;
        cout << "3. Display taxi by ID" << endl;
        cout << "4. Display taxis by brand" << endl;
        cout << "5. Display taxis by RentCarType" << endl;
        cout << "0. Back to the main menu" << endl;

        int actionChoice;
        cin >> actionChoice;
        cin.ignore();

        switch (actionChoice) {
            case 1: {
                taxi.displayAllTaxis(Db);
                break;
            }
            case 2: {
                Taxi taxi;
                taxi.orderTaxi(Db);
                break;
            }
            case 3: {
                int taxiId = InputUtils::getPositiveInput<int>("Enter taxi ID: ");
                taxi.displayTaxiById(Db, taxiId);
                break;
            }
            case 4: {
                string brand = InputUtils::getStringInput("Enter brand: ");
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
                cin.ignore();

                RentCarTypes rentCarType;

                Taxi::displayTaxisByRentCarType(Db, rentCarType);
                break;
            }
            case 0: {
                exitMenu = true;
                break;
            }
            default: {
                cout << "Invalid choice" << endl;
                break;
            }
        }
    }
}

void handleBusSelect(Database& Db) {
    bool exitMenu = false;
    while (!exitMenu) {
        cout << "Choose an action:" << endl;
        cout << "1. View all buses" << endl;
        cout << "2. View all routes" << endl;
        cout << "3. View schedule" << endl;
        cout << "4. Get ticket price for a route" << endl;
        cout << "5. Stop case" << endl;
        cout << "6. Book a ticket" << endl;
        cout << "0. Back to main menu" << endl;
        cout << "Enter your choice (1/2/3/4/5/6/0): ";

        int actionChoice;
        cin >> actionChoice;
        cin.ignore();

        switch (actionChoice) {
            case 1: {
                Bus bus;
                bus.displayAllBuses(Db);
                break;
            }
            case 2: {
                int busId = InputUtils::getPositiveInput<int>("Enter bus ID to find linked routes: ");
                Route route;
                route.getRoutesForTransport(Db, busId, PublicTransport::BUS);
                int choice = InputUtils::getPositiveInput<int>("Wanna see all routes? (1 - yes, 2 - no): ");
                if (choice == 1) {
                    route.displayAllRoutes(Db);
                }
                break;
            }
            case 3: {
                int routeId = InputUtils::getPositiveInput<int>("Enter route ID: ");
                Schedule transportSchedule;
                transportSchedule.printStopsForRoute(Db, routeId);
                break;
            }
            case 4: {
                int routeId = InputUtils::getPositiveInput<int>("Enter the route ID to get the ticket price: ");
                RoutePrice routePrice;
                routePrice.displayTicketPrice(Db, routeId);
                break;
            }
            case 5: {
                Stop::findAllStops(Db);
                int stopId = InputUtils::getPositiveInput<int>("Enter stop ID: ");
                Stop::findStopById(Db, stopId);
                break;
            }
            case 6: {
                PublicTransport publicTransport;
                publicTransport.bookTransport(Db, PublicTransport::BUS);
                break;
            }
            case 0: {
                exitMenu = true;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void handleTrolleyBusSelect(Database& Db) {
    bool exitMenu = false;
    while (!exitMenu) {
        cout << "Choose an action:" << endl;
        cout << "1. View all trolleybuses" << endl;
        cout << "2. View all routes" << endl;
        cout << "3. View schedule" << endl;
        cout << "4. Get ticket price for a route" << endl;
        cout << "5. Stop case" << endl;
        cout << "6. Book a ticket" << endl;
        cout << "0. Back to main menu" << endl;
        cout << "Enter your choice (1/2/3/4/5/6/0): ";

        int actionChoice;
        cin >> actionChoice;
        cin.ignore();

        switch (actionChoice) {
            case 1: {
                TrolleyBus trolleyBus;
                trolleyBus.displayAllTrolleyBuses(Db);
                break;
            }
            case 2: {
                int trolleybusId = InputUtils::getPositiveInput<int>("Enter trolleybus ID to find linked routes: ");
                Route route;
                route.getRoutesForTransport(Db, trolleybusId, PublicTransport::TROLLEYBUS);
                int choice = InputUtils::getPositiveInput<int>("Wanna see all routes? (1 - yes, 2 - no): ");
                if (choice == 1) {
                    route.displayAllRoutes(Db);
                }
                break;
            }
            case 3: {
                int routeId = InputUtils::getPositiveInput<int>("Enter route ID: ");
                Schedule transportSchedule;
                transportSchedule.printStopsForRoute(Db, routeId);
                break;
            }
            case 4: {
                int routeId = InputUtils::getPositiveInput<int>("Enter the route ID to get the ticket price: ");
                RoutePrice routePrice;
                routePrice.displayTicketPrice(Db, routeId);
                break;
            }
            case 5: {
                Stop::findAllStops(Db);
                int stopId = InputUtils::getPositiveInput<int>("Enter stop ID: ");
                Stop::findStopById(Db, stopId);
                break;
            }
            case 6: {
                PublicTransport publicTransport;
                publicTransport.bookTransport(Db, PublicTransport::TROLLEYBUS);
                break;
            }
            case 0: {
                exitMenu = true;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void createAndAddBus(Database& Db, int isLogged) {
    Admin admin(Db, "admin_username", "admin_password");
    std::string brand, model, color;
    EngineType engineType;
    int capacity;
    bool hasContactlessPayment;

    brand = InputUtils::getStringInput("Enter bus brand: ");
    model = InputUtils::getStringInput("Enter bus model: ");
    color = InputUtils::getStringInput("Enter bus color: ");

    int engineTypeInput = InputUtils::getPositiveInput<int>("Enter engine type (1 for DIESEL, 2 for PETROL, etc.): ");
    engineType = parseEnumEngineType(engineTypeInput);

    capacity = InputUtils::getPositiveInput<int>("Enter bus capacity: ");

    int hasContactlessPaymentInput = InputUtils::getPositiveInput<int>("Does the bus have contactless payment? (1 for YES, 0 for NO): ");
    hasContactlessPayment = hasContactlessPaymentInput != 0;

    admin.addBus(brand, model, color, engineType, capacity, hasContactlessPayment, isLogged);
}

void createAndAddTrolleyBus(Database& Db, int isLogged) {
    Admin admin(Db, "admin_username", "admin_password");
    std::string brand, model, color;
    EngineType engineType;
    int capacity;
    bool hasSockets;

    brand = InputUtils::getStringInput("Enter trolleybus brand: ");
    model = InputUtils::getStringInput("Enter trolleybus model: ");
    color = InputUtils::getStringInput("Enter trolleybus color: ");

    int engineTypeInput = InputUtils::getPositiveInput<int>("Enter engine type (1 for DIESEL, 2 for PETROL, etc.): ");
    engineType = parseEnumEngineType(engineTypeInput);

    capacity = InputUtils::getPositiveInput<int>("Enter trolleybus capacity: ");

    int hasSocketsInput = InputUtils::getPositiveInput<int>("Does the trolleybus have electrical sockets? (1 for YES, 0 for NO): ");
    hasSockets = hasSocketsInput != 0;

    admin.addTrolleyBus(brand, model, color, engineType, capacity, hasSockets, isLogged);
}

void createAndAddTaxi(Database& Db, int isLogged) {
    Admin admin(Db, "admin_username", "admin_password");
    std::string brand, model, color;
    EngineType engineType;
    double pricePerKilometer;
    bool hasDriver, hasWiFi, hasChildSeat;
    RentCarTypes carType;

    brand = InputUtils::getStringInput("Enter taxi brand: ");
    model = InputUtils::getStringInput("Enter taxi model: ");
    color = InputUtils::getStringInput("Enter taxi color: ");
    int engineTypeInput = InputUtils::getPositiveInput<int>("Enter car type (0 for PETROL, 1 for DIESEL, 2 for HYBRID, 3 for ELECTRIC): ");
    engineType = parseEnumEngineType(engineTypeInput);

    pricePerKilometer = InputUtils::getPositiveInput<double>("Enter price per kilometer: ");

    int hasDriverInput = InputUtils::getPositiveInput<int>("Does the taxi have a driver? (1 for YES, 0 for NO): ");
    hasDriver = hasDriverInput != 0;

    int hasWiFiInput = InputUtils::getPositiveInput<int>("Does the taxi have WiFi? (1 for YES, 0 for NO): ");
    hasWiFi = hasWiFiInput != 0;

    int hasChildSeatInput = InputUtils::getPositiveInput<int>("Does the taxi have a child seat? (1 for YES, 0 for NO): ");
    hasChildSeat = hasChildSeatInput != 0;

    int carTypeInput = InputUtils::getPositiveInput<int>("Enter car type (0 for ECONOMY, 1 for COMFORT, 2 for BUSINESS): ");

    carType = parseEnumRentCarType(carTypeInput);

    admin.addTaxi(brand, model, color, engineType, pricePerKilometer, hasDriver, hasWiFi, hasChildSeat, carType, isLogged);
}



void createAndAddStop(Database& Db, int isLogged) {
    Admin admin(Db, "admin_username", "admin_password");

    std::string stopName = InputUtils::getStringInput("Enter stop name: ");
    std::string address = InputUtils::getStringInput("Enter address: ");

    admin.addStop(stopName, address, isLogged);
}


void createAndAddRoute(Database& Db, int isLogged) {
    Admin admin(Db, "admin_username", "admin_password");

    std::string routeName = InputUtils::getStringInput("Enter route name: ");
    admin.addRoute(routeName, isLogged);
}

void createAndAddSchedule(Database& db, int isLogged) {
    Admin admin(db, "admin_username", "admin_password");
    int transportId;
    int routeId;
    std::string arrivalTime;
    PublicTransport::TransportType transportType;

    transportId = InputUtils::getPositiveInput<int>("Enter transport ID: ");

    int transportTypeInput = InputUtils::getPositiveInput<int>("Enter transport type (1 for BUS, 2 for TROLLEYBUS): ");
    switch (transportTypeInput) {
        case 1:
            transportType = PublicTransport::BUS;
            break;
        case 2:
            transportType = PublicTransport::TROLLEYBUS;
            break;
        default:
            std::cerr << "Invalid transport type selected." << std::endl;
            return;
    }

    routeId = InputUtils::getPositiveInput<int>("Enter route ID: ");

    admin.addSchedule(db, routeId, static_cast<TransportType>(transportType), transportId, isLogged);
}

void createAndSetRoutePrice(Database& db, int isLogged) {
    Admin admin(db, "admin_username", "admin_password");
    int routeId;
    double price;

    routeId = InputUtils::getPositiveInput<int>("Enter route ID: ");
    price = InputUtils::getPositiveInput<double>("Enter price: ");

    admin.setRoutePrice(db, routeId, price, isLogged);
}

void createAndLinkTransportToRoute(Database& db, int isLogged) {
    Admin admin(db, "admin_username", "admin_password");
    int routeId;
    PublicTransport::TransportType transportType;
    int transportId;

    routeId = InputUtils::getPositiveInput<int>("Enter route ID: ");

    int transportTypeInput = InputUtils::getPositiveInput<int>("Enter transport type (1 for BUS, 2 for TROLLEYBUS): ");
    switch (transportTypeInput) {
        case 1:
            transportType = PublicTransport::BUS;
            break;
        case 2:
            transportType = PublicTransport::TROLLEYBUS;
            break;
        default:
            std::cerr << "Invalid transport type selected." << std::endl;
            return;
    }

    transportId = InputUtils::getPositiveInput<int>("Enter transport ID: ");

    admin.linkTransportToRoute(db, routeId, static_cast<TransportType>(transportType), transportId, isLogged);
}

void createAndLinkStopToRoute(Database& db, int isLogged) {
    Admin admin(db, "admin_username", "admin_password");
    int routeId, stopId;

    routeId = InputUtils::getPositiveInput<int>("Enter route ID: ");
    stopId = InputUtils::getPositiveInput<int>("Enter stop ID: ");

    admin.linkStopToRoute(db, routeId, stopId, isLogged);
}

void handleAdminActions(Database& Db) {
    Admin admin(Db, "admin_username", "admin_password");
    std::cout << "1. Login\n2. Register\nChoose an option: ";
    int choice;
    std::cin >> choice;
    cin.ignore();
    std::string username, password;
    int isLogged = 0;
    switch (choice) {
        case 1:
            username = InputUtils::getStringInput("Enter username: ");
            password = InputUtils::getStringInput("Enter password: ");

            if (admin.adminLogin(Db, username, password)) {
                std::cout << "Logged in successfully." << std::endl;
                isLogged = 1;
            } else {
                std::cout << "Login failed." << std::endl;
            }
            break;
        case 2:
            username = InputUtils::getStringInput("Enter username for registration: ");
            password = InputUtils::getStringInput("Enter password for registration: ");
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
        int action = InputUtils::getPositiveInput<int>("        s<< \"Select an action:\\n\"\n"
                                                       "                  << \"1. Add Bus\\n\"\n"
                                                       "                  << \"2. Add Trolleybus\\n\"\n"
                                                       "                  << \"3. Add Taxi\\n\"\n"
                                                       "                  << \"4. Set Stop\\n\"\n"
                                                       "                  << \"5. Set Route\\n\"\n"
                                                       "                  << \"6. Set Schedule\\n\"\n"
                                                       "                  << \"7. Set Price\\n\"\n"
                                                       "                  << \"8. Set link transport to route\\n\"\n"
                                                       "                  << \"9. createAndLinkStopToRoute\\n\"\n"
                                                       "                  << \"10. Get orders\\n\"\n"
                                                       "                  << \"0. Logout\\n\"\n"
                                                       "                  << \"Enter your choice: \"");

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
            case 10:
                Order::printAllOrders(Db, isLogged);
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