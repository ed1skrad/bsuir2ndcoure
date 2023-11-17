#include <string>
#include <iostream>
#include "pqxx/pqxx"
#include <ctime>

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
    Orders() : order_id(0), customer_id(0), car_id(0), order_time("") {}

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

class PublicTransport : public Transport{
private:
    int capacity;
    std::string from;
    std::string to;
    std::string frequency;

public:
    PublicTransport(std::string brand, std::string model, std::string color, EngineType engineType, int capacity, std::string from, std::string to, std::string frequency)
            : Transport(brand, model, color, engineType), capacity(capacity), from(from), to(to), frequency(frequency) {}
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

class Bus : public PublicTransport{
private:
    bool hasContactlessPayment;

public:
    Bus(std::string brand, std::string model, std::string color, EngineType engineType, int capacity, std::string from, std::string to, std::string frequency, bool hasContactlessPayment)
            : PublicTransport(brand, model, color, engineType, capacity, from, to, frequency), hasContactlessPayment(hasContactlessPayment) {}

    bool getHasContactlessPayment() { return hasContactlessPayment; }
    void setHasContactlessPayment(bool hasContactlessPayment) { this->hasContactlessPayment = hasContactlessPayment; }
};

class TrolleyBus : public PublicTransport{
private:
    bool hasSockets;

public:
    TrolleyBus(std::string brand, std::string model, std::string color, EngineType engineType, int capacity, std::string from, std::string to, std::string frequency, bool hasSockets)
            : PublicTransport(brand, model, color, engineType, capacity, from, to, frequency), hasSockets(hasSockets) {}

    bool getHasSockets() { return hasSockets; }
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

    // Деструктор
    ~Taxi() {
        // Возможно, здесь потребуется дополнительная логика освобождения ресурсов
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
            // You might want to handle this error case more gracefully
            throw runtime_error("Failed to open database");
        }
    }

    ~TaxiDatabase() {
        //here disconnect
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

    // Create Taxi object
    unique_ptr<Taxi> taxi = make_unique<Taxi>(
            brand, model, color,
            static_cast<EngineType>(engineType),
            carId, pricePerKil, rating,
            hasDriver, hasWiFi, hasChildSeat,
            static_cast<RentCarTypes>(rentCarTypes)
    );

    // Output taxi details
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

        // Loop through the result set and display taxi details
        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            displayTaxiDetails(c);
        }
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
        // Handle the exception appropriately
    }
}

void displayBusDetails(const pqxx::result::const_iterator& row) {
    // Parse the row and create a Bus object
    int capacity = row["capacity"].as<int>();
    string brand = row["brand"].as<string>();
    string model = row["model"].as<string>();
    string color = row["color"].as<string>();
    EngineType engineType = stringToEngineType(row["engineType"].as<std::string>());
    string from = row["from"].as<string>();
    string to = row["to"].as<string>();
    string frequency = row["frequency"].as<string>();
    bool hasContactlessPayment = row["has_contactless_payment"].as<bool>();

    unique_ptr<Bus> bus = make_unique<Bus>(
            brand, model, color,
            static_cast<EngineType>(engineType),
            capacity, from, to, frequency,
            hasContactlessPayment
    );

    // Output bus details
    cout << "Bus Details:" << endl;
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
    // Parse the row and create a TrolleyBus object
    int capacity = row["capacity"].as<int>();
    string brand = row["brand"].as<string>();
    string model = row["model"].as<string>();
    string color = row["color"].as<string>();
    EngineType engineType = stringToEngineType(row["engineType"].as<std::string>());
    string from = row["from"].as<string>();
    string to = row["to"].as<string>();
    string frequency = row["frequency"].as<string>();
    bool hasSockets = row["has_sockets"].as<bool>();

    unique_ptr<TrolleyBus> trolleyBus = make_unique<TrolleyBus>(
            brand, model, color,
            static_cast<EngineType>(engineType),
            capacity, from, to, frequency,
            hasSockets
    );

    // Output trolley bus details
    cout << "TrolleyBus Details:" << endl;
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
        // Handle the exception appropriately
    }
}

void displayAllTrolleyBuses(TaxiDatabase& taxiDb) {
    try {
        // Query for trolleybuses
        pqxx::result trolleyBusResult = taxiDb.executeQuery("SELECT * FROM trolleybus");
        cout << "Displaying TrolleyBus Details:" << endl;
        for (const auto& row : trolleyBusResult) {
            displayTrolleyBusDetails(row);
        }
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
        // Handle the exception appropriately
    }
}

int main() {
    try {
        TaxiDatabase taxiDb;
        displayAllTaxis(taxiDb);
        displayAllBuses(taxiDb);
        displayAllTrolleyBuses(taxiDb);
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}