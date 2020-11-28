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


class Weather {
    private:
        int day;
        double temperature;
        vector<double> rains;
        ifstream inFile;
        static Weather* instance;
        Weather(char* fileName);
    public:
        double getTemperature();
        double getRain();
        vector<double> getNDaysRain(int n);
        bool nextDay();
        int getDay();
        static Weather* getInstance(char* const fileName = nullptr);

};


#endif //IMS_PROJECT_2020_WEATHER_H
