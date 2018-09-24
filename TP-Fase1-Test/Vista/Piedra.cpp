//
// Created by tito on 07/09/18.
//

#include <iostream>
#include "Piedra.h"

#include "Viewable.h"
#include "Logger.h"

extern Logger* gplogger;
Piedra::Piedra(Window *window) : Viewable(window,"../escenario/piedra.png",0,0,71,68){

    gplogger->log(1,"se crea piedra de view\n");
}

void Piedra::renderHalf(int x, int y) {

    texture.render(x,y,0,71,0,34);
}


void Piedra::render(Scene& scene,SDL_Rect* camera){
    int x;
    int y;
    int w;
    auto lista = scene.plataforms();
    for (std::list< std::tuple<int,int,int>>::iterator it = lista.begin(); it != lista.end(); it++) {
        y = std::get<1>(*it);
        y += 34;
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
            y += 68;
        }
    }
}