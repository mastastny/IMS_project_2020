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
#include "Stats.h"
using namespace std;

//#define TEST

vector<shared_ptr<Roof>> roofs;
shared_ptr<Weather> weather;
shared_ptr<Irrigation> sprinkler;
shared_ptr<Tank> tank;

void parseArguments(int argc, char** argv);
void Config(string configFile);


int main(int argc, char** argv) {

    parseArguments(argc, argv);
    while (weather->nextDay()) {
        sprinkler->irrigate(weather,tank);
        roofs[0]->waterOutlet(weather, tank);
        #ifdef TEST
        cout << "-----------" << endl;
        #endif
    }
    Stats::generateStats();
    return 0;
}



void Config(string configFile){
bool rainIsSet, tempIsSet, monthsAreSet, yearsRestrictionSet= false;
string rainFile, tempFile;
set<int> months;
set<int> years;

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

    for(int lineIdx = 0; lineIdx < lines.size(); lineIdx ++) {
        if (lines[lineIdx][0] == "garden") {
            sprinkler = make_shared<Irrigation>(stoi(lines[lineIdx][1]), 5);
        }
        if (lines[lineIdx][0] == "tank") {
            tank = make_shared<Tank>(stoi(lines[lineIdx][1]));
        }
        if (lines[lineIdx][0] == "roof") {
            int area = stoi(lines[lineIdx][1]);
            float coefficient = stof(lines[lineIdx][2]);

            auto r = make_shared<Roof>(area, coefficient,lines[lineIdx][3]);
            roofs.push_back(r);
        }
        if(lines[lineIdx][0] == "months"){

            for(int i = 1; i< lines[lineIdx].size(); i++){
                months.insert(stoi(lines[lineIdx][i]));
            }
            monthsAreSet = true;
            Stats::setMonths(months);
        }
        else if(lines[lineIdx][0] =="rain"){
                rainFile = lines[lineIdx][1];
            rainIsSet = true;
        }
        else if(lines[lineIdx][0] =="temperatures"){
                tempFile = lines[lineIdx][1];
                tempIsSet = true;
        }
        else if(lines[lineIdx][0] =="yearsRestriction"){

            for(int i = 1; i< lines[lineIdx].size(); i++) {
                years.insert(stoi(lines[lineIdx][i]));
            }
           yearsRestrictionSet = true;
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
        if(yearsRestrictionSet){
            weather->setYearRestriction(years);
        }
    }
    else{
        cerr<<"Rain or Temperature file is missing";
        exit(1);
    }

}

void parseArguments(int argc, char** argv) {
    int c;
    char* param;
    vector<string> parsedParam;

    if (argc < 3) {
        cerr << "[CHYBA] Nektery z argumentu neni zadan." << "\n" << "Spusteni: ./ims -r <plocha_strechy>:<koeficient> -g <plocha_zahrady> -t <objem_nadrze> -f <nazev_souboru_s_pocasim>" << endl;
        exit(1);
    }

    while ((c = getopt (argc, argv, "c:")) != -1)
        switch (c) {
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


