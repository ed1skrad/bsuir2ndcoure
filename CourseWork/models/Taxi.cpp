// Taxi.cpp

#include "Taxi.h"
#include "Order.h"
#include "../action/InputUtils.h"

Taxi::Taxi(std::string brand, std::string model, std::string color, EngineType engineType, int carId, double pricePerKil, bool hasDriver, bool hasWiFi, bool hasChildSeat, RentCarTypes rentCarTypes)
        : Transport(brand, model, color, engineType), carId(carId), pricePerKil(pricePerKil), hasDriver(hasDriver), hasWiFi(hasWiFi), hasChildSeat(hasChildSeat), rentCarTypes(rentCarTypes) {}

Taxi::Taxi() : Transport("", "", "", EngineType::PETROL), carId(0), pricePerKil(0.0), hasDriver(false), hasWiFi(false), hasChildSeat(false), rentCarTypes(RentCarTypes::ECONOMY) {}

int Taxi::getCarId() const {
    return carId;
}

void Taxi::setCarId(int id) {
    carId = id;
}

double Taxi::getPricePerKil() const {
    return pricePerKil;
}

void Taxi::setPricePerKil(double pricePerKil) {
    this->pricePerKil = pricePerKil;
}

bool Taxi::getHasDriver() const {
    return hasDriver;
}

void Taxi::setHasDriver(bool hasDriver) {
    this->hasDriver = hasDriver;
}

bool Taxi::getHasWiFi() const {
    return hasWiFi;
}

void Taxi::setHasWiFi(bool hasWiFi) {
    this->hasWiFi = hasWiFi;
}

bool Taxi::getHasChildSeat() const {
    return hasChildSeat;
}

void Taxi::setHasChildSeat(bool hasChildSeat) {
    this->hasChildSeat = hasChildSeat;
}

RentCarTypes Taxi::getRentCarTypes() const {
    return rentCarTypes;
}

void Taxi::setRentCarTypes(RentCarTypes rentCarTypes) {
    this->rentCarTypes = rentCarTypes;
}

Taxi::~Taxi() {
}

RentCarTypes Taxi::stringToRentCarTypes(const std::string& rentCarTypesStr) {
    if (rentCarTypesStr == "ECONOMY") {
        return RentCarTypes::ECONOMY;
    } else if (rentCarTypesStr == "COMFORT") {
        return RentCarTypes::COMFORT;
    } else if (rentCarTypesStr == "BUSINESS") {
        return RentCarTypes::BUSINESS;
    } else {
        std::cerr << "Error: Invalid rent car type - unknown value: " << rentCarTypesStr << std::endl;
        throw std::runtime_error("Invalid rent car type: " + rentCarTypesStr);
    }
}

void Taxi::displayTaxiDetails(const pqxx::result::const_iterator& row) {
    try {
        int carId = row[0].as<int>();
        std::string brand = row[1].as<std::string>();
        std::string model = row[2].as<std::string>();
        std::string color = row[3].as<std::string>();
        EngineType engineType = stringToEngineType(row["engineType"].as<std::string>());
        double pricePerKil = row[5].as<double>();
        bool hasDriver = row[6].as<bool>();
        bool hasWiFi = row[7].as<bool>();
        bool hasChildSeat = row[8].as<bool>();
        RentCarTypes rentCarTypes = stringToRentCarTypes(row["rent_car_type"].as<std::string>());

        std::unique_ptr<Taxi> taxi = std::make_unique<Taxi>(
                brand, model, color,
                engineType,
                carId, pricePerKil,
                hasDriver, hasWiFi, hasChildSeat,
                rentCarTypes
        );

        std::cout << "Taxi Details:" << std::endl;
        std::cout << "Car ID: " << taxi->getCarId() << std::endl;
        std::cout << "Brand: " << taxi->getBrand() << std::endl;
        std::cout << "Model: " << taxi->getModel() << std::endl;
        std::cout << "Color: " << taxi->getColor() << std::endl;
        std::cout << "Engine Type: " << taxi->getEngineTypeString() << std::endl;
        std::cout << "Price per Kilometer: " << taxi->getPricePerKil() << std::endl;
        std::cout << "Has Driver: " << (hasDriver ? "Yes" : "No") << std::endl;
        std::cout << "Has WiFi: " << (hasWiFi ? "Yes" : "No") << std::endl;
        std::cout << "Has Child Seat: " << (hasChildSeat ? "Yes" : "No") << std::endl;
        std::cout << "Rent Car Type: " << taxi->getRentCarTypes() << std::endl;
        std::cout << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error displaying taxi details: " << e.what() << std::endl;
    }
}

void Taxi::displayAllTaxis(Database& Db) {
    try {
        pqxx::result R = Db.executeQuery("SELECT * FROM taxi");

        if (R.empty()) {
            std::cout << "No taxis found in the database." << std::endl;
            return;
        }

        std::cout << "Printing query result:" << std::endl;
        for (const auto& row : R) {
            for (const auto& field : row) {
                std::cout << field.name() << ": " << field.c_str() << "\t";
            }
            std::cout << std::endl;
        }

        for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {
            displayTaxiDetails(c);
        }
    } catch (const std::exception &e) {
        std::cerr << "Error displaying all taxis: " << e.what() << std::endl;
    }
}

void Taxi::displayTaxiById(Database& Db, int taxiId) {
    try {
        pqxx::result R = Db.executeQuery("SELECT * FROM taxi WHERE taxi_id = " + std::to_string(taxiId));

        if (R.empty()) {
            std::cout << "No taxi found with ID " << taxiId << std::endl;
            return;
        }

        for (const auto& row : R) {
            displayTaxiDetails(row);
        }
    } catch (const std::exception &e) {
        std::cerr << "Error displaying taxi by ID: " << e.what() << std::endl;
    }
}

void Taxi::displayTaxisByBrand(Database& Db, const std::string& brand) {
    try {
        pqxx::result R = Db.executeQuery("SELECT * FROM taxi WHERE brand = '" + brand + "'");

        if (R.empty()) {
            std::cout << "No taxis found with brand '" << brand << "'" << std::endl;
            return;
        }

        for (const auto& row : R) {
            displayTaxiDetails(row);
        }
    } catch (const std::exception &e) {
        std::cerr << "Error displaying taxis by brand: " << e.what() << std::endl;
    }
}

void Taxi::displayTaxisByRentCarType(Database& Db, RentCarTypes rentCarType) {
    try {
        std::string rentCarTypeStr;
        switch (rentCarType) {
            case ECONOMY:
                rentCarTypeStr = "ECONOMY";
                break;
            case COMFORT:
                rentCarTypeStr = "COMFORT";
                break;
            case BUSINESS:
                rentCarTypeStr = "BUSINESS";
                break;
            default:
                std::cerr << "Invalid rent car type." << std::endl;
                return;
        }

        pqxx::result R = Db.executeQuery("SELECT * FROM taxi WHERE rent_car_type = '" + rentCarTypeStr + "'");

        for (const auto& row : R) {
            displayTaxiDetails(row);
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

std::string Taxi::to_string(const int value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

void Taxi::orderTaxi(Database& Db) {
    try {
        int carId = InputUtils::getPositiveInput<int>("Enter the car ID: ");

        std::string checkTaxiQuery = "SELECT EXISTS(SELECT 1 FROM taxi WHERE taxi_id = " + to_string(carId) + ")";
        pqxx::result taxiExistsResult = Db.executeQuery(checkTaxiQuery);
        bool taxiExists = taxiExistsResult[0][0].as<bool>();
        if (!taxiExists) {
            std::cout << "Taxi with ID " << carId << " does not exist. Please enter a valid taxi ID." << std::endl;
            return;
        }

        std::string name = InputUtils::getStringInput("Enter your name: ");
        std::string surname = InputUtils::getStringInput("Enter your surname: ");
        std::string contactInformation = InputUtils::getStringInput("Enter your contact information: ");

        std::string addCustomerQuery = "INSERT INTO customer (name, surname, contact_information) VALUES ('" +
                                  name + "','" +
                                  surname + "','" +
                                  contactInformation + "')";
        Db.executeQuery(addCustomerQuery);

        pqxx::result customerIdResult = Db.executeQuery("SELECT MAX(customer_id) FROM customer");
        int customerId = customerIdResult[0][0].as<int>();

        Order order;
        order.setCustomerId(customerId);
        order.setCarId(carId);

        std::string addOrderQuery = "INSERT INTO orders (customer_id, car_id, order_time) VALUES (" +
                               to_string(customerId) + "," +
                               to_string(carId) + ",'" +
                               order.getOrderTime() + "')";
        Db.executeQuery(addOrderQuery);

        std::cout << "Order placed successfully! Your taxi ID is " << carId << "." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
