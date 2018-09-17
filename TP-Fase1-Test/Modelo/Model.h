//
// Created by tito on 07/09/18.
//

#ifndef TP_FASE1_TEST_MODEL_H
#define TP_FASE1_TEST_MODEL_H


#include <SDL_events.h>
#include "Vista/Scene.h"
#include "Character.h"

class Model {
    private:
        int level;
        Character player1;
        //Character player2;

    public:
        Model();
        ~Model(){}
        void update(Scene&);
        void moveRight();
        void moveLeft();
        void aimDown();
        void aimStraight();
        void aimUp();
        void stop();
        void jump();
        void time();


};


#endif //TP_FASE1_TEST_MODEL_H
