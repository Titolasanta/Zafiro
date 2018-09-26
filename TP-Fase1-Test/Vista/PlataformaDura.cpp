//
// Created by tito on 25/09/18.
//

#include "PlataformaDura.h"
#include "Logger.h"

extern Logger *gplogger;
PlataformaDura::PlataformaDura(Window *window) : Viewable(window,"../escenario/hierro.png",0,0,69,36) {

    gplogger->log(3,"Se crea una plataforma dura");
}

void PlataformaDura::render(Scene &scene,SDL_Rect* camera) {
    this->renderList(scene.getLPlataformHard(),camera);
}