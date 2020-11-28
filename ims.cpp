#include "Tank.h"
#include <iostream>
#include <getopt.h>
#include "Weather.h"
#include "Roof.h"
#include "string"
#include <sstream>
using namespace std;

/**
 * Funkce, ktera se stara o zpracovani argumentu programu.
 * @param argc pocet argumentu programu
 * @param argv argumenty programu
 */

vector<string> split(string myStr, string delimiter);


void parseArguments(int argc, char** argv) {
    int c;
    char* param;
    vector<string> parsedParam;

    while ((c = getopt (argc, argv, "r:g:t:f:")) != -1)
        switch (c)
        {
            case 'r': {
                param = optarg;
                parsedParam = split(param, ":");
                int area = stoi(parsedParam[0]);
                float coefficient = stof(parsedParam[1]);
                Roof(area, coefficient);
                Roof(51, 5.4);
                break;
            }
            case 'g':
                param = optarg;
                break;
            case 't':
                param = optarg;
                break;
            case 'f': {
                param = optarg;
                Weather::getInstance(param);
                break;
            }
            case '?':
                cerr << "[ERROR] Unknown option: " << (char)optopt << endl;
                exit(1);
            default:
                abort ();
        }
}

int main(int argc, char** argv) {

    parseArguments(argc, argv);
    Tank* tank = Tank::getInstance(5000);
    Weather* weather = Weather::getInstance();
    Roof roof = Roof::getAllRoofs()[0];


    cout << "jsem v main" << endl;


    while (weather->nextDay()) {
        roof.waterOutlet();

        cout << "DEN: " << weather->getDay() <<endl;
        cout << "DEST: " << weather->getRain() << endl;
        cout << weather->getTemperature() << endl;
        cout << weather->getNDaysRain(2)[0] << ", " << weather->getNDaysRain(2)[1] << endl;
        cout<<"voda v nadrzi: " << tank->getWaterLevel()<<endl;
        cout << "-----------" << endl;
    }

    /* CTENI ZE SOUBORU - TEST */

    /* NADRZ - ZKOUSKA INITU, NAPUSTENI NADRZE A PREPADU VODY + VYPIS STATS */


    return 0;
}

vector<string> split(string myStr, string delimiter) {
    size_t delimiterPosition;
    size_t end = 0;
    vector<string> temp;

    delimiterPosition = myStr.find_first_of(delimiter);
    temp.push_back(myStr.substr(0, delimiterPosition));
    temp.push_back(myStr.substr(delimiterPosition+1, myStr.size()-1));
    return temp;
}
