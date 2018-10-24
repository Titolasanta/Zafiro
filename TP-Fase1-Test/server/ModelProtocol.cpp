//
// Created by tito on 08/10/18.
//

#include <tuple>
#include <queue>
#include <list>
#include <SDL_rect.h>
#include <netinet/in.h>
#include "ModelProtocol.h"
#include "../common/Exception.h"

ModelProtocol::ModelProtocol(Socket &skt,Socket &sktAux, std::queue<char>& queue,char id,std::mutex& mutex)
:skt(std::move(skt)),sktAux(std::move(sktAux)),queue(queue),id(id),mutex(mutex){}

void sendValue(Socket& skt, int value){
    unsigned int to_send = value;
    unsigned int temp = htonl(to_send);
    char msgNumero[4];
    memcpy(msgNumero,&temp,4);
    skt.send_all(msgNumero,4);
}

void ModelProtocol::run() {
    char msg[4];
    while(!quit){
        printf("informacion relevante\n");
        msg[0] = id;
        try {
            skt.receive_all(&(msg[1]), 2);
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

void ModelProtocol::end(){
    quit = true;
}


ModelProtocol::ModelProtocol(ModelProtocol&& other) : skt(std::move(other.skt)),sktAux(std::move(other.sktAux)),mutex(other.mutex),queue(other.queue) {
    printf("lo hice 1 vaez\n");
    this->thread = std::move(other.thread);
    this->id = other.id;
    other.valid = false;
}


void ModelProtocol::send(Scene& scene){
    int p = scene.getMaxPlayers();
    std::lock_guard<std::mutex> lg(mutex);

        for (auto it = scene.getLBullets().begin(); it != scene.getLBullets().end(); ++it) {
            sendValue(skt, std::get<0>(*it));
            sendValue(skt, std::get<1>(*it));
        }
        sendValue(skt, -1);
        for (int i = 0; i < p; i++) {
            sktAux.flush();
            sktAux.send_all("1",1);
            //std::list<std::tuple<int,int>> lBullets;
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
            sendValue(skt, scene.isJugadorLiseado(i + 1));

        }
        sendValue(skt, scene.getCamera()->x);
        sendValue(skt, scene.getCamera()->y);
        sendValue(skt, scene.getLevel());
        sendValue(skt,scene.getCurrentPlayers());
        sendValue(skt,scene.isVictory());

}

ModelProtocol::~ModelProtocol(){
    if(valid)
        join();
}

char ModelProtocol::getId() const {
    return id;
}
