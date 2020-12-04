//
// Created by Michael Kinc on 28/11/2020.
//

#ifndef IMS_PROJECT_2020_TANK_H
#define IMS_PROJECT_2020_TANK_H

#include <string>
#include "Stats.h"
#include "WaterSupply.h"
using namespace std;

class Tank {
    public:
        Tank(int capacity);
        void fill(int amount);
        int getWaterLevel();
        int getMaxCapacity();
        void drainWater(int amount);
        void prefill(int volumeOfWater);
    private:
        int waterLevel;
        int maxCapacity;
        bool isTankOverfull();
        void dropWater(int amount);
};

#endif //IMS_PROJECT_2020_TANK_H
