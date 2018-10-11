//
// Created by tito on 07/09/18.
//

#include "PlataformaBlanda.h"
#include "../common/Logger.h"

extern Logger *gplogger;
Pasto::Pasto(Window *window) : Viewable(window,"../escenario/pasto.png",0,0,64,61) {

    gplogger->log(3,"Se crea una plataforma blanda");
}

void Pasto::render(Scene &scene,SDL_Rect* camera) {
    this->renderList(scene.getLPlataformSoft(),camera);
}