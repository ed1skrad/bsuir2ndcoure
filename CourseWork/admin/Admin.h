#ifndef COURSEWORK_ADMIN_H
#define COURSEWORK_ADMIN_H


#include <iostream>
#include <pqxx/pqxx>
#include <stdexcept>
#include "../database/Database.h"
#include "../models/Taxi.h"
#include "../models/Bus.h"
#include "../models/Trolleybus.h"

class Admin {
private:
    int admin_id;
    std::string username;
    std::string hashed_password;
    Database& db;

    std::string hashPassword(const std::string& password) {
        std::string hashed;
        for (char c : password) {
            hashed += std::to_string((c + 3) % 256);
        }
        return hashed;
    }

public:
    Admin(Database& db, const std::string& username, const std::string& password)
            : db(db), username(username), hashed_password(hashPassword(password)) {}
    bool login() {
        std::string query = "SELECT admin_id FROM Admins WHERE username = '" + username + "' AND password = '" + hashed_password + "'";
        pqxx::result result = db.executeQuery(query);
        if (!result.empty()) {
            admin_id = result[0]["admin_id"].as<int>();
            std::cout << "Login successful for admin ID: " << admin_id << std::endl;
            return true;
        } else {
            std::cout << "Login failed for username: " << username << std::endl;
            return false;
        }
    }

    std::string engineTypeToString(EngineType engineType) {
        switch (engineType) {
            case EngineType::DIESEL:
                return "DIESEL";
            case EngineType::PETROL:
                return "PETROL";
            case EngineType::ELECTRIC:
                return "ELECTRIC";
            case EngineType::HYBRID:
                return "HYBRID";
            default:
                return "UNKNOWN";
        }
    }


    bool registerAdmin(Database& db, const std::string& username, const std::string& password) {

        std::string hashed_password;
        for (char c : password) {
            hashed_password += std::to_string((c + 3) % 256);
        }

        std::string query = "INSERT INTO Admins (username, password) VALUES ('"
                            + username + "', '" + hashed_password + "')";

        try {
            db.executeQuery(query);
            std::cout << "Admin registered successfully." << std::endl;
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Error registering admin: " << e.what() << std::endl;
            return false;
        }
    }

    void addBus(const std::string &brand, const std::string &model, const std::string &color, EngineType engineType, int capacity, bool has_contactless_payment, int isLogged) {
        if (!isLogged) {
            std::cerr << "Error: You must be logged in as an admin to add a bus." << std::endl;
            return;
        }
        std::string query = "INSERT INTO bus (brand, model, color, engineType, capacity, has_contactless_payment) VALUES ('"
                            + brand + "', '" + model + "', '" + color + "', '" + engineTypeToString(engineType) + "', "
                            + std::to_string(capacity) + ", " + (has_contactless_payment ? "TRUE" : "FALSE") + ")";
        try {
            db.executeQuery(query);
            std::cout << "Bus added successfully." << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error adding bus: " << e.what() << std::endl;
        }
    }

    void addTrolleyBus(const std::string &brand, const std::string &model, const std::string &color, EngineType engineType, int capacity, bool has_sockets, int isLogged) {
        if (!isLogged) {
            std::cerr << "Error: You must be logged in as an admin to add a trolleybus." << std::endl;
            return;
        }
        std::string query = "INSERT INTO trolleybus (brand, model, color, engineType, capacity, has_sockets) VALUES ('"
                            + brand + "', '" + model + "', '" + color + "', '" + engineTypeToString(engineType) + "', "
                            + std::to_string(capacity) + ", " + (has_sockets ? "TRUE" : "FALSE") + ")";
        try {
            db.executeQuery(query);
            std::cout << "TrolleyBus added successfully." << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error adding trolleybus: " << e.what() << std::endl;
        }
    }

    void addTaxi(const std::string& brand, const std::string& model, const std::string& color, const std::string& engineType, double pricePerKilometer, bool hasDriver, bool hasWiFi, bool hasChildSeat, RentCarTypes rentCarTypes, int isLogged) {
        if (!isLogged) {
            std::cerr << "Error: You must be logged in as an admin to add a taxi." << std::endl;
            return;
        }


        std::string rentCarTypeStr;
        switch (rentCarTypes) {
            case ECONOMY: rentCarTypeStr = "ECONOMY"; break;
            case COMFORT: rentCarTypeStr = "COMFORT"; break;
            case BUSINESS: rentCarTypeStr = "BUSINESS"; break;
            default: rentCarTypeStr = "UNKNOWN"; break;
        }

        std::string query = "INSERT INTO taxi (brand, model, color, engineType, price_per_kil, has_driver, has_wifi, has_child_seat, rent_car_type) VALUES ('"
                            + brand + "', '" + model + "', '" + color + "', '" + engineType + "', " + std::to_string(pricePerKilometer) + ", "
                            + (hasDriver ? "TRUE" : "FALSE") + ", " + (hasWiFi ? "TRUE" : "FALSE") + ", " + (hasChildSeat ? "TRUE" : "FALSE") + ", '"
                            + rentCarTypeStr + "')";
        try {
            db.executeQuery(query);
            std::cout << "Taxi added successfully." << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error adding taxi: " << e.what() << std::endl;
        }
    }


    void addStop(const std::string& stop_name, const std::string& address, int isLogged) {
        if (!isLogged) {
            std::cerr << "Error: You must be logged in as an admin to add a taxi." << std::endl;
            return;
        }
        std::string query = "INSERT INTO Stop (stop_name, address) VALUES ('"
                            + stop_name + "', '" + address + "')";
        try {
            db.executeQuery(query);
            std::cout << "Stop added successfully." << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error adding stop: " << e.what() << std::endl;
        }
    }

    void addRoute(const std::string& route_name) {
        std::string query = "INSERT INTO Route (route_name) VALUES ('"
                            + route_name + "')";
        try {
            db.executeQuery(query);
            std::cout << "Route added successfully." << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error adding route: " << e.what() << std::endl;
        }
    }

    void addSchedule(int transport_id, const std::string& transport_type, int route_id, int stop_id, const std::string& arrival_time) {
        std::string query = "INSERT INTO TransportSchedule (transport_type, transport_id, route_id, stop_id, arrival_time) VALUES ('"
                            + transport_type + "', " + std::to_string(transport_id) + ", " + std::to_string(route_id) + ", "
                            + std::to_string(stop_id) + ", '" + arrival_time + "')";
        try {
            db.executeQuery(query);
            std::cout << "Schedule added successfully." << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error adding schedule: " << e.what() << std::endl;
        }
    }

    void setRoutePrice(int route_id, double price) {
        std::string query = "INSERT INTO RoutePrice (route_id, price) VALUES ("
                            + std::to_string(route_id) + ", " + std::to_string(price) + ")";
        try {
            db.executeQuery(query);
            std::cout << "Route price set successfully." << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error setting route price: " << e.what() << std::endl;
        }
    }

    bool adminLogin(Database& db, const std::string& username, const std::string& password) {
        Admin admin(db, username, password);
        return admin.login();
    }

};


#endif //COURSEWORK_ADMIN_H
