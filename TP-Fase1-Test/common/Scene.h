//
// Created by tito on 05/09/18.
//

#ifndef TP_FASE1_TEST_SCENE_H
#define TP_FASE1_TEST_SCENE_H

#include <tuple>

#include <list>
#include <SDL_rect.h>

enum PJSTATE{MOVING_RIGHT,MOVING_LEFT,STANDING_RIGHT,STANDING_LEFT,
        IN_AIR_RIGHT,IN_AIR_LEFT,GROUND,AIM_UP_R,AIM_DOWN_R,AIM_UP_L,AIM_DOWN_L};

class Scene {
public:
    Scene();



    std::list<std::tuple<int,int,int>>& getLPlataformHard();
    std::list<std::tuple<int,int,int>>& getLPlataformHielo();
    std::list<std::tuple<int,int,int>>& getLPlataformSoft();
    std::list<std::tuple<int,int>>& getLBullets();


    void addPlataformSoft(int x, int y, int width);

    void addPlataformHard(int x, int y, int width);
    void addPlataformHielo(int x, int y, int width);


    void setBullets(std::list<std::tuple<int,int>>);

    //logica

    void time();

    void moveScenario(int i);
    void clearPlatform();

private:

    std::list<std::tuple<int,int>> lBullets;
    int P1PositionX = 100;
    int P1PositionY = 300;
    int P1VelocityX = 0;
    int P1VelocityY = 0;
//    int P1AccelerationX;
  //  int P1AccelerationY;
    int P1HitPoints = 0;
    bool P1Walking = 0;
public:
    void setLBullets(const std::list<std::tuple<int, int>> &lBullets) {
        Scene::lBullets = lBullets;
    }

    void setCameraX(int x) {
        Scene::camera.x = x;
    }
    void setCameraY(int y) {
        Scene::camera.y = y;
    }

private:
    bool P1Airborne = 1;
    bool P1Crouching = 0;
    bool P1LookingRight = 1;
    bool P1Dead = 0;
    bool P1Shooting = false;
public:
    bool isP1Shooting() const;

    void setP1Shooting(bool P1Shooting);

private:

    //Weapon weapon;
    int P1AimDirection = 0;
    std::list<std::tuple<int,int,int>> lPlataformsSoft;
    std::list<std::tuple<int,int,int>> lPlataformsHard;
    std::list<std::tuple<int,int,int>> lPlataformsHielo;
    SDL_Rect camera = { 0, 0, 800, 600 };
    int level = 1;

public:
    int getLevel() const {
        return level;
    }


    SDL_Rect *getCamera();

    void setLevel(int level) {
        Scene::level = level;
    }


    int getP1PositionX() const {
        return P1PositionX;
    }

    int getP1PositionY() const {
        return P1PositionY;
    }

    void setP1PositionY(int P1PositionY) {
        Scene::P1PositionY = P1PositionY;
    }
    void setP1PositionX(int P1PositionX) {
        Scene::P1PositionX = P1PositionX;
    }

    int getP1VelocityX() const {
        return P1VelocityX;
    }

    void setP1VelocityX(int P1VelocityX) {
        Scene::P1VelocityX = P1VelocityX;
    }

    int getP1VelocityY() const {
        return P1VelocityY;
    }

    void setP1VelocityY(int P1VelocityY) {
        Scene::P1VelocityY = P1VelocityY;
    }

    int getP1HitPoints() const {
        return P1HitPoints;
    }

    void setP1HitPoints(int P1HitPoints) {
        Scene::P1HitPoints = P1HitPoints;
    }

    bool isP1Walking() const {
        return P1Walking;
    }

    void setP1Walking(bool P1Walking) {
        Scene::P1Walking = P1Walking;
    }

    bool isP1Airborne() const {
        return P1Airborne;
    }

    void setP1Airborne(bool P1Airborne) {
        Scene::P1Airborne = P1Airborne;
    }

    bool isP1Crouching() const {
        return P1Crouching;
    }

    void setP1Crouching(bool P1Crouching) {
        Scene::P1Crouching = P1Crouching;
    }

    bool isP1LookingRight() const {
        return P1LookingRight;
    }

    void setP1LookingRight(bool P1LookingRight) {
        Scene::P1LookingRight = P1LookingRight;
    }

    bool isP1Dead() const {
        return P1Dead;
    }

    void setP1Dead(bool P1Dead) {
        Scene::P1Dead = P1Dead;
    }

    int getP1AimDirection() const {
        return P1AimDirection;
    }

    void setP1AimDirection(int aimDirection) {
        Scene::P1AimDirection = aimDirection;
    }

};


#endif //TP_FASE1_TEST_SCENE_H
