#include "Tank.h"
#include <iostream>
#include <getopt.h>
#include "Weather.h"
#include "Roof.h"
#include "string"
#include "Irrigation.h"
#include <vector>
using namespace std;

vector<shared_ptr<Roof>> roofs;
shared_ptr<Weather> weather;
shared_ptr<Irrigation> sprinkler;
shared_ptr<Tank> tank;

vector<string> split(string myStr, string delimiter);
void parseArguments(int argc, char** argv);

int main(int argc, char** argv) {

    parseArguments(argc, argv);

    /*
     * Kalendar zavlazovani (4X TYDNE, 1 DAVKA = 5MM):
     * PO: ANO
     * UT: NE
     * ST: ANO
     * CT: NE
     * PA: ANO
     * SO: NE
     * NE: ANO
     */

    int supply = 0;
    while (weather->nextDay()) {
        supply = Stats::waterSupply;
        roofs[0]->waterOutlet(weather, tank);
        cout << "DEN: " << weather->getDay() <<endl;
        cout << "DEST: " << weather->getRain() << endl;
        cout << "TEPLOTA: " <<weather->getTemperature() << endl;
        cout<<"VODA V NADRZI: " << tank->getWaterLevel()<<endl;
        cout << endl;
        if (sprinkler->isIrrigationDay(weather)) {
            cout << "ZAVLAZUJI?: " << "ANO" << endl;
            sprinkler->irrigate(weather, tank);
            cout << "VODA V NADRZI PO ZAVLAZE: " << tank->getWaterLevel() << endl;
            cout << "DOPUSTENO: " << Stats::waterSupply - supply << endl;
        }
        else {
            cout << "ZAVLAZUJI?: " << "NE" << endl;
        }
        sprinkler->increaseCounter();
        cout << "-----------" << endl;
    }
    cout << "MNOZSTVI DOCERPAVANE VODY CELKEM: " << Stats::waterSupply << endl;
    return 0;
}

void parseArguments(int argc, char** argv) {
    int c;
    char* param;
    vector<string> parsedParam;

    if (argc != 9) {
        cerr << "[CHYBA] Nektery z argumentu neni zadan." << "\n" << "Spusteni: ./ims -r <plocha_strechy>:<koeficient> -g <plocha_zahrady> -t <objem_nadrze> -f <nazev_souboru_s_pocasim>" << endl;
        exit(1);
    }

    while ((c = getopt (argc, argv, "r:g:t:f:")) != -1)
        switch (c)
        {
            case 'r': {
                param = optarg;
                parsedParam = split(param, ":");
                int area = stoi(parsedParam[0]);
                float coefficient = stof(parsedParam[1]);
                auto r = make_shared<Roof>(area, coefficient);
                roofs.push_back(r);
                break;
            }
            case 'g':
                param = optarg;
                sprinkler = make_shared<Irrigation>(stoi(param), 5);
                break;
            case 't':
                param = optarg;
                tank = make_shared<Tank>(stoi(param));
                break;
            case 'f': {
                param = optarg;
                weather = make_shared<Weather>(param);
                break;
            }
            case '?':
                cerr << "[CHYBA] Neznamy argument: " << (char)optopt << endl;
                exit(1);
            default:
                abort ();
        }
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
