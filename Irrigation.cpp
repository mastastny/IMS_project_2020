//
// Created by Michael Kinc on 28/11/2020.
//
#define TESTING
#include "Irrigation.h"

void Irrigation::irrigate(shared_ptr<Weather> weather, shared_ptr<Tank> tank) {
    if(isIrrigationDay(weather)) {
        int waterConsumption = countDose(weather);
        tank->drainWater(waterConsumption);
#ifdef TESTING
cout << "Mnozsti vody na zalevani: " << waterConsumption << endl;
#endif
    }
}

int Irrigation::countDose(shared_ptr<Weather> weather) {
  double dose = standardDose;

  if(weather->getTemperature() < 3.0){
      dose = 0;
    #ifdef TESTING
    cout<<"teplota < 3";
    #endif
  }
  if(weather->getTemperature() < 15.0){
      dose = standardDose * 0.7;
    #ifdef TESTING
    cout<<"teplota < 15";
    #endif
  }
  if(weather->getTemperature() > 30.0){
      dose = standardDose * 1.3;
    #ifdef TESTING
    cout<<"teplota > 30";
    #endif
  }
  if(totalRain(weather->getNDaysRain(1)) > 3.0){
      dose = 0;
    #ifdef TESTING
    cout<<"srazky za poslednich 24 hod > 3 ";
    #endif
  }
  if(totalRain(weather->getNDaysRain(3)) > 13.0){
      dose = 0;
    #ifdef TESTING
    cout<<"srazky za posledni tri dny > 13 ";
    #endif
  }

    #ifdef TESTING
    cout<<" dose: "<<dose<<endl;
    #endif
  return area*dose;
}

bool Irrigation::isIrrigationDay(shared_ptr<Weather> weather) {
    weekDay today = weather->getDay();
    if (today == Monday or
        today == Wednesday or
        today == Friday or
        today == Sunday) {
        return true;
    }
    else{
        return false;
    }
}

Irrigation::Irrigation(int area, int dosePerDay) {
    this->area = area;
    standardDose = dosePerDay;
}


double Irrigation::totalRain(vector<double> rains){
    double totRain = 0;
    for (double i : rains) {
        totRain += i;
    }
    return totRain;
}