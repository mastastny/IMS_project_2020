//
// Created by Michael Kinc on 28/11/2020.
//

#include "Tank.h"
#include "Weather.h"
#include "Stats.h"
#include <memory>

#ifndef IMS_PROJECT_2020_IRRIGATION_H
#define IMS_PROJECT_2020_IRRIGATION_H


class Irrigation {
    public:
        explicit Irrigation(int gardenArea, int dosePerDay);
        void irrigate(shared_ptr<Weather> weather, shared_ptr<Tank> tank);
        void increaseCounter();
        bool isIrrigationDay(shared_ptr<Weather> weather);

    private:
        int area;
        double standardDose;
        int countDose(shared_ptr<Weather> weather);
        double totalRain(vector<double> rains);

};


#endif //IMS_PROJECT_2020_IRRIGATION_H
