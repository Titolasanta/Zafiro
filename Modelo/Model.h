//
// Created by tito on 07/09/18.
//

#ifndef TP_FASE1_TEST_MODEL_H
#define TP_FASE1_TEST_MODEL_H


#include <SDL_events.h>
#include "Scene.h"
#include "Character.h"

class Model {
    private:
        Scene& scene;
        int level;
        Character player1;
        Character player2;

    public:
        Model(Scene&);
        void update(SDL_Event event);


};


#endif //TP_FASE1_TEST_MODEL_H
