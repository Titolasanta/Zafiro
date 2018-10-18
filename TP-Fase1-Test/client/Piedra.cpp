//
// Created by tito on 07/09/18.
//

#include <iostream>
#include "Piedra.h"

#include "Viewable.h"
#include "../common/Logger.h"

extern Logger* gplogger;
Piedra::Piedra(Window *window) : Viewable(window,"../escenario/piedra.png",0,0,64,64){

    gplogger->log(3,"Se crea Piedra de view");
}

void Piedra::renderHalf(int x, int y) {

    texture.render(x,y,0,71,0,34);
}


void Piedra::render(Scene& scene,SDL_Rect* camera){
    int x;
    int y;
    int w;
    auto lista = scene.getLPlatformGrass();
    for (auto it = lista.begin(); it != lista.end(); it++) {
        y = std::get<1>(*it);
        y += 4;
        while(y < 1500) {
            w = std::get<2>(*it);
            x = std::get<0>(*it);
            while(w > clip.w){
                texture.render(x-camera->x, y-camera->y,&clip);
                x += clip.w;
                w -= clip.w;
            }
            SDL_Rect clipTemp = clip;
            clipTemp.w = w;
            texture.render(x-camera->x, y-camera->y,&clipTemp);
            y += 64;
        }
    }
}