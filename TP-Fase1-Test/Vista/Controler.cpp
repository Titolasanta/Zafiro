//
// Created by tito on 13/09/18.
//

#include <./Modelo/Model.h>
#include "Controler.h"
#include "Logger.h"

extern Logger *gplogger;

Controler::Controler(View &view, Model& model) : view(view),model(model){}

void Controler::processEvent(SDL_Event e) {

    if (e.type == SDL_KEYDOWN) {

        if (e.key.keysym.sym == SDLK_SPACE) {
            model.jump();
        }

        if (e.key.keysym.sym == SDLK_RIGHT) {
            model.moveRight();
        }

        if (e.key.keysym.sym == SDLK_LEFT) {
            model.moveLeft();
        }

        if (e.key.keysym.sym == SDLK_DOWN) {
            model.aimDown();
        }
        if (e.key.keysym.sym == SDLK_UP) {
            model.aimUp();
        }
    }


    if (e.type == SDL_KEYUP){
        if (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_LEFT) {
            model.stop();
        }
        if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_UP) {
            model.aimStraight();
        }
    }
}

void Controler::show() {

    gplogger->log(1,"se llama show de controler\n");
    model.update(scene);
    view.render(scene);
}