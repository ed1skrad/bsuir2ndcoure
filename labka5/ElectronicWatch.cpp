#include "ElectronicWatch.h"

ElectronicWatch::ElectronicWatch() : Clock() {
    battery_charge = 0;
    max_charge = 0;
    screen_brightness = 0;
}

ElectronicWatch::ElectronicWatch(const char* brand, int weight, int price, int batteryCharge, int maxCharge, int screenBrightness)
        : Clock(brand, weight, price) {
    battery_charge = batteryCharge;
    max_charge = maxCharge;
    screen_brightness = screenBrightness;
}

ElectronicWatch::~ElectronicWatch() {}

int ElectronicWatch::getBatteryCharge() const {
    return battery_charge;
}

int ElectronicWatch::getMaxCharge() const {
    return max_charge;
}

int ElectronicWatch::getScreenBrightness() const {
    return screen_brightness;
}

void ElectronicWatch::setBatteryCharge(int newBatteryCharge) {
    battery_charge = newBatteryCharge;
}

void ElectronicWatch::setMaxCharge(int newMaxCharge) {
    max_charge = newMaxCharge;
}

void ElectronicWatch::setScreenBrightness(int newScreenBrightness) {
    screen_brightness = newScreenBrightness;
}
