//
// Created by fede on 06/09/18.
//

#ifndef TP_FASE1_TEST_CHARACTER_H
#define TP_FASE1_TEST_CHARACTER_H


#include "Weapon.h"

class Character {
    private:
        int positionX;
        int positionY;
        int velocityX;
        int velocityY;
        int accelerationX;
        int accelerationY;
        int hitPoints;
        bool walking;
        bool airborne;
        bool crouching;
        bool lookingRight;
        bool dead;

private:
    //si queres que sea polimorifico y pueda tener diferentes
        // clases hijas de weapon deberia ser un puntero o referencia
        Weapon weapon;
        int aimDirection;

    public:
        Character(int, int);
        ~Character();
        void move(int);
        void jump(int);
        void standStill();
        void aim(int);
        void shoot();
        void stand();
        void crouch();
        void takeDamage();
        void time();



public:
    int getPositionX() const {
            return positionX;
    }

    int getPositionY() const {
            return positionY;
    }

    int getVelocityX() const {
            return velocityX;
    }

    int getVelocityY() const {
            return velocityY;
    }

    int getHitPoints() const {
            return hitPoints;
    }

    bool isWalking() const {
            return walking;
    }

    bool isAirborne() const {
            return airborne;
    }

    bool isCrouching() const {
            return crouching;
    }

    bool isLookingRight() const {
            return lookingRight;
    }

    bool isDead() const {
            return dead;
    }

    int getAimDirection() const {
            return aimDirection;
    }

};


#endif //TP_FASE1_TEST_CHARACTER_H
