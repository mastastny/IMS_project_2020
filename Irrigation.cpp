//
// Created by Michael Kinc on 28/11/2020.
//

#include "Irrigation.h"

void Irrigation::irrigate(shared_ptr<Weather> weather, shared_ptr<Tank> tank) {
    tank->drainWater(countDose(weather));
}

int Irrigation::countDose(shared_ptr<Weather> weather) {
    double thirty = ((standardDose*area)/100)*30;
    if (weather->getTemperature() < 15) {
        return (int)(standardDose*area-thirty);
    }
    else if (weather->getTemperature() > 30) {
        return (int)(standardDose*area+thirty);
    }
    else {
        return (int)(standardDose*area);
    }
}

bool Irrigation::isIrrigationDay(shared_ptr<Weather> weather) {
    if (irrigationCounter != 1 and irrigationCounter != 3 and irrigationCounter != 5 and irrigationCounter != 7) {
        return false;
    }
    else {
        double threeDaysRain = 0;
        vector<double> threeDaysRainVec =  weather->getNDaysRain(3);
        for (double i : threeDaysRainVec) {
            threeDaysRain += i;
        }
        return weather->getTemperature() > 3 && weather->getNDaysRain(1)[0] < 3 && threeDaysRain < 13;
    }
}

Irrigation::Irrigation(int area, int dosePerDay) {
    this->area = area;
    irrigationCounter = 1;
    standardDose = dosePerDay;
}

void Irrigation::increaseCounter() {
    if (irrigationCounter == 7) {
        irrigationCounter = 1;
    }
    else {
        irrigationCounter++;
    }
}