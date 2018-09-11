//
// Created by santiago on 11/09/18.
//

#ifndef TP_FASE1_TEST_WEAPON_H
#define TP_FASE1_TEST_WEAPON_H


class Weapon {

    protected:
        int maxAmmo;
        int currentAmmo = maxAmmo;
        int fireRate;

    public:
        Weapon(){};
        ~Weapon();
        void shoot(int, int, bool, int);
};


#endif //TP_FASE1_TEST_WEAPON_H
