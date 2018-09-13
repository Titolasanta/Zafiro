//
// Created by tito on 05/09/18.
//

#include <cstdio>
#include "Scene.h"

Scene::Scene() {}

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


