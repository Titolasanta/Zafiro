//
// Created by tito on 07/09/18.
//

#include "Pasto.h"
#include "Logger.h"

extern Logger *gplogger;
Pasto::Pasto(Window *window) : Viewable(window,"../escenario/pasto.png",0,0,69,36) {

    gplogger->log(1,"se crea Pasto\n");
}

void Pasto::render(Scene &scene) {
    this->renderList(scene.plataforms());
}