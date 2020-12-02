//
// Created by Michael Kinc on 28/11/2020.
//

#include "Stats.h"

Stats::Stats() = default;

/**
 * Staticky atribut tridy Stats, ktery reprezentuje mnozstvi vody vypustene do kanalu z jimky.
 */
int Stats::droppedWater = 0;

int Stats::waterSupply = 0;

/**
 * Vypise na standardni vystup zachycene statistiky.
 */
void Stats::generateStats() {
    cout << "Prepad vody za rok [dm3]: " << droppedWater << endl;
    cout << "Mnozstvi docerpane vody za rok [dm3]: " << waterSupply << endl;

}
