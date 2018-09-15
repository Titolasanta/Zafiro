//
// Created by santiago on 11/09/18.
//

#ifndef TP_FASE1_TEST_PROJECTILE_H
#define TP_FASE1_TEST_PROJECTILE_H


class Projectile {

    private:
        int positionX;
        int positionY;
        int velocityX;
        int velocityY;
        int accelerationX;
        int accelerationY;
        int damage;

    public:
        Projectile(int, int, int, int);
        ~Projectile() = default;
        void move();
};


#endif //TP_FASE1_TEST_PROJECTILE_H