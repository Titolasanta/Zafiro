//
// Created by tito on 13/09/18.
//

#ifndef TP_FASE1_TEST_CONTROLLER_H
#define TP_FASE1_TEST_CONTROLLER_H

#include "View.h"
#include "../common/Socket.h"
#include "ViewProtocol.h"

class Controller {

public:
    void show();
    void processEvent(SDL_Event);
    Controller(View& view, Socket& skt,Socket& sktAux);
    void startGame();

    void readChar(SDL_Event);
    void nextValidation();
    void unsuccesfullValidation();

private:
    View& view;
    Socket sktAux;
    ViewProtocol protocol;
    Scene scene;
    bool validated = false;
    bool onPass = false;
    std::string UvalidationData;
    std::string PvalidationData;
};


#endif //TP_FASE1_TEST_CONTROLLER_H
