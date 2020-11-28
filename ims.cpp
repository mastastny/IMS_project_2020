#include "Tank.h"
#include <iostream>
#include <getopt.h>
#include <fstream>
#include "Weather.h"
using namespace std;

/**
 * Funkce, ktera se stara o zpracovani argumentu programu.
 * @param argc pocet argumentu programu
 * @param argv argumenty programu
 */

void parseArguments(int argc, char** argv) {
    int c;
    int aflag;
    int bflag;
    char* param;
    while ((c = getopt (argc, argv, "s:z:n:f:")) != -1)
        switch (c)
        {
            case 's':
                param = optarg;
                break;
            case 'z':
                param = optarg;
                break;
            case 'n':
                param = optarg;
                break;
            case 'f':
                param = optarg;
                Weather::getInstance(param);
                break;
            case '?':
                cerr << "[ERROR] Unknown option: " << (char)optopt << endl;
                exit(1);
            default:
                abort ();
        }
}

int main(int argc, char** argv) {
    parseArguments(argc, argv);
    cout << "jsem v main" << endl;
    Weather* weather = Weather::getInstance();
    while (weather->nextDay()) {
        cout << "DEN: " << weather->getDay() <<endl;
        cout << "DEST: " << weather->getRain() << endl;
        cout << weather->getTemperature() << endl;
        cout << weather->getNDaysRain(2)[0] << ", " << weather->getNDaysRain(2)[1] << endl;
        cout << "-----------" << endl;
    }

    /* CTENI ZE SOUBORU - TEST */

    /* NADRZ - ZKOUSKA INITU, NAPUSTENI NADRZE A PREPADU VODY + VYPIS STATS */
    int cap = 5000;
    Tank* tank = Tank::getInstance(&cap);
    tank->fill(3000);
    cout << tank->getWaterLevel() << endl;
    cout << tank->getMaxCapacity() << endl;
    tank->drainWater(6000);
    Stats::generateStats();
    return 0;
}
