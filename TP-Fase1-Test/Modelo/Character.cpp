//
// Created by fede on 06/09/18.
//

#include <Vista/Logger.h>
#include "Character.h"

extern Logger *gplogger;

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


    gplogger->log(2, "Se creó el personaje");
}
void Character::land(int x, int y) {

    airborne = false;
    if(getVelocityX() != 0)
        walking = true;
    velocityY = 0;
    currentPlatX = x;
    currentPlatY = y;

    gplogger->log(3, "El personaje aterriza");
}

void Character::time() {

    if (positionX < 3) {
        positionX = 1;
        velocityX = 0;
    }
    if (positionX > 697) {
        positionX = 699;
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
            gplogger->log(3, "El personaje mira hacia la derecha");
        }
    }
    else {
        if (lookingRight){
            positionX -= 3;
            lookingRight = false;
            gplogger->log(3, "El personaje mira hacia la izquierda");
        }
    }

    if (crouching) return;

    velocityX = velX;

    gplogger->log(3, "El personaje se mueve");

    if(!airborne)
        walking = true;
}



void Character::jump(int velY) {

    if (airborne) return;

    velocityY = velY;

    airborne = true;
    walking = false;

    gplogger->log(3, "El personaje salta");
}

void Character::standStill() {
    velocityX = 0;
    walking = false;

    gplogger->log(3, "El personaje salta");
}

void Character::aim(int direction) {
    aimDirection = direction;
}

void Character::shoot() {
    weapon.shoot(positionX, positionY, lookingRight, aimDirection);

    gplogger->log(3, "El personaje dispara");
}

void Character::stand() {
    if (crouching) positionY -= 5;
    crouching = false;

    gplogger->log(3, "El personaje se para");
}

void Character::crouch() {
    if (airborne||crouching) return;
    this->standStill();
    positionY += 5;
    crouching = true;

    gplogger->log(3, "El personaje se agacha");
}

void Character::takeDamage() {
    if (hitPoints > 0) hitPoints--;
    else dead = true;
    //RIP Destruirlo o algo
}