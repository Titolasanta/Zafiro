//
// Created by tito on 05/09/18.
//

#ifndef TP_FASE1_TEST_SCENE_H
#define TP_FASE1_TEST_SCENE_H

#include <tuple>

#include <list>

enum PJSTATE{MOVING_RIGHT,MOVING_LEFT,STANDING_RIGHT,STANDING_LEFT,AIR,GROUND};

class Scene {
public:
    Scene();

    //geter
    int rojox();

    int rojoy();

    int rojoState();

    std::list<std::tuple<int,int>> plataforms();

    void addPlataforms(int,int);

    std::list<std::tuple<int,int>> bulets();

    void addBulets(int,int);

    //seter
    void rojoNotMove();

    void rojoMove(int i);

    //drawers

private:
    std::list<std::tuple<int,int>> lBulets;
    std::list<std::tuple<int,int>> lPlataforms;
    int rojoX = 0;
    int state = STANDING_RIGHT;

};


#endif //TP_FASE1_TEST_SCENE_H
