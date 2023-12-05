#include "Transport.h"

Transport::Transport() : brand(""), model(""), color(""), engineType(EngineType::DIESEL) {}

Transport::Transport(std::string brand, std::string model, std::string color, EngineType engineType) : brand(brand), model(model), color(color), engineType(engineType) {}

Transport::~Transport() {}

std::string Transport::getBrand()
{
    return brand;
}

void Transport::setBrand(std::string brand)
{
    this->brand = brand;
}

std::string Transport::getModel()
{
    return model;
}

void Transport::setModel(std::string model)
{
    this->model = model;
}

std::string Transport::getColor()
{
    return color;
}

void Transport::setColor(std::string color)
{
    this->color = color;
}

EngineType Transport::getEngineType()
{
    return engineType;
}

void Transport::setEngineType(EngineType engineType)
{
    this->engineType = engineType;
}

std::string Transport::getEngineTypeString()
{
    switch (engineType)
    {
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

EngineType Transport::stringToEngineType(const std::string &engineTypeStr) {
    if (engineTypeStr == "PETROL") {
        return EngineType::PETROL;
    } else if (engineTypeStr == "DIESEL") {
        return EngineType::DIESEL;
    } else if (engineTypeStr == "HYBRID") {
        return EngineType::HYBRID;
    } else if (engineTypeStr == "ELECTRIC") {
        return EngineType::ELECTRIC;
    } else {
        std::cerr << "Error: Invalid engine type - unknown value: " << engineTypeStr << std::endl;
        throw std::runtime_error("Invalid engine type: " + engineTypeStr);
    }
}

void Transport::isIdValid(int &id, const std::string &transportName, Database *Db)
{
    while (true)
    {
        try
        {
            std::cout << "Enter the " << transportName << " ID: ";
            std::cin >> id;

            std::string checkQuery = "SELECT * FROM " + transportName + " WHERE " + transportName + "_id = " + std::to_string(id);
            pqxx::result result = Db->executeQuery(checkQuery);

            if (!result.empty())
            {
                return;
            }
            else
            {
                std::cerr << transportName << " with entered value does not exist. Try again." << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}
