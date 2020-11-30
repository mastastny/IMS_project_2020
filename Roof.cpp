//
// Created by marek on 28.11.20.
//

#include "Roof.h"

Roof::Roof(int area, float coefficient) {
    this->area = area;
    coef = coefficient;
}

void Roof::waterOutlet(shared_ptr<Weather> weather, shared_ptr<Tank> tank) {
    double rain;
    rain = weather->getRain();
    int waterAmount = int(rain*(area)*(coef));
    tank->fill(waterAmount);
}
