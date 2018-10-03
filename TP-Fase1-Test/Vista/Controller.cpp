//
// Created by tito on 13/09/18.
//

#include <./Modelo/Model.h>
#include "Controller.h"
#include "Logger.h"
#include "pugixml.hpp"
#include "xml.h"

extern Logger *gplogger;
extern pugi::xml_document*gXML_doc[2];
extern pugi::xml_parse_result *gXML_parse_result;

Controller::Controller(View &view, Model& model) : view(view),model(model){
    if (*gXML_parse_result) cargar_plataformas(*gXML_doc[0], scene,model, 1, model.getLevelHeight(), model.getLevelWidth());     //No tenia idea de como hacer este
    else cargar_plataformas(*gXML_doc[1],scene, model, 1, model.getLevelHeight(), model.getLevelWidth()); //chequeo de otra manera

    gplogger->log(3, "Se crea el controlador");
}

void Controller::processEvent(SDL_Event e) {

    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_SPACE) model.jump();
        if (e.key.keysym.sym == SDLK_RIGHT) {
            model.moveRight();
           // view.moveBackground();
        }
        if (e.key.keysym.sym == SDLK_LEFT) model.moveLeft();
        if (e.key.keysym.sym == SDLK_DOWN) model.aimDown();
        if (e.key.keysym.sym == SDLK_UP) model.aimUp();
        if (e.key.keysym.sym == SDLK_LCTRL) model.crouch();
        if (e.key.keysym.sym == SDLK_x) model.shoot();
    }

    if (e.type == SDL_KEYUP) {
        if (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_LEFT) model.stop();
        if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_UP)  model.aimStraight();
        if (e.key.keysym.sym == SDLK_LCTRL) model.stand();
        if (e.key.keysym.sym == SDLK_x) model.stopShoot();
    }
}

void Controller::show() {
    model.update(scene);
    view.render(scene);
}