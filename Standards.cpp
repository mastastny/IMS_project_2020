//
// Created by Michael Kinc on 02/12/2020.
//

#include "Standards.h"

int Standards::din() {
    annualPrecInflow = roofArea * coeficient * annualPrecTotal * hydraulicFilterEff;
    annualWaterConsump = gardenArea * specificWaterDemand;
    dinTankVolume = min(annualPrecInflow, annualWaterConsump) * 0.114; //TODO
    return dinTankVolume;
}

int Standards::en() {
    annualPrecInflow = roofArea * coeficient * annualPrecTotal * hydraulicFilterEff;
    annualWaterConsump = gardenArea * specificWaterDemand;
    int dayWaterConsump = annualWaterConsump/184;
    enTankVolume = dayWaterConsump * 21;
    return enTankVolume;
}