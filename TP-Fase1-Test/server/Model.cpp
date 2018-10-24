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
#define MARGENY 400

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

void Model::rejoinCharacter(int id){
    players[id-1]->jump(1);
    jugadorLiseado[id-1] = false;
}

void Model::createCharacter(int id){
    switch (currentPlayers) {
        case 0:
            players[currentPlayers] = &player1;
            jugadorLiseado[currentPlayers] = false;
            break;
        case 1:
            players[currentPlayers] = &player2;
            jugadorLiseado[currentPlayers] = false;
            break;
        case 2:
            players[currentPlayers] = &player3;
            jugadorLiseado[currentPlayers] = false;
            break;
        case 3:
            players[currentPlayers] = &player4;
            jugadorLiseado[currentPlayers] = false;
            break;
        default:
            currentPlayers--;
    }
    currentPlayers++;
    if (currentPlayers == maxPlayers) maxPlayersReached = true;
}

int Model::getMaxPlayers(){
    return maxPlayers;
}

int Model::getCurrentPlayers(){
    return currentPlayers;
}

void Model::time(Scene& scene){
    int velocidad = maxPlayers;
    for(int i = 0; i < maxPlayers; i++)
        velocidad -= jugadorLiseado[i];
    for (int i = 0; i < currentPlayers; i++) {
        if (!jugadorLiseado[i]) {
            players[i]->time(velocidad);
            CollisionHard(*players[i], lPlataformsHard);
            CollisionSoft(*players[i], lPlataformsSoft);
        } else{
            SDL_Rect *cam = scene.getCamera();
            players[i]->setPositionX(cam->x + 50);
            players[i]->setPositionY((cam->y)+500);
        }
      //      players[i]->freeze();
    }
}

int XMasChico(Scene scene,Character** lp, const bool* const liseados){
    int min = 100000;
    for(int i = 0; i < scene.getCurrentPlayers() ; i++){
        if(min > lp[i]->getPositionX() && !liseados[i])
            min = lp[i]->getPositionX();
    }
    return min;
}

int YMasGrande(Scene scene,Character** lp,const bool* const liseados){
    int min = -1000;
    for(int i = 0; i < scene.getCurrentPlayers() ; i++){
        if(min < lp[i]->getPositionY() && !liseados[i])
            min = lp[i]->getPositionY();
    }
    return min;
}


void Model::update(Scene &scene) {

    std::lock_guard<std::mutex> mute(mutex);
    
    
    this->time(scene);

    SDL_Rect* cam = scene.getCamera();

    std::list<std::tuple<int,int>> lTemp;

    int moveCamAtras = 0;
    int moveCamAdelante = 0;
    
    for (int i = 0; i < currentPlayers; i++) {

        if (players[i]->getPositionX() < 5 + cam->x) {
            players[i]->setPositionX( 5 + cam->x);
            players[i]->setVelocityX(0);
        }

        if(players[i]->getPositionY() > 600 + cam->y) {
            players[i]->spawn(*cam);
        }


        if(level.getLevel() != 2){
            if (players[i]->getPositionY() < -5 + cam->y) {
                players[i]->setPositionY(-5 +  cam->y);
                players[i]->setVelocityY(0);
            }
        }else{
            if (players[i]->getPositionX() > 770 + cam->x) {
                players[i]->setPositionX(770 + cam->x);
                players[i]->setVelocityX(0);
            }
        }

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
        scene.setCurrentPlayers(currentPlayers);

        /*if (scene.getLevel() != 2) {
            if (scene.getPositionX(i + 1) > MARGENX + cam->x)
                moveCamAdelante++;
        } else {
            if (scene.getPositionY(i + 1) < MARGENY + cam->y)
                if (scene.getPositionY(i + 1) - MARGENY < 0)
                    moveCamAdelante++;
        }
        if (scene.getLevel() != 2) {
            if (scene.getPositionX(i + 1) < MARGENX/2 + cam->x)
                moveCamAtras++;
        } else {
            if (scene.getPositionY(i + 1) > MARGENY/2 + cam->y)
                //if (scene.getPositionY(i + 1) - MARGENY < 0)
                    moveCamAtras++;
        }
    }
    if(moveCamAdelante && !(moveCamAtras)) {
        if (scene.getLevel() != 2)
            cam->x = XMasChico(scene, players) - MARGENX/3;
        else
            cam->y = YMasGrande(scene, players)- MARGENY/3;
    }*/
    }
    placeCamera(scene);

    int velocidad = maxPlayers;
    for(int i = 0; i < maxPlayers; i++)
        velocidad -= jugadorLiseado[i];
    for(auto it = lBullets.begin(); it != lBullets.end();)
    {
        it->move(velocidad);
        if(!(it->inSight(scene))) {
            it=lBullets.erase(it);
        }
        else {
            lTemp.push_back(std::tuple<int,int>(it->getPositionX(),it->getPositionY()));
            ++it;
        }
    }

    scene.setBullets(std::move(lTemp));

    if(endOfLevel(scene))
        this->changeLevel(level.next(),scene);
}

void Model::stopShooting(int p){

    std::lock_guard<std::mutex> mute(mutex);
    players[p-1]->stopShoot();
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
    players[p-1]->move(20);
}

void Model::moveLeft(int p) {

    std::lock_guard<std::mutex> mute(mutex);
    players[p-1]->move(-20);
}

void Model::stop(int p) {
    std::lock_guard<std::mutex> mute(mutex);
    players[p-1]->standStill();
}

void Model::jump(int p) {

    std::lock_guard<std::mutex> mute(mutex);
    if (!players[p-1]->isCrouching()) players[p-1]->jump(-44);
    else if(players[p-1]->canGoThrough())
        players[p-1]->goThroughPlatform();
}

void Model::aimDown(int p) {
    std::lock_guard<std::mutex> mute(mutex);
    players[p-1]->aim(1);
    gplogger->log(3, "El personaje apunta hacia abajo");
}

void Model::aimUp(int p) {
    std::lock_guard<std::mutex> mute(mutex);
    players[p-1]->aim(-1);
    gplogger->log(3, "El personaje apunta hacia arriba");
}

void Model::aimStraight(int p) {
    std::lock_guard<std::mutex> mute(mutex);
    players[p-1]->aim(0);
}

void Model::crouch(int p) {
    std::lock_guard<std::mutex> mute(mutex);
    players[p-1]->crouch();
}

void Model::stand(int p) {
    std::lock_guard<std::mutex> mute(mutex);
    players[p-1]->stand();
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

    for (int i = 0; i < currentPlayers; i++) {
        players[i]->spawn(*scene.getCamera());
        players[i]->nextLevel();
    }
    gplogger->log(2, "Se cambió de nivel");
}

int Model::getLevelWidth() { return level.getWidth(); }

int Model::getLevelHeight() { return level.getHeight(); }

void Model::shoot(int p){

    std::lock_guard<std::mutex> mute(mutex);
    try {

        lBullets.push_back(std::move(players[p-1]->shoot()));
    } catch(int e) { //no recargo el arma
    }
}

void Model::bajaJugador(int p) {
    //currentPlayers--;
    jugadorLiseado[p-1] = true;
}
/*
const Level &Model::getLevel() const {
    return level;
}
*/

bool Model::getMaxPlayersReached(){
    return maxPlayersReached;
}

const bool *Model::getJugadorLiseado() const {
    return jugadorLiseado;
}

void Model::placeCamera(Scene &scene){
    SDL_Rect* cam = scene.getCamera();
    int minX = XMasChico(scene,players, jugadorLiseado);
    int minY = YMasGrande(scene,players, jugadorLiseado);

    for (int i = 0; i < currentPlayers; i++) {
        if (!jugadorLiseado[i]) {
            if (scene.getLevel() != 2) {
                int playerPosX = players[i]->getPositionX();
                if (playerPosX > cam->x + MARGENX) {
                    if (minX > cam->x + 50 && maxPlayers == currentPlayers) {
                        scene.setCameraX(cam->x + 20);
                    } else {
                        if (players[i]->getPositionX() > 770 + cam->x) {
                            players[i]->setPositionX(770 + cam->x);
                            players[i]->setVelocityX(0);
                        }


                    }
                }
            } else {
                int playerPosY = players[i]->getPositionY();
                if (playerPosY < cam->y + 100) {
                    if (minY < cam->y + 550 && maxPlayers == currentPlayers) {
                        scene.setCameraY(cam->y - 20);
                    } else {
                        if (players[i]->getPositionY() < cam->y + 50) {
                            players[i]->setPositionY(cam->y + 50);
                            players[i]->setVelocityY(0);
                        }
                    }
                }
            }
        }
    }
}
