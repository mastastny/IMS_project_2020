//
// Created by marek on 28.11.20.
//

#include "Roof.h"

vector<Roof> Roof::roofs;

Roof::Roof(int area, float coefficient) {
    this->area = area;
    coef = coefficient;
    roofs.push_back(*this);
}

    vector<Roof> Roof::getAllRoofs(){
    //vector<Roof*> cpyRoofs(roofs);
    //return roofs[n];
    return roofs;
}

void Roof::waterOutlet() {
    double rain;
    rain = Weather::getInstance()->getRain();
    int waterAmount = int(rain*(area)*(coef));
    Tank::getInstance()->fill(waterAmount);
}
