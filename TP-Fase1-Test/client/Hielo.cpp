//
// Created by tito on 25/09/18.
//

#include "Hielo.h"
#include "../common/Logger.h"

extern Logger *gplogger;
Hielo::Hielo(Window *window) : Viewable(window,"../escenario/hielo.png",0,0,78,100) {

    gplogger->log(3,"Se crea Hielo de View");
}

void Hielo::render(Scene &scene,SDL_Rect* camera) {
    this->renderList(scene.getLPlataformHielo(),camera);
}