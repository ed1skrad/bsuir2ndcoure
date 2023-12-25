#include "Clock.h"
#include <cstring>
#include "Exception.h"

Clock::Clock() {
    std::strcpy(brand, "");
    weight = 0;
    price = 0;
}

Clock::Clock(const char* brand, int weight, int price) {
    std::strcpy(this->brand, brand);
    this->weight = weight;
    this->price = price;
}

Clock::~Clock() {}

const char* Clock::getBrand() const {
    return brand;
}

int Clock::getWeight() const {
    try {
        if(weight < 0){
            throw NegativeWeightException();
        }
    } catch (const NegativeWeightException& e) {
        e.show();
        return 0;
    }
    return weight;
}

int Clock::getPrice() const {
    try {
        if(price < 0){
            throw NegativePriceException();
        }
    } catch (const NegativePriceException& e) {
        e.show();
        return 0;
    }
    return price;
}

void Clock::setBrand(const char* brand) {
    std::strcpy(this->brand, brand);
}

void Clock::setWeight(int weight) {
    this->weight = weight;
}

void Clock::setPrice(int price) {
    this->price = price;
}

void Clock::serialize(std::ostream& os) const {
    os << brand << ' ' << weight << ' ' << price << ' ';
}

void Clock::deserialize(std::istream& is) {
    is >> brand >> weight >> price;
    is.ignore();
}

void Clock::serialize_bin(std::ofstream& os) const {
    os.write(reinterpret_cast<const char*>(&brand), sizeof(brand));
    os.write(reinterpret_cast<const char*>(&weight), sizeof(weight));
    os.write(reinterpret_cast<const char*>(&price), sizeof(price));
}

void Clock::deserialize_bin(std::ifstream& is) {
    is.read(reinterpret_cast<char*>(&brand), sizeof(brand));
    is.read(reinterpret_cast<char*>(&weight), sizeof(weight));
    is.read(reinterpret_cast<char*>(&price), sizeof(price));
}

std::ostream& operator<<(std::ostream& os, const Clock& clock) {
    clock.serialize(os);
    return os;
}

std::istream& operator>>(std::istream& is, Clock& clock) {
    clock.deserialize(is);
    return is;
}

