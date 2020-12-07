#include "Weather.h"
#include "split.h"

//# define TESTING

/**
 * Konstruktor třídy Weather. Otevírá soubory, ze kterých se čte srážkový úhrn a teplota
 * @param rainFileName jméno souboru se srážkami
 * @param tempFileName jméno souboru s teplotami
 * @param monthsToRead měsíce, na které se zaměřujeme
 */

Weather::Weather(string rainFileName, string tempFileName, set<int> monthsToRead) {
    prevYear = NOTSET;
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

/**
 * Metoda, který zajišťuje iteraci po jednom dni a zpracovává data ze vstupních souborů.
 * @return vrací úspěch operace
 */

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

        rains.push_back(stof(rainString));

        if(yearRestriction){
            if(years.find(year1) == years.end())
                continue;
        }
        if(months.find(month1) != months.end()){

            if(prevYear == NOTSET){
                prevYear = year1;
                Stats::newYear(year1);
            }
            else{
                if (prevYear != year1) {
                    prevYear = year1;
                    Stats::newYear(year1);
                    today = Monday;
                }

            }

            //set another day
            today = static_cast<weekDay>((static_cast<int>(today) + 1) % NUMBER_OF_DAYS_PER_WEEK);
            day++;
            Stats::newDay();
            temperature = stof(tempString);
            Stats::incrementRain(stof(rainString));
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

/**
 * Metoda, která vrací aktuální teplotu
 * @return teplota
 */

double Weather::getTemperature() {
    return temperature;
}

/**
 * Metoda, která vrací aktuální srážkový úhrn.
 * @return srážky v mm
 */

double Weather::getRain() {
    return rains.back();
}

/**
 * Metoda, která vrací, co je dnes za den
 * @return den
 */

weekDay Weather::getDayOfTheWeek() {
    return today;
}

/**
 * Metoda, která vrací, kolikátý den simulace právě probíhá.
 * @return den
 */

int Weather::getDay() {
    return day;
}

/**
 * Metoda, která vrací vektor dešťů za posledních N dní.
 * @param n počet zkoumanách dní
 * @return vrací vektor se srážkovými úhrny
 */

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

/**
 * Metoda, která nastaví, na jaké dny se v simulaci omezujeme.
 * @param yearsToUse množina roků
 */

void Weather::setYearRestriction(set<int> yearsToUse){
    yearRestriction = true;
    years = yearsToUse;
}