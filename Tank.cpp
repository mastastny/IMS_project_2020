//
// Created by Michael Kinc on 28/11/2020.
//

#include "Tank.h"

Tank* Tank::instance = nullptr;

/**
 * Metoda, která slouží k přistupování k Tank. Pokud instance dane tridy jeste nebyla vytvorena, vytvori ji. Tato trida tedy vstupuje jako jedinacek.
 * @return vrací instanci tridy Tank
 */


Tank* Tank::getInstance(int *const capacity) {
    if (instance == nullptr) {
        instance = new Tank(capacity);
    }
    return instance;
}

/**
 * Konstruktor tridy Tank.
 * @param capacity maximalni kapacita akumulacni nadrze
 */

Tank::Tank(int* const capacity) {
    if (capacity != nullptr) {
        maxCapacity = *capacity;
    }
    else {
        cerr << "[CHYBA] Nadrz nema nastavenou maximalni kapacitu." << endl;
        exit(1);
    }
    waterLevel = 0.0;
}

/**
 * Funkce, ktera vraci aktualni zaplneni vodni nadrze
 * @return aktualni zaplneni
 */

double Tank::getWaterLevel() {
    return waterLevel;
}

/**
 * Metoda, ktera vraci maximalni kapacitu vodni nadrze.
 * @return maximalni mozne zaplneni
 */

double Tank::getMaxCapacity() {
    return maxCapacity;
}

/**
 * Metoda, ktera repzerentuje prepad vody.
 * @param amount mnozstvi vody, ktera se vypusti do kanalizace
 */

void Tank::dropWater(int amount) {
    Stats::droppedWater += amount;
    waterLevel = maxCapacity;
}

/**
 * Metoda, ktera naplni nadrz urcitym mnozstvim vody.
 * @param amount mnozstvi vody
 */

void Tank::fill(int amount) {
    waterLevel += amount;
    if (isTankOverfull()) {
        dropWater(waterLevel - maxCapacity);
    }
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
    else {
        WaterSupply::getWater(amount - waterLevel);
        waterLevel = 0;
    }
}