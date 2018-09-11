//
// Created by tito on 05/09/18.
//

#include <cstdio>
#include "Scene.h"

Scene::Scene(int i) {

}



int Scene::rojox() {
    return 300 + rojoX;
}

int Scene::rojoy() {
    return 300;
}

void Scene::rojox(int i) {
    rojoX += i;
    rojoM = 1;
}

void Scene::rojoMove(int i) {

}

bool Scene::rojoMove(){
    return rojoM;
}

void Scene::rojoNotMove() {
    rojoM = 0;
}

