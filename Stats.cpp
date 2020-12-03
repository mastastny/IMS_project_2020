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
int Stats::roofWater = 0;
int Stats::totalWaterConsumpt = 0;
int Stats::dinTankVolume = 0;
int Stats::enTankVolume = 0;
int Stats::totalRain = 0;
int Stats::containedWater = 0;
double Stats::rainTotalInYear = 0;

/**
 * Vypise na standardni vystup zachycene statistiky.
 */
void Stats::generateStats() {
    cout << "Mnozstvi docerpane vody za rok [dm3]: " << waterSupply << endl;
    cout << "TotalWaterConsump: " << (Stats::totalWaterConsumpt)/29 << endl;//todo
    cout << "Celkové množství zadržené vody: " << Stats::containedWater << endl;
    cout << "Celkové množství přepadlé vody: " << Stats::droppedWater << endl;
    cout << "Celkove srazky za rok: " << Stats::rainTotalInYear << endl;
}

void Stats::en(int roofArea, double coeficient, double hydraulicFilterEff) {
    int annualPrecInflow = roofArea * coeficient * totalRain/29 * hydraulicFilterEff;
    int annualWaterConsump = totalWaterConsumpt/29;
    int dayWaterConsump = annualWaterConsump/184;
    enTankVolume = dayWaterConsump * 21;
}

void Stats::din(int roofArea, double coeficient, double hydraulicFilterEff) {
    int annualPrecInflow = roofArea * coeficient * totalRain/29 * hydraulicFilterEff;
    int annualWaterConsump = totalWaterConsumpt/29;
    dinTankVolume = min(annualPrecInflow, annualWaterConsump) * 0.114; //TODO
}




