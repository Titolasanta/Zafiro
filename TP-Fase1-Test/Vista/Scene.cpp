//
// Created by tito on 05/09/18.
//

#include <cstdio>
#include "Scene.h"

Scene::Scene() {
    lPlataforms.push_back(std::move(std::make_tuple<int,int>(500,100)));
}

int Scene::rojox() {
    return 300 + rojoX;
}

int Scene::rojoy() {
    return 300;
}

void Scene::rojoMove(int i) {
    rojoX +=i;
    state = MOVING;
}

int Scene::rojoState(){
    return state;
}
void Scene::rojoNotMove() {
    state = GROUND;
}

std::list<std::tuple<int,int>> Scene::plataforms() {
    return lPlataforms;
}

