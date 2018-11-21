//
// Created by tito on 13/09/18.
//

#ifndef TP_FASE1_TEST_CONTROLLER_H
#define TP_FASE1_TEST_CONTROLLER_H

#include "View.h"
#include "../common/Socket.h"
#include "ViewProtocol.h"
#include "lifeSupport.h"

class Controller {

private:
    lifeSupport& ls;
    Socket& sktLatido;
    View& view;
    ViewProtocol protocol;
    Scene scene;
    int endOfMainMenu = 0;
    int timeTillNextShoot = 5 * 12;

public:
    void show();
    void processEvent(SDL_Event);
    Controller(View& view, Socket& skt,lifeSupport&,Socket& sktLatido);
    void startGame();

};


#endif //TP_FASE1_TEST_CONTROLLER_H
