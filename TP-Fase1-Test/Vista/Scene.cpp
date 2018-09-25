//
// Created by tito on 05/09/18.
//

#include <cstdio>
#include "Scene.h"
#include "Logger.h"

extern Logger *gplogger;
Scene::Scene() {

    gplogger->log(1,"se crea Escena\n");
}

void Scene::addPlataform(int x, int y, int width) {
    gplogger->log(1,"se agrega plataforma\n");
    lPlataforms.push_back(std::move(std::make_tuple(x,y,width)));
}

void Scene::setBullets(std::list<std::tuple<int,int>> l){
    lBullets = std::move(l);
}

SDL_Rect *Scene::getCamera(){
    return &camera;
}






std::list<std::tuple<int,int,int>>& Scene::plataforms() {
    return lPlataforms;
}

std::list<std::tuple<int,int>>& Scene::Bullets() {
    return lBullets;
}


