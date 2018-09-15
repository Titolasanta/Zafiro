//
// Created by tito on 13/09/18.
//

#ifndef TP_FASE1_TEST_CONTROLER_H
#define TP_FASE1_TEST_CONTROLER_H


#include <dumyModel.h>
#include "View.h"

class Controler {

public:
    void show();
    void proces_event(SDL_Event e);


    Controler(View& view, dumyModel& model);

private:
    View& view;
    dumyModel& model;
    Scene scene;
};


#endif //TP_FASE1_TEST_CONTROLER_H