//
// Created by santiago on 11/09/18.
//

#ifndef TP_FASE1_TEST_WEAPON_H
#define TP_FASE1_TEST_WEAPON_H


#include "Projectile.h"

class Weapon {

    protected:
        int maxAmmo;
        int currentAmmo = maxAmmo;
        int fireRate = 5;
public:
    int getFireRate() const;

    void setFireRate(int fireRate);

    ~Weapon();
    Projectile shoot(int, int, bool, int);
};


#endif //TP_FASE1_TEST_WEAPON_H
