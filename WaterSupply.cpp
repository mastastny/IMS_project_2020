#include "WaterSupply.h"
extern shared_ptr<Tank> tank;

/**
 * Metoda, která zapíše do statistik, kolik bylo potřeba dopustit z vodovodního řadu.
 * @param amount
 */

void WaterSupply::getWater(int amount) {
    Stats::waterSupply(amount);
}

WaterSupply::WaterSupply() = default;

