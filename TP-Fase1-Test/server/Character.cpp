//
// Created by fede on 06/09/18.
//


#include <iostream>
#include "Character.h"
#include "../common/Projectile.h"
#include "Pistol.h"
#include "CollisionHard.h"
#include "../common/Logger.h"

extern Logger *gplogger;

Character::Character() : weapon(Pistol()) {
    
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
    
    immortal = false;

    weapon.setId(id);
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

Character::~Character() = default;

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

    if(!airborne) walking = true;
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
        weapon.setId(id);
    }
    return weapon.shoot(positionX, positionY, lookingRight, aimDirection);
}
void Character::changeWeapon(Weapon w){
    weapon = w;
    gplogger->log(3, "El personaje cambia de arma");
}


void Character::stand() {
    if (crouching) positionY -= 40;
    crouching = false;

    gplogger->log(3, "El personaje se levanta");
}

void Character::crouch() {
    if (airborne||crouching) return;
    standStill();
    positionY += 40;
    crouching = true;

    gplogger->log(3, "El personaje se agacha");
}

void Character::takeDamage() {
    if (!immortal && !dead){
        hitPoints--;
        if (hitPoints <= 0) {
            positionY += 40;
            dead = true;
        }
        //RIP Destruirlo o algo
    }
}

void Character::goThroughPlatform(){
    positionY += 10;
    airborne = true;
    crouching = false;

    gplogger->log(3, "El personaje atraviesa una plataforma");
}

void Character::spawn(SDL_Rect cam) {
    
    if(level == 2){
        positionX = cam.x + 400;
        positionY = cam.y + 250;
    } else {
        positionX = cam.x + 150;
        positionY = cam.y + 100;
    }
    
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

void Character::spawn(int x, int y) {
    
    positionX = x;
    positionY = y;
    
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

int Character::getId() const {
    return id;
}

void Character::setId(int id) {
    Character::id = id;
}
