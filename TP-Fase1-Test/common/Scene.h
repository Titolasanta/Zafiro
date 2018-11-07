//
// Created by tito on 05/09/18.
//

#ifndef TP_FASE1_TEST_SCENE_H
#define TP_FASE1_TEST_SCENE_H

#include <tuple>

#include <list>
#include "Enemy.h"
#include <SDL_rect.h>


class Scene {

public:
    Scene(int);
    std::list<std::tuple<int,int,int>>& getLPlatformGrass();
    std::list<std::tuple<int,int,int>>& getLPlatformMetal();
    std::list<std::tuple<int,int,int>>& getLPlatformIce();
    std::list<std::tuple<int,int>>& getLBullets();

    void addPlatformGrass(int x, int y, int width);
    void addPlatformMetal(int x, int y, int width);
    void addPlatformIce(int x, int y, int width);

    void setBullets(std::list<std::tuple<int,int>>);

    void clearPlatform();
    bool isAllPlayersConnected() const;
    void setAllPlayersConnected(bool allPlayersConnected);
    bool isVictory() const;
    void setVictory(bool victory);



private:
    std::list<std::tuple<int,int,int>> lPlataformsSoft;
    std::list<std::tuple<int,int,int>> lPlataformsHard;
    std::list<std::tuple<int,int,int>> lPlataformsHielo;
    std::list<std::tuple<int,int>> lBullets;
    SDL_Rect camera = { 0, 0, 800, 600 };
    int level = 1;
    int players = 0;
    int MaxPlayers;

    int positionX[4];
    int positionY[4];
    int velocityX[4];
    int velocityY[4];
    bool victory = false;
    bool allPlayersConnected = false;

private:
//  int accelerationX[4];
//  int accelerationY[4];
    int hitPoints[4];
    int walking[4];
    int airborne[4];
    int crouching[4];
    int lookingRight[4];
    int dead[4];
    int shooting[4];
    int aimDirection[4];
    bool jugadorGrisado[4];
    std::list<Enemy> Enemies;
public:
    void setEnemies(const std::list<Enemy> &Enemies);

public:
    const std::list<Enemy> &getEnemies() const;


public:

    void setLBullets(const std::list<std::tuple<int, int>> &lb) { lBullets = lb; }

    SDL_Rect *getCamera();

    void setCameraX(int x) { camera.x = x; }
    void setCameraY(int y) { camera.y = y; }

    int getLevel() const { return level; }
    void setLevel(int l) { level = l; }


    int getPositionX(int p) const { return positionX[p-1]; }
    void setPositionX(int posX, int p) { positionX[p-1] = posX; }

    int getPositionY(int p) const { return positionY[p-1]; }
    void setPositionY(int posY, int p) { positionY[p-1] = posY; }

    int getVelocityX(int p) const { return velocityX[p-1]; }
    void setVelocityX(int velX, int p) { velocityX[p-1] = velX; }

    int getVelocityY(int p) const { return velocityY[p-1]; }
    void setVelocityY(int velY, int p) { velocityY[p-1] = velY; }

    int getHitPoints(int p) const { return hitPoints[p-1]; }
    void setHitPoints(int hp, int p) { hitPoints[p-1] = hp; }

    int isWalking(int p) const { return walking[p-1]; }
    void setWalking(int w, int p) { walking[p-1] = w; }

    int isAirborne(int p) const { return airborne[p-1]; }
    void setAirborne(int a, int p) { airborne[p-1] = a; }

    int isCrouching(int p) const { return crouching[p-1]; }
    void setCrouching(int c, int p) { crouching[p-1] = c; }

    int isLookingRight(int p) const { return lookingRight[p-1]; }
    void setLookingRight(int lr, int p) { lookingRight[p-1] = lr; }

    int isDead(int p) const { return dead[p-1]; }
    void setDead(int d, int p) { dead[p-1] = d; }

    int getAimDirection(int p) const { return aimDirection[p-1]; }
    void setAimDirection(int ad, int p) { aimDirection[p-1] = ad; }

    int isShooting(int p) const { return shooting[p-1]; }
    void setShooting(int s, int p) { shooting[p-1] = s; }

    int getCurrentPlayers() const { return players; }
    void setCurrentPlayers(int p){ players = p;}
    
    int getMaxPlayers(){ return MaxPlayers;}
    
    bool isJugadorGrisado(int p) const { return jugadorGrisado[p-1]; }
    void setJugadorGrisado(bool b, int p) { jugadorGrisado[p-1] = b; }


    void addEnemy(Enemy &&enemy);
};


#endif //TP_FASE1_TEST_SCENE_H
