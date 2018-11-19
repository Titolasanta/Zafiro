//
// Created by santiago on 11/09/18.
//

#include <iostream>
#include "Projectile.h"

#define AMPLITUD 40
#define FRECUENCIA 2
Projectile::Projectile(int posX, int posY, int velX, int velY,int duenoId) {

    positionX = posX;
    positionY = posY;

    velocityX = velX;
    velocityY = velY;

    ownerId = duenoId;
}

bool Projectile::inSight(SDL_Rect *cam) {
    int camX = cam->x;
    int camY = cam->y;
    return ((0 + camX < positionX )&&(positionX  < 800 + camX )&&(0 + camY < positionY)&&(positionY < 600+ camY));
}

void Projectile::move() {   //No se si anda
    if(angle != 0) {
        float tmep = velocityY  + AMPLITUD * sin(angle);
        angle = (angle - M_PI/FRECUENCIA);
        positionY += tmep;
        if(angle == 0)
            angle = 2 * M_PI;
    } else

        positionY += velocityY;
        positionX += velocityX;
}


int Projectile::getPositionX() const { return positionX; }
void Projectile::setPositionX(int positionX) { Projectile::positionX = positionX; }

int Projectile::getPositionY() const { return positionY; }
void Projectile::setPositionY(int positionY) { Projectile::positionY = positionY; }

int Projectile::getVelocityX() const { return velocityX; }
void Projectile::setVelocityX(int velocityX) { Projectile::velocityX = velocityX; }

int Projectile::getVelocityY() const { return velocityY; }
void Projectile::setVelocityY(int velocityY) { Projectile::velocityY = velocityY; }

int Projectile::getOwnerId() { return ownerId; }
