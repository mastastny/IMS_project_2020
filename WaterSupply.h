//
// Created by Michael Kinc on 28/11/2020.
//

#ifndef IMS_PROJECT_2020_WATERSUPPLY_H
#define IMS_PROJECT_2020_WATERSUPPLY_H

#include "Stats.h"
#include "Tank.h"
#include <memory>
using namespace std;


class WaterSupply {
    public:
        WaterSupply();
        static void getWater( int amount);
};


#endif //IMS_PROJECT_2020_WATERSUPPLY_H
