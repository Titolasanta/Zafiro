//
// Created by tito on 13/09/18.
//

#include <./Modelo/Model.h>
#include "Controller.h"
#include "Logger.h"

extern Logger *gplogger;

Controller::Controller(View &view, Model& model) : view(view),model(model){}

void Controller::processEvent(SDL_Event e) {

    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_SPACE) model.jump();
        if (e.key.keysym.sym == SDLK_RIGHT) model.moveRight();
        if (e.key.keysym.sym == SDLK_LEFT) model.moveLeft();
        if (e.key.keysym.sym == SDLK_DOWN) model.aimDown();
        if (e.key.keysym.sym == SDLK_UP) model.aimUp();
        if (e.key.keysym.sym == SDLK_LCTRL) model.crouch();
    }

    if (e.type == SDL_KEYUP) {
        if (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_LEFT) model.stop();
        if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_UP)  model.aimStraight();
        if (e.key.keysym.sym == SDLK_LCTRL) model.stand();
    }
}

void Controller::show() {

    gplogger->log(1,"se llama show de controler\n");
    model.update(scene);
    view.render(scene);
}