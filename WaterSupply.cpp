//
// Created by Michael Kinc on 28/11/2020.
//

#include "WaterSupply.h"

void WaterSupply::getWater(int amount) {
    Stats::waterSupply += amount;
}

WaterSupply::WaterSupply() = default;

