//
// Created by tito on 13/09/18.
//

#ifndef TP_FASE1_TEST_CONTROLER_H
#define TP_FASE1_TEST_CONTROLER_H


#include <Model.h>
#include "View.h"

class Controler {

public:
    void show();
    void processEvent(SDL_Event);


    Controler(View& view, Model& model);

private:
    View& view;
    Model& model;
    Scene scene;
};


#endif //TP_FASE1_TEST_CONTROLER_H
