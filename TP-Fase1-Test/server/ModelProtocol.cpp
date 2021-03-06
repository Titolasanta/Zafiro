//
// Created by tito on 08/10/18.
//

#include <tuple>
#include <queue>
#include <list>
#include <SDL2/SDL_rect.h>
#include <netinet/in.h>
#include "ModelProtocol.h"
#include "../common/Exception.h"

ModelProtocol::ModelProtocol(Socket &skt, std::queue<char>& queue,char id,std::mutex& mutex,Socket& sktAux)
:skt(std::move(skt)),queue(queue),id(id),mutex(mutex),sktSignal(std::move(sktAux)){}

void sendValue(Socket& skt, int value){
    auto to_send = (unsigned int) value;
    unsigned int temp = htonl(to_send);
    char msgNumero[4];
    memcpy(msgNumero,&temp,4);
    skt.send_all(msgNumero,4);
}

void ModelProtocol::run() {
    char msg[4];
    while(!quit){
        msg[0] = id;
        try {
            skt.receive_all(&(msg[1]), 2);
        }catch(Finalizo_conexion &f){
            msg[1] = 'f';
            msg[2] = 'c';
            quit = true;
        }catch(...){
            break;
        }
        mutex.lock();
        queue.push(msg[0]);
        queue.push(msg[1]);
        queue.push(msg[2]);
        mutex.unlock();
    }
}

bool ModelProtocol::end(){
    if(quit)
        return  false;
    skt.manual_close();
    sktSignal.manual_close();
    quit = true;
    return true;
}


ModelProtocol::ModelProtocol(ModelProtocol&& other) noexcept
: skt(std::move(other.skt)),mutex(other.mutex),queue(other.queue),sktSignal(std::move(other.sktSignal)) {
    this->thread = std::move(other.thread);
    this->id = other.id;
    other.valid = false;
}


void ModelProtocol::send(Scene& scene){
    int p = scene.getMaxPlayers();
    std::lock_guard<std::mutex> lg(mutex);

    for (auto& it : scene.getLBullets()) {
        sendValue(skt, std::get<0>(it));
        sendValue(skt, std::get<1>(it));
        sendValue(skt, std::get<2>(it));
    }
    sendValue(skt, -1);

    for (auto& it : *scene.getLWeapons()) {
        sendValue(skt, std::get<0>(it));
        sendValue(skt, std::get<1>(it));
        sendValue(skt, std::get<2>(it));
    }
    sendValue(skt, -1);
    
    for (auto& it : *scene.getEnemies()) {
        sendValue(skt, it.getPosX());
        sendValue(skt, it.getPosY());
        sendValue(skt, it.isStatic());
        sendValue(skt, it.isLookingRight());
        sendValue(skt, it.getCurrentFrame());
        sendValue(skt, it.isDead());
        sendValue(skt, it.getContador());
    }
    sendValue(skt, -1);
    sendValue(skt, scene.getLevel());
    for (int i = 0; i < p; i++){
        sendValue(skt, scene.getImmortal(i + 1));
        sendValue(skt, scene.getPositionX(i + 1));
        sendValue(skt, scene.getPositionY(i + 1));
        sendValue(skt, scene.getVelocityX(i + 1));
        sendValue(skt, scene.getVelocityY(i + 1));
        sendValue(skt, scene.getHitPoints(i + 1));
        sendValue(skt, scene.isWalking(i + 1));
        sendValue(skt, scene.isAirborne(i + 1));
        sendValue(skt, scene.isCrouching(i + 1));
        sendValue(skt, scene.isLookingRight(i + 1));
        sendValue(skt, scene.isDead(i + 1));
        sendValue(skt, scene.isShooting(i + 1));
        sendValue(skt, scene.getAimDirection(i + 1));
        sendValue(skt, scene.isJugadorGrisado(i + 1));
        sendValue(skt,scene.isInGracePeriod(i+1));
        for(int j = 0; j < 3; j++)
            sendValue(skt,scene.getScore(i+1,j+1));
    }
    sendValue(skt, scene.getCamera()->x);
    sendValue(skt, scene.getCamera()->y);
    sendValue(skt, scene.getBossX());
    sendValue(skt, scene.getBossY());
    sendValue(skt, scene.getBossHP());
    sendValue(skt,scene.getCurrentPlayers());
    sendValue(skt,scene.isVictory());
    sendValue(skt,scene.isShootSound());

}

ModelProtocol::~ModelProtocol(){
    if(valid)
        join();
}

char ModelProtocol::getId() const {
    return id;
}

void ModelProtocol::receiveLatency(){
    char msg;
    sktSignal.receive_all(&msg,1);
}