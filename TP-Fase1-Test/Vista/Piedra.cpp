//
// Created by tito on 07/09/18.
//

#include "Piedra.h"

#include "Viewable.h"

Piedra::Piedra(Window *window) : Viewable(window,"../escenario/piedra.png"){}

void Piedra::renderHalf(int x, int y) {

    texture.render(x,y,0,71,0,34);
}


void Piedra::render(Scene& scene){
    int x;
    int y;
    auto lista = scene.plataforms();
    for (std::list< std::tuple<int,int>>::iterator it = lista.begin(); it != lista.end(); it++) {
        x = std::get<0>(*it);
        y = std::get<1>(*it);
        y += 34;
        while(y < 1000) {
            texture.render(x, y);
            y += 68;

        }
    }
}