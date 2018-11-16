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
    int bx, by, bvx, bvy = 0;
    float angulo;
    int modV = 12;
    if (staticEnemy) {
        by = posY + EnemyHight / 2;
        bx = posX + EnemyWidth / 2;
        angulo = 2 * M_PI - currentFrame * M_PI / 6;
        bvx = modV * cos(angulo);
        bvy = modV * -sin(angulo);
    } else {
        by = posY + EnemyHight / 2;
        bx = posX + EnemyWidth / 4;
        bvx = modV * lookingRight - modV * !lookingRight;
    }
    Projectile p(bx, by, bvx, bvy, -1);
    list.push_back(std::move(p));
}

void Enemy::move(int randm, int chx, int chy){
    if (staticEnemy){
        float distX = chx - posX;
        float distY = chy - 1 - posY;
        float tang = distY/distX;
        if(distX >= 0){//char a la der
            if (distY == 0 && distX > 0) currentFrame = 0;
            else if (tang > tan((M_PI/18)) && tang <= tan((M_PI/4))) currentFrame = 1;
            else if (tang > tan((M_PI/4)) && tang <= tan((4*M_PI/9))) currentFrame = 2;
            else if (distX < 10 && distX > -10 && distY >= 0) currentFrame = 3;
            else if (distX < 10 && distX > -10 && distY < 0) currentFrame = 9;
            else if (tang > tan((14 * M_PI / 9)) && tang <= tan((7 * M_PI / 4))) currentFrame = 10;
            else if (tang > tan(7 * M_PI / 4) && tang <= tan(35 * M_PI / 36)) currentFrame = 11;
        }else {//char a la izq
            if (distY == 0 && distX <= 0) currentFrame = 6;
            else if (tang > tan((5*M_PI/9)) && tang <= tan((9*M_PI/12))) currentFrame = 4;
            else if (tang > tan((9*M_PI/4)) && tang <= tan((17*M_PI/18))) currentFrame = 5;
            else if (tang > tan((19 * M_PI / 18)) && tang <= tan((5 * M_PI / 4))) currentFrame = 7;
            else if (tang > tan((5 * M_PI / 4)) && tang <= tan((13 * M_PI / 9))) currentFrame = 8;
        }
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
