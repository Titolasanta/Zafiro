//
// Created by tito on 07/11/18.
//

#ifndef TP_FASE1_TEST_ENEMY_H
#define TP_FASE1_TEST_ENEMY_H



class Enemy {
public:
    Enemy(int x,int y,int px, int pw);
private:
    int posX;
    int posY;
    int currentFrame = 0;
    bool dead = false;
    bool lookingRight = true;
    int velY = 0;
    int currentPlatX;
    int currentPlatW;
    int timeTillNextShoot = 0;
    bool airborne = false;
public:
    bool isAirborne() const;
    void time(Scene&);

    void setAirborne(bool airborne);

public:
    int getVelY() const;

    void setVelY(int velY);

public:
    bool isLookingRight() const;

    void setLookingRight(bool lookingRight);

private:
    int aimDirrection = 0;
public:
    int getPosX() const;

    void setPosX(int posX);

    int getPosY() const;

    void setPosY(int posY);

private:
    bool alive = true;
};


#endif //TP_FASE1_TEST_ENEMY_H
