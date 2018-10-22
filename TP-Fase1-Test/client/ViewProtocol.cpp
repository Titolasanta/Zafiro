//
// Created by tito on 08/10/18.
//

#include <netinet/in.h>
#include "ViewProtocol.h"
#include "../common/Socket.h"
#include "../common/Scene.h"

ViewProtocol::ViewProtocol(Socket &skt) : socket(std::move(skt)) {}

bool ViewProtocol::validate(std::string toVal) {
    return true;
}

void ViewProtocol::jump() {
    char msg[3] = "jp";
    socket.send_all(msg,2);
}

void ViewProtocol::moveRight() {
    char msg[3] = "mr";
    socket.send_all(msg,2);

}

void ViewProtocol::moveLeft() {
    char msg[3] = "ml";
    socket.send_all(msg,2);
}

void ViewProtocol::aimDown() {
    char msg[3] = "ad";
    socket.send_all(msg,2);
}

void ViewProtocol::aimUp() {
    char msg[3] = "au";
    socket.send_all(msg,2);
}

void ViewProtocol::crouch() {
    char msg[3] = "cr";
    socket.send_all(msg,2);
}

void ViewProtocol::shoot() {
    char msg[3] = "sh";
    socket.send_all(msg,2);
}

void ViewProtocol::stop() {
    char msg[3] = "st";
    socket.send_all(msg,2);

}

void ViewProtocol::aimStraight() {
    char msg[3] = "as";
    socket.send_all(msg,2);
}

void ViewProtocol::stand() {
    char msg[3] = "sd";
    socket.send_all(msg,2);
}

void ViewProtocol::stopShooting() {
    char msg[3] = "ss";
    socket.send_all(msg,2);
}
int receiveNumber(Socket& skt){

    unsigned int numeroRecibido;
    char recibido[4];
    
    skt.receive_all(recibido,4);

    unsigned int temp = *(unsigned int*)recibido;
    numeroRecibido = ntohl(temp);
    return (int)numeroRecibido;
}

void ViewProtocol::update(Scene& scene){

    //scene.setBullets(std::move(lTemp));
    std::list<std::tuple<int,int>> lb;
    int recvy;
    int recvx = receiveNumber(socket);
    while(recvx != -1){
        recvy = receiveNumber(socket);
        lb.push_back(std::tuple<int,int>(recvx,recvy));
        recvx = receiveNumber(socket);
    }
    scene.setBullets(lb);
    int p = scene.getMaxPlayers();
    for (int i = 0; i < p; i++) {
       //scene.setBullets(std::move(lTemp));
       scene.setPositionX(receiveNumber(socket), i + 1);
       scene.setPositionY(receiveNumber(socket), i + 1);
       scene.setVelocityX(receiveNumber(socket), i + 1);
       scene.setVelocityY(receiveNumber(socket), i + 1);
       scene.setHitPoints(receiveNumber(socket), i + 1);
       scene.setWalking(receiveNumber(socket), i + 1);
       scene.setAirborne(receiveNumber(socket), i + 1);
       scene.setCrouching(receiveNumber(socket), i + 1);
       scene.setLookingRight(receiveNumber(socket), i + 1);
       scene.setDead(receiveNumber(socket), i + 1);
       scene.setShooting(receiveNumber(socket), i + 1);
       scene.setAimDirection(receiveNumber(socket), i + 1);
   }
    scene.setCameraX(receiveNumber(socket));
    scene.setCameraY(receiveNumber(socket));
    scene.setLevel(receiveNumber(socket));
    scene.setCurrentPlayers(receiveNumber(socket));


}
