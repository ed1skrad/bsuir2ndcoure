//
// Created by atema on 11.10.2023.
//

#ifndef UNTITLED10_MECHANICCLOCK_H
#define UNTITLED10_MECHANICCLOCK_H

#include "Clock.h"

class MechanicClock : public Clock {
private:
    char bodyMaterial[50];
    int numberOfGears;
    char glassType[50];

public:
    MechanicClock();
    MechanicClock(const char* brand, int weight, int price, const char* bodyMaterial, int numberOfGears, const char* glassType);
    ~MechanicClock();

    const char* getBodyMaterial() const;
    int getNumberOfGears() const;
    const char* getGlassType() const;

    void setBodyMaterial(const char* bodyMaterial);
    void setNumberOfGears(int numberOfGears);
    void setGlassType(const char* glassType);
};
#endif //UNTITLED10_MECHANICCLOCK_H
