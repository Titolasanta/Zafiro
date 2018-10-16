//
// Created by tito on 08/10/18.
//

#include <netinet/in.h>
#include "ViewProtocol.h"
#include "../common/Socket.h"
#include "../common/Scene.h"

ViewProtocol::ViewProtocol(Socket &skt) : socket(std::move(skt)) {}

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
    printf("%d\n",(int)numeroRecibido);
    return (int)numeroRecibido;
}

void ViewProtocol::update(Scene& scene){

    //scene.setBullets(std::move(lTemp));
    scene.setP1PositionX(receiveNumber(socket));
    scene.setP1PositionY(receiveNumber(socket));
    scene.setP1VelocityX(receiveNumber(socket));
    scene.setP1VelocityY(receiveNumber(socket));
    scene.setP1HitPoints(receiveNumber(socket));
    scene.setP1Walking(receiveNumber(socket));
    scene.setP1Airborne(receiveNumber(socket));
    scene.setP1Crouching(receiveNumber(socket));
    scene.setP1LookingRight(receiveNumber(socket));
    scene.setP1Dead(receiveNumber(socket));
    scene.setP1Shooting(receiveNumber(socket));
    
    scene.setCameraX(receiveNumber(socket));
    scene.setCameraY(receiveNumber(socket));
    scene.setLevel(receiveNumber(socket));
    scene.setP1AimDirection(receiveNumber(socket));

}
