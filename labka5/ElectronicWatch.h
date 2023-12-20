//
// Created by atema on 11.10.2023.
//

#ifndef UNTITLED10_ELECTRONICWATCH_H
#define UNTITLED10_ELECTRONICWATCH_H

#include "Clock.h"

class ElectronicWatch : public Clock {
private:
    int battery_charge;
    int max_charge;
    int screen_brightness;

public:
    ElectronicWatch();
    ElectronicWatch(const char* brand, int weight, int price, int batteryCharge, int maxCharge, int screenBrightness);
    ~ElectronicWatch();

    int getBatteryCharge() const;
    int getMaxCharge() const;
    int getScreenBrightness() const;

    void setBatteryCharge(int newBatteryCharge);
    void setMaxCharge(int newMaxCharge);
    void setScreenBrightness(int newScreenBrightness);
};
#endif //UNTITLED10_ELECTRONICWATCH_H
