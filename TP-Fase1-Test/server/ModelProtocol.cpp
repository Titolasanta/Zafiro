//
// Created by tito on 08/10/18.
//

#include <tuple>
#include <queue>
#include <list>
#include <SDL_rect.h>
#include <netinet/in.h>
#include "ModelProtocol.h"

ModelProtocol::ModelProtocol(Socket &skt,std::queue<char>& queue,char id,std::mutex& mutex)
:skt(std::move(skt)),queue(queue),id(id),mutex(mutex){}

void sendValue(Socket& skt, int value){
    int to_send = value;
    int temp = htonl(to_send);
    char msgNumero[4];
    memcpy(msgNumero,&temp,4);

    skt.send_all(msgNumero,4);
}

void ModelProtocol::run() {
    char msg[3];
    while(!quit){
        msg[0] = id;
        skt.receive_all(&(msg[1]),2);
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


ModelProtocol::ModelProtocol(ModelProtocol&& other) : skt(std::move(other.skt)),mutex(other.mutex) {
    this->thread = std::move(other.thread);
}


void ModelProtocol::send(Scene& scene){
    //std::list<std::tuple<int,int>> lBullets;
    sendValue(skt,scene.getP1PositionX());
    sendValue(skt,scene.getP1PositionY());
    sendValue(skt,scene.getP1VelocityX());
    sendValue(skt,scene.getP1VelocityY());
    sendValue(skt,scene.getP1HitPoints());
    sendValue(skt,scene.isP1Walking());
    sendValue(skt,scene.isP1Airborne());
    sendValue(skt,scene.isP1Crouching());
    sendValue(skt,scene.isP1LookingRight());
    sendValue(skt,scene.isP1Dead());
    sendValue(skt,scene.isP1Shooting());

    sendValue(skt,scene.getCamera()->x);
    sendValue(skt,scene.getCamera()->y);
    sendValue(skt,scene.getLevel());
}