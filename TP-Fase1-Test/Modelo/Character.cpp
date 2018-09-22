//
// Created by fede on 06/09/18.
//

#include "Character.h"

Character::Character(int posX, int posY) {
    // XML deberia chequear que las posiciones esten
    // en el rango valido de la ventana
    positionX = posX;
    positionY = posY;
    velocityX = 0;
    velocityY = 0;
    accelerationX = 0;
    accelerationY = 0;
    walking = false;
    lookingRight = true;
    crouching = false;
    dead = false;
    airborne = true;
    aimDirection = 0;


    //Loggear creacion del personaje
}
void Character::land(int x, int y) {

    airborne = false;
    if(getVelocityX() != 0)
        walking = true;
    velocityY = 0;
    currentPlatX = x;
    currentPlatY = y;
}

void Character::time() {

    if (positionX < 5) {
        positionX = 5;
        velocityX = 0;
    }
    if (positionX > 700) {
        positionX = 700;
        velocityX = 0;
    }

    if(positionY > 600) {
        positionY = 0;
        velocityY = 0;
    }

    if (currentPlatX + largoPlataforma + changui < positionX + velocityX || currentPlatX  > changui + positionX + velocityX)
        airborne = true;


    if(airborne)
        velocityY += 4;


    velocityY += accelerationY;

    velocityX += accelerationX;
    positionX += velocityX;

    positionY += velocityY;
}

Character::~Character() = default; //Loggear destruccion

void Character::move(int velX) {

    if (velX > 0) {
        if (!lookingRight) {
            positionX += 3;
            lookingRight = true;
        }
    }
    else {
        if (lookingRight){
            positionX -= 3;
            lookingRight = false;}
    }

    if (crouching) return;

    velocityX = velX;

    if(!airborne)
        walking = true;
}



void Character::jump(int velY) {

    if (airborne) return;

    velocityY = velY;

    airborne = true;
    walking = false;
}

void Character::standStill() {
    velocityX = 0;
    walking = false;
}

void Character::aim(int direction) {
    aimDirection = direction;
}

void Character::shoot() {
    weapon.shoot(positionX, positionY, lookingRight, aimDirection);
}

void Character::stand() {
    if (crouching) positionY -= 5;
    crouching = false;
}

void Character::crouch() {
    if (airborne||crouching) return;
    this->standStill();
    positionY += 5;
    crouching = true;
}

void Character::takeDamage() {
    if (hitPoints > 0) hitPoints--;
    else dead = true;
    //RIP Destruirlo o algo
}