//
// Created by tito on 07/09/18.
//

#include "Piedra.h"


Piedra::Piedra(Window *window) : Viewable(window,"/home/tito/Desktop/Tallar/github/TP-Fase1-Test/escenario/piedra.png"){}

void Piedra::renderHalf(int x, int y) {

    texture.render(x,y,0,71,0,34);
}