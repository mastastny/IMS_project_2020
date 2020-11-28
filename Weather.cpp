//
// Created by Michael Kinc on 28/11/2020.
//

#include "Weather.h"

Weather* Weather::instance = nullptr;

Weather * Weather::getInstance(char *const fileName) {
    if (instance == nullptr) {
        instance = new Weather(fileName);
    }
    return instance;
}

Weather::Weather(char *fileName) {
    if (fileName != nullptr) {
        inFile.open(fileName, ios::in);
        temperature = 0.0;
        if (!inFile) {
            cerr << "[CHYBA] Nelze otevrit soubor s nazvem " << "\"" << fileName << "\"" << endl;
            exit(1);
        }
    }
    else {
        cerr << "[CHYBA] Neni nastaven soubor pro cteni dat pocasi." << endl;
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
        vector<double>::const_iterator first = rains.begin() + (rains.size() - n);
        vector<double>::const_iterator last = rains.end();
        vector<double> newVect(first, last);
        return newVect;
    }
}