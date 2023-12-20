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

// Определение оператора вывода
std::ostream& operator<<(std::ostream& os, const ElectronicWatch& watch) {
    os << watch.getBrand() << " " << watch.getWeight() << " " << watch.getPrice() << " "
       << watch.getBatteryCharge() << " " << watch.getMaxCharge() << " " << watch.getScreenBrightness();
    return os;
}

// Определение оператора ввода
std::istream& operator>>(std::istream& is, ElectronicWatch& watch) {
    std::string brand;
    int weight, price, batteryCharge, maxCharge, screenBrightness;

    is >> brand >> reinterpret_cast<ElectronicWatch &>(weight) >> reinterpret_cast<ElectronicWatch &>(price)
       >> reinterpret_cast<ElectronicWatch &>(batteryCharge) >> reinterpret_cast<ElectronicWatch &>(maxCharge)
       >> reinterpret_cast<ElectronicWatch &>(screenBrightness);

    watch.setBrand(brand.c_str());
    watch.setWeight(weight);
    watch.setPrice(price);
    watch.setBatteryCharge(batteryCharge);
    watch.setMaxCharge(maxCharge);
    watch.setScreenBrightness(screenBrightness);

    return is;
}