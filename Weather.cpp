//
// Created by Michael Kinc on 28/11/2020.
//

#include "Weather.h"
#include "split.h"

//# define TESTING



Weather::Weather(string rainFileName, string tempFileName, set<int> monthsToRead) {
    today = Monday;
    day = 0;
    yearRestriction = false;
    months = monthsToRead;
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
    string tempLine, rainLine;
    vector<string> tmp;
    string tempString;
    string rainString;
//year1 >> month1 >> day1 >> input_temperature

    while(tempInFile >> tempLine and rainInFile >> rainLine ) {

            tmp = split(tempLine, ";");
            year1 = stoi(tmp[0]);
            month1 = stoi(tmp[1]);
            day1 = stoi(tmp[2]);
        tempString = tmp[3];
        tempString = preprocessFloat(tempString);

            tmp = split(rainLine, ";");
            year2 = stoi(tmp[0]);
            month2 = stoi(tmp[1]);
            day2 = stoi(tmp[2]);
            rainString = tmp[3];
            rainString = preprocessFloat(rainString);

        if (year1 != year2 or month1 != month2 or day1 != day2) {
            cerr << "Vstupni soubory nejsou synchronizovany, jednotlive radky neodpovidaji stejnym dnum" << endl;
            exit(1);
        }

        if(yearRestriction){
            if(years.find(year1) == years.end())
                continue;
        }
        if(months.find(month1) != months.end()){

            if(prevYear == NOTSET){
                prevYear = year1;
            }
            else{
                cout<<"ahoj"<<endl;
            }



            //set another day
            today = static_cast<weekDay>((static_cast<int>(today) + 1) % NUMBER_OF_DAYS_PER_WEEK);
            day++;
            temperature = stof(tempString);
            rains.push_back(stof(rainString));
            Stats::rainTotalInYear += stof(rainString);
#ifdef TESTING
            cout << "DEN: " << this->getDay() <<endl;
            cout << "DEST: " << this->getRain() << endl;
            cout << "TEPLOTA: " <<this->getTemperature() << endl;
#endif
            return true;
        }
    }
    return false;
}

double Weather::getTemperature() {
    return temperature;
}

double Weather::getRain() {
    return rains.back();
}

weekDay Weather::getDayOfTheWeek() {
    return today;
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

void Weather::setYearRestriction(set<int> yearsToUse){
    yearRestriction = true;
    years = yearsToUse;
}