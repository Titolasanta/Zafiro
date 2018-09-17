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

void Scene::time(){
    for (std::list< std::tuple<int,int>>::iterator it = lBulets.begin(); it != lBulets.end(); it++) {
        std::get<0>(*it) += 5;
    }
}

void Scene::moveScenario(int i){
    for (std::list< std::tuple<int,int>>::iterator it = lPlataforms.begin(); it != lPlataforms.end(); it++) {
        std::get<0>(*it) += i;
    }
}



std::list<std::tuple<int,int>> Scene::plataforms() {
    return lPlataforms;
}

std::list<std::tuple<int,int>> Scene::bulets() {
    return lBulets;
}

