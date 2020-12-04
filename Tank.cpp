//
// Created by Michael Kinc on 28/11/2020.
//

#include "Tank.h"

//#define TEST
/**
 * Konstruktor tridy Tank.
 * @param capacity maximalni kapacita akumulacni nadrze
 */

Tank::Tank(int capacity) {
    maxCapacity = capacity;
    waterLevel = 0;
}

/**
 * Funkce, ktera vraci aktualni zaplneni vodni nadrze
 * @return aktualni zaplneni
 */

int Tank::getWaterLevel() {
    return waterLevel;
}

/**
 * Metoda, ktera vraci maximalni kapacitu vodni nadrze.
 * @return maximalni mozne zaplneni
 */

int Tank::getMaxCapacity() {
    return maxCapacity;
}

/**
 * Metoda, ktera repzerentuje prepad vody.
 * @param amount mnozstvi vody, ktera se vypusti do kanalizace
 */

void Tank::dropWater(int amount) {
    Stats::droppedWater(amount);
    waterLevel = maxCapacity;
#ifdef TEST
    cout<<"prepad vody: " << amount<<endl;
#endif
}

/**
 * Metoda, ktera naplni nadrz urcitym mnozstvim vody.
 * @param amount mnozstvi vody
 */

void Tank::fill(int amount) {
    int waterToDrop = 0;
    waterLevel += amount;
#ifdef TEST
    cout<<"do nadrze nateklo: " << amount  <<endl;
#endif
    if (isTankOverfull()) {
        waterToDrop = waterLevel - maxCapacity;
        dropWater(waterToDrop);
    }
    Stats::containedWater(amount - waterToDrop);
}

/**
 * Metoda, ktera zjistuje, zda nebude mit nadrz po napusteni vetsi kapacitu, nez je maximalni. Pokud ano, vypusti prebytecnou vodu do kanalu
 * @return
 */

bool Tank::isTankOverfull() {
    return waterLevel > maxCapacity;
}

void Tank::drainWater(int amount) {
    if (amount > maxCapacity) {
        cout << "Nadrz s kapacitou " << maxCapacity << " litrů není vhodná pro vase potreby zavlazovani." << endl;
        exit(0);
    }
    if (waterLevel >= amount) {
        waterLevel -= amount;
    }
    else{
        cerr<<"cerpani vetsiho mnozstvi vody z nadrze nez kolik obsahuje."<<endl;
        exit(0);
    }
}

void Tank::prefill(int volumeOfWater){
    int amountToGet = ( (volumeOfWater - waterLevel) < 0) ? 0 : volumeOfWater - waterLevel;
    WaterSupply::getWater(amountToGet);
    waterLevel += amountToGet;
}