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
        void fill(int amount);
        double getWaterLevel();
        double getMaxCapacity();
        static Tank* getInstance(int* const capacity = nullptr);
        void drainWater(int amount);
    private:
        Tank();
        Tank(int* const capacity);
        static Tank* instance;
        int waterLevel;
        int maxCapacity;
        bool isTankOverfull();
        void dropWater(int amount);
};

#endif //IMS_PROJECT_2020_TANK_H
