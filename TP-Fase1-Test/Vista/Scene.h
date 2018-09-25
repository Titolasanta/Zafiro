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




    std::list<std::tuple<int,int,int>>& plataforms();
    std::list<std::tuple<int,int>>& Bullets();

    void addPlataform(int x, int y, int width);


    void setBullets(std::list<std::tuple<int,int>>);

    //logica

    void time();

    void moveScenario(int i);
    void clearPlatforms();

private:

    std::list<std::tuple<int,int>> lBullets;
    int P1PositionX;
    int P1PositionY;
    int P1VelocityX;
    int P1VelocityY;
//    int P1AccelerationX;
  //  int P1AccelerationY;
    int P1HitPoints;
    bool P1Walking;
    bool P1Airborne;
    bool P1Crouching;
    bool P1LookingRight;
    bool P1Dead;
    //Weapon weapon;
    int P1AimDirection;
    std::list<std::tuple<int,int,int>> lPlataforms;

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
