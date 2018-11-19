//
// Created by santiago on 11/09/18.
//

#ifndef TP_FASE1_TEST_PROJECTILE_H
#define TP_FASE1_TEST_PROJECTILE_H


#include <SDL2/SDL_rect.h>

class Projectile {

private:
    int positionX;
    int positionY;
    int ownerId;
    int velocityX;
    int velocityY;
    int damage;
    float angle = 0;
public:
    float getAngle() const {
        return angle;
    }

    void setAngle(float angle) {
        Projectile::angle = angle;
    }

    int getVelocityX() const;
    void setVelocityX(int velocityX);

    int getVelocityY() const;
    void setVelocityY(int velocityY);
    
    int getPositionX() const;
    void setPositionX(int positionX);

    int getPositionY() const;
    void setPositionY(int positionY);

    int getOwnerId();

    Projectile(int px, int py, int vx, int vy, int ownerId);

    ~Projectile() = default;
    void move();

    bool inSight(SDL_Rect *cam);
};


#endif //TP_FASE1_TEST_PROJECTILE_H
