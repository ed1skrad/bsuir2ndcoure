//
// Created by atema on 02.12.2023.
//

#ifndef COURSEWORK_PUBLICTRANSPORT_H
#define COURSEWORK_PUBLICTRANSPORT_H
#include <iostream>
#include "Transport.h"

class PublicTransport : public Transport {
private:
    int transport_id;
    int capacity;
    std::string from;
    std::string to;
    std::string frequency;

public:

    enum TransportType {
        BUS,
        TROLLEYBUS,
    };

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



#endif //COURSEWORK_PUBLICTRANSPORT_H
