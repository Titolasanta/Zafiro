//
// Created by tito on 18/11/18.
//

#include "Weapons.h"
#include "../common/Logger.h"

extern Logger *gplogger;
Weapons::Weapons(Window *window) : Viewable(window,"../spirites/NES_contra_enemies2.png"),
rect1{411,153,66,66},rect2{207,153,66,66}
{

    gplogger->log(3,"Se crea Bullet de vista");
}

void Weapons::render(Scene &scene,SDL_Rect* camera) {
    for (auto it = scene.getLWeapons()->begin(); it != scene.getLWeapons()->end(); it++) {
        int tipo = std::get<2>(*it);
        if(tipo == 1)
            texture.render(std::get<0>(*it)-camera->x, std::get<1>(*it)-camera->y,&rect1);
        else
            texture.render(std::get<0>(*it)-camera->x, std::get<1>(*it)-camera->y,&rect2);
    }
}