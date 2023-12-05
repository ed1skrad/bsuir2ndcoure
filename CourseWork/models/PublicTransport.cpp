#include "PublicTransport.h"

PublicTransport::PublicTransport() : transportId(0), capacity(0) {}

PublicTransport::PublicTransport(int transportId, std::string brand, std::string model, std::string color, EngineType engineType, int capacity)
        : Transport(brand, model, color, engineType), transportId(transportId), capacity(capacity) {}

int PublicTransport::getTransportId() {
    return transportId;
}

void PublicTransport::setTransportId(int id) {
    transportId = id;
}

int PublicTransport::getCapacity() {
    return capacity;
}

void PublicTransport::setCapacity(int capacity) {
    this->capacity = capacity;
}

PublicTransport::~PublicTransport() {}
