//#define TESTING
#include "Irrigation.h"

/*
 * Kalendar zavlazovani (4X TYDNE, 1 DAVKA = 5MM):
 * PO: ANO
 * UT: ANO
 * ST: ME
 * CT: ANO
 * PA: NE
 * SO: ANO
 * NE: NE
 */

/**
 * Metoda, ktera zavlazi travnik urcitym mnozstvim vody.
 * @param weather objekt pocasi
 * @param tank objekt nadrze
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

/**
 * Metoda, ktera pocita, jakou davkou se ma zavlazit travnik.
 * @param weather objekt pocasi
 * @return vraci davku, kterou se ma zavlazit travnik
 */

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

/**
 * Metoda, ktera zjistuje, jestli je dnes den, kdy zavlauzjeme.
 * @param weather objekt pocasu
 * @return vraci pravdivostni hodnotu
 */

bool Irrigation::isIrrigationDay(shared_ptr<Weather> weather) {
    weekDay today = weather->getDayOfTheWeek();
    if (today == Monday or
        today == Tuesday or
        today == Thursday or
        today == Saturday) {
        return true;
    }
    else{
        return false;
    }
}

/**
 * Konstruktor tridy Irrigiation. Nastavi plochu, kterou chceme zavlažovat, a standardni denni davku.
 * @param area plocha zahrady
 * @param dosePerDay standardni denni davka
 */

Irrigation::Irrigation(int area, int dosePerDay) {
    this->area = area;
    standardDose = dosePerDay;
    maxWaterNeeded = (int)roundUptoHundreds(area * dosePerDay * 1.3);
}

/**
 * Metoda, ktera dostane vektor srazkovych uhrnu a spocita jejich soucet.
 * @param rains vektor srazkovych uhrnu
 * @return vraci soucet srazkovych uhrnu
 */

double Irrigation::totalRain(vector<double> rains){
    double totRain = 0;
    for (double i : rains) {
        totRain += i;
    }
    return totRain;
}

/**
 * Metoda, ktera zaokrouhli cislo na vyssi stovky.
 * @param number zaokrouhlovano cislo
 * @return vraci zaokrouhlene cislo
 */

double Irrigation::roundUptoHundreds(double number){
        int intNum = number;
        return intNum + 100 - (intNum % 100);
}