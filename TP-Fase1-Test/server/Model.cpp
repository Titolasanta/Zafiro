//
// Created by tito on 07/09/18.
//

#include <iostream>

#include <tuple>

#include <list>
#include "Model.h"
#include "CollisionSoft.h"
#include "CollisionHard.h"
#include "../common/Logger.h"
#include "../common/pugixml.hpp"
#include "../common/xml.h"
#include "xmlServer.h"


#define MARGENX (800/2)
#define MARGENY (600/3)

extern Logger *gplogger;

extern pugi::xml_document*gXML_doc[2];
extern pugi::xml_parse_result *gXML_parse_result;


bool Model::endOfLevel(Scene& scene){
    for (int i = 0; i < currentPlayers; i++) {
        if (level.getLevel() != 2) {
            if (scene.getPositionX(i + 1) > level.getWidth())
                return true;
        } else {
            if (level.getHeight() + scene.getPositionY(i + 1) - 600 < 0)
                return true;
        }
    }
    return false;
}

Model::Model(int initialLevel) : level(initialLevel) {
    maxPlayers = get_cantidad_jugadores(*gXML_doc[0],*gXML_doc[1],*gXML_parse_result);
    gplogger->log(3, "Se creó el server");
}

void Model::createCharacter(){
    switch (currentPlayers){
        case 0: players[currentPlayers] = &player1; break;
        case 1: players[currentPlayers] = &player2; break;
        case 2: players[currentPlayers] = &player3; break;
        case 3: players[currentPlayers] = &player4; break;
    }
    currentPlayers++;
}

int Model::getMaxPlayers(){
    return maxPlayers;
}

int Model::getCurrentPlayers(){
    return currentPlayers;
}

void Model::time(){

    players[0]->time();

    CollisionHard(*players[0],lPlataformsHard);
    CollisionSoft(*players[0],lPlataformsSoft);
}

void Model::update(Scene &scene) {

    std::lock_guard<std::mutex> mute(mutex);


    this->time();

    SDL_Rect* cam = scene.getCamera();
    if (players[0]->getPositionX() < 5 + cam->x) {
        players[0]->setPositionX( 5 + cam->x);
        players[0]->setVelocityX(0);
    }

    if(players[0]->getPositionY() > 600 + cam->y) {
        players[0]->spawn();
        scene.getCamera()->x = 0;
        scene.getCamera()->y = 0;
    }


    if(level.getLevel() != 2){
        if (players[0]->getPositionY() < -5 + cam->y) {
            players[0]->setPositionY(-5 +  cam->y);
            players[0]->setPositionY(-5 +  cam->y);
            players[0]->setVelocityY(0);
        }
    }else{
        if (players[0]->getPositionX() > 770 + cam->x) {
            players[0]->setPositionX(770 + cam->x);
            players[0]->setVelocityX(0);
        }
    }
    std::list<std::tuple<int,int>> lTemp;

    for(auto it = lBullets.begin(); it != lBullets.end();)
    {
        it->move();
        if(!(it->inSight(scene))) {
            it=lBullets.erase(it);
        }
        else {
            lTemp.push_back(std::tuple<int,int>(it->getPositionX(),it->getPositionY()));
            ++it;
        }
    }

    scene.setBullets(std::move(lTemp));

    for (int i = 0; i < currentPlayers; i++) {
        scene.setPositionX(players[i]->getPositionX(), i + 1);
        scene.setVelocityX(players[i]->getVelocityX(), i + 1);
        scene.setVelocityY(players[i]->getVelocityY(), i + 1);
        scene.setPositionY(players[i]->getPositionY(), i + 1);
        scene.setAirborne(players[i]->isAirborne(), i + 1);
        scene.setAimDirection(players[i]->getAimDirection(), i + 1);
        scene.setDead(players[i]->isDead(), i + 1);
        scene.setCrouching(players[i]->isCrouching(), i + 1);
        scene.setLookingRight(players[i]->isLookingRight(), i + 1);
        scene.setWalking(players[i]->isWalking(), i + 1);
        scene.setShooting(players[i]->isShooting(), i + 1);

        if (scene.getLevel() != 2) {
            if (scene.getPositionX(i + 1) > MARGENX + cam->x)
                cam->x = scene.getPositionX(i + 1) - MARGENX;
        } else {
            if (scene.getPositionY(i + 1) < MARGENY + cam->y)
                if (scene.getPositionY(i + 1) - MARGENY < 0)
                    cam->y = scene.getPositionY( i + 1) - MARGENY;
        }
    }

    if(endOfLevel(scene))
        this->changeLevel(level.next(),scene);
}

void Model::stopShooting(int p){

    std::lock_guard<std::mutex> mute(mutex);
    players[p]->stopShoot();
}

void Model::addPlataformSoft(int x, int y, int w) {
    lPlataformsSoft.push_back(std::move(std::make_tuple(x,y,w)));
    gplogger->log(2, "Se agregó una plataforma blanda");
}

void Model::addPlataformHard(int x, int y, int w) {
    lPlataformsHard.push_back(std::move(std::make_tuple(x,y,w)));
    gplogger->log(2, "Se agregó una plataforma dura");
}

void Model::moveRight(int p) {

    std::lock_guard<std::mutex> mute(mutex);
    players[p]->move(20);
}

void Model::moveLeft(int p) {

    std::lock_guard<std::mutex> mute(mutex);
    players[p]->move(-20);
}

void Model::stop(int p) {
    std::lock_guard<std::mutex> mute(mutex);
    players[p]->standStill();
}

void Model::jump(int p) {

    std::lock_guard<std::mutex> mute(mutex);
    if (!players[p]->isCrouching()) players[p]->jump(-44);
    else if(players[p]->canGoThrough())
        players[p]->goThroughPlatform();
}

void Model::aimDown(int p) {
    std::lock_guard<std::mutex> mute(mutex);
    players[p]->aim(1);
    gplogger->log(3, "El personaje apunta hacia abajo");
}

void Model::aimUp(int p) {
    std::lock_guard<std::mutex> mute(mutex);
    players[p]->aim(-1);
    gplogger->log(3, "El personaje apunta hacia arriba");
}

void Model::aimStraight(int p) {
    std::lock_guard<std::mutex> mute(mutex);
    players[p]->aim(0);
}

void Model::crouch(int p) {
    std::lock_guard<std::mutex> mute(mutex);
    players[p]->crouch();
}

void Model::stand(int p) {
    std::lock_guard<std::mutex> mute(mutex);
    players[p]->stand();
}

void Model::changeLevel(Level level,Scene& scene) {

    this->level = level;
    this->lPlataformsSoft.clear();
    this->lPlataformsHard.clear();
    scene.clearPlatform();

    if (*gXML_parse_result) cargar_plataformas(*gXML_doc[0], scene,*this, level.getLevel(), this->getLevelHeight(), this->getLevelWidth());     //No tenia idea de como hacer este
    else cargar_plataformas(*gXML_doc[1],scene, *this, level.getLevel(), this->getLevelHeight(), this->getLevelWidth()); //chequeo de otra manera


    //update(scene);
    scene.setLevel(level.getLevel());
    scene.getCamera()->x = 0;
    scene.getCamera()->y = 0;
    players[0]->spawn();
    players[0]->nextLevel();

    gplogger->log(2, "Se cambió de nivel");
}

int Model::getLevelWidth() { return level.getWidth(); }

int Model::getLevelHeight() { return level.getHeight(); }

void Model::shoot(int p){

    std::lock_guard<std::mutex> mute(mutex);
    try {

        lBullets.push_back(std::move(players[p]->shoot()));
    } catch(int e) { //no recargo el arma
    }
}
/*
const Level &Model::getLevel() const {
    return level;
}
*/