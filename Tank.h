//
// Created by Michael Kinc on 28/11/2020.
//

#ifndef IMS_PROJECT_2020_TANK_H
#define IMS_PROJECT_2020_TANK_H

#include <string>
#include "Stats.h"
using namespace std;

class Tank {
    public:
        void fill(double amount);
        double getWaterLevel();
        double getMaxCapacity();
        static Tank* getInstance(double* const capacity = nullptr);
    private:
        Tank();
        Tank(double* const capacity);
        static Tank* instance;
        double waterLevel;
        double maxCapacity;
        bool isTankOverfull();
        void dropWater(double amount);
};

#endif //IMS_PROJECT_2020_TANK_H
