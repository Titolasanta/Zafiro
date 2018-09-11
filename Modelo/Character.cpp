//
// Created by fede on 06/09/18.
//

#include "Character.h"

Character::Character(int posX, int posY){
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
    dead = 0;
    airborne = false;
    if (posY > 100) airborne = true;
    weapon = Weapon pistol;
    aimDirection = 0;


    //Loggear creacion del personaje
}

Character::~Character() = default; //Loggear destruccion


void Character::move(int velX) {

    if (velocityY == 0) airborne = false; //No se donde poner esto

    if (velX > 0) {              //Si me muevo hacia la derecha
        if (!lookingRight) {
            positionX += 3;
            lookingRight = true;
        }                        //Miro a la derecha si estaba mirando para la izq
    }
    else {                       //Si me muevo hacia la izq
        if (lookingRight){
            positionX -= 3;
            lookingRight = false;}
    }                            //Miro a la izq si estaba mirado para la derecha

    velocityX = velX;

    velocityX += accelerationX;

    positionX += velocityX;

    walking = true;

}

void Character::jump(int velY){

    if (airborne) return;

    velocityY += 2;             //En algun lado setear varible gravedad = 2 (ver valor)

    velocityY = velY;

    velocityY += accelerationY;

    positionY += velocityY;

    airborne = true;
    walking = false;

}

void Character::standStill(){
    velocityX = 0;
    walking = false;
}

void Character::aim(int direction){
    aimDirection = direction;
}

void Character::shoot(){
    weapon.shoot(positionX, positionY, lookingRight, aimDirection);
}

void Character::stand(){
    if (crouching) positionY += 5; //Ver cuanto agacharse
    crouching = false;
}

void Character::crouch(){
    if (airborne||crouching) return;
    positionY -= 5;             //Ver cuanto agacharse
    crouching = true;
}

void Character::takeDamage() {
    if (hitPoints > 0) hitPoints--;
    else dead = true;
    //RIP Destruirlo o algo
}

