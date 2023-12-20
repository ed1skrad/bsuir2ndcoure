#include "WallClock.h"
#include <cstring>

WallClock::WallClock() : MechanicClock() {
    pendulum = false;
    std::strcpy(fasteningMaterial, "");
}

WallClock::WallClock(const char* brand, int weight, int price, const char* bodyMaterial, int numberOfGears, const char* glassType, bool pendulum, const char* fasteningMaterial)
        : MechanicClock(brand, weight, price, bodyMaterial, numberOfGears, glassType) {
    this->pendulum = pendulum;
    std::strcpy(this->fasteningMaterial, fasteningMaterial);
}

WallClock::~WallClock() {}

bool WallClock::getPendulum() const {
    return pendulum;
}

const char* WallClock::getFasteningMaterial() const {
    return fasteningMaterial;
}

void WallClock::setPendulum(bool newPendulum) {
    pendulum = newPendulum;
}

void WallClock::setFasteningMaterial(const char* newFasteningMaterial) {
    std::strcpy(fasteningMaterial, newFasteningMaterial);
}
