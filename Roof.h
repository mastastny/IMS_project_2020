//
// Created by marek on 28.11.20.
//

#ifndef IMS_PROJECT_2020_ROOF_H
#define IMS_PROJECT_2020_ROOF_H

#include <vector>
#include "Weather.h"
#include "Tank.h"
using namespace std;

class Roof {
    static vector<Roof> roofs;
    private:
        int area = 666;
        float coef = 777;

    public:
        Roof(int area, float coefficient);
        static vector<Roof> getAllRoofs();
        void waterOutlet();
};


#endif //IMS_PROJECT_2020_ROOF_H
