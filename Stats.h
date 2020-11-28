//
// Created by Michael Kinc on 28/11/2020.
//

#include <iostream>
using namespace std;

#ifndef IMS_PROJECT_2020_STATS_H
#define IMS_PROJECT_2020_STATS_H

class Stats {
    public:
        Stats();
        static int droppedWater;
        static int waterSupply;
        static void generateStats();
};


#endif //IMS_PROJECT_2020_STATS_H
