//
// Created by tito on 07/09/18.
//

#include "Pasto.h"

Pasto::Pasto(Window *window) : Viewable(window,"/home/tito/Desktop/Tallar/github/TP-Fase1-Test/escenario/pasto.png") {}

void Pasto::render(Scene &scene) {
    this->renderList(scene.plataforms());
}