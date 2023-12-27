#include <regex>
#include "Admin.h"

Admin::Admin(Database& db, const std::string& username, const std::string& password)
        : db(db), username(username), hashedPassword(hashPassword(password)) {
}

std::string Admin::hashPassword(const std::string &password) {
    std::string hashed;
    for (char c: password) {
        hashed += std::to_string((c + 3) % 256);
    }
    return hashed;
}

bool Admin::checkAuthorization(int isLogged) {
    if (!isLogged) {
        std::cerr << "Error: You must be logged in as an admin to link transport to a route." << std::endl;
        return false;
    }
    return true;
}

bool Admin::login() {
    std::string query =
            "SELECT admin_id FROM Admins WHERE username = '" + username + "' AND password = '" + hashedPassword +
            "'";
    pqxx::result result = db.executeQuery(query);
    if (!result.empty()) {
        adminId = result[0]["admin_id"].as<int>();
        std::cout << "Login successful for admin ID: " << adminId << std::endl;
        return true;
    } else {
        std::cout << "Login failed for username: " << username << std::endl;
        return false;
    }
}

std::string Admin::engineTypeToString(EngineType engineType) {
    switch (engineType) {
        case DIESEL:
            return "DIESEL";
        case PETROL:
            return "PETROL";
        case ELECTRIC:
            return "ELECTRIC";
        case HYBRID:
            return "HYBRID";
        default:
            return "UNKNOWN";
    }
}

std::string Admin::rentCarTypesToString(RentCarTypes rentCarTypes) {
        switch (rentCarTypes) {
            case ECONOMY:
                return "ECONOMY";
            break;
            case COMFORT:
                return "COMFORT";
            break;
            case BUSINESS:
                return "BUSINESS";
            break;
            default:
                return "UNKNOWN";
            break;
        }
};

bool Admin::isValidRouteID(Database &db, int routeId) {
    std::string query = "SELECT EXISTS(SELECT 1 FROM Route WHERE route_id = " + std::to_string(routeId) + ");";
    auto result = db.executeQuery(query);
    return !result.empty() && result[0][0].as<bool>();
}


bool Admin::adminLogin(Database &db, const std::string &username, const std::string &password) {
    Admin admin(db, username, password);
    return admin.login();
}

bool Admin::registerAdmin(Database &db, const std::string &username, const std::string &password) {
    std::string hashedPassword;
    for (char c: password) {
        hashedPassword += std::to_string((c + 3) % 256);
    }

    std::string query = "INSERT INTO Admins (username, password) VALUES ('"
                        + username + "', '" + hashedPassword + "')";

    try {
        db.executeQuery(query);
        std::cout << "Admin registered successfully." << std::endl;
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Error registering admin: " << e.what() << std::endl;
        return false;
    }
}

void Admin::addBus(const std::string &brand, const std::string &model, const std::string &color, EngineType engineType,
                   int capacity, bool hasContactlessPayment, int isLogged) {
    if (!checkAuthorization(isLogged)) {
        return;
    }
    std::string query =
            "INSERT INTO bus (brand, model, color, engineType, capacity, has_contactless_payment) VALUES ('"
            + brand + "', '" + model + "', '" + color + "', '" + engineTypeToString(engineType) + "', "
            + std::to_string(capacity) + ", " + (hasContactlessPayment ? "TRUE" : "FALSE") + ")";
    try {
        db.executeQuery(query);
        std::cout << "Bus added successfully." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error adding bus: " << e.what() << std::endl;
    }
}

void Admin::addTrolleyBus(const std::string &brand, const std::string &model, const std::string &color, EngineType engineType,
                          int capacity, bool hasSockets, int isLogged) {
    if (!checkAuthorization(isLogged)) {
        return;
    }
    std::string query = "INSERT INTO trolleybus (brand, model, color, engineType, capacity, has_sockets) VALUES ('"
                        + brand + "', '" + model + "', '" + color + "', '" + engineTypeToString(engineType) + "', "
                        + std::to_string(capacity) + ", " + (hasSockets ? "TRUE" : "FALSE") + ")";
    try {
        db.executeQuery(query);
        std::cout << "TrolleyBus added successfully." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error adding trolleybus: " << e.what() << std::endl;
    }
}

void Admin::addTaxi(const std::string &brand, const std::string &model, const std::string &color, EngineType engineType,
                    double pricePerKilometer, bool hasDriver, bool hasWiFi, bool hasChildSeat, RentCarTypes rentCarTypes,
                    int isLogged) {
    if (!checkAuthorization(isLogged)) {
        return;
    }

    std::string rentCarTypeStr = rentCarTypesToString(rentCarTypes);
    std::string engineTypeStr = engineTypeToString(engineType);

    std::string query =
            "INSERT INTO taxi (brand, model, color, engineType, price_per_kil, has_driver, has_wifi, has_child_seat, rent_car_type) VALUES ('"
            + brand + "', '" + model + "', '" + color + "', '" + engineTypeStr + "', " +
            std::to_string(pricePerKilometer) + ", "
            + (hasDriver ? "TRUE" : "FALSE") + ", " + (hasWiFi ? "TRUE" : "FALSE") + ", " +
            (hasChildSeat ? "TRUE" : "FALSE") + ", '"
            + rentCarTypeStr + "')";
    try {
        db.executeQuery(query);
        std::cout << "Taxi added successfully." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error adding taxi: " << e.what() << std::endl;
    }
}

void Admin::addStop(const std::string &stopName, const std::string &address, int isLogged) {
    if (!checkAuthorization(isLogged)) {
        return;
    }
    std::string query = "INSERT INTO Stop (stop_name, address) VALUES ('"
                        + stopName + "', '" + address + "')";
    try {
        db.executeQuery(query);
        std::cout << "Stop added successfully." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error adding stop: " << e.what() << std::endl;
    }
}

void Admin::addRoute(const std::string &routeName, int isLogged) {
    if (!checkAuthorization(isLogged)) {
        return;
    }

    std::string query = "INSERT INTO Route (route_name) VALUES ('"
                        + routeName + "')";
    try {
        db.executeQuery(query);
        std::cout << "Route added successfully." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error adding route: " << e.what() << std::endl;
    }
}

void Admin::addSchedule(Database& db, int routeId, TransportType transportType, int transportId, int isLogged) {
    if (!checkAuthorization(isLogged)) {
        return;
    }

    std::string transportTypeStr = (transportType == BUS) ? "BUS" : "TROLLEYBUS";
    std::string transportTable = (transportType == BUS) ? "bus" : "trolleybus";
    std::string transportIdColumn = (transportType == BUS) ? "bus_id" : "trolleybus_id";

    std::string checkTransportRouteQuery = "SELECT EXISTS(SELECT 1 FROM TransportRoute WHERE route_id = " +
                                           std::to_string(routeId) + " AND transport_type = '" +
                                           transportTypeStr + "' AND transport_id = " +
                                           std::to_string(transportId) + ");";
    auto transportRouteExists = db.executeQuery(checkTransportRouteQuery);
    if (transportRouteExists.empty() || !transportRouteExists[0][0].as<bool>()) {
        std::cerr << "Transport is not linked to the route." << std::endl;
        return;
    }

    std::string getStopsQuery = "SELECT stop_id FROM StopRoute WHERE route_id = " + std::to_string(routeId) + ";";
    auto stops = db.executeQuery(getStopsQuery);

    /*
     * HH:MM:SS
     * 20:23
     * 0:59
     * 0:59
     */
    std::regex timeRegex(R"((2[0-3]|[01]?[0-9]):([0-5]?[0-9]):([0-5]?[0-9]))");

    for (const auto& stop : stops) {
        int stopId = stop[0].as<int>();
        std::string arrivalTime;

        do {
            std::cout << "Enter arrival time for stop ID " << stopId << " (HH:MM:SS): ";
            std::cin >> arrivalTime;

            if (!std::regex_match(arrivalTime, timeRegex)) {
                std::cerr << "Error: Invalid time format. Please enter the time in HH:MM:SS format." << std::endl;
            }
        } while (!std::regex_match(arrivalTime, timeRegex));

        std::string insertScheduleQuery = "INSERT INTO Schedule (route_id, stop_id, transport_type, transport_id, arrival_time) VALUES (" +
                                          std::to_string(routeId) + ", " +
                                          std::to_string(stopId) + ", '" +
                                          transportTypeStr + "', " +
                                          std::to_string(transportId) + ", '" +
                                          arrivalTime + "');";
        db.executeQuery(insertScheduleQuery);
    }

    std::cout << "Schedule added successfully for all linked stops with individual arrival times." << std::endl;
}

void Admin::setRoutePrice(Database &Db, int routeId, double price, int isLogged) {
    if (!checkAuthorization(isLogged)) {
        return;
    }

    if (!isValidRouteID(Db, routeId)) {
        std::cerr << "Invalid route ID provided." << std::endl;
        return;
    }

    std::string checkQuery = "SELECT price FROM RoutePrice WHERE route_id = " + std::to_string(routeId);
    auto checkResult = Db.executeQuery(checkQuery);
    if (!checkResult.empty()) {
        std::string updateQuery = "UPDATE RoutePrice SET price = " + std::to_string(price) + " WHERE routeId = " +
                                  std::to_string(routeId);
        Db.executeQuery(updateQuery);
        std::cout << "Route price updated successfully." << std::endl;
    } else {
        std::string insertQuery =
                "INSERT INTO RoutePrice (route_id, price) VALUES (" + std::to_string(routeId) + ", " +
                std::to_string(price) + ")";
        Db.executeQuery(insertQuery);
        std::cout << "Route price set successfully." << std::endl;
    }
}

void Admin::linkTransportToRoute(Database &Db, int routeId, TransportType transportType, int transport_id, int isLogged) {
    if (!checkAuthorization(isLogged)) {
        return;
    }

    if (!isValidRouteID(Db, routeId)) {
        std::cerr << "Invalid route ID provided." << std::endl;
        return;
    }

    std::string transportTypeStr = (transportType == BUS) ? "BUS" : "TROLLEYBUS";
    std::string transportTable = (transportType == BUS) ? "bus" : "trolleybus";
    std::string transportIdColumn = (transportType == BUS) ? "bus_id" : "trolleybus_id";
    std::string checkTransportQuery = "SELECT EXISTS(SELECT 1 FROM " + transportTable +
                                      " WHERE " + transportIdColumn + " = " + std::to_string(transport_id) + ");";
    auto transportExists = Db.executeQuery(checkTransportQuery);
    if (transportExists.empty() || !transportExists[0][0].as<bool>()) {
        std::cerr << "Transport ID does not exist in the database." << std::endl;
        return;
    }

    std::string checkQuery = "SELECT 1 FROM TransportRoute WHERE route_id = " + std::to_string(routeId) +
                             " AND transport_type = '" + transportTypeStr + "' AND transport_id = " +
                             std::to_string(transport_id);
    auto checkResult = Db.executeQuery(checkQuery);
    if (!checkResult.empty()) {
        std::cerr << "This transport is already linked to the route." << std::endl;
        return;
    }

    try {
        std::string insertQuery = "INSERT INTO TransportRoute (route_id, transport_type, transport_id) VALUES (" +
                                  std::to_string(routeId) + ", '" + transportTypeStr + "', " +
                                  std::to_string(transport_id) + ")";
        Db.executeQuery(insertQuery);
        std::cout << "Transport linked to route successfully." << std::endl;
    } catch (const pqxx::unique_violation &e) {
        std::cerr << "Error: Transport is already linked to this route." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Admin::linkStopToRoute(Database &db, int routeId, int stopId, int isLogged) {
    if (!checkAuthorization(isLogged)) {
        return;
    }

    std::string checkRouteQuery = "SELECT EXISTS(SELECT 1 FROM Route WHERE route_id = " + std::to_string(routeId) + ");";
    auto routeExists = db.executeQuery(checkRouteQuery);
    if (routeExists.empty() || !routeExists[0][0].as<bool>()) {
        std::cerr << "Invalid route ID provided." << std::endl;
        return;
    }

    std::string checkStopQuery = "SELECT EXISTS(SELECT 1 FROM Stop WHERE stop_id = " + std::to_string(stopId) + ");";
    auto stopExists = db.executeQuery(checkStopQuery);
    if (stopExists.empty() || !stopExists[0][0].as<bool>()) {
        std::cerr << "Invalid stop ID provided." << std::endl;
        return;
    }

    std::string checkLinkQuery = "SELECT 1 FROM StopRoute WHERE route_id = " + std::to_string(routeId) +
                                 " AND stop_id = " + std::to_string(stopId) + ";";
    auto checkLinkResult = db.executeQuery(checkLinkQuery);
    if (!checkLinkResult.empty()) {
        std::cerr << "This stop is already linked to the route." << std::endl;
        return;
    }

    std::string insertQuery = "INSERT INTO StopRoute (route_id, stop_id) VALUES (" +
                              std::to_string(routeId) + ", " +
                              std::to_string(stopId) + ");";
    db.executeQuery(insertQuery);
    std::cout << "Stop linked to route successfully." << std::endl;
}

void Admin::deleteTaxi(Database &db, int taxiId, int isLogged) {
    if (!checkAuthorization(isLogged)) {
        return;
    }

    std::string query = "DELETE FROM taxi WHERE taxi_id = " + std::to_string(taxiId);
    db.executeQuery(query);
}

void Admin::deleteBus(Database &db, int busId, int isLogged) {

    std::string query = "SELECT EXISTS(SELECT 1 FROM TransportRoute WHERE transport_id = " + std::to_string(busId) + " AND transport_type = 'BUS');";
    auto busExistsInRoute = db.executeQuery(query);
    if (!busExistsInRoute.empty() && busExistsInRoute[0][0].as<bool>()) {
        std::cerr << "Bus is linked to a route. Please unlink before deleting." << std::endl;
        return;
    }

    query = "DELETE FROM bus WHERE bus_id = " + std::to_string(busId);
    db.executeQuery(query);
}

void Admin::deleteTrolleybus(Database &db, int trolleybusId, int isLogged) {
    if (!checkAuthorization(isLogged)) {
        return;
    }

    std::string query = "SELECT EXISTS(SELECT 1 FROM TransportRoute WHERE transport_id = " + std::to_string(trolleybusId) + " AND transport_type = 'TROLLEYBUS');";
    auto trolleybusExistsInRoute = db.executeQuery(query);
    if (!trolleybusExistsInRoute.empty() && trolleybusExistsInRoute[0][0].as<bool>()) {
        std::cerr << "Trolleybus is linked to a route. Please unlink before deleting." << std::endl;
        return;
    }

    query = "DELETE FROM trolleybus WHERE trolleybus_id = " + std::to_string(trolleybusId);
    db.executeQuery(query);
}

void Admin::deleteStop(Database &db, int stopId, int isLogged) {
    if (!checkAuthorization(isLogged)) {
        return;
    }

    std::string query = "SELECT EXISTS(SELECT 1 FROM StopRoute WHERE stop_id = " + std::to_string(stopId) + ");";
    auto stopExistsInRoute = db.executeQuery(query);
    if (!stopExistsInRoute.empty() && stopExistsInRoute[0][0].as<bool>()) {
        std::cerr << "Stop is linked to a route. Please unlink before deleting." << std::endl;
        return;
    }

    query = "DELETE FROM Stop WHERE stop_id = " + std::to_string(stopId);
    db.executeQuery(query);
}

void Admin::deleteRoute(Database &db, int routeId, int isLogged) {
    if (!checkAuthorization(isLogged)) {
        return;
    }

    std::string query = "SELECT EXISTS(SELECT 1 FROM TransportRoute WHERE route_id = " + std::to_string(routeId) + ");";
    auto routeExistsInTransport = db.executeQuery(query);
    if (!routeExistsInTransport.empty() && routeExistsInTransport[0][0].as<bool>()) {
        std::cerr << "Route is linked to a transport. Please unlink before deleting." << std::endl;
        return;
    }

    query = "DELETE FROM Route WHERE route_id = " + std::to_string(routeId);
    db.executeQuery(query);
}

void Admin::unlinkStop(Database &db, int stopId, int isLogged){
    std::string query = "DELETE FROM StopRoute WHERE stop_id = " + std::to_string(stopId);
    db.executeQuery(query);
    std::cout << "Stop unlinked successfully." << std::endl;
}


void Admin::unlinkTransport(Database &Db, int routeId, TransportType transportType, int transportId, int isLogged){
    if (!checkAuthorization(isLogged)) {
        return;
    }

    std::string transportTypeStr = (transportType == BUS) ? "BUS" : "TROLLEYBUS";
    std::string transportTable = (transportType == BUS) ? "bus" : "trolleybus";
    std::string transportIdColumn = (transportType == BUS) ? "bus_id" : "trolleybus_id";
    std::string checkTransportQuery = "SELECT EXISTS(SELECT 1 FROM " + transportTable +
                                      " WHERE " + transportIdColumn + " = " + std::to_string(transportId) + ");";
    auto transportExists = Db.executeQuery(checkTransportQuery);
    if (transportExists.empty() || !transportExists[0][0].as<bool>()) {
        std::cerr << "Transport ID does not exist in the database." << std::endl;
        return;
    }

    std::string checkQuery = "SELECT 1 FROM TransportRoute WHERE route_id = " + std::to_string(routeId) +
                             " AND transport_type = '" + transportTypeStr + "' AND transport_id = " +
                             std::to_string(transportId);
    auto checkResult = Db.executeQuery(checkQuery);
    if (checkResult.empty()) {
        std::cerr << "Transport isn't linked to route!" << std::endl;
        return;
    }

    try {
        std::string deleteQuery = "DELETE FROM TransportRoute WHERE transport_type = '" + transportTypeStr +
                                  "' AND transport_id = " + std::to_string(transportId);
        Db.executeQuery(deleteQuery);
        std::cout << "Transport unlinked from route successfully." << std::endl;
    } catch (const pqxx::unique_violation &e) {
        std::cerr << "Error: Transport is not linked to this route." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

}

