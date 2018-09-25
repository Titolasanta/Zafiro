//
// Created by santiago on 11/09/18.
//

#include "Weapon.h"
#include "Projectile.h"


Projectile Weapon::shoot(int positionX, int positionY, bool lookingRight, int direction) {

    if (currentAmmo > 0){

        int velX;
        int velY;

        if(lookingRight) velX = 10;
        else velX = -10;

        velY = (direction*10);

        positionX += velX;
        positionY += velY;

        currentAmmo--;

        //el +10 en y es para matchear la altura del arma
        return Projectile(positionX, positionY + 20, velX,  velY);
    }
    throw Projectile(0,0,0,0);
}

int Weapon::getFireRate() const {
    return fireRate;
}

void Weapon::setFireRate(int fireRate) {
    Weapon::fireRate = fireRate;
}

Weapon::~Weapon() = default;
