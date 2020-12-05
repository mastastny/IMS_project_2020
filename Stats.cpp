//
// Created by Michael Kinc on 28/11/2020.
//

#include "Stats.h"
#include <iomanip>

Stats::Stats() = default;

/**
 * Staticky atribut tridy Stats, ktery reprezentuje mnozstvi vody vypustene do kanalu z jimky.
 */
int Stats::totalDroppedWater = 0;
int Stats::totalWaterSupply = 0;
int Stats::roofWater = 0;
int Stats::totalWaterUsed = 0;
int Stats::dinTankVolume = 0;
int Stats::enTankVolume = 0;
double Stats::totalRain = 0;
int Stats::totalContainedWater = 0;
vector<Stats::yearStats> Stats::years;
int Stats::observedDays = 0;
int Stats::roofArea = 0;
float Stats::roofCoef = 0.0;

/**
 * Vypise na standardni vystup zachycene statistiky.
 */
void Stats::generateStats() {
#define YEARLEN 9
    cout  <<left<<setw(YEARLEN)<<setfill('-')<< "+";
    cout  <<left<<setw(23)<<setfill('-')<< "+";
    cout  <<left<<setw(23)<<setfill('-')<< "+";
    cout  <<left<<setw(23)<<setfill('-')<< "+";
    cout  <<left<<setw(23)<<setfill('-')<< "+";
    cout  <<left<<setw(23)<<setfill('-')<< "+";
    cout  <<right<< "+"<<endl;
    cout<<"|  "<<left<<setw(YEARLEN -3 )<<setfill(' ')<<"ROK";
    cout<<"|  "<<left<<setw(20)<<setfill(' ')<<"ZACHYCENA VODA";
    cout<<"|  "<<left<<setw(20)<<setfill(' ')<<"PREPAD VODY";
    cout<<"|  "<<left<<setw(20)<<setfill(' ')<<"DOPUSTENA VODA";
    cout<<"|  "<<left<<setw(20)<<setfill(' ')<<"VYUZITA VODA";
    cout<<"|  "<<left<<setw(20)<<setfill(' ')<<"SRAZEK CELKEM"<<"|"<<endl;
    cout  <<left<<setw(YEARLEN)<<setfill('-')<< "+";
    cout  <<left<<setw(23)<<setfill('-')<< "+";
    cout  <<left<<setw(23)<<setfill('-')<< "+";
    cout  <<left<<setw(23)<<setfill('-')<< "+";
    cout  <<left<<setw(23)<<setfill('-')<< "+";
    cout  <<left<<setw(23)<<setfill('-')<< "+";
    cout  <<right<< "+"<<endl;
    for (int i = 0; i < years.size(); i++) {
        //cout << "|\t" << years[i].year << "\t\t|\t" << years[i].containedWater << "\t\t\t|\t" << years[i].droppedWater << "\t\t|\t" << years[i].waterSupply << "\t\t\t|\t" << years[i].waterUsed << "\t\t\t|\t" << years[i].rain << "\t\t|"<<endl;
        cout<<"|  "<<left<<setw(YEARLEN-3)<<setfill(' ')<<years[i].year;
        cout<<"|  "<<left<<setw(20)<<setfill(' ')<<years[i].containedWater;
        cout<<"|  "<<left<<setw(20)<<setfill(' ')<<years[i].droppedWater;
        cout<<"|  "<<left<<setw(20)<<setfill(' ')<<years[i].waterSupply;
        cout<<"|  "<<left<<setw(20)<<setfill(' ')<<years[i].waterUsed;
        cout<<"|  "<<left<<setw(20)<<setfill(' ')<<years[i].rain<<"|"<<endl;
        cout  <<left<<setw(YEARLEN)<<setfill('-')<< "+";
        cout  <<left<<setw(23)<<setfill('-')<< "+";
        cout  <<left<<setw(23)<<setfill('-')<< "+";
        cout  <<left<<setw(23)<<setfill('-')<< "+";
        cout  <<left<<setw(23)<<setfill('-')<< "+";
        cout  <<left<<setw(23)<<setfill('-')<< "+";
        cout  <<right<< "+"<<endl;


    }

    cout<<endl;
    cout << "Celkové množství dočerpané vody [dm3]: " << totalWaterSupply << endl;
    cout << "Celkové množství zadržené vody: " << Stats::totalContainedWater << endl;
    cout << "Celkové množství přepadlé vody: " << Stats::totalDroppedWater << endl;
    cout << "Celkové množství srážek: " << Stats::totalRain << endl;
    cout<<endl;
    cout << "Průměrné roční zavlažování: " << Stats::totalWaterUsed/years.size() << endl;
    cout << "Průměrné roční srážky: " << Stats::totalRain/years.size() << endl;
    Stats::din(Stats::roofArea, Stats::roofCoef, 0.95);
    Stats::en(Stats::roofArea, Stats::roofCoef, 0.95);
    cout<<endl;
    cout << "DIN: " << Stats::dinTankVolume << endl;
    cout << "EN: " << Stats::enTankVolume << endl;

    //cout << "Celkove srazky za rok: " << Stats::rainTotalInYear << endl;
}

void Stats::newYear(int year) {
    yearStats y;
    y.year = year;
    years.push_back(y);
}

void Stats::en(int roofArea, float coeficient, double hydraulicFilterEff) {
    int annualPrecInflow = roofArea * coeficient * totalRain/29 * hydraulicFilterEff;
    int annualWaterConsump = totalWaterUsed/years.size();
    int dayWaterConsump = annualWaterConsump / observedDays;
    enTankVolume = dayWaterConsump * 21;
}

void Stats::din(int roofArea, float coeficient, double hydraulicFilterEff) {
    float rainlessPeriodCoeff = 21.0/(float)observedDays;                                                //prumerny rocni srazkovy uhrn v mm
    int annualPrecInflow = roofArea * coeficient * totalRain/years.size() * hydraulicFilterEff;//0.95
    int annualWaterConsump = totalWaterUsed/years.size();// deleno rokama
    int res = (float)min(annualPrecInflow, annualWaterConsump) * rainlessPeriodCoeff;
    dinTankVolume = res;
}

void Stats::containedWater(int amount) {
    years.back().containedWater += amount;
    totalContainedWater += amount;
}

void Stats::droppedWater(int amount) {
    years.back().droppedWater += amount;
    totalDroppedWater += amount;
}

void Stats::waterSupply(int amount) {
    years.back().waterSupply += amount;
    totalWaterSupply += amount;
}

void Stats::usedWater(int amount) {
    years.back().waterUsed += amount;
    totalWaterUsed += amount;
}

void Stats::incrementRain(double amount) {
    years.back().rain += amount;
    totalRain += amount;
}

void Stats::setMonths(set<int> months) {
    for (auto elem : months) {
        if (elem == 4 or elem == 6 or elem == 9 or elem == 11) {
            observedDays += 30;
        }
        else if (elem == 2) {
            observedDays += 28;
        }
        else {
            observedDays += 31;
        }
    }
}