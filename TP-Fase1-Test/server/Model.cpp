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
    if(level.getLevel() != 2) {
        if(scene.getP1PositionX() > level.getWidth() )
            return true;
    }else {
        if (level.getHeight() + scene.getP1PositionY() - 600 < 0)
            return true;
    }
    return false;
}

Model::Model(int initialLevel) : player1(100,0), level(initialLevel) {
    gplogger->log(3, "Se creó el server");
}

void Model::time(){

    player1.time();

    CollisionHard(player1,lPlataformsHard);
    CollisionSoft(player1,lPlataformsSoft);
}

void Model::update(Scene &scene) {

    std::lock_guard<std::mutex> mute(mutex);


    this->time();

    SDL_Rect* cam = scene.getCamera();
    if (player1.getPositionX() < 5 + cam->x) {
        player1.setPositionX( 5 + cam->x);
        player1.setVelocityX(0);
    }

    if(player1.getPositionY() > 600 + cam->y) {
        player1.spawn();
        scene.getCamera()->x = 0;
        scene.getCamera()->y = 0;
    }


    if(level.getLevel() != 2){
        if (player1.getPositionY() < -5 + cam->y) {
            player1.setPositionY(-5 +  cam->y);
            player1.setPositionY(-5 +  cam->y);
            player1.setVelocityY(0);
        }
    }else{
        if (player1.getPositionX() > 770 + cam->x) {
            player1.setPositionX(770 + cam->x);
            player1.setVelocityX(0);
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

    scene.setP1PositionX(player1.getPositionX());
    scene.setP1VelocityX(player1.getVelocityX());
    scene.setP1VelocityY(player1.getVelocityY());
    scene.setP1PositionY(player1.getPositionY());
    scene.setP1Airborne(player1.isAirborne());
    scene.setP1AimDirection(player1.getAimDirection());
    scene.setP1Dead(player1.isDead());
    scene.setP1Crouching(player1.isCrouching());
    scene.setP1LookingRight(player1.isLookingRight());
    scene.setP1Walking(player1.isWalking());
    scene.setP1Shooting(player1.isShooting());

    if (scene.getLevel() != 2){
        if (scene.getP1PositionX() > MARGENX + cam->x)
            cam->x = scene.getP1PositionX() - MARGENX;
    }else {
        if (scene.getP1PositionY() < MARGENY + cam->y)
            if(scene.getP1PositionY() - MARGENY < 0)
                cam->y = scene.getP1PositionY() - MARGENY;
    }


    if(endOfLevel(scene))
        this->changeLevel(level.next(),scene);
}

void Model::stopShooting(){

    std::lock_guard<std::mutex> mute(mutex);
    player1.stopShoot();
}

void Model::addPlataformSoft(int x, int y, int w) {
    lPlataformsSoft.push_back(std::move(std::make_tuple(x,y,w)));
    gplogger->log(2, "Se agregó una plataforma blanda");
}

void Model::addPlataformHard(int x, int y, int w) {
    lPlataformsHard.push_back(std::move(std::make_tuple(x,y,w)));
    gplogger->log(2, "Se agregó una plataforma dura");
}

void Model::moveRight() {

    std::lock_guard<std::mutex> mute(mutex);
    player1.move(20);
}

void Model::moveLeft() {

    std::lock_guard<std::mutex> mute(mutex);
    player1.move(-20);
}

void Model::stop() {
    std::lock_guard<std::mutex> mute(mutex);
    player1.standStill();
}

void Model::jump() {

    std::lock_guard<std::mutex> mute(mutex);
    if (!player1.isCrouching()) player1.jump(-44);
    else if(player1.canGoThrough())
        player1.goThroughPlatform();
}

void Model::aimDown() {
    std::lock_guard<std::mutex> mute(mutex);
    player1.aim(1);
    gplogger->log(3, "El personaje apunta hacia abajo");
}

void Model::aimUp() {
    std::lock_guard<std::mutex> mute(mutex);
    player1.aim(-1);
    gplogger->log(3, "El personaje apunta hacia arriba");
}

void Model::aimStraight() {
    std::lock_guard<std::mutex> mute(mutex);
    player1.aim(0); 
}

void Model::crouch() {
    std::lock_guard<std::mutex> mute(mutex);
    player1.crouch();
}

void Model::stand() {
    std::lock_guard<std::mutex> mute(mutex);
    player1.stand(); 
}

void Model::changeLevel(Level level,Scene& scene) {

    this->level = level;
    this->lPlataformsSoft.clear();
    this->lPlataformsHard.clear();
    scene.clearPlatform();

    if (*gXML_parse_result) cargar_plataformas(*gXML_doc[0], scene,*this, level.getLevel(), this->getLevelHeight(), this->getLevelWidth());     //No tenia idea de como hacer este
    else cargar_plataformas(*gXML_doc[1],scene, *this, level.getLevel(), this->getLevelHeight(), this->getLevelWidth()); //chequeo de otra manera


    update(scene);
    scene.setLevel(level.getLevel());
    scene.getCamera()->x = 0;
    scene.getCamera()->y = 0;
    player1.spawn();
    player1.nextLevel();

    gplogger->log(2, "Se cambió de nivel");
}

int Model::getLevelWidth() { return level.getWidth(); }

int Model::getLevelHeight() { return level.getHeight(); }

void Model::shoot(){

    std::lock_guard<std::mutex> mute(mutex);
    try {

        lBullets.push_back(std::move(player1.shoot()));
    } catch(int e) { //no recargo el arma
    }
}
/*
const Level &Model::getLevel() const {
    return level;
}
*/