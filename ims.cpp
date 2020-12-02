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
#include <set>
using namespace std;

vector<shared_ptr<Roof>> roofs;
shared_ptr<Weather> weather;
shared_ptr<Irrigation> sprinkler;
shared_ptr<Tank> tank;

void parseArguments(int argc, char** argv);
void Config(string configFile);

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

//    if (argc < 9) {
//        cerr << "[CHYBA] Nektery z argumentu neni zadan." << "\n" << "Spusteni: ./ims -r <plocha_strechy>:<koeficient> -g <plocha_zahrady> -t <objem_nadrze> -f <nazev_souboru_s_pocasim>" << endl;
//        exit(1);
//    }

    while ((c = getopt (argc, argv, "r:g:t:f:c:")) != -1)
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

            case 'c': {
                param = optarg;
                Config(param);
                break;
            }
            case '?':
                cerr << "[CHYBA] Neznamy argument: " << (char)optopt << endl;
                exit(1);
            default:
                abort ();
        }
}

void Config(string configFile){
bool rainIsSet, tempIsSet, monthsAreSet = false;
string rainFile, tempFile;
set<int> months;

vector<vector<string>> lines;
ifstream fileStream;
fileStream.open(configFile);
    if (!fileStream) {
        cerr << "[CHYBA] Nelze otevrit konfiguracni soubor: " << "\"" << configFile << "\"" << endl;
        exit(1);
    }
    string line;
    while(getline(fileStream, line)){
        lines.push_back(split(line,":"));
    }

    for(int lineIdx = 0; lineIdx < lines.size(); lineIdx ++){
        if(lines[lineIdx][0] == "months"){

            for(int i = 1; i< lines[lineIdx].size(); i++){
                months.insert(stoi(lines[lineIdx][i]));
            }
            monthsAreSet = true;
        }
        else if(lines[lineIdx][0] =="rain"){
                rainFile = lines[lineIdx][1];
            rainIsSet = true;
        }
        else if(lines[lineIdx][0] =="temperatures"){
                tempFile = lines[lineIdx][1];
                tempIsSet = true;
        }
    }

    if(rainIsSet and tempIsSet){
        if(!monthsAreSet){
            set<int> implicitMonths({1,2,3,4,5,6,7,8,9,10,11,12});
            weather = make_shared<Weather>(rainFile, tempFile, implicitMonths);
        }
        else{
            weather = make_shared<Weather>(rainFile, tempFile, months);
        }
    }
    else{
        cerr<<"Rain or Temperature file is missing";
        exit(1);
    }

}


