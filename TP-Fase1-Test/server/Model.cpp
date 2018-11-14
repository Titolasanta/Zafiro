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
#include <random>

#define MARGENX (800/2)
#define MARGENY 400
#define CHARACTERHEIGHT 60
#define CHARACTERWIDTH 25
#define ENEMYHEIGHT 55
#define ENEMYWIDTH 25
#define ENEMYID -1

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
    jugadorGrisado[id-1] = false;
    jugadorReconectado[id - 1] = true;
}

void Model::createCharacter(int id){
    switch (currentPlayers) {
        case 0:
            player1.setId(id);
            players[currentPlayers] = &player1;
            jugadorGrisado[currentPlayers] = false;
            break;
        case 1:
            player2.setId(id);
            players[currentPlayers] = &player2;
            jugadorGrisado[currentPlayers] = false;
            break;
        case 2:
            player3.setId(id);
            players[currentPlayers] = &player3;
            jugadorGrisado[currentPlayers] = false;
            break;
        case 3:
            player4.setId(id);
            players[currentPlayers] = &player4;
            jugadorGrisado[currentPlayers] = false;
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

void Model::time(){
    
    int velocidad = maxPlayers;
    for(int i = 0; i < maxPlayers; i++)
        velocidad -= jugadorGrisado[i];
    
    for (int i = 0; i < currentPlayers; i++) {
        players[i]->time(velocidad);
        CollisionHard(*players[i], lPlataformsHard);
        CollisionSoft(*players[i], lPlataformsSoft);
    }
}

int Model::XMasChico(Scene &scene){
    int min = 100000;
    for(int i = 0; i < scene.getCurrentPlayers() ; i++){
        if ((!jugadorGrisado[i]) && (!players[i]->isDead())) {
            if (min > players[i]->getPositionX())
                min = players[i]->getPositionX();
        }
    }
    return min;
}

int Model::YMasGrande(Scene &scene){
    int min = -100000;
    for(int i = 0; i < scene.getCurrentPlayers() ; i++){
        if ((!jugadorGrisado[i]) && (!players[i]->isDead())){
            if (min < players[i]->getPositionY())
                min = players[i]->getPositionY();
        }
    }
    return min;
}

void Model::respawn(int toRespawn,SDL_Rect* cam, bool damage){
    //if (players[toRespawn]->isDead()) return;
    for(int i = 0; i < currentPlayers; i++){
        if(i != toRespawn && !players[i]->isAirborne() && !jugadorGrisado[i]){
            players[toRespawn]->spawn(players[i]->getPositionX(),players[i]->getPositionY() - 50);
            if (damage) players[toRespawn]->takeDamage();
            return;
        }
    }
    players[toRespawn]->spawn(*cam);
    if (damage) players[toRespawn]->takeDamage();
}

void Model::update(Scene &scene) {

    std::lock_guard<std::mutex> mute(mutex);
    
    time();

    SDL_Rect* cam = scene.getCamera();

    for (int i = 0; i < currentPlayers; i++) {
        if (!players[i]->isDead()){
            
            if (jugadorReconectado[i]){
                jugadorReconectado[i] = false;
                respawn(i, cam, false);
            }
            if (players[i]->getPositionX() < 5 + cam->x) {
                players[i]->setPositionX( 20 + cam->x);
                players[i]->setVelocityX(0);
            }
    
            if(players[i]->getPositionY() > 600 + cam->y) {
                respawn(i,cam, true);
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
            scene.setImmortal(players[i]->isImmortal(), i + 1);
            scene.setPositionX(players[i]->getPositionX(), i + 1);
            scene.setVelocityX(players[i]->getVelocityX(), i + 1);
            scene.setVelocityY(players[i]->getVelocityY(), i + 1);
            scene.setPositionY(players[i]->getPositionY(), i + 1);
            scene.setAimDirection(players[i]->getAimDirection(), i + 1);
            scene.setDead(players[i]->isDead(), i + 1);
            scene.setCrouching(players[i]->isCrouching(), i + 1);
            scene.setLookingRight(players[i]->isLookingRight(), i + 1);
            scene.setWalking(players[i]->isWalking(), i + 1);
            scene.setShooting(players[i]->isShooting(), i + 1);
            scene.setCurrentPlayers(currentPlayers);
            scene.setJugadorGrisado(jugadorGrisado[i], i + 1);
    
            if (getCurrentPlayers() == getMaxPlayers()) {
                scene.setAllPlayersConnected(true);
            }
        }
        else scene.setDead(players[i]->isDead(), i + 1);
        scene.setAirborne(players[i]->isAirborne(), i + 1);
        scene.setPositionX(players[i]->getPositionX(), i + 1);
        scene.setVelocityX(players[i]->getVelocityX(), i + 1);
        scene.setVelocityY(players[i]->getVelocityY(), i + 1);
        scene.setPositionY(players[i]->getPositionY(), i + 1);
    }
    
    placeCamera(scene);
    

    handleBullet(scene);

    moveEnemies(scene);


    if(endOfLevel(scene)) changeLevel(level.next(),scene);
}

void Model::stopShooting(int p){

    std::lock_guard<std::mutex> mute(mutex);
    players[p-1]->setShooting(false);
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
    scene.getEnemies().clear();
    if(level.getLevel() > 3){
        scene.setVictory(true);
    }else{
        this->level = level;
        this->lPlataformsSoft.clear();
        this->lPlataformsHard.clear();
        scene.clearPlatform();

        if (*gXML_parse_result)
            cargar_plataformas(*gXML_doc[0], scene, *this, level.getLevel(), this->getLevelHeight(),
                               this->getLevelWidth());     //No tenia idea de como hacer este
        else
            cargar_plataformas(*gXML_doc[1], scene, *this, level.getLevel(), this->getLevelHeight(),
                               this->getLevelWidth()); //chequeo de otra manera


        //update(scene);
        scene.setLevel(level.getLevel());
        scene.getCamera()->x = 0;
        scene.getCamera()->y = 0;

        for (int i = 0; i < currentPlayers; i++) {
            players[i]->spawn(*scene.getCamera());
            players[i]->nextLevel();
        }

        //setEnemies(scene);
        gplogger->log(2, "Se cambió de nivel");
    }
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
    jugadorGrisado[p-1] = true;
}
/*
const Level &Model::getLevel() const {
    return level;
}
*/

bool Model::getMaxPlayersReached(){
    return maxPlayersReached;
}

const bool *Model::getJugadorGrisado() const {
    return jugadorGrisado;
}

void Model::placeCamera(Scene &scene){
    SDL_Rect* cam = scene.getCamera();
    int minX = XMasChico(scene);
    int minY = YMasGrande(scene);

    for (int i = 0; i < currentPlayers; i++) {
        if (jugadorGrisado[i]) continue;

        if (scene.getLevel() != 2) {
            int playerPosX = players[i]->getPositionX();
            if (playerPosX > cam->x + MARGENX) {
                if (minX > cam->x + 50 && currentPlayers == maxPlayers) {
                    scene.setCameraX(cam->x + 21);
                } else {
                    if (players[i]->getPositionX() > 770 + cam->x) {
                        players[i]->setPositionX(770 + cam->x);
                        players[i]->setVelocityX(0);
                    }
                }
            }
        }else {
            int playerPosY = players[i]->getPositionY();
            if (playerPosY < cam->y + 100) {
                if (minY < cam->y + 550 && currentPlayers == maxPlayers) {
                    scene.setCameraY(cam->y - 20);
                } else {
                    if (players[i]->getPositionY() < cam->y + 50) {
                        players[i]->setPositionY(cam->y + 50);
                        players[i]->setVelocityY(0);
                    }
                }
            }else{
                if (playerPosY > cam->y + 550) {
                    respawn(i,cam, true);
                }
            }
        }
    }
}

void Model::setEnemies(Scene& scene) {
    std::random_device                  rand_dev;
    std::default_random_engine generator(rand_dev());
    std::uniform_int_distribution<int> distribution(0,lPlataformsSoft.size());
    int enemiesToPlaceInSoft = get_cant_enemigos_moviles(*gXML_doc[0],*gXML_doc[1],scene.getLevel(),*gXML_parse_result);
    for(int i = 0;i < enemiesToPlaceInSoft ;i++) {
        int random = distribution(generator);
        auto it = lPlataformsSoft.begin();
        for (;random > 0 ; random-- ){
            it++;
        };
        if(scene.getLevel() != 2) {
            if (std::get<0>(*it) < 600) {
                i--;
                continue;
            }
        }else{
            if (std::get<1>(*it) < 600) {
                i--;
                continue;
            }
        }
        std::uniform_int_distribution<int> distribution(0,std::get<2>(*it));
        int x = distribution(generator) + std::get<0>(*it);
        Enemy enemy(x, std::get<1>(*it),std::get<0>(*it),std::get<2>(*it));
        scene.addEnemy(std::move(enemy));
    }
}

void Model::moveEnemies(Scene &scene) {
    std::random_device rand_dev;
    std::default_random_engine generator(rand_dev());
    std::uniform_int_distribution<int> distribution(0,100);
    int velx = 5;
    int largoEnemigo = 50;
    for(auto it = scene.getEnemies().begin(); it != scene.getEnemies().end(); it++){
        int r = distribution(generator);
        it->move(r);
        this->enemyCollision(*it,scene);
    }
}

void Model::enemyCollision(Enemy &enemy,Scene& scene) {
    enemy.time(scene.getCurrentPlayers(),lBullets);
    if (enemy.isAirborne()) {
        CollisionSoft c(enemy, lPlataformsSoft);
        CollisionSoft h(enemy, lPlataformsHard);
    }
}

bool Model::isBetween(int bulletX, int bulletY, int posX, int posY, int width, int height) {
    return (bulletX > posX && bulletX < posX + width && bulletY > posY && bulletY < posY + height);
}

void Model::handleBullet(Scene &scene) {

    std::list<std::tuple<int,int>> lTemp;
    int velocidad = maxPlayers;
    for(int i = 0; i < maxPlayers; i++)
        velocidad -= jugadorGrisado[i];
    for(auto it = lBullets.begin(); it != lBullets.end();){
        it->move(velocidad);
        if(!(it->inSight(scene.getCamera()))) {
            it=lBullets.erase(it);
        }
        else {
            if (it->getOwnerId() == ENEMYID) {
                for (int i = 0; i < currentPlayers; i++) {
                    if (isBetween(it->getPositionX(), it->getPositionY(), players[i]->getPositionX(),
                            players[i]->getPositionY(), CHARACTERWIDTH, CHARACTERHEIGHT)){
                        players[i]->takeDamage();
                        it = lBullets.erase(it);
                    }
                }
            }
            else{
                for (auto enemyIt = scene.getEnemies().begin(); enemyIt != scene.getEnemies().end(); enemyIt++){
                    if (isBetween(it->getPositionX(), it->getPositionY(), enemyIt->getPosX(), enemyIt->getPosY(), ENEMYWIDTH, ENEMYHEIGHT)){
                        enemyIt = scene.getEnemies().erase(enemyIt);
                        it = lBullets.erase(it);
                    }
                }
            }
            lTemp.push_back(std::tuple<int,int>(it->getPositionX(),it->getPositionY()));
            ++it;
        }
    }
    scene.setBullets(std::move(lTemp));
}

void Model::immortalize(int id) {
    players[id-1]->changeImmortal();
}
