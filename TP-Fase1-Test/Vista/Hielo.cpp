//
// Created by tito on 25/09/18.
//

#include "Hielo.h"
#include "Logger.h"

extern Logger *gplogger;
Hielo::Hielo(Window *window) : Viewable(window,"../escenario/hielo.png",0,0,79,29) {

    gplogger->log(2,"se crea Hielo\n");
}

void Hielo::render(Scene &scene,SDL_Rect* camera) {
    this->renderList(scene.getLPlataformHielo(),camera);
}