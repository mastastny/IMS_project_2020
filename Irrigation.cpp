//
// Created by Michael Kinc on 28/11/2020.
//

#include "Irrigation.h"

void Irrigation::irrigate(int amount) {
    Tank* tank = Tank::getInstance();
    tank->drainWater(amount);
}