#include <string>
#include <iostream>
#include "pqxx/pqxx"
#include <ctime>

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

class Order {
private:
    int order_id;
    int customer_id;
    int car_id;
    pqxx::result::const_iterator order_time;

public:
    Order() {
        order_id = 0;
        customer_id = 0;
        car_id = 0;
    }

    int getOrderId() const { return order_id; }
    void setOrderId(int id) { order_id = id; }

    int getCustomerId() const { return customer_id; }
    void setCustomerId(int id) { customer_id = id; }

    int getCarId() const { return car_id; }
    void setCarId(int id) { car_id = id; }

    const pqxx::result::const_iterator& getOrderTime() const { return order_time; }
    void setOrderTime(const pqxx::result::const_iterator& time) { order_time = time; }
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

    void displayInfo() {
        std::cout << "Brand: " << brand << std::endl;
        std::cout << "Model: " << model << std::endl;
        std::cout << "Color: " << color << std::endl;
        std::cout << "Engine Type: " << getEngineTypeString() << std::endl;
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

    void displayInfo() {
        Transport::displayInfo(); // Вывод информации о базовом классе
        std::cout << "Capacity: " << capacity << std::endl;
        std::cout << "From: " << from << std::endl;
        std::cout << "To: " << to << std::endl;
        std::cout << "Frequency: " << frequency << std::endl;
    }
};

class Bus : public PublicTransport{
private:
    bool hasContactlessPayment;

public:
    Bus(std::string brand, std::string model, std::string color, EngineType engineType, int capacity, std::string from, std::string to, std::string frequency, bool hasContactlessPayment)
            : PublicTransport(brand, model, color, engineType, capacity, from, to, frequency), hasContactlessPayment(hasContactlessPayment) {}

    bool getHasContactlessPayment() { return hasContactlessPayment; }
    void setHasContactlessPayment(bool hasContactlessPayment) { this->hasContactlessPayment = hasContactlessPayment; }

    void displayInfo() {
        PublicTransport::displayInfo(); // Вывод информации о базовом классе
        std::cout << "Transport Type: Bus" << std::endl;
        std::cout << "Has Contactless Payment: " << (hasContactlessPayment ? "Yes" : "No") << std::endl;
    }
};

class TrolleyBus : public PublicTransport{
private:
    bool hasSockets;

public:
    TrolleyBus(std::string brand, std::string model, std::string color, EngineType engineType, int capacity, std::string from, std::string to, std::string frequency, bool hasSockets)
            : PublicTransport(brand, model, color, engineType, capacity, from, to, frequency), hasSockets(hasSockets) {}

    bool getHasSockets() { return hasSockets; }
    void setHasSockets(bool hasSockets) { this->hasSockets = hasSockets; }
    void displayInfo() {
        PublicTransport::displayInfo(); // Вывод информации о базовом классе
        std::cout << "Transport Type: Trolleybus" << std::endl;
        std::cout << "Has Sockets: " << (hasSockets ? "Yes" : "No") << std::endl;
    }
};

enum RentCarTypes{
    ECONOMY,
    COMFORT,
    BUSINESS
};

class Taxi : public Transport{
private:
    double pricePerKil;
    double rating;
    bool hasDriver;
    bool hasWiFi;
    bool hasChildSeat;
    RentCarTypes rentCarTypes;

public:
    Taxi(std::string brand, std::string model, std::string color, EngineType engineType, double pricePerKil, double rating, bool hasDriver, bool hasWiFi, bool hasChildSeat, RentCarTypes rentCarTypes)
            : Transport(brand, model, color, engineType), pricePerKil(pricePerKil), rating(rating), hasDriver(hasDriver), hasWiFi(hasWiFi), hasChildSeat(hasChildSeat), rentCarTypes(rentCarTypes) {}

    double getPricePerKil() { return pricePerKil; }
    void setPricePerKil(double pricePerKil) { this->pricePerKil = pricePerKil; }

    double getRating() { return rating; }
    void setRating(double rating) { this->rating = rating; }

    bool getHasDriver() { return hasDriver; }
    void setHasDriver(bool hasDriver) { this->hasDriver = hasDriver; }

    bool getHasWiFi() { return hasWiFi; }
    void setHasWiFi(bool hasWiFi) { this->hasWiFi = hasWiFi; }

    bool getHasChildSeat() { return hasChildSeat; }
    void setHasChildSeat(bool hasChildSeat) { this->hasChildSeat = hasChildSeat; }

    RentCarTypes getRentCarTypes() { return rentCarTypes; }
    void setRentCarTypes(RentCarTypes rentCarTypes) { this->rentCarTypes = rentCarTypes; }

    void displayInfo() {
        Transport::displayInfo(); // Вывод информации о базовом классе
        std::cout << "Transport Type: Taxi" << std::endl;
        std::cout << "Price per Kilometer: " << pricePerKil << std::endl;
        std::cout << "Rating: " << rating << std::endl;
        std::cout << "Has Driver: " << (hasDriver ? "Yes" : "No") << std::endl;
        std::cout << "Has WiFi: " << (hasWiFi ? "Yes" : "No") << std::endl;
        std::cout << "Has Child Seat: " << (hasChildSeat ? "Yes" : "No") << std::endl;
        std::cout << "Rent Car Type: " << getRentCarTypes() << std::endl;
    }
};

class WorkingTaxi : public Taxi {
private:
    bool isOccupied;

public:
    WorkingTaxi(std::string brand, std::string model, std::string color, EngineType engineType, double pricePerKil, double rating, bool hasDriver, bool hasWiFi, bool hasChildSeat, RentCarTypes rentCarType)
            : Taxi(brand, model, color, engineType, pricePerKil, rating, hasDriver, hasWiFi, hasChildSeat, rentCarType), isOccupied(true) {}

    bool getIsOccupied() const { return isOccupied; }
    void setIsOccupied(bool occupied) { isOccupied = occupied; }

    WorkingTaxi(const WorkingTaxi& other)
            : Taxi(other), isOccupied(other.isOccupied) {}

    ~WorkingTaxi() {}

    WorkingTaxi()
            : Taxi("", "", "", PETROL, 0.0, 0.0, false, false, false, ECONOMY), isOccupied(true) {}
};


class CarSharing : public Transport {
private:
    double pricePerMinute;
    bool hasInsurance;
    bool hasADS;
    RentCarTypes rentCarType;

public:
    CarSharing(std::string brand, std::string model, std::string color, EngineType engineType, double pricePerMinute, bool hasInsurance, bool hasADS, RentCarTypes rentCarType)
            : Transport(brand, model, color, engineType), pricePerMinute(pricePerMinute), hasInsurance(hasInsurance), hasADS(hasADS), rentCarType(rentCarType) {}

    double getPricePerMinute() const { return pricePerMinute; }
    void setPricePerMinute(double pricePerMinute) { this->pricePerMinute = pricePerMinute; }

    bool getHasInsurance() const { return hasInsurance; }
    void setHasInsurance(bool hasInsurance) { this->hasInsurance = hasInsurance; }

    bool getHasADS() const { return hasADS; }
    void setHasADS(bool hasADS) { this->hasADS = hasADS; }

    RentCarTypes getRentCarType() const { return rentCarType; }
    void setRentCarType(RentCarTypes rentCarType) { this->rentCarType = rentCarType; }

    void displayInfo() {
        Transport::displayInfo();
        std::cout << "Transport Type: Car Sharing" << std::endl;
        std::cout << "Price per Minute: " << pricePerMinute << std::endl;
        std::cout << "Has Insurance: " << (hasInsurance ? "Yes" : "No") << std::endl;
        std::cout << "Has ADS: " << (hasADS ? "Yes" : "No") << std::endl;
        std::cout << "Rent Car Type: " << getRentCarType() << std::endl;
    }
};



int main() {
    try {
        pqxx::connection conn("dbname=CourseWorkDb user=postgres password=aboba host=localhost port=5432");

        int choice;
        while (true) {
            std::cout << "Select transport type:" << std::endl;
            std::cout << "1 - Bus" << std::endl;
            std::cout << "2 - Trolleybus" << std::endl;
            std::cout << "3 - Taxi" << std::endl;
            std::cout << "4 - Car Sharing" << std::endl;
            std::cout << "0 - Exit" << std::endl;
            std::cout << "Your choice: ";
            std::cin >> choice;

            if (choice == 0) {
                break;
            }

            pqxx::work txn(conn);
            pqxx::result result;

            switch (choice) {
                case 1:
                    result = txn.exec("SELECT * FROM bus");
                    std::cout << "Checking was successfull" << std::endl;
                    break;
                case 2:
                    result = txn.exec("SELECT * FROM trolleybus");
                    break;
                case 3:
                    result = txn.exec("SELECT * FROM taxi");
                    break;
                case 4:
                    result = txn.exec("SELECT * FROM car_sharing");
                    break;
                default:
                    std::cout << "Incorrect input." << std::endl;
                    continue;
            }

            txn.commit();

            for (pqxx::result::size_type i = 0; i < result.size(); ++i) {
                std::string brand = result[i]["brand"].as<std::string>();
                std::string model = result[i]["model"].as<std::string>();
                std::string color = result[i]["color"].as<std::string>();
                std::string engineTypeStr = result[i]["engineType"].as<std::string>();

                EngineType engineType;
                if (engineTypeStr == "PETROL") {
                    engineType = PETROL;
                } else if (engineTypeStr == "DIESEL") {
                    engineType = DIESEL;
                } else if (engineTypeStr == "HYBRID") {
                    engineType = HYBRID;
                } else if (engineTypeStr == "ELECTRIC") {
                    engineType = ELECTRIC;
                } else {
                    std::cerr << "Invalid engine type: " << engineTypeStr << std::endl;
                    continue;
                }

                if (choice == 1) {
                    int capacity = result[i]["capacity"].as<int>();
                    std::string from = result[i]["from_location"].as<std::string>();
                    std::string to = result[i]["to_location"].as<std::string>();
                    std::string frequency = result[i]["frequency"].as<std::string>();
                    bool hasContactlessPayment = result[i]["has_contactless_payment"].as<bool>();

                    Bus bus(brand, model, color, engineType, capacity, from, to, frequency, hasContactlessPayment);
                    bus.displayInfo();
                }
                else if (choice == 2) {
                    int capacity = result[i]["capacity"].as<int>();
                    std::string from = result[i]["from_location"].as<std::string>();
                    std::string to = result[i]["to_location"].as<std::string>();
                    std::string frequency = result[i]["frequency"].as<std::string>();
                    bool hasSockets = result[i]["has_sockets"].as<bool>();

                    TrolleyBus trolleybus(brand, model, color, engineType, capacity, from, to, frequency, hasSockets);
                    trolleybus.displayInfo();
                }
                else if (choice == 3) {
                    double pricePerKil = result[i]["price_per_kil"].as<double>();
                    double rating = result[i]["rating"].as<double>();
                    bool hasDriver = result[i]["has_driver"].as<bool>();
                    bool hasWiFi = result[i]["has_wifi"].as<bool>();
                    bool hasChildSeat = result[i]["has_child_seat"].as<bool>();
                    std::string rentCarTypeStr = result[i]["rent_car_type"].as<std::string>();

                    RentCarTypes rentCarType;
                    if (rentCarTypeStr == "ECONOMY") {
                        rentCarType = ECONOMY;
                    } else if (rentCarTypeStr == "COMFORT") {
                        rentCarType = COMFORT;
                    } else if (rentCarTypeStr == "BUSINESS") {
                        rentCarType = BUSINESS;
                    } else {
                        std::cerr << "Invalid rent car type: " << rentCarTypeStr << std::endl;
                        continue;
                    }
                    Taxi taxi(brand, model, color, engineType, pricePerKil, rating, hasDriver, hasWiFi, hasChildSeat, rentCarType);
                    taxi.displayInfo();

                    int requestTaxi;
                    std::cout << "Do you want to request a taxi? (1 for Yes, 0 for No): ";
                    std::cin >> requestTaxi;

                    if (requestTaxi == 1) {
                        Customer customer;
                        std::cout << "Enter your name: ";
                        std::string name;
                        std::cin >> name;
                        customer.setName(name);

                        std::cout << "Enter your surname: ";
                        std::string surname;
                        std::cin >> surname;
                        customer.setSurname(surname);

                        std::cout << "Enter your contact information: ";
                        std::string contactInfo;
                        std::cin >> contactInfo;
                        customer.setContactInformation(contactInfo);

                        pqxx::work taxiTxn(conn);
                        std::string selectRandomTaxiSQL = "SELECT taxi_id FROM taxi ORDER BY RANDOM() LIMIT 1";
                        pqxx::result randomTaxiResult = taxiTxn.exec(selectRandomTaxiSQL);

                        std::time_t current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                        std::string current_time_str = std::ctime(&current_time);

                        if (!randomTaxiResult.empty()) {
                            int carId = randomTaxiResult[0][0].as<int>();

                            pqxx::work orderTxn(conn);
                            std::string insertOrderSQL = "INSERT INTO \"order\" (customer_id, car_id, order_time) VALUES (" + std::to_string(customer.getCustomerId()) + ", " + std::to_string(carId) + ", current_timestamp) RETURNING order_id";
                            pqxx::result insertOrderResult = orderTxn.exec(insertOrderSQL);
                            orderTxn.commit();

                            if (!insertOrderResult.empty()) {
                                int orderId = insertOrderResult[0][0].as<int>();
                                std::cout << "Order created successfully! Order ID: " << orderId << std::endl;

                                // You can now display more information about the order, if needed.
                            } else {
                                std::cerr << "Failed to create an order." << std::endl;
                            }
                        } else {
                            std::cerr << "No available cars found." << std::endl;
                        }
                    } else {
                        std::cout << "Order canceled. Exiting..." << std::endl;
                        break;
                    }
                }
                else if (choice == 4) {
                    double pricePerMinute = result[i]["price_per_minute"].as<double>();
                    bool hasInsurance = result[i]["has_insurance"].as<bool>();
                    bool hasADS = result[i]["has_ads"].as<bool>();
                    RentCarTypes rentCarType = static_cast<RentCarTypes>(result[i]["rent_car_type"].as<int>());

                    CarSharing carSharing(brand, model, color, engineType, pricePerMinute, hasInsurance, hasADS, rentCarType);
                    carSharing.displayInfo();

                }
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
