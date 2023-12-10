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

template <typename T>
T getPositiveInput(const std::string &prompt) {
    T value;
    std::string input;

    while (true) {
        std::cout << prompt;

        std::getline(std::cin, input);

        try {
            size_t pos = 0;
            value = std::stod(input, &pos);

            if (pos == input.length() && value > 0) {
                break;
            } else {
                std::cout << "Error: Input is not a positive number. Please try again." << std::endl;
            }
        } catch (std::invalid_argument&) {
            std::cout << "Error: Input is not a number. Please try again." << std::endl;
        } catch (std::out_of_range&) {
            std::cout << "Error: Input is too large. Please try again." << std::endl;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return value;
}

std::string getStringInput(const std::string &prompt) {
    std::string input;

    while (true) {
        std::cout << prompt;

        std::getline(std::cin, input);

        if (!std::cin.fail()) {
            break;  // Всё в порядке, выходим из цикла
        } else {
            std::cout << "Error: Input failed. Please try again." << std::endl;
        }

        // Очищаем входной поток, чтобы избежать зацикливания
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return input;
}

void displayMenu() {
    cout << "Choose the type of transport:" << endl;
    cout << "1. Taxi" << endl;
    cout << "2. Bus" << endl;
    cout << "3. Trolleybus" << endl;
    cout << "4. Admin panel" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice (1/2/3/4/0): ";
}

void bookTransport(Database& Db, PublicTransport::TransportType transportType) {
    string transportTypeName = (transportType == PublicTransport::BUS) ? "bus" : "trolleybus";

    try {
        Customer customer;

        customer.setName(getStringInput("Enter your name: "));
        customer.setSurname(getStringInput("Enter your surname: "));
        customer.setContactInformation(getStringInput("Enter your contact information: "));

        string addCustomerQuery = "INSERT INTO customer (name, surname, contact_information) VALUES ('" +
                                  customer.getName() + "','" +
                                  customer.getSurname() + "','" +
                                  customer.getContactInformation() + "') RETURNING customer_id";
        pqxx::result customerIdResult = Db.executeQuery(addCustomerQuery);
        customer.setCustomerId(customerIdResult[0][0].as<int>());

        int routeId = getPositiveInput<int>("Enter the route ID: ");

        RoutePrice routePrice;
        try {
            routePrice = RoutePrice().getTicketPrice(Db, routeId);
            cout << "The price for the ticket on Route ID: " << routeId
                 << " is $" << routePrice.getPrice() << std::endl;
        } catch (const std::exception& e) {
            cerr << "Error: " << e.what() << endl;
            return;
        }

        int transportId = getPositiveInput<int>("Enter the " + transportTypeName + " ID: ");

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
        int ticketId = ticketManager.insertTicket(ticket);

        cout << transportTypeName << " booked successfully! Ticket ID: " << ticketId << endl;
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
    }
}

void orderTaxi(Database& Db) {
    try {
        int carId = getPositiveInput<int>("Enter the car ID: ");

        string checkTaxiQuery = "SELECT EXISTS(SELECT 1 FROM taxi WHERE taxi_id = " + to_string(carId) + ")";
        pqxx::result taxiExistsResult = Db.executeQuery(checkTaxiQuery);
        bool taxiExists = taxiExistsResult[0][0].as<bool>();
        if (!taxiExists) {
            cout << "Taxi with ID " << carId << " does not exist. Please enter a valid taxi ID." << endl;
            return;
        }

        string name = getStringInput("Enter your name: ");
        string surname = getStringInput("Enter your surname: ");
        string contactInformation = getStringInput("Enter your contact information: ");

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
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
    }
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
                orderTaxi(Db);
                break;
            }
            case 3: {
                int taxiId = getPositiveInput<int>("Enter taxi ID: ");
                taxi.displayTaxiById(Db, taxiId);
                break;
            }
            case 4: {
                string brand = getStringInput("Enter brand: ");
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
                        continue;
                }

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
                int busId = getPositiveInput<int>("Enter bus ID to find linked routes: ");
                Route route;
                route.getRoutesForTransport(Db, busId, PublicTransport::BUS);
                int choice = getPositiveInput<int>("Wanna see all routes? (1 - yes, 2 - no): ");
                if (choice == 1) {
                    route.displayAllRoutes(Db);
                }
                break;
            }
            case 3: {
                int routeId = getPositiveInput<int>("Enter route ID: ");
                Schedule transportSchedule;
                transportSchedule.printStopsForRoute(Db, routeId);
                break;
            }
            case 4: {
                int routeId = getPositiveInput<int>("Enter the route ID to get the ticket price: ");
                RoutePrice routePrice;
                routePrice.displayTicketPrice(Db, routeId);
                break;
            }
            case 5: {
                Stop::findAllStops(Db);
                int stopId = getPositiveInput<int>("Enter stop ID: ");
                Stop::findStopById(Db, stopId);
                break;
            }
            case 6: {
                bookTransport(Db, PublicTransport::BUS);
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
                int trolleybusId = getPositiveInput<int>("Enter trolleybus ID to find linked routes: ");
                Route route;
                route.getRoutesForTransport(Db, trolleybusId, PublicTransport::TROLLEYBUS);
                int choice = getPositiveInput<int>("Wanna see all routes? (1 - yes, 2 - no): ");
                if (choice == 1) {
                    route.displayAllRoutes(Db);
                }
                break;
            }
            case 3: {
                int routeId = getPositiveInput<int>("Enter route ID: ");
                Schedule transportSchedule;
                transportSchedule.printStopsForRoute(Db, routeId);
                break;
            }
            case 4: {
                int routeId = getPositiveInput<int>("Enter the route ID to get the ticket price: ");
                RoutePrice routePrice;
                routePrice.displayTicketPrice(Db, routeId);
                break;
            }
            case 5: {
                Stop::findAllStops(Db);
                int stopId = getPositiveInput<int>("Enter stop ID: ");
                Stop::findStopById(Db, stopId);
                break;
            }
            case 6: {
                bookTransport(Db, PublicTransport::TROLLEYBUS);
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

    brand = getStringInput("Enter bus brand: ");
    model = getStringInput("Enter bus model: ");
    color = getStringInput("Enter bus color: ");

    int engineTypeInput = getPositiveInput<int>("Enter engine type (1 for DIESEL, 2 for PETROL, etc.): ");
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
            return;
    }

    capacity = getPositiveInput<int>("Enter bus capacity: ");

    int hasContactlessPaymentInput = getPositiveInput<int>("Does the bus have contactless payment? (1 for YES, 0 for NO): ");
    hasContactlessPayment = hasContactlessPaymentInput != 0;

    admin.addBus(brand, model, color, engineType, capacity, hasContactlessPayment, isLogged);
}

void createAndAddTrolleyBus(Database& Db, int isLogged) {
    Admin admin(Db, "admin_username", "admin_password");
    std::string brand, model, color;
    EngineType engineType;
    int capacity;
    bool hasSockets;

    brand = getStringInput("Enter trolleybus brand: ");
    model = getStringInput("Enter trolleybus model: ");
    color = getStringInput("Enter trolleybus color: ");

    int engineTypeInput = getPositiveInput<int>("Enter engine type (1 for DIESEL, 2 for PETROL, etc.): ");
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
            return;
    }

    capacity = getPositiveInput<int>("Enter trolleybus capacity: ");

    int hasSocketsInput = getPositiveInput<int>("Does the trolleybus have electrical sockets? (1 for YES, 0 for NO): ");
    hasSockets = hasSocketsInput != 0;

    admin.addTrolleyBus(brand, model, color, engineType, capacity, hasSockets, isLogged);
}

void createAndAddTaxi(Database& Db, int isLogged) {
    Admin admin(Db, "admin_username", "admin_password");
    std::string brand, model, color, engineType;
    double pricePerKilometer;
    bool hasDriver, hasWiFi, hasChildSeat;
    RentCarTypes carType;

    brand = getStringInput("Enter taxi brand: ");
    model = getStringInput("Enter taxi model: ");
    color = getStringInput("Enter taxi color: ");
    engineType = getStringInput("Enter engine type (e.g., DIESEL, PETROL): ");

    pricePerKilometer = getPositiveInput<double>("Enter price per kilometer: ");

    int hasDriverInput = getPositiveInput<int>("Does the taxi have a driver? (1 for YES, 0 for NO): ");
    hasDriver = hasDriverInput != 0;

    int hasWiFiInput = getPositiveInput<int>("Does the taxi have WiFi? (1 for YES, 0 for NO): ");
    hasWiFi = hasWiFiInput != 0;

    int hasChildSeatInput = getPositiveInput<int>("Does the taxi have a child seat? (1 for YES, 0 for NO): ");
    hasChildSeat = hasChildSeatInput != 0;

    int carTypeInput = getPositiveInput<int>("Enter car type (0 for ECONOMY, 1 for COMFORT, 2 for BUSINESS): ");
    switch (carTypeInput) {
        case 0:
            carType = ECONOMY;
            break;
        case 1:
            carType = COMFORT;
            break;
        case 2:
            carType = BUSINESS;
            break;
        default:
            std::cerr << "Invalid car type selected." << std::endl;
            return;
    }

    admin.addTaxi(brand, model, color, engineType, pricePerKilometer, hasDriver, hasWiFi, hasChildSeat, carType, isLogged);
}


void createAndAddStop(Database& Db, int isLogged) {
    Admin admin(Db, "admin_username", "admin_password");

    std::string stopName = getStringInput("Enter stop name: ");
    std::string address = getStringInput("Enter address: ");

    admin.addStop(stopName, address, isLogged);
}


void createAndAddRoute(Database& Db, int isLogged) {
    Admin admin(Db, "admin_username", "admin_password");

    std::string routeName = getStringInput("Enter route name: ");
    admin.addRoute(routeName, isLogged);
}

void createAndAddSchedule(Database& db, int isLogged) {
    Admin admin(db, "admin_username", "admin_password");
    int transportId;
    int routeId;
    std::string arrivalTime;
    Admin::TransportType transportType;

    transportId = getPositiveInput<int>("Enter transport ID: ");

    int transportTypeInput = getPositiveInput<int>("Enter transport type (1 for BUS, 2 for TROLLEYBUS): ");
    switch (transportTypeInput) {
        case 1:
            transportType = Admin::BUS;
            break;
        case 2:
            transportType = Admin::TROLLEYBUS;
            break;
        default:
            std::cerr << "Invalid transport type selected." << std::endl;
            return;
    }

    routeId = getPositiveInput<int>("Enter route ID: ");
    arrivalTime = getStringInput("Enter arrival time (HH:MM:SS): ");

    admin.addSchedule(db, routeId, transportType, transportId, isLogged);
}

void createAndSetRoutePrice(Database& db, int isLogged) {
    Admin admin(db, "admin_username", "admin_password");
    int routeId;
    double price;

    routeId = getPositiveInput<int>("Enter route ID: ");
    price = getPositiveInput<double>("Enter price: ");

    admin.setRoutePrice(db, routeId, price, isLogged);
}

void createAndLinkTransportToRoute(Database& db, int isLogged) {
    Admin admin(db, "admin_username", "admin_password");
    int routeId;
    Admin::TransportType transportType;
    int transportId;

    routeId = getPositiveInput<int>("Enter route ID: ");

    int transportTypeInput = getPositiveInput<int>("Enter transport type (1 for BUS, 2 for TROLLEYBUS): ");
    switch (transportTypeInput) {
        case 1:
            transportType = Admin::BUS;
            break;
        case 2:
            transportType = Admin::TROLLEYBUS;
            break;
        default:
            std::cerr << "Invalid transport type selected." << std::endl;
            return;
    }

    transportId = getPositiveInput<int>("Enter transport ID: ");

    admin.linkTransportToRoute(db, routeId, transportType, transportId, isLogged);
}

void createAndLinkStopToRoute(Database& db, int isLogged) {
    Admin admin(db, "admin_username", "admin_password");
    int routeId, stopId;

    routeId = getPositiveInput<int>("Enter route ID: ");
    stopId = getPositiveInput<int>("Enter stop ID: ");

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
            username = getStringInput("Enter username: ");
            password = getStringInput("Enter password: ");

            if (admin.adminLogin(Db, username, password)) {
                std::cout << "Logged in successfully." << std::endl;
                isLogged = 1;
            } else {
                std::cout << "Login failed." << std::endl;
            }
            break;
        case 2:
            username = getStringInput("Enter username for registration: ");
            password = getStringInput("Enter password for registration: ");
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
        int action = getPositiveInput<int>("        s<< \"Select an action:\\n\"\n"
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
