// TrolleyBus.cpp

#include "TrolleyBus.h"

TrolleyBus::TrolleyBus() : PublicTransport(), hasSockets(false) {}

TrolleyBus::TrolleyBus(int transportId, std::string brand, std::string model, std::string color, EngineType engineType, int capacity, bool hasSockets)
        : PublicTransport(transportId, brand, model, color, engineType, capacity), hasSockets(hasSockets) {}

TrolleyBus::TrolleyBus(const std::string& brand, const std::string& model, const std::string& color, EngineType engineType, int capacity, bool hasSockets)
        : PublicTransport(brand, model, color, engineType, capacity), hasSockets(hasSockets) {}

bool TrolleyBus::getHasSockets() const {
    return hasSockets;
}

void TrolleyBus::setHasSockets(bool hasSockets) {
    this->hasSockets = hasSockets;
}

void TrolleyBus::displayTrolleyBusDetails(const pqxx::result::const_iterator& row) {
    int transportId = row["trolleybus_id"].as<int>();
    int capacity = row["capacity"].as<int>();
    std::string brand = row["brand"].as<std::string>();
    std::string model = row["model"].as<std::string>();
    std::string color = row["color"].as<std::string>();
    EngineType engineType = stringToEngineType(row["engineType"].as<std::string>());
    bool hasSockets = row["has_sockets"].as<bool>();

    std::unique_ptr<TrolleyBus> trolleyBus = std::make_unique<TrolleyBus>(
            transportId, brand, model, color,
            static_cast<EngineType>(engineType),
            capacity,
            hasSockets
    );

    std::cout << "TrolleyBus Details:" << std::endl;
    std::cout << "Transport ID: " << trolleyBus->getTransportId() << std::endl;
    std::cout << "Brand: " << trolleyBus->getBrand() << std::endl;
    std::cout << "Model: " << trolleyBus->getModel() << std::endl;
    std::cout << "Color: " << trolleyBus->getColor() << std::endl;
    std::cout << "Engine Type: " << trolleyBus->getEngineTypeString() << std::endl;
    std::cout << "Capacity: " << trolleyBus->getCapacity() << std::endl;
    std::cout << "Has Sockets: " << (trolleyBus->getHasSockets() ? "Yes" : "No") << std::endl;
    std::cout << std::endl;
}

void TrolleyBus::displayAllTrolleyBuses(Database& db) {
    try {
        pqxx::result trolleyBusResult = db.executeQuery("SELECT * FROM trolleybus");
        std::cout << "Displaying TrolleyBus Details:" << std::endl;
        for (const auto& row : trolleyBusResult) {
            displayTrolleyBusDetails(row);
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
