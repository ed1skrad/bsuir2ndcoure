#include <string>
#include <iostream>
#include "pqxx/pqxx"

using namespace std;

class Customer {
private:
    int customer_id;
    std::string name;
    std::string surname;
    std::string contact_information;

public:
    Customer() {
        customer_id = 0;
    }

    int getCustomerId() const { return customer_id; }
    void setCustomerId(int id) { customer_id = id; }

    const std::string& getName() const { return name; }
    void setName(const std::string& n) { name = n; }

    const std::string& getSurname() const { return surname; }
    void setSurname(const std::string& s) { surname = s; }

    const std::string& getContactInformation() const { return contact_information; }
    void setContactInformation(const std::string& info) { contact_information = info; }
};

class Orders {
private:
    int order_id;
    int customer_id;
    int car_id;
    std::string order_time;

public:
    Orders() : order_id(0), customer_id(0), car_id(0), order_time(getCurrentTime()) {}

    Orders(int order_id, int customer_id, int car_id, const std::string& order_time)
            : order_id(order_id), customer_id(customer_id), car_id(car_id), order_time(order_time) {}

    int getOrderId() const { return order_id; }
    void setOrderId(int id) { order_id = id; }

    int getCustomerId() const { return customer_id; }
    void setCustomerId(int id) { customer_id = id; }

    int getCarId() const { return car_id; }
    void setCarId(int id) { car_id = id; }

    const std::string& getOrderTime() const { return order_time; }
    void setOrderTime(const std::string& time) { order_time = time; }

    std::string getCurrentTime() const {
        auto now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::ctime(&currentTime);
        return ss.str();
    }
};

enum EngineType
{
    PETROL,
    DIESEL,
    HYBRID,
    ELECTRIC
};

class Transport{
private:
    std::string brand;
    std::string model;
    std::string color;
    EngineType engineType;

public:
    Transport(std::string brand, std::string model, std::string color, EngineType engineType) : brand(brand), model(model), color(color), engineType(engineType) {}
    ~Transport() {}

    std::string getBrand() { return brand; }
    void setBrand(std::string brand) { this->brand = brand; }

    std::string getModel() { return model; }
    void setModel(std::string model) { this->model = model; }

    std::string getColor() { return color; }
    void setColor(std::string color) { this->color = color; }

    EngineType getEngineType() { return engineType; }
    void setEngineType(EngineType engineType) { this->engineType = engineType; }

    std::string getEngineTypeString() {
        switch (engineType) {
            case EngineType::PETROL:
                return "PETROL";
            case EngineType::DIESEL:
                return "DIESEL";
            case EngineType::HYBRID:
                return "HYBRID";
            case EngineType::ELECTRIC:
                return "ELECTRIC";
            default:
                return "Unknown";
        }
    }

};

class PublicTransport : public Transport {
private:
    int transport_id;  
    int capacity;
    std::string from;
    std::string to;
    std::string frequency;

public:
    PublicTransport(int transport_id, std::string brand, std::string model, std::string color, EngineType engineType, int capacity, std::string from, std::string to, std::string frequency)
            : Transport(brand, model, color, engineType), transport_id(transport_id), capacity(capacity), from(from), to(to), frequency(frequency) {}

    int gettransport_id() const { return transport_id; }
    void settransport_id(int id) { transport_id = id; }
    ~PublicTransport() {}

    int getCapacity() { return capacity; }
    void setCapacity(int capacity) { this->capacity = capacity; }

    std::string getFrom() { return from; }
    void setFrom(std::string from) { this->from = from; }

    std::string getTo() { return to; }
    void setTo(std::string to) { this->to = to; }

    std::string getFrequency() { return frequency; }
    void setFrequency(std::string frequency) { this->frequency = frequency; }

};

class Bus : public PublicTransport {
private:

    bool has_contactless_payment;

public:
    Bus(int transport_id, std::string brand, std::string model, std::string color, EngineType engineType, int capacity, std::string from, std::string to, std::string frequency, bool has_contactless_payment)
            : PublicTransport(transport_id, brand, model, color, engineType, capacity, from, to, frequency), has_contactless_payment(has_contactless_payment) {}


    bool gethas_contactless_payment() const { return has_contactless_payment; }
    void sethas_contactless_payment(bool has_contactless_payment) { this->has_contactless_payment = has_contactless_payment; }


};

class TrolleyBus : public PublicTransport {
private:
    bool has_sockets;

public:
    TrolleyBus(int transport_id, std::string brand, std::string model, std::string color, EngineType engineType, int capacity, std::string from, std::string to, std::string frequency, bool has_sockets)
            : PublicTransport(transport_id, brand, model, color, engineType, capacity, from, to, frequency), has_sockets(has_sockets) {}


    bool gethas_sockets() const { return has_sockets; }
    void sethas_sockets(bool has_sockets) { this->has_sockets = has_sockets; }
};


enum RentCarTypes{
    ECONOMY,
    COMFORT,
    BUSINESS
};

class Taxi : public Transport {
private:
    int carId;
    double pricePerKil;
    double rating;
    bool hasDriver;
    bool hasWiFi;
    bool hasChildSeat;
    RentCarTypes rentCarTypes;

public:
    Taxi(std::string brand, std::string model, std::string color, EngineType engineType, int carId, double pricePerKil, double rating, bool hasDriver, bool hasWiFi, bool hasChildSeat, RentCarTypes rentCarTypes)
            : Transport(brand, model, color, engineType), carId(carId), pricePerKil(pricePerKil), rating(rating), hasDriver(hasDriver), hasWiFi(hasWiFi), hasChildSeat(hasChildSeat), rentCarTypes(rentCarTypes) {}

    int getCarId() const { return carId; }
    void setCarId(int id) { carId = id; }

    double getPricePerKil() const { return pricePerKil; }
    void setPricePerKil(double pricePerKil) { this->pricePerKil = pricePerKil; }

    double getRating() const { return rating; }
    void setRating(double rating) { this->rating = rating; }

    bool getHasDriver() const { return hasDriver; }
    void setHasDriver(bool hasDriver) { this->hasDriver = hasDriver; }

    bool getHasWiFi() const { return hasWiFi; }
    void setHasWiFi(bool hasWiFi) { this->hasWiFi = hasWiFi; }

    bool getHasChildSeat() const { return hasChildSeat; }
    void setHasChildSeat(bool hasChildSeat) { this->hasChildSeat = hasChildSeat; }

    RentCarTypes getRentCarTypes() const { return rentCarTypes; }
    void setRentCarTypes(RentCarTypes rentCarTypes) { this->rentCarTypes = rentCarTypes; }

    ~Taxi() {
    }
};


class Database {
private:
    pqxx::connection C;

public:
    Database() : C("dbname=CourseWorkDb user=postgres password=aboba hostaddr=127.0.0.1 port=5432") {
        if (C.is_open()) {
            cout << "Opened database successfully: " << C.dbname() << endl;
        } else {
            cout << "Can't open database" << endl;
            throw runtime_error("Failed to open database");
        }
    }

    ~Database() {
    }

    pqxx::result executeQuery(const string& query) {
        pqxx::nontransaction N(C);
        return N.exec(query);
    }
};

EngineType stringToEngineType(const std::string& engineTypeStr) {
    if (engineTypeStr == "PETROL") {
        return EngineType::PETROL;
    } else if (engineTypeStr == "DIESEL") {
        return EngineType::DIESEL;
    } else if (engineTypeStr == "HYBRID") {
        return EngineType::HYBRID;
    } else if (engineTypeStr == "ELECTRIC") {
        return EngineType::ELECTRIC;
    } else {
        throw std::runtime_error("Invalid engine type: " + engineTypeStr);
    }
}

RentCarTypes stringToRentCarTypes(const std::string& rentCarTypesStr) {
    if (rentCarTypesStr == "ECONOMY") {
        return RentCarTypes::ECONOMY;
    } else if (rentCarTypesStr == "COMFORT") {
        return RentCarTypes::COMFORT;
    } else if (rentCarTypesStr == "BUSINESS") {
        return RentCarTypes::BUSINESS;
    } else {
        throw std::runtime_error("Invalid rent car type: " + rentCarTypesStr);
    }
}

void displayTaxiDetails(const pqxx::result::const_iterator& row) {
    int carId = row[0].as<int>();
    string brand = row[1].as<string>();
    string model = row[2].as<string>();
    string color = row[3].as<string>();
    EngineType engineType = stringToEngineType(row["engineType"].as<std::string>());
    double pricePerKil = row[5].as<double>();
    double rating = row[6].as<double>();
    bool hasDriver = row[7].as<bool>();
    bool hasWiFi = row[8].as<bool>();
    bool hasChildSeat = row[9].as<bool>();
    RentCarTypes rentCarTypes = stringToRentCarTypes(row["rent_car_type"].as<std::string>());

    unique_ptr<Taxi> taxi = make_unique<Taxi>(
            brand, model, color,
            static_cast<EngineType>(engineType),
            carId, pricePerKil, rating,
            hasDriver, hasWiFi, hasChildSeat,
            static_cast<RentCarTypes>(rentCarTypes)
    );

    cout << "Taxi Details:" << endl;
    cout << "Car ID: " << taxi->getCarId() << endl;
    cout << "Brand: " << taxi->getBrand() << endl;
    cout << "Model: " << taxi->getModel() << endl;
    cout << "Color: " << taxi->getColor() << endl;
    cout << "Engine Type: " << taxi->getEngineTypeString() << endl;
    cout << "Price per Kilometer: " << taxi->getPricePerKil() << endl;
    cout << "Rating: " << taxi->getRating() << endl;
    cout << "Has Driver: " << (taxi->getHasDriver() ? "Yes" : "No") << endl;
    cout << "Has WiFi: " << (taxi->getHasWiFi() ? "Yes" : "No") << endl;
    cout << "Has Child Seat: " << (taxi->getHasChildSeat() ? "Yes" : "No") << endl;
    cout << "Rent Car Type: " << taxi->getRentCarTypes() << endl;
    cout << endl;
}

void displayAllTaxis(Database& Db) {
    try {
        pqxx::result R = Db.executeQuery("SELECT * FROM taxi");
        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            displayTaxiDetails(c);
        }
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
    }
}

void displayBusDetails(const pqxx::result::const_iterator& row) {
    // Parse the row and create a Bus object
    int transport_id = row["bus_id"].as<int>();
    int capacity = row["capacity"].as<int>();
    string brand = row["brand"].as<string>();
    string model = row["model"].as<string>();
    string color = row["color"].as<string>();
    EngineType engineType = stringToEngineType(row["engineType"].as<std::string>());
    string from = row["from_location"].as<string>();
    string to = row["to_location"].as<string>();
    string frequency = row["frequency"].as<string>();
    bool has_contactless_payment = row["has_contactless_payment"].as<bool>();

    unique_ptr<Bus> bus = make_unique<Bus>(
            transport_id, brand, model, color,
            static_cast<EngineType>(engineType),
            capacity, from, to, frequency,
            has_contactless_payment
    );

    cout << "Bus Details:" << endl;
    cout << "Transport ID: " << bus->gettransport_id() << endl;
    cout << "Brand: " << bus->getBrand() << endl;
    cout << "Model: " << bus->getModel() << endl;
    cout << "Color: " << bus->getColor() << endl;
    cout << "Engine Type: " << bus->getEngineTypeString() << endl;
    cout << "Capacity: " << bus->getCapacity() << endl;
    cout << "From: " << bus->getFrom() << endl;
    cout << "To: " << bus->getTo() << endl;
    cout << "Frequency: " << bus->getFrequency() << endl;
    cout << "Has Contactless Payment: " << (bus->gethas_contactless_payment() ? "Yes" : "No") << endl;
    cout << endl;
}

void displayTrolleyBusDetails(const pqxx::result::const_iterator& row) {
    int transport_id = row["trolleybus_id"].as<int>();
    int capacity = row["capacity"].as<int>();
    string brand = row["brand"].as<string>();
    string model = row["model"].as<string>();
    string color = row["color"].as<string>();
    EngineType engineType = stringToEngineType(row["engineType"].as<std::string>());
    string from = row["from_location"].as<string>();
    string to = row["to_location"].as<string>();
    string frequency = row["frequency"].as<string>();
    bool has_sockets = row["has_sockets"].as<bool>();

    unique_ptr<TrolleyBus> trolleyBus = make_unique<TrolleyBus>(
            transport_id, brand, model, color,
            static_cast<EngineType>(engineType),
            capacity, from, to, frequency,
            has_sockets
    );

    cout << "TrolleyBus Details:" << endl;
    cout << "Transport ID: " << trolleyBus->gettransport_id() << endl;
    cout << "Brand: " << trolleyBus->getBrand() << endl;
    cout << "Model: " << trolleyBus->getModel() << endl;
    cout << "Color: " << trolleyBus->getColor() << endl;
    cout << "Engine Type: " << trolleyBus->getEngineTypeString() << endl;
    cout << "Capacity: " << trolleyBus->getCapacity() << endl;
    cout << "From: " << trolleyBus->getFrom() << endl;
    cout << "To: " << trolleyBus->getTo() << endl;
    cout << "Frequency: " << trolleyBus->getFrequency() << endl;
    cout << "Has Sockets: " << (trolleyBus->gethas_sockets() ? "Yes" : "No") << endl;
    cout << endl;
}
void displayAllBuses(Database& Db) {
    try {
        pqxx::result busResult = Db.executeQuery("SELECT * FROM bus");
        cout << "Displaying Bus Details:" << endl;
        for (const auto& row : busResult) {
            displayBusDetails(row);
        }
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
    }
}

void displayAllTrolleyBuses(Database& Db) {
    try {
        pqxx::result trolleyBusResult = Db.executeQuery("SELECT * FROM trolleybus");
        cout << "Displaying TrolleyBus Details:" << endl;
        for (const auto& row : trolleyBusResult) {
            displayTrolleyBusDetails(row);
        }
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
    }
}

enum TransportType {
    BUS,
    TROLLEYBUS
};

class TransportTicket {
private:
    int ticket_id;
    int transport_id;
    int customerId;
    double price;
    std::string purchaseTime;
    TransportType transportType;

public:
    TransportTicket(int ticket_id, int transport_id, int customerId, double price, std::string purchaseTime, TransportType transportType)
            : ticket_id(ticket_id), customerId(customerId), price(price), purchaseTime(purchaseTime), transportType(transportType) {
        if (transportType == TransportType::BUS) {
            this->transport_id = transport_id * 10 + static_cast<int>(TransportType::BUS);
        } else if (transportType == TransportType::TROLLEYBUS) {
            this->transport_id = transport_id * 10 + static_cast<int>(TransportType::TROLLEYBUS);
        } else {
            throw std::invalid_argument("Invalid transport type");
        }
    }

    TransportTicket() : ticket_id(0), transport_id(0), customerId(0), price(0.0), purchaseTime(""), transportType(TransportType::BUS) {}


    int getticket_id() const {
        return ticket_id;
    }

    int gettransport_id() const {
        return transport_id;
    }

    int getCustomerId() const {
        return customerId;
    }

    double getPrice() const {
        return price;
    }

    std::string getPurchaseTime() const {
        return purchaseTime;
    }

    TransportType getTransportType() const {
        return transportType;
    }

    void setCustomerId(int customerId) {
        TransportTicket::customerId = customerId;
    }

    void settransport_id(int transport_id) {
        TransportTicket::transport_id = transport_id;
    }

    void displayTicketInfo() const {
        std::cout << "Ticket ID: " << getticket_id() << std::endl;
        std::cout << "Transport ID: " << gettransport_id() << std::endl;
        std::cout << "Customer ID: " << getCustomerId() << std::endl;
        std::cout << "Price: " << getPrice() << std::endl;
        std::cout << "Purchase Time: " << getPurchaseTime() << std::endl;
        std::cout << "Transport Type: " << (getTransportType() == TransportType::BUS ? "Bus" : "Trolleybus") << std::endl;
        std::cout << std::endl;
    }
};

std::string getCurrentTimestampAsString() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::ctime(&currentTime);
    return ss.str();
}

class TicketPrice {
private:
    int id;
    double price;

public:
    TicketPrice(int id, double price) : id(id), price(price) {}

    int getId() const { return id; }
    double getPrice() const { return price; }
};


class TicketManager {
private:
    pqxx::connection C;

public:
    TicketManager() : C("dbname=CourseWorkDb user=postgres password=aboba hostaddr=127.0.0.1 port=5432") {
        if (C.is_open()) {
            std::cout << "Opened database successfully: " << C.dbname() << std::endl;
        } else {
            std::cout << "Can't open database" << std::endl;
            throw std::runtime_error("Failed to open database");
        }
    }

    ~TicketManager() {
    }

    pqxx::result executeQuery(const std::string& query) {
        pqxx::nontransaction N(C);
        return N.exec(query);
    }

    int insertTicket(const TransportTicket& ticket) {
        try {
            pqxx::work W(C);

            std::string currentTimestamp = getCurrentTimestampAsString();

            std::string insertQuery = "INSERT INTO ticket (transport_id, customer_id, price, purchase_time, transport_type) VALUES ("
                                      + std::to_string(ticket.gettransport_id()) + ", "
                                      + std::to_string(ticket.getCustomerId()) + ", "
                                      + std::to_string(ticket.getPrice()) + ", '"
                                      + currentTimestamp + "', '"
                                      + (ticket.getTransportType() == TransportType::BUS ? "BUS" : "TROLLEYBUS") + "') RETURNING ticket_id";

            pqxx::result ticket_idResult = W.exec(insertQuery);
            int ticket_id = ticket_idResult[0]["ticket_id"].as<int>();

            W.commit();

            return ticket_id;
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            throw std::runtime_error("Failed to insert ticket into the database");
        }
    }


    void displayAllTickets() {
        try {
            pqxx::result R = executeQuery("SELECT * FROM ticket");

            for (const auto& row : R) {
                displayTicketDetails(row);
            }
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            throw std::runtime_error("Failed to display tickets from the database");
        }
    }

private:
    void displayTicketDetails(const pqxx::result::const_iterator& row) {
        int ticket_id = row["ticket_id"].as<int>();
        int transport_id = row["transport_id"].as<int>();
        int customerId = row["customer_id"].as<int>();
        double price = row["price"].as<double>();
        std::string purchaseTime = row["purchase_time"].as<std::string>();
        std::string transportTypeStr = row["transport_type"].as<std::string>();

        TransportType transportType;
        if (transportTypeStr == "BUS") {
            transportType = TransportType::BUS;
        } else if (transportTypeStr == "TROLLEYBUS") {
            transportType = TransportType::TROLLEYBUS;
        } else {
            throw std::runtime_error("Invalid transport type in the database");
        }

        TransportTicket ticket(ticket_id, transport_id, customerId, price, purchaseTime, transportType);
        ticket.displayTicketInfo();
    }
};

void isIdValid(int& id, const std::string& transportName, Database* Db) {
    while (true) {
        try {
            std::cout << "Enter the " << transportName << " ID: ";
            std::cin >> id;

            std::string checkQuery = "SELECT * FROM " + transportName + " WHERE " + transportName + "_id = " + std::to_string(id);
            pqxx::result result = Db->executeQuery(checkQuery);

            if (!result.empty()) {
                return;
            } else {
                std::cerr << transportName << " with entered value does not exist. Try again." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

class Stop {
private:
    int stop_id;
    int trolleybus_id;
    int bus_id;
    std::string stop_name;
    std::string address;

public:
    Stop(int stopId, int trolleybusId, int busId, const std::string& stopName, const std::string& stopAddress)
            : stop_id(stopId), trolleybus_id(trolleybusId), bus_id(busId), stop_name(stopName), address(stopAddress) {}

    int getStopId() const { return stop_id; }
    int getTrolleybusId() const { return trolleybus_id; }
    int getBusId() const { return bus_id; }
    const std::string& getStopName() const { return stop_name; }
    const std::string& getAddress() const { return address; }

    void setStopId(int stopId) { stop_id = stopId; }
    void setTrolleybusId(int trolleybusId) { trolleybus_id = trolleybusId; }
    void setBusId(int busId) { bus_id = busId; }
    void setStopName(const std::string& stopName) { stop_name = stopName; }
    void setAddress(const std::string& stopAddress) { address = stopAddress; }
};

class Route {
private:
    int route_id;
    std::string route_name;
    int trolleybus_id;
    int bus_id;
    std::vector<Stop> stops;

public:
    Route(int routeId, const std::string& routeName, int trolleybusId, int busId, const std::vector<Stop>& routeStops)
            : route_id(routeId), route_name(routeName), trolleybus_id(trolleybusId), bus_id(busId), stops(routeStops) {}

    int getRouteId() const { return route_id; }
    const std::string& getRouteName() const { return route_name; }
    int getTrolleybusId() const { return trolleybus_id; }
    int getBusId() const { return bus_id; }
    const std::vector<Stop>& getStops() const { return stops; }

    void setRouteId(int routeId) { route_id = routeId; }
    void setRouteName(const std::string& routeName) { route_name = routeName; }
    void setTrolleybusId(int trolleybusId) { trolleybus_id = trolleybusId; }
    void setBusId(int busId) { bus_id = busId; }
    void setStops(const std::vector<Stop>& routeStops) { stops = routeStops; }

};

class RouteStop {
private:
    int route_id;
    int stop_id;

public:
    RouteStop(int routeId, int stopId) : route_id(routeId), stop_id(stopId) {}

    int getRouteId() const { return route_id; }
    int getStopId() const { return stop_id; }

    void setRouteId(int routeId) { route_id = routeId; }
    void setStopId(int stopId) { stop_id = stopId; }
};

std::vector<Route> getAllRoutesForBus(int busId, Database &Db) {
    std::vector<Route> routes;
    std::string query = "SELECT r.* FROM Route r JOIN RouteStop rs ON r.route_id = rs.route_id JOIN Stop s ON rs.stop_id = s.stop_id WHERE s.bus_id = " + std::to_string(busId);


    pqxx::result result = Db.executeQuery(query);

    for (auto row : result) {
        int routeId = row["route_id"].as<int>();
        std::string routeName = row["route_name"].as<std::string>();
        int trolleybusId = row["trolleybus_id"].as<int>();
        int busId = row["bus_id"].as<int>();
        std::vector<Stop> stops; // Здесь вы можете добавить логику для получения списка остановок для каждого маршрута
        routes.push_back(Route(routeId, routeName, trolleybusId, busId, stops));
    }

    return routes;
}

std::vector<Stop> getStopsForRoute(int routeId, Database &Db) {
    std::vector<Stop> stops;
    std::string query = "SELECT s.* FROM Stop s JOIN RouteStop rs ON s.stop_id = rs.stop_id WHERE rs.route_id = " + std::to_string(routeId);
    pqxx::result result = Db.executeQuery(query);

    for (auto row : result) {
        int stopId = row["stop_id"].as<int>();
        std::string stopName = row["stop_name"].as<std::string>();
        int trolleybusId = row["trolleybus_id"].as<int>();
        int busId = row["bus_id"].as<int>();
        std::string address = row["address"].as<std::string>();
        stops.push_back(Stop(stopId, trolleybusId, busId, stopName, address));
    }

    return stops;
}

std::vector<Stop> getAllStopsForTrolleybus(int trolleybusId, Database &Db) {
    std::vector<Stop> stops;
    std::string query = "SELECT s.* FROM Stop s JOIN RouteStop rs ON s.stop_id = rs.stop_id JOIN Trolleybus t ON rs.trolleybus_id = t.trolleybus_id WHERE t.trolleybus_id = " + std::to_string(trolleybusId);
    pqxx::result result = Db.executeQuery(query);

    for (auto row : result) {
        int stopId = row["stop_id"].as<int>();
        std::string stopName = row["stop_name"].as<std::string>();
        int trolleybusId = row["trolleybus_id"].as<int>();
        int busId = row["bus_id"].as<int>();
        std::string address = row["address"].as<std::string>();
        stops.push_back(Stop(stopId, trolleybusId, busId, stopName, address));
    }

    return stops;
}

std::vector<Stop> getAllStopsForBus(int busId, Database &Db) {
    std::vector<Stop> stops;
    std::string query = "SELECT s.* FROM Stop s JOIN RouteStop rs ON s.stop_id = rs.stop_id JOIN Bus b ON rs.bus_id = b.bus_id WHERE b.bus_id = " + std::to_string(busId);
    pqxx::result result = Db.executeQuery(query);

    for (auto row : result) {
        int stopId = row["stop_id"].as<int>();
        std::string stopName = row["stop_name"].as<std::string>();
        int trolleybusId = row["trolleybus_id"].as<int>();
        int busId = row["bus_id"].as<int>();
        std::string address = row["address"].as<std::string>();
        stops.push_back(Stop(stopId, trolleybusId, busId, stopName, address));
    }

    return stops;
}

std::vector<Route> getAllRoutesForTrolleybus(int trolleybusId, Database &Db) {
    std::vector<Route> routes;
    std::string query = "SELECT r.* FROM Route r JOIN RouteStop rs ON r.route_id = rs.route_id JOIN Trolleybus t ON rs.trolleybus_id = t.trolleybus_id WHERE t.trolleybus_id = " + std::to_string(trolleybusId);
    pqxx::result result = Db.executeQuery(query);

    for (auto row : result) {
        int routeId = row["route_id"].as<int>();
        std::string routeName = row["route_name"].as<std::string>();
        int trolleybusId = row["trolleybus_id"].as<int>();
        int busId = row["bus_id"].as<int>();
        std::vector<Stop> stops = getStopsForRoute(routeId, Db);
        routes.push_back(Route(routeId, routeName, trolleybusId, busId, stops));
    }

    return routes;
}

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
                displayAllTaxis(Db);
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
                getAllRoutesForBus(1, Db);
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

