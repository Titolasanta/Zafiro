//
// Created by fede on 06/09/18.
//


#include <iostream>
#include "Character.h"
#include "../common/Projectile.h"
#include "Pistol.h"
#include "CollisionHard.h"
#include "../common/Logger.h"
#include "Trigonometricgun.h"

extern Logger *gplogger;

Character::Character() : weapon(&tg) { // esta inicialiacion no importa, pero evado un bug
    
    positionX = 100;
    positionY = 0;
    velocityX = 0;
    velocityY = 0;
    //accelerationX = 0;
    //accelerationY = 0;
    
    hitPoints = 3;
    walking = false;
    lookingRight = true;
    crouching = false;
    dead = false;
    airborne = true;
    aimDirection = 0;
    shooting = false;
    
    immortal = true;

    weapon->setCurrentAmmo(0);
    gplogger->log(2, "Se creó el personaje");
}
void Character::land(int x, int y,int w,bool hard) {

    airborne = false;
    if(velocityX != 0) walking = true;
    velocityY = 0;
    
    currentPlatHard = hard;
    currentPlatX = x;
    currentPlatW = w;
    currentPlatY = y;

    gplogger->log(3, "El personaje aterriza");
}

void Character::time() {
    if(gracePeriod>0)
        gracePeriod--;

    timeTillNextShoot-=(12);
    if(timeTillNextShoot < 0){
        timeTillNextShoot = 0;
        setShooting(false);
    }

    if (currentPlatX + currentPlatW  < positionX + velocityX || currentPlatX  >  positionX + velocityX) {
        airborne = true;
    }

    if(airborne) velocityY += 4;
    if(dead) velocityX = 0;
    //velocityY += accelerationY;
    //velocityX += accelerationX;

    positionX += velocityX;
    positionY += velocityY;
    
    if (crouching) aimDirection = 0;
}

Character::~Character() = default;

void Character::move(int velX) {
    if (dead) return;
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

    if(!airborne) walking = true;
}

void Character::jump(int velY) {
    
    if (airborne || dead) return;

    velocityY = velY;

    airborne = true;
    walking = false;

    gplogger->log(3, "El personaje salta");
}

void Character::standStill() {
    if (dead) return;
    velocityX = 0;
    walking = false;

    gplogger->log(3, "El personaje se detiene");
}

void Character::aim(int direction) {
    if (dead) return;
    if (!crouching) aimDirection = direction;
    else aimDirection = 0;
}

Projectile Character::shoot() {

    if (timeTillNextShoot != 0){
        throw 1; //no recargo el arma
    }
    setShooting(true);
    timeTillNextShoot = weapon->getFireRate();

    try {
        return weapon->shoot(positionX, positionY, lookingRight, aimDirection);
    } catch(...){
        changeWeapon(0);
        weapon->setId(id);
    }
    return weapon->shoot(positionX, positionY, lookingRight, aimDirection);
}
void Character::changeWeapon(int i){
    if (dead) return;
    if(i == 0){
        ps = Pistol();
        weapon = &ps;
    }
    if(i == 1){
        mg = Machinegun();
        weapon = &mg;
    }
    if(i == 2){
        tg = Trigonometricgun();
        weapon = &tg;
    }
    weapon->setId(id);
    gplogger->log(3, "El personaje cambia de arma");
}


void Character::stand() {
    if (dead) return;
    if (crouching) positionY -= 40;
    crouching = false;

    gplogger->log(3, "El personaje se levanta");
}

void Character::crouch() {
    if (airborne||crouching||dead) return;
    standStill();
    positionY += 40;
    crouching = true;

    gplogger->log(3, "El personaje se agacha");
}

void Character::takeDamage() {
    if (!immortal && !dead && !gracePeriod){
        hitPoints--;
        if (hitPoints <= 0) {
            positionY+=45;
            dead = true;
        }
        startGracePeriod();
        //RIP Destruirlo o algo
    }
}

void Character::goThroughPlatform(){
    if (dead) return;
    positionY += 10;
    airborne = true;
    crouching = false;

    gplogger->log(3, "El personaje atraviesa una plataforma");
}

void Character::spawn(SDL_Rect cam) {
    
    if(level == 2){
        positionX = cam.x + 400;
        positionY = cam.y + 200;
    } else {
        positionX = cam.x + 150;
        positionY = cam.y + 100;
    }
    
    velocityY = 0;
    velocityX = 0;
    airborne = true;
    walking = false;
    currentPlatW = 0;
    currentPlatX = 0;
    currentPlatY = 0;
    crouching = false;
    lookingRight = true;
    aimDirection = 0;
}

void Character::spawn(int x, int y) {
    
    positionX = x;
    positionY = y;
    
    velocityY = 0;
    velocityX = 0;
    airborne = true;
    walking = false;
    currentPlatW = 0;
    currentPlatX = 0;
    currentPlatY = 0;
    crouching = false;
    lookingRight = true;
    dead = false;
    aimDirection = 0;
}

int Character::getId() const {
    return id;
}

void Character::setId(int id) {
    Character::id = id;
}

void Character::changeImmortal() {
    immortal = !immortal;
}

bool Character::isImmortal() const {
    return immortal;
}

void Character::setImmortal(bool immortal) {
    Character::immortal = immortal;
}

void Character::gainHealth(int h){
    hitPoints += h;
    if (hitPoints >= 0) dead = false;
}

void Character::startGracePeriod() {
    gracePeriod = 20;
}
bool Character::isInGracePeriod(){
    return gracePeriod;
}