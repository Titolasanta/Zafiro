//
// Created by tito on 07/09/18.
//

#include "Pasto.h"

Pasto::Pasto(Window *window) : Viewable(window,"../escenario/pasto.png") {}

void Pasto::render(Scene &scene) {
    this->renderList(scene.plataforms());
}