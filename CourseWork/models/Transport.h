#ifndef COURSEWORK_TRANSPORT_H
#define COURSEWORK_TRANSPORT_H

#include "../database/Database.h"
#include <iostream>

enum EngineType
{
    PETROL,
    DIESEL,
    HYBRID,
    ELECTRIC
};

class Transport
{
private:
    std::string brand;
    std::string model;
    std::string color;
    EngineType engineType;

public:

    Transport();
    Transport(std::string brand, std::string model, std::string color, EngineType engineType);
    ~Transport();

    std::string getBrand();
    void setBrand(std::string brand);

    std::string getModel();
    void setModel(std::string model);

    std::string getColor();
    void setColor(std::string color);

    EngineType getEngineType();
    void setEngineType(EngineType engineType);

    std::string getEngineTypeString();

    static EngineType stringToEngineType(const std::string &engineTypeStr);

    void isIdValid(int &id, const std::string &transportName, Database *Db);
};

#endif //COURSEWORK_TRANSPORT_H
