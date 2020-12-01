//
// Created by Michael Kinc on 28/11/2020.
//

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#ifndef IMS_PROJECT_2020_WEATHER_H
#define IMS_PROJECT_2020_WEATHER_H

enum weekDay {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};
#define NUMBER_OF_DAYS_PER_WEEK 7

class Weather {
    private:
        int day;
        double temperature;
        vector<double> rains;
        ifstream rainInFile;
        ifstream tempInFile;
        weekDay today;
    public:
        Weather(string fileName, string tempFileName);
        double getTemperature();
        double getRain();
        vector<double> getNDaysRain(int n);
        bool nextDay();
        weekDay getDay();

};


#endif //IMS_PROJECT_2020_WEATHER_H
