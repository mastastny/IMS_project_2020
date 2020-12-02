//
// Created by Michael Kinc on 02/12/2020.
//

#include <iostream>
using namespace std;

#ifndef IMS_PROJECT_2020_STANDARDS_H
#define IMS_PROJECT_2020_STANDARDS_H

class Standards {
    public:
        int din();
        int en();
    private:
        int annualPrecInflow;
        int roofArea;
        int coeficient;
        int annualPrecTotal;
        int hydraulicFilterEff;
        int annualWaterConsump;
        int gardenArea;
        int specificWaterDemand;
        int dinTankVolume;
        int enTankVolume;
};


#endif //IMS_PROJECT_2020_STANDARDS_H
