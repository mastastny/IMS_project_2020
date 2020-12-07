//
// Created by marek on 28.11.20.
//

#include "Roof.h"

//#define TEST

/**
 * Konstruktor třídy Roof. Nastavuje jeji rozlohu, pritokovy koeficient a nazev
 * @param area rozloha strechy
 * @param coefficient pritokovy koeficient
 * @param id nazev
 */

Roof::Roof(int area, float coefficient, string id) {
    Stats::roofArea = area;
    this->area = area;
    coef = coefficient;
    Stats::roofCoef = coefficient;
    this->id = id;
}

/**
 * Metoda, ktera se stara o sber vody ze strechy.
 * @param weather objekt pocasu
 * @param tank objekt nadrze
 */

void Roof::waterOutlet(shared_ptr<Weather> weather, shared_ptr<Tank> tank) {
    double rain;
    rain = weather->getRain();
    int waterAmount = int(rain*(area)*(coef));
    if(waterAmount > 0) {
        tank->fill(waterAmount);
        Stats::roofWater += waterAmount;
    }
    #ifdef TEST
        if(waterAmount > 0) {
            cout << "střecha: " << id << " pridala do nadrze: " << waterAmount << "[dm3] vody" << endl;
        }
    #endif
}
