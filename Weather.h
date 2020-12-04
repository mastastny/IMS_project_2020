//
// Created by Michael Kinc on 28/11/2020.
//

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "Stats.h"
using namespace std;

#ifndef IMS_PROJECT_2020_WEATHER_H
#define IMS_PROJECT_2020_WEATHER_H

enum weekDay {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};
#define NUMBER_OF_DAYS_PER_WEEK 7
#define NOTSET -1

class Weather {
    private:
        int day;
        double temperature;
        vector<double> rains;
        ifstream rainInFile;
        ifstream tempInFile;
        weekDay today;
        set<int> months;
        set<int> years;
        bool yearRestriction;
        int prevYear;

    public:
        Weather(string rainFile, string tempFile, set<int> monthsToRead);
        double getTemperature();
        double getRain();
        vector<double> getNDaysRain(int n);
        bool nextDay();
        int getDay();
        weekDay getDayOfTheWeek();
        void setYearRestriction(set<int> years);

};

#endif //IMS_PROJECT_2020_WEATHER_H
