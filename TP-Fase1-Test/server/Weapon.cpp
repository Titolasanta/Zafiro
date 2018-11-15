//
// Created by santiago on 11/09/18.
//

#include "Weapon.h"
#include "../common/Projectile.h"


Weapon::Weapon() = default;

Projectile Weapon::shoot(int positionX, int positionY, bool lookingRight, int direction) {

    if(id == -1){
        throw "no tengo dueño";
    }
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
        return Projectile(positionX, positionY + 20, velX,  velY,id);
    }
    throw Projectile(0,0,0,0,id);
}

int Weapon::getFireRate() const {
    return fireRate;
}

void Weapon::setFireRate(int fireRate) {
    Weapon::fireRate = fireRate;
}

int Weapon::getId() const {
    return id;
}

void Weapon::setId(int id) {
    Weapon::id = id;
}

Weapon::~Weapon() = default;
