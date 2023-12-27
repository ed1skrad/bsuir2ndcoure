#include "Route.h"

Route::Route() : routeId(0) {}

Route::Route(int routeId, const std::string& routeName, const std::vector<Stop>& routeStops)
        : routeId(routeId), routeName(routeName), stops(routeStops) {}

int Route::getRouteId(){ return routeId; }
std::string Route::getRouteName(){ return routeName; }
std::vector<Stop> Route::getStops(){ return stops; }

void Route::setRouteId(int routeId) {
    this->routeId = routeId;
}
void Route::setRouteName(std::string routeName) {
    this->routeName = routeName;
}
void Route::setStops(std::vector<Stop> stops) {
    this->stops = stops;
}

void Route::getStopsForRoute(Database& db, int routeId) {
    std::cout << "Attempting to get stops for Route ID: " << routeId << std::endl;

    pqxx::result routeCheck = db.executeQuery("SELECT route_id FROM Route WHERE route_id = " + std::to_string(routeId));
    if (routeCheck.empty()) {
        std::cout << "Route ID: " << routeId << " does not exist in the Route table." << std::endl;
        return;
    }

    pqxx::result routeStopCheck = db.executeQuery("SELECT stop_id FROM RouteStop WHERE route_id = " + std::to_string(routeId));
    if (routeStopCheck.empty()) {
        std::cout << "No stops are linked to Route ID: " << routeId << " in the RouteStop table." << std::endl;
        return;
    }

    try {
        pqxx::result result = db.executeQuery("SELECT s.stop_name, s.address "
                                              "FROM Stop s "
                                              "JOIN RouteStop rs ON s.stop_id = rs.stop_id "
                                              "WHERE rs.route_id = " + std::to_string(routeId));

        if (!result.empty()) {
            for (const auto& row : result) {
                std::cout << "Stop Name: " << row[0].as<std::string>() << ", Address: " << row[1].as<std::string>() << std::endl;
            }
        } else {
            std::cout << "No stops found for the specified route." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

//INNER JOIN
void Route::getRoutesForTransport(Database& db, int transportId, PublicTransport::TransportType transportType) {
    std::string transportTypeName = (transportType == PublicTransport::TransportType::BUS) ? "BUS" : "TROLLEYBUS";
    std::cout << "Attempting to get routes for Transport: " << transportTypeName << " with ID: " << transportId << std::endl;

    try {
        pqxx::result result = db.executeQuery(
                // Выборка route_id и route_name из таблицы Route
                "SELECT r.route_id, r.route_name "
                "FROM Route r "
                // Присоединение результатов подзапроса, который выбирает route_id из таблицы TransportRoute
                // где transport_id и transport_type соответствуют переданным в функцию значениям
                "JOIN (SELECT route_id FROM TransportRoute WHERE transport_id = " +
                std::to_string(transportId) +
                " AND transport_type = '" + transportTypeName + "') tr ON r.route_id = tr.route_id");
                /*
                 * Таким образом, каждая строка в выводе будет содержать route_id и route_name для маршрутов, связанных с указанным транспортом.
                 * Если для данного транспорта не найдено ни одного маршрута, то результат будет пустым.
                 */
        if (!result.empty()) {
            for (const auto& row : result) {
                std::cout << "Route ID: " << row[0].as<int>() << ", Route Name: " << row[1].as<std::string>() << std::endl;
            }
        } else {
            std::cout << "No routes found for the specified transport." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Route::displayAllRoutes(Database& db) {
    try {
        pqxx::result result = db.executeQuery("SELECT * FROM Route");

        if (!result.empty()) {
            std::cout << "All Routes:" << std::endl;
            for (const auto& row : result) {
                int routeId = row[0].as<int>();
                std::string routeName = row[1].as<std::string>();

                std::cout << "Route ID: " << routeId << ", Route Name: " << routeName << std::endl;

                std::cout << std::endl;
            }
        } else {
            std::cout << "No routes found in the database." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

