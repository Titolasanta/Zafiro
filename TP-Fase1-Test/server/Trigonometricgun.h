//
// Created by tito on 18/11/18.
//

#ifndef TP_FASE1_TEST_SHOTGUN_H
#define TP_FASE1_TEST_SHOTGUN_H


#include "Weapon.h"

class Trigonometricgun : public Weapon {
public:
    Trigonometricgun() {
        maxAmmo = 50;     //Como digo infinito?
        currentAmmo = maxAmmo;
    }

    ~Trigonometricgun(){}
    
    Projectile shoot(int positionX, int positionY, bool lookingRight, int direction) override{

        if (currentAmmo > 0){

            int velX;
            int velY;

            if(lookingRight) velX = 35;
            else velX = -35;

            velY = (direction*35);
            
            positionX += velX;
            positionY += velY;

            currentAmmo--;

            //el +10 en y es para matchear la altura del arma
            Projectile projectile(positionX, positionY + 20, velX,  velY,id);
            projectile.setAngle(2 * M_PI);
            return projectile;
        }
        throw Projectile(0,0,0,0,id);
    }
};


#endif //TP_FASE1_TEST_SHOTGUN_H
