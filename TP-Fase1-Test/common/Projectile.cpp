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
        angle = (float) (angle - M_PI/FRECUENCIA);
        positionY = (int) (positionY + tmep);
        if(angle == 0) angle = (float) (2 * M_PI);
    } else {
        positionY += velocityY;
        positionX += velocityX;
    }
}


int Projectile::getPositionX() const { return positionX; }
int Projectile::getPositionY() const { return positionY; }
int Projectile::getOwnerId() { return ownerId; }
