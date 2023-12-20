#ifndef CLOCK_H
#define CLOCK_H

#include <ctime>

class Clock {
private:
    char brand[50];
    int weight;
    int price;
    time_t currentTime;

public:
    Clock();
    Clock(const char* brand, int weight, int price);
    ~Clock();

    const char* getBrand() const;
    int getWeight() const;
    int getPrice() const;
    time_t getCurrentTime() const;

    void setBrand(const char* brand);
    void setWeight(int weight);
    void setPrice(int price);
};


#endif
