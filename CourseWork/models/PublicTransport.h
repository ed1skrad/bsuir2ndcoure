#ifndef COURSEWORK_PUBLICTRANSPORT_H
#define COURSEWORK_PUBLICTRANSPORT_H

#include <iostream>
#include "Transport.h"

class PublicTransport : public Transport {
private:
    int transportId;
    int capacity;

public:
    enum TransportType {
        BUS,
        TROLLEYBUS,
    };

    PublicTransport();
    PublicTransport(int transportId, std::string brand, std::string model, std::string color, EngineType engineType, int capacity);
    PublicTransport(std::string brand, std::string model, std::string color, EngineType engineType, int capacity);

    int getTransportId();
    void setTransportId(int id);

    int getCapacity();
    void setCapacity(int capacity);

    ~PublicTransport();
};

#endif //COURSEWORK_PUBLICTRANSPORT_H
