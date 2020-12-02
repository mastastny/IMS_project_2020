#include "Tank.h"
#include <iostream>
#include <getopt.h>
#include "Weather.h"
#include "Roof.h"
#include "string"
#include "Irrigation.h"
#include <vector>
#include <memory>
#include "split.h"
using namespace std;

vector<shared_ptr<Roof>> roofs;
shared_ptr<Weather> weather;
shared_ptr<Irrigation> sprinkler;
shared_ptr<Tank> tank;

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


    while (weather->nextDay()) {
        roofs[0]->waterOutlet(weather, tank);
        //roofs[1]->waterOutlet(weather, tank);
        sprinkler->irrigate(weather,tank);
        cout << "-----------" << endl;
    }

    Stats::generateStats();
    cout << "Prumerna spotrebovana za rok: " << (Stats::trappedWater + Stats::waterSupply)/29 << endl;
    cout << "TotalWaterConsump: " << (Stats::totalWaterConsumpt)/29 << endl;
    return 0;
}

void parseArguments(int argc, char** argv) {
    int c;
    char* param;
    vector<string> parsedParam;

    if (argc < 9) {
        cerr << "[CHYBA] Nektery z argumentu neni zadan." << "\n" << "Spusteni: ./ims -r <plocha_strechy>:<koeficient> -g <plocha_zahrady> -t <objem_nadrze> -f <nazev_souboru_s_pocasim>" << endl;
        exit(1);
    }

    while ((c = getopt (argc, argv, "r:g:t:f:")) != -1)
        switch (c) {
            case 'r': {
                param = optarg;
                parsedParam = split(param, ":");
                int area = stoi(parsedParam[0]);
                float coefficient = stof(parsedParam[1]);

                auto r = make_shared<Roof>(area, coefficient,parsedParam[2]);
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
                parsedParam = split(param, ":");
                weather = make_shared<Weather>(parsedParam[0], parsedParam[1]);
                break;
            }
            case '?':
                cerr << "[CHYBA] Neznamy argument: " << (char)optopt << endl;
                exit(1);
            default:
                abort ();
        }
}




