#ifndef IMS_PROJECT_2020_WATERSUPPLY_H
#define IMS_PROJECT_2020_WATERSUPPLY_H

#include "Stats.h"
#include "Tank.h"
#include <memory>
using namespace std;

/**
 * Třída reperentující vodovodní řad.
 */

class WaterSupply {
    public:
        WaterSupply();
        static void getWater( int amount);
};


#endif //IMS_PROJECT_2020_WATERSUPPLY_H
