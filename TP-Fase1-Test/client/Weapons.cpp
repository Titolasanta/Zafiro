//
// Created by tito on 18/11/18.
//

#include "Weapons.h"
#include "../common/Logger.h"

extern Logger *gplogger;
Weapons::Weapons(Window *window) : Viewable(window,"../spirites/ContraSheet4.png"),
rect1{175, 4, 32, 32},rect2{141, 4, 32, 32}
{

    gplogger->log(3,"Se crea Bullet de vista");
}

void Weapons::render(Scene &scene,SDL_Rect* camera) {
    for (auto &it : *scene.getLWeapons()) {
        int tipo = std::get<2>(it);
        if(tipo == 1)
            texture.render(std::get<0>(it)-camera->x, std::get<1>(it)-camera->y,&rect1);
        else
            texture.render(std::get<0>(it)-camera->x, std::get<1>(it)-camera->y,&rect2);
    }
}