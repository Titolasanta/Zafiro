//
// Created by santiago on 11/09/18.
//

#include "Weapon.h"
#include "Projectile.h"


void Weapon::shoot(int positionX, int positionY, bool lookingRight, int direction) {

    if (currentAmmo > 0){

        int velX = (lookingRight*10);
        int velY = (direction*10);
        positionX += velX;
        positionY += velY;
        Projectile projectile(positionX, positionY, velX,  velY);
        projectile.move();
        currentAmmo--;

        //Hacer algo con este proyectil. Se mueve?
        //Hacer algo para que el fireRate afecte la velocidad con la que dispara
    }
}
Weapon::~Weapon() {}