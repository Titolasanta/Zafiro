//
// Created by tito on 05/09/18.
//

#include <cstdio>
#include "Scene.h"
#include "Logger.h"

extern Logger *gplogger;
Scene::Scene() {

    gplogger->log(3,"Se crea una Escena");
}


void Scene::clearPlatform(){
    lPlataformsSoft.clear();
    lPlataformsHielo.clear();
    lPlataformsHard.clear();
}


void Scene::setBullets(std::list<std::tuple<int,int>> l){
    lBullets = std::move(l);
}

SDL_Rect *Scene::getCamera(){
    return &camera;
}






std::list<std::tuple<int,int,int>>& Scene::getLPlataformSoft() {
    return lPlataformsSoft;
}

std::list<std::tuple<int,int,int>>& Scene::getLPlataformHielo() {
    return lPlataformsHielo;
}

std::list<std::tuple<int,int,int>>& Scene::getLPlataformHard() {
    return lPlataformsHard;
}

std::list<std::tuple<int,int>>& Scene::getLBullets() {
    return lBullets;
}

void Scene::addPlataformSoft(int x, int y, int width) {
    lPlataformsSoft.push_back(std::move(std::tuple<int,int,int>(x,y,width)));
}

void Scene::addPlataformHielo(int x, int y, int width) {
    lPlataformsHielo.push_back(std::move(std::tuple<int,int,int>(x,y,width)));
}

void Scene::addPlataformHard(int x, int y, int width) {
    lPlataformsHard.push_back(std::move(std::tuple<int,int,int>(x,y,width)));
}

bool Scene::isP1Shooting() const {
    return P1Shooting;
}

void Scene::setP1Shooting(bool P1Shooting) {
    Scene::P1Shooting = P1Shooting;
}


