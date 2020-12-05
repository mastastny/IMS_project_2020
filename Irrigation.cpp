//
// Created by Michael Kinc on 28/11/2020.
//
//#define TESTING
#include "Irrigation.h"

/*
 * Kalendar zavlazovani (4X TYDNE, 1 DAVKA = 5MM):
 * PO: NE
 * UT: ANO
 * ST: ANO
 * CT: NE
 * PA: ANO
 * SO: NE
 * NE: ANO
 */
void Irrigation::irrigate(shared_ptr<Weather> weather, shared_ptr<Tank> tank) {
#ifdef TESTING
int supply = Stats::waterSupply;
cout <<"\t" << "ZAVLAZOVANI "<< endl;
#endif


    if(isIrrigationDay(weather)) {
        tank->prefill(maxWaterNeeded);
        int waterConsumption = countDose(weather);
        tank->drainWater(waterConsumption);
        Stats::usedWater(waterConsumption);

#ifdef TESTING
cout <<"\t"<< "Mnozsti vody na zalevani: " << waterConsumption << endl;
cout <<"\t" << "VODA V NADRZI PO ZAVLAZE: " << tank->getWaterLevel() << endl;
cout <<"\t" << "DOPUSTENO: " << Stats::waterSupply - supply << endl;
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
  double a = totalRain(weather->getNDaysRain(2));
  double b = totalRain(weather->getNDaysRain(1));
  if( (a-b) > 3.0){
      dose = 0;
    #ifdef TESTING
    cout<<"srazky za poslednich 24 hod > 3 ";
    #endif
  }
   a = totalRain(weather->getNDaysRain(4));
   b = totalRain(weather->getNDaysRain(1));
  if((a-b) > 13.0){
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
    weekDay today = weather->getDayOfTheWeek();
    if (today == Tuesday or
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
    maxWaterNeeded = (int)roundUptoHundreds(area * dosePerDay * 1.3);
}


double Irrigation::totalRain(vector<double> rains){
    double totRain = 0;
    for (double i : rains) {
        totRain += i;
    }
    return totRain;
}

double Irrigation::roundUptoHundreds(double number){
        int intNum = number;
        return intNum + 100 - (intNum % 100);
}