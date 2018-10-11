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


    Controller(View& view, Socket& skt);

private:
    View& view;
    ViewProtocol protocol;
    Scene scene;
};


#endif //TP_FASE1_TEST_CONTROLLER_H
