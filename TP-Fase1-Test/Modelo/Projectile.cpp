//
// Created by santiago on 11/09/18.
//

#include <iostream>
#include "Projectile.h"

Projectile::Projectile(int posX, int posY, int velX, int velY) {

    positionX = posX;
    positionY = posY;

    velocityX = velX;
    velocityY = velY;

    accelerationX = 0;
    accelerationY = 0;

}

bool Projectile::inSight(Scene& scene) {

    int camX = scene.getCamera()->x;
    int camY = scene.getCamera()->y;
    return ((0 + camX < positionX )&&(positionX  < 800 + camX )&&(0 + camY < positionY)&&(positionY < 600+ camY));

}

void Projectile::move() {   //No se si anda

        velocityX += accelerationX;
        velocityY += accelerationY;

        positionX += velocityX;
        positionY += velocityY;
    }


int Projectile::getPositionX() const {
    return positionX;
}

void Projectile::setPositionX(int positionX) {
    Projectile::positionX = positionX;
}

int Projectile::getPositionY() const {
    return positionY;
}

void Projectile::setPositionY(int positionY) {
    Projectile::positionY = positionY;
}

int Projectile::getVelocityX() const {
    return velocityX;
}

void Projectile::setVelocityX(int velocityX) {
    Projectile::velocityX = velocityX;
}

int Projectile::getVelocityY() const {
    return velocityY;
}

void Projectile::setVelocityY(int velocityY) {
    Projectile::velocityY = velocityY;
}
