#ifndef CLOCK_H
#define CLOCK_H

#include <ctime>
#include <fstream>
#include <iostream>

class Clock {
private:
    char brand[50];
    int weight;
    int price;

public:
    Clock();
    Clock(const char* brand, int weight, int price);
    ~Clock();

    const char* getBrand() const;
    int getWeight() const;
    int getPrice() const;

    void setBrand(const char* brand);
    void setWeight(int weight);
    void setPrice(int price);

    virtual void serialize(std::ostream& os) const;
    virtual void deserialize(std::istream& is);
    virtual void serialize_bin(std::ofstream& os) const;
    virtual void deserialize_bin(std::ifstream& is);
};


std::ostream& operator<<(std::ostream& os, const Clock& clock);
std::istream& operator>>(std::istream& is, Clock& clock);

#endif
