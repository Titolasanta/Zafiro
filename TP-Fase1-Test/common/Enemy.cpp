//
// Created by tito on 07/11/18.
//

#include "Enemy.h"
#include "../server/CollisionSoft.h"

Enemy::Enemy(int x,int y,int px, int pw) : currentPlatX(px),currentPlatW(pw) {
    posX = x;
    posY = y;
}

Enemy::Enemy(int x,int y) {
    posX = x;
    posY = y;
}


int Enemy::getPosX() const {
    return posX;
}

void Enemy::setPosX(int posX) {
    Enemy::posX = posX;
}

int Enemy::getPosY() const {
    return posY;
}

void Enemy::setPosY(int posY) {
    Enemy::posY = posY;
}

bool Enemy::isLookingRight() const {
    return lookingRight;
}

void Enemy::setLookingRight(bool lookingRight) {
    Enemy::lookingRight = lookingRight;
}

int Enemy::getVelY() const {
    return velY;
}

void Enemy::setVelY(int velY) {
    Enemy::velY = velY;
}

bool Enemy::isAirborne() const {
    return airborne;
}

void Enemy::setAirborne(bool airborne) {
    Enemy::airborne = airborne;
}

void Enemy::time(int max, std::list<Projectile>& lBullets) {
    timeTillNextShoot-=(12/max);
    
    if(timeTillNextShoot < 0){
        timeTillNextShoot = 120;
        this->shoot(lBullets);
    }

    if (currentPlatX + currentPlatW  < posX || currentPlatX  >  posX) {
        airborne = true;
    }

    if(airborne) velY += 4/max;

    posY += velY/max;

}

void Enemy::land(int x, int y, int w) {

    airborne = false;
    velY = 0;
    currentPlatX = x;
    currentPlatW = w;
}


void Enemy::incrementCurrentFrame(){
    currentFrame++;
}

void Enemy::setCurrentFrame(int frame){
    currentFrame = frame;
}

int Enemy::getCurrentFrame() const {
    return currentFrame;
}

int Enemy::getCurrentPlatX() const {
    return currentPlatX;
}

void Enemy::setCurrentPlatX(int currentPlatX) {
    Enemy::currentPlatX = currentPlatX;
}

int Enemy::getCurrentPlatW() const {
    return currentPlatW;
}

void Enemy::setCurrentPlatW(int currentPlatW) {
    Enemy::currentPlatW = currentPlatW;
}

void Enemy::shoot(std::list<Projectile>& list) {
    int EnemyHight = 45;
    int EnemyWidth = 50;
    int bx,by,bv;
    by = posY + EnemyHight/2;
    if(lookingRight){
            bx = posX + EnemyWidth;
            bv = 10;
    } else{
            bx = posX;
            bv = -10;
    }
    Projectile p(bx,by,bv,0);
    list.push_back(std::move(p));
}
