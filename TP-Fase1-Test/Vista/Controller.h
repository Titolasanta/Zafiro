//
// Created by tito on 13/09/18.
//

#ifndef TP_FASE1_TEST_CONTROLLER_H
#define TP_FASE1_TEST_CONTROLLER_H


#include <./Modelo/Model.h>
#include "View.h"

class Controller {

public:
    void show();
    void processEvent(SDL_Event);


    Controller(View& view, Model& model);

private:
    View& view;
    Model& model;
    Scene scene;
};


#endif //TP_FASE1_TEST_CONTROLLER_H
