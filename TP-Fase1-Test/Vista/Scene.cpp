//
// Created by tito on 05/09/18.
//

#include <cstdio>
#include "Scene.h"
#include "Logger.h"

extern Logger *gplogger;
Scene::Scene() {
    addPlataforms(100,350,180);
    addBulets(300,300);

    addPlataforms(200,250,100);

    gplogger->log(1,"se crea Escena\n");
}

void Scene::addPlataforms(int x, int y,int width) {

    gplogger->log(1,"se agrega plataforma\n");
    lPlataforms.push_back(std::move(std::make_tuple(x,y,width)));

}

void Scene::addBulets(int x,int y) {

    gplogger->log(1,"se agrega bala\n");
    lBulets.push_back(std::move(std::make_tuple(x,y)));

}

void Scene::time(){
    for (std::list< std::tuple<int,int>>::iterator it = lBulets.begin(); it != lBulets.end(); it++) {
        std::get<0>(*it) += 5;
    }
}

void Scene::moveScenario(int i){
    for (std::list< std::tuple<int,int,int>>::iterator it = lPlataforms.begin(); it != lPlataforms.end(); it++) {
        std::get<0>(*it) += i;
    }
}



std::list<std::tuple<int,int,int>> Scene::plataforms() {
    return lPlataforms;
}

std::list<std::tuple<int,int>> Scene::bulets() {
    return lBulets;
}

