//
// Created by atema on 11.10.2023.
//

#ifndef UNTITLED10_WATCH_H
#define UNTITLED10_WATCH_H

#include "MechanicClock.h"

class Watch : public MechanicClock {
private:
    bool self_winding;
    int strap_diameter;

public:
    Watch();
    Watch(const char* brand, int weight, int price, const char* bodyMaterial, int numberOfGears, const char* glassType, bool selfWinding, int strapDiameter);
    ~Watch();

    bool getSelfWinding() const;
    int getStrapDiameter() const;

    void setSelfWinding(bool newSelfWinding);
    void setStrapDiameter(int newStrapDiameter);
};
#endif //UNTITLED10_WATCH_H
