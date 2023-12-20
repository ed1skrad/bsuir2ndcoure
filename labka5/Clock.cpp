#include "Clock.h"
#include <cstring>
#include "Exception.h"

Clock::Clock() {
    std::strcpy(brand, "");
    weight = 0;
    price = 0;
    currentTime = std::time(0);
}

Clock::Clock(const char* brand, int weight, int price) {
    std::strcpy(this->brand, brand);
    this->weight = weight;
    this->price = price;
    currentTime = std::time(0);
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


std::time_t Clock::getCurrentTime() const {
    return currentTime;
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
