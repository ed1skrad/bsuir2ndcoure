//
// Created by atema on 11.10.2023.
//

#ifndef UNTITLED10_FITNESSTRACKER_H
#define UNTITLED10_FITNESSTRACKER_H

#include "ElectronicWatch.h"

class FitnessTracker : public ElectronicWatch {
private:
    int distance;
    bool heart_rate_monitor;

public:
    FitnessTracker();
    FitnessTracker(const char* brand, int weight, int price, int batteryCharge, int maxCharge, int screenBrightness, int distance, bool heartRateMonitor);
    ~FitnessTracker();

    int getDistance() const;
    bool getHeartRateMonitor() const;

    void setDistance(int newDistance);
    void setHeartRateMonitor(bool newHeartRateMonitor);
};
#endif //UNTITLED10_FITNESSTRACKER_H
