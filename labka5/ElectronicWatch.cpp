#include "ElectronicWatch.h"
#include <iostream>


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

// Определение оператора для вывода объекта ElectronicWatch в поток
std::ostream& operator<<(std::ostream& os, const ElectronicWatch& watch) {
    os << "Brand: " << watch.getBrand() << ", Weight: " << watch.getWeight()
       << ", Price: " << watch.getPrice() << ", Battery Charge: " << watch.battery_charge
       << ", Max Charge: " << watch.max_charge << ", Screen Brightness: " << watch.screen_brightness;
    return os;
}

// Определение оператора для чтения объекта ElectronicWatch из потока
std::istream& operator>>(std::istream& is, ElectronicWatch& watch) {
    char brand[50];
    int weight, price, batteryCharge, maxCharge, screenBrightness;

    is >> brand >> weight >> price >> batteryCharge >> maxCharge >> screenBrightness;

    watch.setBrand(brand);
    watch.setWeight(weight);
    watch.setPrice(price);
    watch.setBatteryCharge(batteryCharge);
    watch.setMaxCharge(maxCharge);
    watch.setScreenBrightness(screenBrightness);

    return is;
}

