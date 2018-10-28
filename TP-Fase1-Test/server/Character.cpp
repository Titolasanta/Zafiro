//
// Created by fede on 06/09/18.
//


#include <iostream>
#include "Character.h"
#include "Projectile.h"
#include "Pistol.h"
#include "CollisionHard.h"
#include "../common/Logger.h"

extern Logger *gplogger;

Character::Character() : weapon(Pistol()) {
    // XML deberia chequear que las posiciones esten
    // en el rango valido de la ventana
    positionX = 100;
    positionY = 0;
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
void Character::land(int x, int y,int w,bool hard) {

    airborne = false;
    if(getVelocityX() != 0)
        walking = true;
    velocityY = 0;
    currentPlatHard = hard;
    currentPlatX = x;
    currentPlatW = w;
    currentPlatY = y;

    gplogger->log(3, "El personaje aterriza");
}

void Character::time(int currentPlayers) {

    timeTillNextShoot-=(12/currentPlayers);
    if(timeTillNextShoot < 0){
        timeTillNextShoot = 0;
        setShooting(false);
    }

    if (currentPlatX + currentPlatW  < positionX + velocityX || currentPlatX  >  positionX + velocityX) {
        airborne = true;
    }

   if(airborne) velocityY += 4/currentPlayers;

    //velocityY += accelerationY;
    //velocityX += accelerationX;

    positionX += velocityX/currentPlayers;
    positionY += velocityY/currentPlayers;
    
    if (crouching) aimDirection = 0;
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

    gplogger->log(3, "El personaje se detiene");
}

void Character::aim(int direction) {
    if (!crouching) aimDirection = direction;
    else aimDirection = 0;
}

Projectile Character::shoot() {
    if (timeTillNextShoot != 0){
        throw 1; //no recargo el arma
    }
    setShooting(true);
    timeTillNextShoot = weapon.getFireRate();

    try {
        return weapon.shoot(positionX, positionY, lookingRight, aimDirection);
    } catch(...){
        changeWeapon(Pistol());
    }
    return weapon.shoot(positionX, positionY, lookingRight, aimDirection);
}
void Character::changeWeapon(Weapon weapon){
    weapon = weapon;

    gplogger->log(3, "El personaje cambia de arma");
}


void Character::stand() {
    if (crouching) positionY -= 40;
    crouching = false;

    gplogger->log(3, "El personaje se levanta");
}

void Character::crouch() {
    if (airborne||crouching) return;
    this->standStill();
    positionY += 40;
    crouching = true;

    gplogger->log(3, "El personaje se agacha");
}

void Character::takeDamage() {
    if (hitPoints > 0) hitPoints--;
    else dead = true;
    //RIP Destruirlo o algo
}

void Character::goThroughPlatform(){
    positionY += 10;
    airborne = true;
    crouching = false;

    gplogger->log(3, "El personaje atraviesa una plataforma");
}

void Character::spawn() {
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

bool Character::canGoThrough() {
    return !currentPlatHard;
}

bool Character::isShooting() const {
    return shooting;
}

void Character::setShooting(bool shooting) {
    Character::shooting = shooting;
}

void Character::stopShoot() {
//    setShooting(false);
}

void Character::respawn(Scene& scene, SDL_Rect cam, Character *players[]){
    int connectedPlayers = 0;
    for (int i = 1; i <= scene.getMaxPlayers(); i++) connectedPlayers += !scene.isJugadorGrisado(i);
    if (connectedPlayers == 1){
        positionY = cam.y + 310;
        positionX = cam.x + 200;
        spawn();
    } else {
        for (int i = 1; i <= scene.getMaxPlayers(); i++){
            if ((scene.isJugadorGrisado(i)) || (players[i-1]->getPositionY() == positionY)) continue;
            positionX = players[i-1]->getPositionX();
            positionY = players[i-1]->getPositionY() - 50;
            spawn();
            break;
        }
    }
}
