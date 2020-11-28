//
// Created by Michael Kinc on 28/11/2020.
//

#include "Stats.h"

/**
 * Staticky atribut tridy Stats, ktery reprezentuje mnozstvi vody vypustene do kanalu z jimky.
 */
double Stats::droppedWater = 0.0;

/**
 * Vypise na standardni vystup zachycene statistiky.
 */
void Stats::generateStats() {
    cout << "Prepad vody za rok [m3]: " << droppedWater << endl;
}

Stats::Stats() = default;
