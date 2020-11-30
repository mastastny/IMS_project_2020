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
    public:
        int area = 666;
        float coef = 777;
        Roof(int area, float coefficient);
        void waterOutlet(shared_ptr<Weather> weather, shared_ptr<Tank> tank);
};


#endif //IMS_PROJECT_2020_ROOF_H
