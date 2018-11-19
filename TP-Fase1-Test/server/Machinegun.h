//
// Created by tito on 18/11/18.
//

#ifndef TP_FASE1_TEST_MACHINEGUN_H
#define TP_FASE1_TEST_MACHINEGUN_H


#include "Weapon.h"

class Machinegun : public Weapon {
public:
    Machinegun() {
        maxAmmo = 150;     //Como digo infinito?
        currentAmmo = maxAmmo;
        fireRate = 2;
    }

    ~Machinegun(){}
    
};


#endif //TP_FASE1_TEST_MACHINEGUN_H
