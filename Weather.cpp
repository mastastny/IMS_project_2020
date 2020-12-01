//
// Created by Michael Kinc on 28/11/2020.
//

#include "Weather.h"
#include "split.h"

Weather::Weather(string rainFileName, string tempFileName) {
    today = Monday;
    day = 1;
    rainInFile.open(rainFileName, ios::in);

    if (!rainInFile) {
        cerr << "[CHYBA] Nelze otevrit soubor s nazvem " << "\"" << rainFileName << "\"" << endl;
        exit(1);
    }

    tempInFile.open(tempFileName, ios::in);
    temperature = 0.0;
    if (!tempInFile) {
        cerr << "[CHYBA] Nelze otevrit soubor s nazvem " << "\"" << tempFileName << "\"" << endl;
        exit(1);
    }
}

bool Weather::nextDay() {
    int year1, month1, day1 ;
    int year2, month2, day2 ;
    string line;
    vector<string> tmp;
    string tmpString;
//year1 >> month1 >> day1 >> input_temperature
    if (tempInFile >> line)
    {
        tmp = split(line, ";");
        year1 = stoi(tmp[0]);
        month1 = stoi(tmp[1]);
        day1 = stoi(tmp[2]);
        tmpString = tmp[3];
        tmpString = preprocessFloat(tmpString);
        temperature = stof(tmpString);
    }
    else {
        return false;
    }

    if (rainInFile >> line)
    {
        tmp = split(line, ";");
        year2 = stoi(tmp[0]);
        month2 = stoi(tmp[1]);
        day2 = stoi(tmp[2]);
        tmpString = tmp[3];
        tmpString = preprocessFloat(tmpString);
        rains.push_back(stof(tmpString));
    }
    else {
        return false;
    }

    if(year1 != year2 or month1 != month2 or day1 != day2){
        cerr<< "Vstupni soubory nejsou synchronizovany, jednotlive radky neodpovidaji stejnym dnum"<<endl;
        exit(1);
    }

    //set another day
    today = static_cast<weekDay>((static_cast<int>(today) + 1) % NUMBER_OF_DAYS_PER_WEEK);
    day++;
    return true;
}

double Weather::getTemperature() {
    return temperature;
}

double Weather::getRain() {
    return rains.back();
}

weekDay Weather::getDay() {
    return today;
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