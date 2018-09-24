//
// Created by tito on 07/09/18.
//

#ifndef TP_FASE1_TEST_MODEL_H
#define TP_FASE1_TEST_MODEL_H


#include <SDL_events.h>
#include <Vista/Level.h>
#include "Vista/Scene.h"
#include "Character.h"
#include "Projectile.h"

class Model {
    private:
        Level level;
        Character player1;
        std::list<Projectile> lBullets;
        //Character player2;

    public:
        explicit Model(int initialLevel);
        ~Model() = default;
        void update(Scene&);
        void moveRight();
        void moveLeft();
        void aimDown();
        void aimStraight();
        void aimUp();
        void stop();
        void jump();
        void time();
        bool endOfLevel(Scene&);
        std::list<std::tuple<int,int,int>> lPlataforms;
        void addPlataform(int x, int y, int w);
        void changeLevel(Level,Scene&);
        void crouch();
        void stand();
        int getLevelWidth();
        int getLevelHeight();
        void shoot();
};


#endif //TP_FASE1_TEST_MODEL_H
