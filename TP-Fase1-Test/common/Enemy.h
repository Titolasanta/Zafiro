//
// Created by tito on 07/11/18.
//

#ifndef TP_FASE1_TEST_ENEMY_H
#define TP_FASE1_TEST_ENEMY_H


#include <list>
#include "Projectile.h"

class Enemy {
public:
    Enemy(int x,int y,int px, int pw);
    Enemy(int x,int y);
private:
    int posX;
    int posY;
    int currentFrame = 0;
    bool dead = false;
    bool lookingRight = true;
    int velY = 0;
    int currentPlatX = 0;
public:
    int getCurrentPlatX() const;

    void setCurrentPlatX(int currentPlatX);

    int getCurrentPlatW() const;

    void setCurrentPlatW(int currentPlatW);

    void time(int max, std::list<Projectile> &lBullets);
    void land(int x, int y, int w);
    void move(int randm);
private:
    int currentPlatW = 0;
    int timeTillNextShoot = 0;
    bool airborne = false;
    int aimDirrection = 0;

public:
    bool isAirborne() const;

    void setAirborne(bool airborne);

    int getVelY() const;

    void setVelY(int velY);

    bool isLookingRight() const;

    void setLookingRight(bool lookingRight);

    int getPosX() const;

    void setPosX(int posX);

    int getCurrentFrame() const;

    int getPosY() const;

    void setPosY(int posY);

    void incrementCurrentFrame();
    void setCurrentFrame(int);

    void shoot(std::list<Projectile> &list);
};


#endif //TP_FASE1_TEST_ENEMY_H
