//
// Created by tito on 07/11/18.
//

#ifndef TP_FASE1_TEST_ENEMY_H
#define TP_FASE1_TEST_ENEMY_H



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
    int currentPlatW = 0;
    int timeTillNextShoot = 0;
    bool airborne = false;
    int aimDirrection = 0;

public:
    bool isAirborne() const;
    void time(int max);
    void land(int x, int y, int w);

    void setAirborne(bool airborne);

public:
    int getVelY() const;

    void setVelY(int velY);

public:
    bool isLookingRight() const;

    void setLookingRight(bool lookingRight);

public:
    int getPosX() const;

    void setPosX(int posX);

    int getCurrentFrame() const;

    int getPosY() const;

    void setPosY(int posY);

    void incrementCurrentFrame();
    void setCurrentFrame(int);
};


#endif //TP_FASE1_TEST_ENEMY_H
