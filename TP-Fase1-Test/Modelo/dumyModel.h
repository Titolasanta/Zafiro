//
// Created by tito on 07/09/18.
//

#ifndef TP_FASE1_TEST_MODEL_H
#define TP_FASE1_TEST_MODEL_H


#include <SDL2/SDL_events.h>
#include "Vista/Scene.h"

class dumyModel {
public:
    dumyModel();
    void update(Scene &scene);

    void proces_event(SDL_Event event);

private:
    int moveX;

};


#endif //TP_FASE1_TEST_MODEL_H
