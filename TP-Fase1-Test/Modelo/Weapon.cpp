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

        return Projectile(positionX, positionY, velX,  velY);
    }
    throw Projectile(0,0,0,0);
}

Weapon::~Weapon() = default;