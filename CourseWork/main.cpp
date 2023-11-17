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
    int total_requests_value;

public:
    Customer() {
        customer_id = 0;
        total_requests_value = 0;
    }

    int getCustomerId() const { return customer_id; }
    void setCustomerId(int id) { customer_id = id; }

    const std::string& getName() const { return name; }
    void setName(const std::string& n) { name = n; }

    const std::string& getSurname() const { return surname; }
    void setSurname(const std::string& s) { surname = s; }

    const std::string& getContactInformation() const { return contact_information; }
    void setContactInformation(const std::string& info) { contact_information = info; }

    int getTotalRequestsValue() const { return total_requests_value; }
    void setTotalRequestsValue(int value) { total_requests_value = value; }
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
    int transportId;  // Moved from Bus and TrolleyBus
    int capacity;
    std::string from;
    std::string to;
    std::string frequency;

public:
    PublicTransport(int transportId, std::string brand, std::string model, std::string color, EngineType engineType, int capacity, std::string from, std::string to, std::string frequency)
            : Transport(brand, model, color, engineType), transportId(transportId), capacity(capacity), from(from), to(to), frequency(frequency) {}

    int getTransportId() const { return transportId; }
    void setTransportId(int id) { transportId = id; }
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

    bool hasContactlessPayment;

public:
    Bus(int transportId, std::string brand, std::string model, std::string color, EngineType engineType, int capacity, std::string from, std::string to, std::string frequency, bool hasContactlessPayment)
            : PublicTransport(transportId, brand, model, color, engineType, capacity, from, to, frequency), hasContactlessPayment(hasContactlessPayment) {}


    bool getHasContactlessPayment() const { return hasContactlessPayment; }
    void setHasContactlessPayment(bool hasContactlessPayment) { this->hasContactlessPayment = hasContactlessPayment; }


};

class TrolleyBus : public PublicTransport {
private:
    // int trolleybus_id;  // Removed field
    bool hasSockets;

public:
    TrolleyBus(int transportId, std::string brand, std::string model, std::string color, EngineType engineType, int capacity, std::string from, std::string to, std::string frequency, bool hasSockets)
            : PublicTransport(transportId, brand, model, color, engineType, capacity, from, to, frequency), hasSockets(hasSockets) {}


    bool getHasSockets() const { return hasSockets; }
    void setHasSockets(bool hasSockets) { this->hasSockets = hasSockets; }
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


class TaxiDatabase {
private:
    pqxx::connection C;

public:
    TaxiDatabase() : C("dbname=CourseWorkDb user=postgres password=aboba hostaddr=127.0.0.1 port=5432") {
        if (C.is_open()) {
            cout << "Opened database successfully: " << C.dbname() << endl;
        } else {
            cout << "Can't open database" << endl;
            throw runtime_error("Failed to open database");
        }
    }

    ~TaxiDatabase() {
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

void displayAllTaxis(TaxiDatabase& taxiDb) {
    try {
        pqxx::result R = taxiDb.executeQuery("SELECT * FROM taxi");
        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            displayTaxiDetails(c);
        }
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
    }
}

void displayBusDetails(const pqxx::result::const_iterator& row) {
    // Parse the row and create a Bus object
    int transportId = row["bus_id"].as<int>();
    int capacity = row["capacity"].as<int>();
    string brand = row["brand"].as<string>();
    string model = row["model"].as<string>();
    string color = row["color"].as<string>();
    EngineType engineType = stringToEngineType(row["engineType"].as<std::string>());
    string from = row["from_location"].as<string>();
    string to = row["to_location"].as<string>();
    string frequency = row["frequency"].as<string>();
    bool hasContactlessPayment = row["has_contactless_payment"].as<bool>();

    unique_ptr<Bus> bus = make_unique<Bus>(
            transportId, brand, model, color,
            static_cast<EngineType>(engineType),
            capacity, from, to, frequency,
            hasContactlessPayment
    );

    cout << "Bus Details:" << endl;
    cout << "Transport ID: " << bus->getTransportId() << endl;
    cout << "Brand: " << bus->getBrand() << endl;
    cout << "Model: " << bus->getModel() << endl;
    cout << "Color: " << bus->getColor() << endl;
    cout << "Engine Type: " << bus->getEngineTypeString() << endl;
    cout << "Capacity: " << bus->getCapacity() << endl;
    cout << "From: " << bus->getFrom() << endl;
    cout << "To: " << bus->getTo() << endl;
    cout << "Frequency: " << bus->getFrequency() << endl;
    cout << "Has Contactless Payment: " << (bus->getHasContactlessPayment() ? "Yes" : "No") << endl;
    cout << endl;
}

void displayTrolleyBusDetails(const pqxx::result::const_iterator& row) {
    int transportId = row["trolleybus_id"].as<int>();
    int capacity = row["capacity"].as<int>();
    string brand = row["brand"].as<string>();
    string model = row["model"].as<string>();
    string color = row["color"].as<string>();
    EngineType engineType = stringToEngineType(row["engineType"].as<std::string>());
    string from = row["from_location"].as<string>();
    string to = row["to_location"].as<string>();
    string frequency = row["frequency"].as<string>();
    bool hasSockets = row["has_sockets"].as<bool>();

    unique_ptr<TrolleyBus> trolleyBus = make_unique<TrolleyBus>(
            transportId, brand, model, color,
            static_cast<EngineType>(engineType),
            capacity, from, to, frequency,
            hasSockets
    );

    cout << "TrolleyBus Details:" << endl;
    cout << "Transport ID: " << trolleyBus->getTransportId() << endl;
    cout << "Brand: " << trolleyBus->getBrand() << endl;
    cout << "Model: " << trolleyBus->getModel() << endl;
    cout << "Color: " << trolleyBus->getColor() << endl;
    cout << "Engine Type: " << trolleyBus->getEngineTypeString() << endl;
    cout << "Capacity: " << trolleyBus->getCapacity() << endl;
    cout << "From: " << trolleyBus->getFrom() << endl;
    cout << "To: " << trolleyBus->getTo() << endl;
    cout << "Frequency: " << trolleyBus->getFrequency() << endl;
    cout << "Has Sockets: " << (trolleyBus->getHasSockets() ? "Yes" : "No") << endl;
    cout << endl;
}
void displayAllBuses(TaxiDatabase& taxiDb) {
    try {
        // Query for buses
        pqxx::result busResult = taxiDb.executeQuery("SELECT * FROM bus");
        cout << "Displaying Bus Details:" << endl;
        for (const auto& row : busResult) {
            displayBusDetails(row);
        }
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
    }
}

void displayAllTrolleyBuses(TaxiDatabase& taxiDb) {
    try {
        pqxx::result trolleyBusResult = taxiDb.executeQuery("SELECT * FROM trolleybus");
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
    int ticketId;
    int transportId;
    int customerId;
    double price;
    std::string purchaseTime;
    TransportType transportType;

public:
    TransportTicket(int ticketId, int transportId, int customerId, double price, std::string purchaseTime, TransportType transportType)
            : ticketId(ticketId), customerId(customerId), price(price), purchaseTime(purchaseTime), transportType(transportType) {
        if (transportType == TransportType::BUS) {
            this->transportId = transportId * 10 + static_cast<int>(TransportType::BUS);
        } else if (transportType == TransportType::TROLLEYBUS) {
            this->transportId = transportId * 10 + static_cast<int>(TransportType::TROLLEYBUS);
        } else {
            throw std::invalid_argument("Invalid transport type");
        }
    }


    int getTicketId() const {
        return ticketId;
    }

    int getTransportId() const {
        return transportId;
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

    void displayTicketInfo() const {
        std::cout << "Ticket ID: " << getTicketId() << std::endl;
        std::cout << "Transport ID: " << getTransportId() << std::endl;
        std::cout << "Customer ID: " << getCustomerId() << std::endl;
        std::cout << "Price: " << getPrice() << std::endl;
        std::cout << "Purchase Time: " << getPurchaseTime() << std::endl;
        std::cout << "Transport Type: " << (getTransportType() == TransportType::BUS ? "Bus" : "Trolleybus") << std::endl;
        std::cout << std::endl;
    }
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
        // Здесь происходит отключение от базы данных
    }

    pqxx::result executeQuery(const std::string& query) {
        pqxx::nontransaction N(C);
        return N.exec(query);
    }

    void insertTicket(const TransportTicket& ticket) {
        try {
            pqxx::work W(C);
            std::string insertQuery = "INSERT INTO ticket (transport_id, customer_id, price, purchase_time, transport_type) VALUES ("
                                      + std::to_string(ticket.getTransportId()) + ", "
                                      + std::to_string(ticket.getCustomerId()) + ", "
                                      + std::to_string(ticket.getPrice()) + ", '"
                                      + ticket.getPurchaseTime() + "', '"
                                      + (ticket.getTransportType() == TransportType::BUS ? "BUS" : "TROLLEYBUS") + "')";
            W.exec(insertQuery);
            W.commit();
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
        int ticketId = row["ticket_id"].as<int>();
        int transportId = row["transport_id"].as<int>();
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

        TransportTicket ticket(ticketId, transportId, customerId, price, purchaseTime, transportType);
        ticket.displayTicketInfo();
    }
};

int main() {
    try {
        TaxiDatabase taxiDb;

        // Display information about taxis
        cout << "Choose the type of transport:" << endl;
        cout << "1. Taxi" << endl;
        cout << "2. Bus" << endl;
        cout << "3. Trolleybus" << endl;
        cout << "Enter your choice (1/2/3): ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                displayAllTaxis(taxiDb);
                cout << "Do you want to order a taxi? (yes/no): ";
                string orderChoice;
                cin >> orderChoice;

                if (orderChoice == "yes" || orderChoice == "Yes") {
                    // ... (code for ordering a taxi)
                    cout << "Taxi order placed successfully!" << endl;

                    // Declare variables for customer details
                    string name, surname, contactInformation;

                    // Get customer details
                    cout << "Enter your name: ";
                    cin >> name;

                    cout << "Enter your surname: ";
                    cin >> surname;

                    cout << "Enter your contact information: ";
                    cin >> contactInformation;

                    // Add the customer to the database
                    string addCustomerQuery = "INSERT INTO customer (name, surname, contact_information) VALUES ('" +
                                              name + "','" +
                                              surname + "','" +
                                              contactInformation + "')";
                    taxiDb.executeQuery(addCustomerQuery);

                    // Get the customer ID
                    pqxx::result customerIdResult = taxiDb.executeQuery("SELECT MAX(customer_id) FROM customer");
                    int customerId = customerIdResult[0][0].as<int>();

                    // Declare variables for order details
                    int carId;
                    Orders order;

                    // Get order details
                    cout << "Enter the car ID you want to order: ";
                    cin >> carId;

                    order.setCustomerId(customerId);
                    order.setCarId(carId);

                    // Add the order to the database
                    string addOrderQuery = "INSERT INTO orders (customer_id, car_id, order_time) VALUES (" +
                                           to_string(order.getCustomerId()) + "," +
                                           to_string(order.getCarId()) + ",'" +
                                           order.getOrderTime() + "')";
                    taxiDb.executeQuery(addOrderQuery);

                    cout << "Order placed successfully!" << endl;
                }
                break;
            }
            case 2: {
                // Block for displaying bus details
                displayAllBuses(taxiDb);
                cout << "Do you want to book a bus? (yes/no): ";
                string bookChoice;
                cin >> bookChoice;

                if (bookChoice == "yes" || bookChoice == "Yes") {
                    // ... (code for booking a bus)
                    cout << "Bus booked successfully!" << endl;

                    // Declare variables for customer details
                    string name, surname, contactInformation;

                    // Get customer details
                    cout << "Enter your name: ";
                    cin >> name;

                    cout << "Enter your surname: ";
                    cin >> surname;

                    cout << "Enter your contact information: ";
                    cin >> contactInformation;

                    // Add the customer to the database
                    string addCustomerQuery = "INSERT INTO customer (name, surname, contact_information) VALUES ('" +
                                              name + "','" +
                                              surname + "','" +
                                              contactInformation + "') RETURNING customer_id";
                    pqxx::result customerIdResult = taxiDb.executeQuery(addCustomerQuery);
                    int customerId = customerIdResult[0][0].as<int>();

                    // Declare variables for ticket details
                    int busId;
                    TransportTicket ticket;

                    // Get ticket details
                    cout << "Enter the bus ID you want to book: ";
                    cin >> busId;

                    ticket.setTransportId(busId);
                    ticket.setCustomerId(customerId);

                    // Add the ticket to the database
                    string addTicketQuery = "INSERT INTO ticket (transport_id, customer_id, price, purchase_time, transport_type) VALUES (" +
                                            to_string(ticket.getTransportId()) + "," +
                                            to_string(ticket.getCustomerId()) + "," +
                                            to_string(ticket.getPrice()) + ",'" +
                                            ticket.getPurchaseTime() + "','" +
                                            "BUS" + "')";
                    taxiDb.executeQuery(addTicketQuery);

                    cout << "Bus booked successfully!" << endl;
                }
                break;
            }
            case 3: {
                // Block for displaying trolleybus details
                displayAllTrolleyBuses(taxiDb);
                cout << "Do you want to book a trolleybus? (yes/no): ";
                string bookChoice;
                cin >> bookChoice;

                if (bookChoice == "yes" || bookChoice == "Yes") {
                    // ... (code for booking a trolleybus)
                    cout << "Trolleybus booked successfully!" << endl;

                    // Declare variables for customer details
                    string name, surname, contactInformation;

                    // Get customer details
                    cout << "Enter your name: ";
                    cin >> name;

                    cout << "Enter your surname: ";
                    cin >> surname;

                    cout << "Enter your contact information: ";
                    cin >> contactInformation;

                    // Add the customer to the database
                    string addCustomerQuery = "INSERT INTO customer (name, surname, contact_information) VALUES ('" +
                                              name + "','" +
                                              surname + "','" +
                                              contactInformation + "') RETURNING customer_id";
                    pqxx::result customerIdResult = taxiDb.executeQuery(addCustomerQuery);
                    int customerId = customerIdResult[0][0].as<int>();

                    // Declare variables for ticket details
                    int trolleybusId;
                    TransportTicket ticket;

                    // Get ticket details
                    cout << "Enter the trolleybus ID you want to book: ";
                    cin >> trolleybusId;

                    ticket.setTransportId(trolleybusId);
                    ticket.setCustomerId(customerId);

                    // Add the ticket to the database
                    string addTicketQuery = "INSERT INTO ticket (transport_id, customer_id, price, purchase_time, transport_type) VALUES (" +
                                            to_string(ticket.getTransportId()) + "," +
                                            to_string(ticket.getCustomerId()) + "," +
                                            to_string(ticket.getPrice()) + ",'" +
                                            ticket.getPurchaseTime() + "','" +
                                            "TROLLEYBUS" + "')";
                    taxiDb.executeQuery(addTicketQuery);

                    cout << "Trolleybus booked successfully!" << endl;
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

