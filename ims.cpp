#include "Tank.h"
#include <iostream>
#include <getopt.h>
#include <fstream>
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
                cout << param << endl;
                break;
            case 'z':
                param = optarg;
                cout << param << endl;
                break;
            case 'n':
                param = optarg;
                cout << param << endl;
                break;
            case 'f':
                param = optarg;
                cout << param << endl;
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

    /* CTENI ZE SOUBORU - TEST */
    ifstream infile("pocasi");
    double a, b;
    while (infile >> a >> b)
    {
        cout << "Srazky: " << a << ", " << "Teplota: " << b << endl;
    }

    /* NADRZ - ZKOUSKA INITU, NAPUSTENI NADRZE A PREPADU VODY + VYPIS STATS */
    double cap = 3;
    Tank* tank = Tank::getInstance(&cap);
    tank->fill(8.0);
    cout << tank->getWaterLevel() << endl;
    cout << tank->getMaxCapacity() << endl;
    Stats::generateStats();
    return 0;
}
