//
// Created by tito on 05/09/18.
//

#ifndef TP_FASE1_TEST_SCENE_H
#define TP_FASE1_TEST_SCENE_H

#include <tuple>

#include <list>

enum PJSTATE{MOVING,AIR,GROUND};

class Scene {
public:
    Scene();

    //geter
    int rojox();

    int rojoy();

    int rojoState();

    std::list<std::tuple<int,int>> plataforms();

    //seter
    void rojoNotMove();

    void rojoMove(int i);

    //drawers

private:
    std::list<std::tuple<int,int>> lPlataforms;
    int rojoX = 0;
    int state = GROUND;

};


#endif //TP_FASE1_TEST_SCENE_H
