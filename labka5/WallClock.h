//
// Created by atema on 11.10.2023.
//

#ifndef UNTITLED10_WALLCLOCK_H
#define UNTITLED10_WALLCLOCK_H

#include "MechanicClock.h"

class WallClock : public MechanicClock {
private:
    bool pendulum;
    char fasteningMaterial[50];

public:
    WallClock();
    WallClock(const char* brand, int weight, int price, const char* bodyMaterial, int numberOfGears, const char* glassType, bool pendulum, const char* fasteningMaterial);
    ~WallClock();

    bool getPendulum() const;
    const char* getFasteningMaterial() const;

    void setPendulum(bool newPendulum);
    void setFasteningMaterial(const char* newFasteningMaterial);
};
#endif //UNTITLED10_WALLCLOCK_H
