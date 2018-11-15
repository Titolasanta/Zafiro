//
// Created by tito on 07/11/18.
//

#include <random>
#include "Enemy.h"
#include "../server/CollisionSoft.h"
#include <math.h>
#include <iostream>

Enemy::Enemy(int x,int y,int px, int pw, bool isStatic) : currentPlatX(px),currentPlatW(pw) {

    std::random_device rand_dev;
    std::default_random_engine generator(rand_dev());
    std::uniform_int_distribution<int> distribution(0,100);
    currentFrame = distribution(generator);
    posX = x;
    posY = y;
    staticEnemy = isStatic;
    lookingRight = (bool) (distribution(generator) % 2);
}

Enemy::Enemy(int x,int y, bool isStatic) {

    std::random_device rand_dev;
    std::default_random_engine generator(rand_dev());
    std::uniform_int_distribution<int> distribution(0,100);
    posX = x;
    posY = y;
    staticEnemy = isStatic;
    lookingRight = (bool) (distribution(generator) % 2);

}

void Enemy::time( std::list<Projectile>& lBullets) {
    timeTillNextShoot-=(12);
    
    if(timeTillNextShoot < 0){
        timeTillNextShoot = 360;
        this->shoot(lBullets);
    }

    if (currentPlatX + currentPlatW  < posX || currentPlatX  >  posX) {
        airborne = true;
    }

    if(airborne) velY += 4;

    posY += velY;

}

void Enemy::land(int x, int y, int w) {

    airborne = false;
    velY = 0;
    currentPlatX = x;
    currentPlatW = w;
}

void Enemy::incrementCurrentFrame(){
    currentFrame++;
    currentFrame %= 6;
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
    Projectile p(bx,by,bv,0,-1);
    list.push_back(std::move(p));
}

void Enemy::move(int randm, int chx, int chy){
    if (staticEnemy){
        float distX = posX - chx;
        float distY = posY - chy + 61;
        float angle = atan(distY/distX);
        std::cout << "dx: "<< distX << "|dy: "<< distY<< "|angle: "<<angle<<std::endl;
        if ((angle > -(M_1_PIf64/12) && angle < (M_1_PIf64/12)) && distX < 0) currentFrame = 0;
        else if (angle > -(M_1_PIf64/12) && angle < (M_1_PIf64/12) && distX > 0) currentFrame = 6;
        else if ((angle > (M_1_PIf64/12) && angle < (M_1_PIf64/4)) && distX < 0) currentFrame = 5;
        else if ((angle > (M_1_PIf64/12) && angle < (M_1_PIf64/4)) && distX > 0) currentFrame = 11;
        else if ((angle > (M_1_PIf64/4) && angle < (5*M_1_PIf64/12)) && distX < 0) currentFrame = 4;
        else if ((angle > (M_1_PIf64/4) && angle < (5*M_1_PIf64/12)) && distX > 0) currentFrame = 10;
        else if (angle > (5*M_1_PIf64/12) && distX < 0) currentFrame = 3;
        else if (angle > (5*M_1_PIf64/12) && distX > 0) currentFrame = 9;
        else if ((angle > -(M_1_PIf64/4) && angle < -(M_1_PIf64/12)) && distX > 0) currentFrame = 1;
        else if ((angle > -(M_1_PIf64/4) && angle < -(M_1_PIf64/12)) && distX < 0) currentFrame = 7;
        else if (angle > -(5*M_1_PIf64/12) && angle < -(M_1_PIf64/4) && distX > 0) currentFrame = 2;
        else currentFrame = 8;
        return;
    }
    int velx = 5;
    int largoEnemigo = 50;
    int r = randm;
    int x = this->getPosX();
    int px = this->getCurrentPlatX();
    int pw = this->getCurrentPlatW();
    if(r < 90){
        if(this->isLookingRight() ) {
            if (px + pw > x + velx + largoEnemigo)
                this->setPosX(x + velx);
        }else if( px < x - velx )
            this->setPosX(this->getPosX() - velx);
    } else if(r < 95 ){
        if(!this->isAirborne()) {
            this->setVelY(this->getVelY() - 40);
            this->setAirborne(true);
        }
    }else{
        this->setLookingRight(!this->isLookingRight());
    }
}
