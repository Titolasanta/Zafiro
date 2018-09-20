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
    airborne = true;
    //if (posY > 100) airborne = true;
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

void Character::time(){

    if(positionY > 1000) {
        positionY = 0;
        velocityY = 0;
    }

    if (currentPlatX + largoPlataforma + changui < positionX + velocityX || currentPlatX  > changui + positionX + velocityX)
        airborne = true;


    if(isAirborne())
        velocityY += 4;


    velocityY += accelerationY;

    velocityX += accelerationX;
    positionX += velocityX;

    positionY += velocityY;
}

Character::~Character() = default; //Loggear destruccion


void Character::move(int velX) {

 //No se donde poner esto

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


    if(!isAirborne())
        walking = true;

}



void Character::jump(int velY){

    if (airborne) return;
             //En algun lado setear varible gravedad = 2 (ver valor)

    velocityY = velY;

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

