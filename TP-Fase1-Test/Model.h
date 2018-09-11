//
// Created by tito on 07/09/18.
//

#ifndef TP_FASE1_TEST_MODEL_H
#define TP_FASE1_TEST_MODEL_H


#include <SDL_events.h>
#include "Scene.h"

class Model {
public:
    Model(Scene &scene);

    void update(SDL_Event event);

private:
    Scene& scene;

};


#endif //TP_FASE1_TEST_MODEL_H
