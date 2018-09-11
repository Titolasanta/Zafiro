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

};


#endif //TP_FASE1_TEST_CHARACTER_H
