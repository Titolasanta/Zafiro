//
// Created by tito on 05/09/18.
//


#include <cstdio>
#include <stdio.h>
#include <iostream>
#include "Scene.h"
#include "Logger.h"

extern Logger *gplogger;

Scene::Scene(int numberOfPlayers) {
    MaxPlayers = numberOfPlayers;
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

SDL_Rect *Scene::getCamera() {
    return &camera;
}

std::list<std::tuple<int,int,int>>& Scene::getLPlatformGrass() {
    return lPlataformsSoft;
}

std::list<std::tuple<int,int,int>>& Scene::getLPlatformIce() {
    return lPlataformsHielo;
}

std::list<std::tuple<int,int,int>>& Scene::getLPlatformMetal() {
    return lPlataformsHard;
}

std::list<std::tuple<int,int>>& Scene::getLBullets() {
    return lBullets;
}

void Scene::addPlatformGrass(int x, int y, int width) {
    lPlataformsSoft.push_back(std::move(std::tuple<int,int,int>(x,y,width)));
}

void Scene::addPlatformIce(int x, int y, int width) {
    lPlataformsHielo.push_back(std::move(std::tuple<int,int,int>(x,y,width)));
}

void Scene::addPlatformMetal(int x, int y, int width) {
    lPlataformsHard.push_back(std::move(std::tuple<int,int,int>(x,y,width)));
}

bool Scene::isVictory() const {
    return victory;
}

void Scene::setVictory(bool victory) {
    Scene::victory = victory;
}

bool Scene::isAllPlayersConnected() const {
    return allPlayersConnected;
}

void Scene::setAllPlayersConnected(bool allPlayersConnected) {
    Scene::allPlayersConnected = allPlayersConnected;
}

void Scene::addEnemy(Enemy &&enemy) {
    Enemies.push_back(enemy);
}

std::list<Enemy> &Scene::getEnemies() {
    return Enemies;
}

void Scene::setEnemies(const std::list<Enemy> &Enemies) {
    Scene::Enemies = std::move(Enemies);
}

