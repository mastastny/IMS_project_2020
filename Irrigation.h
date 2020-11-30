//
// Created by Michael Kinc on 28/11/2020.
//

#include "Tank.h"
#include "Weather.h"

#ifndef IMS_PROJECT_2020_IRRIGATION_H
#define IMS_PROJECT_2020_IRRIGATION_H


class Irrigation {
    public:
        explicit Irrigation(int gardenArea, int dosePerDay);
        void irrigate(shared_ptr<Weather> weather, shared_ptr<Tank> tank);
        void increaseCounter();
        int getIrrigationCounter();

    private:
        int area;
        int irrigationCounter;
        double standardDose;
        int hydrawise(shared_ptr<Weather> weather);

};


#endif //IMS_PROJECT_2020_IRRIGATION_H
