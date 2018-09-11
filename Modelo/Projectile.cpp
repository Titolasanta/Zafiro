//
// Created by santiago on 11/09/18.
//

#include "Projectile.h"

Projectile::Projectile(int posX, int posY, int velX, int velY) {

    positionX = posX;
    positionY = posY;

    velocityX = velX;
    velocityY = velY;

    accelerationX = 0;
    accelerationY = 0;

}

void Projectile::move() {   //No se si anda
    while ((0 < positionX)&&(positionX < 800)&&(0 < positionY)&&(positionY < 600)){ //Hacerlo mejor

        velocityX += accelerationX;
        velocityY += accelerationY;

        positionX += velocityX;
        positionY += velocityY;
    }
}