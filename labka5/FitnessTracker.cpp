#include "FitnessTracker.h"

FitnessTracker::FitnessTracker() : ElectronicWatch() {
    distance = 0;
    heart_rate_monitor = false;
}

FitnessTracker::FitnessTracker(const char* brand, int weight, int price, int batteryCharge, int maxCharge, int screenBrightness, int distance, bool heartRateMonitor)
        : ElectronicWatch(brand, weight, price, batteryCharge, maxCharge, screenBrightness) {
    this->distance = distance;
    this->heart_rate_monitor = heartRateMonitor;
}

FitnessTracker::~FitnessTracker() {}

int FitnessTracker::getDistance() const {
    return distance;
}

bool FitnessTracker::getHeartRateMonitor() const {
    return heart_rate_monitor;
}

void FitnessTracker::setDistance(int newDistance) {
    distance = newDistance;
}

void FitnessTracker::setHeartRateMonitor(bool newHeartRateMonitor) {
    heart_rate_monitor = newHeartRateMonitor;
}
