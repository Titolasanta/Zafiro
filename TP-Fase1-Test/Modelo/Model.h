//
// Created by tito on 07/09/18.
//

#ifndef TP_FASE1_TEST_MODEL_H
#define TP_FASE1_TEST_MODEL_H


#include <SDL_events.h>
#include <Vista/Nivel.h>
#include "Vista/Scene.h"
#include "Character.h"

class Model {
    private:
        Nivel level;
        Character player1;
        //Character player2;

    public:
        Model(Nivel &initialLevel);
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
        std::list<std::tuple<int,int,int>> lPlataforms;
        void addPlataform(int xi,int xf, int y);
        void changeLevel(Nivel &nivel);

};


#endif //TP_FASE1_TEST_MODEL_H
