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
bool Stats::shouldPrintYears = false;
float Stats::priceForCubicMeter = 0;

/**
 * Vypise na standardni vystup hodnoty pro jednotlive roky.
 */

void Stats::printYears() {
#define YEARLEN 9
    cout  <<left<<setw(YEARLEN)<<setfill('-')<< "+";
    cout  <<left<<setw(23)<<setfill('-')<< "+";
    cout  <<left<<setw(23)<<setfill('-')<< "+";
    cout  <<left<<setw(23)<<setfill('-')<< "+";
    cout  <<left<<setw(23)<<setfill('-')<< "+";
    cout  <<left<<setw(23)<<setfill('-')<< "+";
    cout  <<right<< "+"<<endl;
    cout<<"|  "<<left<<setw(YEARLEN -3 )<<setfill(' ')<<"ROK";
    cout<<"|  "<<left<<setw(20)<<setfill(' ')<<"ZACHYCENA VODA [l]";
    cout<<"|  "<<left<<setw(20)<<setfill(' ')<<"PREPAD VODY [l]";
    cout<<"|  "<<left<<setw(20)<<setfill(' ')<<"DOPUSTENA VODA [l]";
    cout<<"|  "<<left<<setw(20)<<setfill(' ')<<"VYUZITA VODA [l]";
    cout<<"|  "<<left<<setw(20)<<setfill(' ')<<"SRAZEK CELKEM [mm]"<<"|"<<endl;
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
}

/**
 * Vypise na standardni vystup zakladni ekonomicke hodnoty
 */

void Stats::money() {
    cout  <<left<<setw(44)<<setfill('-')<< "+";
    cout  <<left<<setw(13)<<setfill('-')<< "+";
    cout  <<right<< "+"<<endl;
    cout<<"|  "<<left<<setw(41)<<setfill(' ')<< "Prumerna rocni cena za dopusteni [Kc]: ";
    cout<<"|  "<<left<<setw(10)<<setfill(' ')<< ((float)totalWaterSupply*(Stats::priceForCubicMeter/1000))/years.size() << "|" << endl;
    cout  <<left<<setw(44)<<setfill('-')<< "+";
    cout  <<left<<setw(13)<<setfill('-')<< "+";
    cout  <<right<< "+"<<endl;
    cout<<"|  "<<left<<setw(41)<<setfill(' ')<< "Prumerna rocni ztrata v prepadu [Kc]: ";
    cout<<"|  "<<left<<setw(10)<<setfill(' ')<< ((float)totalDroppedWater*(Stats::priceForCubicMeter/1000))/years.size() << "|" << endl;
    cout  <<left<<setw(44)<<setfill('-')<< "+";
    cout  <<left<<setw(13)<<setfill('-')<< "+";
    cout  <<right<< "+"<<endl;
    cout<<"|  "<<left<<setw(41)<<setfill(' ')<< "Realne usetreno v prumeru za rok [Kc]: ";
    cout<<"|  "<<left<<setw(10)<<setfill(' ')<< ((float)(totalContainedWater)*(Stats::priceForCubicMeter/1000))/years.size() << "|" << endl;
    cout  <<left<<setw(44)<<setfill('-')<< "+";
    cout  <<left<<setw(13)<<setfill('-')<< "+";
    cout  <<right<< "+"<<endl;
}

/**
 * Vypise na standardni vystup zachycene statistiky.
 */

void Stats::generateStats() {
    bool areYearsContinuous = true;
    for (auto it = years.begin(); it != years.end(); ++it) {
        if (it != years.begin()) {
            if (it->year - 1 != prev(it)->year) {
                areYearsContinuous = false;
                break;
            }
        }
    }
    if (areYearsContinuous) {
        if (years.size() == 1) {
            cout << "Simulace probihala pro rok ";
            cout << years.front().year << endl;
        }
        else {
            cout << "Simulace probihala pro roky ";
            cout << years.front().year << " - " << years.back().year << "." << endl;
        }
    }
    else {
        cout << "Simulace probihala pro roky ";
        for (auto it = years.begin(); it != years.end(); ++it) {
            if (next(it) != years.end()) {
                cout << it->year << ", ";
            }
            else {
                cout << it->year << "." << endl;
            }
        }
    }
    if (shouldPrintYears) {
        printYears();
    }
    cout  <<left<<setw(44)<<setfill('-')<< "+";
    cout  <<left<<setw(13)<<setfill('-')<< "+";
    cout  <<right<< "+"<<endl;
    cout<<"|  "<<left<<setw(41)<<setfill(' ')<< "Celkove mnozstvi zachycene vody [l]: ";
    cout<<"|  "<<left<<setw(10)<<setfill(' ')<< Stats::totalContainedWater << "|" << endl;
    cout  <<left<<setw(44)<<setfill('-')<< "+";
    cout  <<left<<setw(13)<<setfill('-')<< "+";
    cout  <<right<< "+"<<endl;
    cout<<"|  "<<left<<setw(41)<<setfill(' ')<< "Celkove mnozstvi prepadle vody [l]: ";
    cout<<"|  "<<left<<setw(10)<<setfill(' ')<< Stats::totalDroppedWater << "|" << endl;
    cout  <<left<<setw(44)<<setfill('-')<< "+";
    cout  <<left<<setw(13)<<setfill('-')<< "+";
    cout  <<right<< "+"<<endl;
    cout<<"|  "<<left<<setw(41)<<setfill(' ')<< "Celkove mnozstvi docerpane vody [l]: ";
    cout<<"|  "<<left<<setw(10)<<setfill(' ')<< Stats::totalWaterSupply << "|" << endl;
    cout  <<left<<setw(44)<<setfill('-')<< "+";
    cout  <<left<<setw(13)<<setfill('-')<< "+";
    cout  <<right<< "+"<<endl;
    cout<<"|  "<<left<<setw(41)<<setfill(' ')<< "Celkove mnozstvi srazek [mm]: ";
    cout<<"|  "<<left<<setw(10)<<setfill(' ')<< Stats::totalRain<< "|" << endl;
    cout  <<left<<setw(44)<<setfill('-')<< "+";
    cout  <<left<<setw(13)<<setfill('-')<< "+";
    cout  <<right<< "+"<<endl;
    cout<<endl;
    cout  <<left<<setw(54)<<setfill('-')<< "+";
    cout  <<left<<setw(13)<<setfill('-')<< "+";
    cout  <<right<< "+"<<endl;
    cout<<"|  "<<left<<setw(51)<<setfill(' ')<< "Prumerna rocni spotreba vody pro zalivku [l]: ";
    cout<<"|  "<<left<<setw(10)<<setfill(' ')<< Stats::totalWaterUsed/years.size() << "|" << endl;
    cout  <<left<<setw(54)<<setfill('-')<< "+";
    cout  <<left<<setw(13)<<setfill('-')<< "+";
    cout  <<right<< "+"<<endl;
    cout<<"|  "<<left<<setw(51)<<setfill(' ')<< "Prumerny rocni uhrn srazek [mm]: ";
    cout<<"|  "<<left<<setw(10)<<setfill(' ')<< Stats::totalRain/years.size()<< "|" << endl;
    cout  <<left<<setw(54)<<setfill('-')<< "+";
    cout  <<left<<setw(13)<<setfill('-')<< "+";
    cout  <<right<< "+"<<endl;
    //cout << "Průměrné roční zavlažování: " << Stats::totalWaterUsed/years.size() << endl;
    //cout << "Průměrný roční úhrn srážek: " << Stats::totalRain/years.size() << endl;
    Stats::din(Stats::roofArea, Stats::roofCoef, 0.95);
    Stats::en(Stats::roofArea, Stats::roofCoef, 0.95);
    cout<<endl;
    cout  <<left<<setw(64)<<setfill('-')<< "+";
    cout  <<left<<setw(13)<<setfill('-')<< "+";
    cout  <<right<< "+"<<endl;
    cout<<"|  "<<left<<setw(61)<<setfill(' ')<< "Navrh akumulacni jimky podle normy EN 16941-1 [l]: ";
    cout<<"|  "<<left<<setw(10)<<setfill(' ')<< Stats::enTankVolume << "|" << endl;
    cout  <<left<<setw(64)<<setfill('-')<< "+";
    cout  <<left<<setw(13)<<setfill('-')<< "+";
    cout  <<right<< "+"<<endl;
    cout<<"|  "<<left<<setw(61)<<setfill(' ')<< "Navrh akumulacni jimky podle normy DIN 1989 - 1:2001 [l]: ";
    cout<<"|  "<<left<<setw(10)<<setfill(' ')<< Stats::dinTankVolume<< "|" << endl;
    cout  <<left<<setw(64)<<setfill('-')<< "+";
    cout  <<left<<setw(13)<<setfill('-')<< "+";
    cout  <<right<< "+"<<endl;
    cout << endl;
    money();
    //cout << "DIN: " << Stats::dinTankVolume << endl;
    //cout << "EN: " << Stats::enTankVolume << endl;

    //cout << "Celkove srazky za rok: " << Stats::rainTotalInYear << endl;
}

/**
 * Nastaví nový rok - vytvoří novou proměnnou typu yearStats a uloží ji do vektoru roků.
 * @param year rok
 */

void Stats::newYear(int year) {
    yearStats y;
    y.year = year;
    years.push_back(y);
}

/**
 * Metoda, ktera počítá velikost akumulační nádrže pro normu EN 16941-1
 * @param roofArea velikost strechy
 * @param coeficient pritokovy koeficient strechy
 * @param hydraulicFilterEff efektivita hydraulickeho filtru
 */

void Stats::en(int roofArea, float coeficient, double hydraulicFilterEff) {
    int annualPrecInflow = roofArea * coeficient * totalRain/29 * hydraulicFilterEff;
    int annualWaterConsump = totalWaterUsed/years.size();
    int dayWaterConsump = annualWaterConsump / years.back().numberOfDays;
    enTankVolume = dayWaterConsump * 21;
}

/**
 * Metoda, ktera počítá velikost akumulační nádrže pro normu DIN 1989 - 1:2001
 * @param roofArea velikost strechy
 * @param coeficient pritokovy koeficient strechy
 * @param hydraulicFilterEff efektivita hydraulickeho filtru
 */

void Stats::din(int roofArea, float coeficient, double hydraulicFilterEff) {
    float rainlessPeriodCoeff = 21.0/(float)years.back().numberOfDays;                                                //prumerny rocni srazkovy uhrn v mm
    int annualPrecInflow = roofArea * coeficient * totalRain/years.size() * hydraulicFilterEff;//0.95
    int annualWaterConsump = totalWaterUsed/years.size();// deleno rokama
    int res = (float)min(annualPrecInflow, annualWaterConsump) * rainlessPeriodCoeff;
    dinTankVolume = res;
}

/**
 * Metoda, která přičítá zachycenou vodu pro aktuální rok i celkově,
 * @param amount množství
 */

void Stats::containedWater(int amount) {
    years.back().containedWater += amount;
    totalContainedWater += amount;
}

/**
 * Metoda, která přičítá přepadlou vodu pro aktuální rok i celkově,
 * @param amount množství
 */

void Stats::droppedWater(int amount) {
    years.back().droppedWater += amount;
    totalDroppedWater += amount;
}

/**
 * Metoda, která přičítá dočerpanou vodu pro aktuální rok i celkově,
 * @param amount množství
 */

void Stats::waterSupply(int amount) {
    years.back().waterSupply += amount;
    totalWaterSupply += amount;
}

/**
 * Metoda, která přičítá využitou vodu pro aktuální rok i celkově,
 * @param amount množství
 */

void Stats::usedWater(int amount) {
    years.back().waterUsed += amount;
    totalWaterUsed += amount;
}

/**
 * Metoda, která přičítá srazkovy urh pro aktuální rok i celkově,
 * @param amount množství
 */

void Stats::incrementRain(double amount) {
    years.back().rain += amount;
    totalRain += amount;
}

/**
 * Metoda, která počíta, s kolik dny v roce pracujeme
 * @param months množina měsíců, se kterými pracujeme
 */

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

/**
 * Metoda, ktera nastavi novy den.
 */

void Stats::newDay() {
    years.back().numberOfDays += 1;
}