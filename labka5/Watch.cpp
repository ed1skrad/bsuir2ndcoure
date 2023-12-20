#include "Watch.h"

Watch::Watch() : MechanicClock() {
    self_winding = false;
    strap_diameter = 0;
}

Watch::Watch(const char* brand, int weight, int price, const char* bodyMaterial, int numberOfGears, const char* glassType, bool selfWinding, int strapDiameter)
        : MechanicClock(brand, weight, price, bodyMaterial, numberOfGears, glassType) {
    self_winding = selfWinding;
    strap_diameter = strapDiameter;
}

Watch::~Watch() {}

bool Watch::getSelfWinding() const {
    return self_winding;
}

int Watch::getStrapDiameter() const {
    return strap_diameter;
}

void Watch::setSelfWinding(bool newSelfWinding) {
    self_winding = newSelfWinding;
}

void Watch::setStrapDiameter(int newStrapDiameter) {
    strap_diameter = newStrapDiameter;
}
