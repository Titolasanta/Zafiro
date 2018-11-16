//
// Created by santiago on 11/09/18.
//

#ifndef TP_FASE1_TEST_WEAPON_H
#define TP_FASE1_TEST_WEAPON_H


#include "../common/Projectile.h"

class Weapon {

    protected:
        int maxAmmo;
        int currentAmmo = maxAmmo;
public:
    int getCurrentAmmo() const;

    void setCurrentAmmo(int currentAmmo);

protected:
    int fireRate = 5 * 12;
        int id = -1;
public:
    int getId() const;

    void setId(int id);

public:
    Weapon();
    int getFireRate() const;

    void setFireRate(int fireRate);

    ~Weapon();
    Projectile shoot(int, int, bool, int);
};


#endif //TP_FASE1_TEST_WEAPON_H
