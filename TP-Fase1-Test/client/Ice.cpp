//
// Created by tito on 25/09/18.
//

#include "Ice.h"
#include "../common/Logger.h"

extern Logger *gplogger;
Ice::Ice(Window *window) : Viewable(window,"../escenario/hielo.png",0,0,78,100) {
    gplogger->log(3,"Se crea Ice de View");
}

void Ice::render(Scene &scene,SDL_Rect* camera) {
    this->renderList(scene.getLPlatformIce(),camera);
}