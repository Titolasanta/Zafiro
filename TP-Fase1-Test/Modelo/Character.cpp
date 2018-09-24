//
// Created by fede on 06/09/18.
//

#include "Character.h"
#include "Projectile.h"

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
void Character::land(int x, int y,int w) {

    airborne = false;
    if(getVelocityX() != 0)
        walking = true;
    velocityY = 0;
    currentPlatX = x;
    currentPlatW = w;
    currentPlatY = y;
}

void Character::time() {



    if (currentPlatX + currentPlatW  < positionX + velocityX || currentPlatX  >  positionX + velocityX)
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

Projectile Character::shoot() {
    try {
        return weapon.shoot(positionX, positionY, lookingRight, aimDirection);
    } catch(...){
        changeWeapon(Weapon());
    }

    return weapon.shoot(positionX, positionY, lookingRight, aimDirection);
}
void Character::changeWeapon(Weapon weapon){
    weapon = weapon;
}


void Character::stand() {
    if (crouching) positionY -= 20;
    crouching = false;
}

void Character::crouch() {
    if (airborne||crouching) return;
    this->standStill();
    positionY += 20;
    crouching = true;
}

void Character::takeDamage() {
    if (hitPoints > 0) hitPoints--;
    else dead = true;
    //RIP Destruirlo o algo
}

void Character::goThroughPlatform(){
    positionY += 55;
    airborne = true;
    crouching = false;
}

void Character::spawn() {

    positionY = 200;
    positionX = 200;
    velocityY = 0;
    velocityX = 0;
    airborne = false;
    walking = false;
    currentPlatW = 0;
    currentPlatX = 0;
    currentPlatY = 0;
    crouching = false;
    lookingRight = true;
    dead = false;
    aimDirection = 0;

}

void Character::nextLevel() {
    level += 1;
}

void Character::setVelocityX(int velocityX) {
    Character::velocityX = velocityX;
}

void Character::setVelocityY(int velocityY) {
    Character::velocityY = velocityY;
}
