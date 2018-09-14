//
// Created by tito on 05/09/18.
//

#include <cstdio>
#include "Scene.h"

Scene::Scene() {
    addPlataforms(400,400);
    addBulets(300,300);
}

void Scene::addPlataforms(int x, int y) {

    lPlataforms.push_back(std::move(std::make_tuple(x,y)));

}

void Scene::addBulets(int x,int y) {

    lBulets.push_back(std::move(std::make_tuple(x,y)));

}

int Scene::rojox() {
    return 300 + rojoX;
}

int Scene::rojoy() {
    return 300;
}

void Scene::rojoMove(int i) {
    rojoX +=i;
    if(i>0)
       state = MOVING_RIGHT;
    else
        state = MOVING_LEFT;
}

int Scene::rojoState(){
    return state;
}
void Scene::rojoNotMove() {
    if(state == MOVING_LEFT)
        state = STANDING_LEFT;
    if(state == MOVING_RIGHT)
        state = STANDING_RIGHT;
}

std::list<std::tuple<int,int>> Scene::plataforms() {
    return lPlataforms;
}

std::list<std::tuple<int,int>> Scene::bulets() {
    return lBulets;
}

