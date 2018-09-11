//
// Created by santiago on 11/09/18.
//

#ifndef TP_FASE1_TEST_PISTOL_H
#define TP_FASE1_TEST_PISTOL_H


#include "Weapon.h"

class Pistol : public Weapon{

    private:
        int fireRate = 1;

    public:
        Pistol();
        ~Pistol();

};


#endif //TP_FASE1_TEST_PISTOL_H
