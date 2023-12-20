#include "MechanicClock.h"
#include <cstring>

MechanicClock::MechanicClock() : Clock() {
    std::strcpy(bodyMaterial, "");
    numberOfGears = 0;
    std::strcpy(glassType, "");
}

MechanicClock::MechanicClock(const char* brand, int weight, int price, const char* bodyMaterial, int numberOfGears, const char* glassType)
        : Clock(brand, weight, price) {
    std::strcpy(this->bodyMaterial, bodyMaterial);
    this->numberOfGears = numberOfGears;
    std::strcpy(this->glassType, glassType);
}

MechanicClock::~MechanicClock() {}

const char* MechanicClock::getBodyMaterial() const {
    return bodyMaterial;
}

int MechanicClock::getNumberOfGears() const {
    return numberOfGears;
}

const char* MechanicClock::getGlassType() const {
    return glassType;
}

void MechanicClock::setBodyMaterial(const char* bodyMaterial) {
    std::strcpy(this->bodyMaterial, bodyMaterial);
}

void MechanicClock::setNumberOfGears(int numberOfGears) {
    this->numberOfGears = numberOfGears;
}

void MechanicClock::setGlassType(const char* glassType) {
    std::strcpy(this->glassType, glassType);
}
