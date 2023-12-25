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

void ElectronicWatch::serialize(std::ostream& os) const {
    Clock::serialize(os);
    os << "\t" << battery_charge << "\t" << max_charge << "\t" << screen_brightness;
}

void ElectronicWatch::deserialize(std::istream& is) {
    Clock::deserialize(is);
    is >> battery_charge >> max_charge >> screen_brightness;
    is.ignore();
}

void ElectronicWatch::serialize_bin(std::ofstream& os) const {
    Clock::serialize_bin(os);
    os.write(reinterpret_cast<const char*>(&battery_charge), sizeof(battery_charge));
    os.write(reinterpret_cast<const char*>(&max_charge), sizeof(max_charge));
    os.write(reinterpret_cast<const char*>(&screen_brightness), sizeof(screen_brightness));
}

void ElectronicWatch::deserialize_bin(std::ifstream& is) {
    Clock::deserialize_bin(is);
    is.read(reinterpret_cast<char*>(&battery_charge), sizeof(battery_charge));
    is.read(reinterpret_cast<char*>(&max_charge), sizeof(max_charge));
    is.read(reinterpret_cast<char*>(&screen_brightness), sizeof(screen_brightness));
}
