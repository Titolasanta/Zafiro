//
// Created by tito on 07/11/18.
//

#ifndef TP_FASE1_TEST_ENEMY_H
#define TP_FASE1_TEST_ENEMY_H
#define MOBILEENEMYFRAME 6
#define STATICENEMYFRAME 12

#include <list>
#include "Projectile.h"

class Enemy {

private:
    int posX;
    int posY;
    int currentFrame = 0;
    bool dead = false;
    bool lookingRight;
    int velY = 0;
    int currentPlatX = 0;
    bool staticEnemy;
    int currentPlatW = 0;
    int timeTillNextShoot = 0;
    bool airborne = false;
    int aimDirrection = 0;

public:

    void time( std::list<Projectile> &lBullets);

    Enemy(int x,int y,int px, int pw, bool);
    Enemy(int x,int y, bool);
    void land(int x, int y, int w);
    void move(int random);
    void incrementCurrentFrame();

    void shoot(std::list<Projectile> &list);

    int getCurrentFrame() const { return currentFrame; }
    void setCurrentFrame(int frame){ currentFrame = frame; }

    int getCurrentPlatX() const { return currentPlatX; }
    void setCurrentPlatX(int cpx) { currentPlatX = cpx; }

    int getCurrentPlatW() const { return currentPlatW; }
    void setCurrentPlatW(int cpw) { currentPlatW = cpw; }

    int getPosX() const { return posX; }
    void setPosX(int x) { posX = x; }

    int getPosY() const { return posY; }
    void setPosY(int y) { posY = y; }

    bool isLookingRight() const { return lookingRight; }
    void setLookingRight(bool lr) { lookingRight = lr; }

    int getVelY() const { return velY; }
    void setVelY(int y) { velY = y; }

    bool isAirborne() const { return airborne; }
    void setAirborne(bool a) { airborne = a; }

    bool isStatic() const { return staticEnemy; }
    void setStatic(bool s) { staticEnemy = s; }
};


#endif //TP_FASE1_TEST_ENEMY_H
