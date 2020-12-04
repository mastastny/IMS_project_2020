//
// Created by Michael Kinc on 28/11/2020.
//

#include "Stats.h"

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
    cout << "Mnozstvi docerpane vody za rok [dm3]: " << totalWaterSupply << endl;
    //cout << "TotalWaterConsump: " << (Stats::totalWaterConsumpt)/29 << endl;//todo
    cout << "Celkové množství zadržené vody: " << Stats::totalContainedWater << endl;
    cout << "Celkové množství přepadlé vody: " << Stats::totalDroppedWater << endl;
    cout << "observedDays: " << Stats::observedDays << endl;
    cout << "Srazek celkem: " << Stats::totalRain << endl;
    Stats::din(Stats::roofArea, Stats::roofCoef, 0.95);
    Stats::en(Stats::roofArea, Stats::roofCoef, 0.95);
    cout << "DIN: " << Stats::dinTankVolume << endl;
    cout << "EN: " << Stats::enTankVolume << endl;
    //cout << "Celkove srazky za rok: " << Stats::rainTotalInYear << endl;

    cout << "+------------------------------------------------+" << endl;
    cout << "|\tROK\t|\tZACHYCENA VODA\t|\tPREPAD VODY\t|\tDOPUSTENA VODA\t|\tVYUZITA VODA\t|\tSRAZEK CELKEM\t|" << endl;
    cout << "+------------------------------------------------+" << endl;
    for (int i = 0; i < years.size(); i++) {
        cout << "|\t" << years[i].year << "\t|\t" << years[i].containedWater << "\t|\t" << years[i].droppedWater << "\t|\t" << years[i].waterSupply << "\t|\t" << years[i].waterUsed << "\t|\t" << years[i].rain << endl;
        cout << "+------------------------------------------------+" << endl;
    }
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
                                                    //prumerny rocni srazkovy uhrn v mm
    int annualPrecInflow = roofArea * coeficient * totalRain/years.size() * hydraulicFilterEff;//0.95
    int annualWaterConsump = totalWaterUsed/years.size();// deleno rokama
    int res = min(annualPrecInflow, annualWaterConsump) * ((float)observedDays / (float)DAYS_PER_YEAR);
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





