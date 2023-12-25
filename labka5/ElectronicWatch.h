#ifndef ELECTRONICWATCH_H
#define ELECTRONICWATCH_H

#include "Clock.h"
#include <fstream>
#include <iostream>

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

    void serialize(std::ostream& os) const override;
    void deserialize(std::istream& is) override;
    void serialize_bin(std::ofstream& os) const override;
    void deserialize_bin(std::ifstream& is) override;
};

#endif
