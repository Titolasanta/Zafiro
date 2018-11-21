//
// Created by tito on 08/10/18.
//

#ifndef TP_FASE1_TEST_VIEWPROTOCOL_H
#define TP_FASE1_TEST_VIEWPROTOCOL_H

#include "../common/Socket.h"
#include "../common/Scene.h"

class ViewProtocol {

private:

    Socket& socket;

public:

    explicit ViewProtocol(Socket &skt);
    void update(Scene& scene);
    void jump();
    void moveRight();
    void moveLeft();
    void aimDown();
    void aimUp();
    void crouch();
    void shoot();
    void stop();
    void aimStraight();
    void stand();
    void stopShooting();
    void immortal();

};

#endif //TP_FASE1_TEST_VIEWPROTOCOL_H
