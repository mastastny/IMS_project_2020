//
// Created by Michael Kinc on 28/11/2020.
//

#include <iostream>
#include <vector>
#include <set>
using namespace std;

#ifndef IMS_PROJECT_2020_STATS_H
#define IMS_PROJECT_2020_STATS_H
#define DAYS_PER_YEAR 365

class Stats {
    public:
        Stats();
        static int roofArea;
        static float roofCoef;
        static int observedDays;
        static int totalDroppedWater;
        static int totalWaterSupply;
        static int roofWater;
        static int totalContainedWater;
        static int totalWaterUsed;
        static double totalRain;
        static int dinTankVolume;
        static int enTankVolume;
        static void din(int roofArea, float coeficient, double hydraulicFilterEff);
        static void en(int roofArea, float coeficient, double hydraulicFilterEff);
        static void generateStats();
        struct yearStats {
            int year = -1;
            int droppedWater = 0; //prepad vody
            int waterSupply = 0; //dopustena voda
            int containedWater = 0; //zachycena voda
            double rain = 0; //srazkovy uhrn za rok (v mm)
            int waterUsed = 0; //vyzalivana voda
        };
        static vector<yearStats> years;
        static void newYear(int year);
        static void containedWater(int amount);
        static void droppedWater(int amount);
        static void waterSupply(int amount);
        static void setMonths(set<int> months);
        static void usedWater(int amount);
        static void incrementRain(double amount);

};


#endif //IMS_PROJECT_2020_STATS_H
