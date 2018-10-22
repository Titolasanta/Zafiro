//
// Created by santiago on 11/09/18.
//

#ifndef TP_FASE1_TEST_PROJECTILE_H
#define TP_FASE1_TEST_PROJECTILE_H


#include "../common/Scene.h"

class Projectile {

    private:
        int positionX;
        int positionY;
public:
    int getVelocityX() const;

    void setVelocityX(int velocityX);

    int getVelocityY() const;

    void setVelocityY(int velocityY);

public:
    int getPositionX() const;

    void setPositionX(int positionX);

    int getPositionY() const;

    void setPositionY(int positionY);

private:
    int velocityX;
        int velocityY;
        int accelerationX;
        int accelerationY;
        int damage;

    public:
        Projectile(int, int, int, int);
        ~Projectile() = default;
        void move(int);
        bool inSight(Scene& scene);
};


#endif //TP_FASE1_TEST_PROJECTILE_H
