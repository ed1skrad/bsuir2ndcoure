#include "PublicTransport.h"

PublicTransport::PublicTransport() : transport_id(0), capacity(0) {}

PublicTransport::PublicTransport(int transport_id, std::string brand, std::string model, std::string color, EngineType engineType, int capacity)
        : Transport(brand, model, color, engineType), transport_id(transport_id), capacity(capacity) {}

int PublicTransport::getTransportId() {
    return transport_id;
}

void PublicTransport::setTransportId(int id) {
    transport_id = id;
}

int PublicTransport::getCapacity() {
    return capacity;
}

void PublicTransport::setCapacity(int capacity) {
    this->capacity = capacity;
}

PublicTransport::~PublicTransport() {}
