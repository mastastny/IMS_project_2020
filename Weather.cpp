//
// Created by Michael Kinc on 28/11/2020.
//

#include "Weather.h"

Weather::Weather(char *fileName) {
    inFile.open(fileName, ios::in);
    temperature = 0.0;
    if (!inFile) {
        cerr << "[CHYBA] Nelze otevrit soubor s nazvem " << "\"" << fileName << "\"" << endl;
        exit(1);
    }
}

bool Weather::nextDay() {
    double a;
    double b;
    if (inFile >> a >> b)
    {
        day++;
        rains.push_back(a);
        temperature = b;
        return true;
    }
    else {
        return false;
    }
}

double Weather::getTemperature() {
    return temperature;
}

double Weather::getRain() {
    return rains.back();
}

int Weather::getDay() {
    return day;
}

vector<double> Weather::getNDaysRain(int n) {
    if (n >= rains.size()) {
        vector<double> newVect(rains);
        return newVect;
    }
    else {
        auto first = rains.begin() + (rains.size() - n);
        auto last = rains.end();
        vector<double> newVect(first, last);
        return newVect;
    }
}