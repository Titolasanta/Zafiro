//
// Created by fede on 06/09/18.
//

#ifndef TP_FASE1_TEST_CHARACTER_H
#define TP_FASE1_TEST_CHARACTER_H


#define characterHeight 60
#include "Weapon.h"
#include "../common/Projectile.h"

class Character {
    
private:
    
    int positionX;
    int positionY;
    int velocityX;
    int velocityY;
    //int accelerationX;
    //int accelerationY;
    
    int hitPoints;
    bool walking;
    bool airborne;
    bool crouching;
    bool lookingRight;
    int aimDirection;
    bool dead;
    bool shooting;
    bool immortal;
public:
    bool isImmortal() const;

    void setImmortal(bool immortal);

private:

    Weapon weapon;
    
    int currentPlatX;
    int currentPlatY;
    int currentPlatW;
    bool currentPlatHard;

    
    float timeTillNextShoot = 0;
    int id;
public:
    int getId() const;

    void setId(int id);

public:

    int level = 1; //?????

    Character();
    ~Character();
    void move(int);
    void jump(int);
    void standStill();
    void aim(int);
    Projectile shoot();
    void stand();
    void crouch();
    void takeDamage();
    void time(int);
    void changeImmortal();
    void land(int,int,int,bool);
    void goThroughPlatform();
    void changeWeapon(Weapon);
    //void respawn(Scene&,SDL_Rect,Character*[]);

    void spawn(SDL_Rect);
    void spawn(int x,int y);
    
    int getPositionX() const { return positionX; }
    int getPositionY() const { return positionY; }
    int getVelocityX() const { return velocityX; }
    int getVelocityY() const { return velocityY; }
    int getHitPoints() const { return hitPoints; }
    bool isWalking() const { return walking; }
    bool isAirborne() const { return airborne; }
    bool isCrouching() const { return crouching; }
    bool isLookingRight() const { return lookingRight; }
    bool isDead() const { return dead; }
    int getAimDirection() const { return aimDirection; }
    
    void setPositionX(int posX) { positionX = posX; }
    void setPositionY(int posY) { positionY = posY; }
    void setVelocityX(int velX) { velocityX = velX; }
    void setVelocityY(int velY) { velocityY = velY; }
    void setAirborne(bool a) { airborne = a; }
    void setWalking(bool w){ walking = w; }

    void nextLevel() { level += 1; }
    bool canGoThrough() { return !currentPlatHard; }

    bool isShooting() const { return shooting; }
    void setShooting(bool s) { shooting = s; }
    
};




#endif //TP_FASE1_TEST_CHARACTER_H
