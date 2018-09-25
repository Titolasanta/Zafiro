//
// Created by tito on 07/09/18.
//

#include "Viewable.h"
#include "Window.h"
#include "Exception.h"
#include <list>
#include <tuple>
#include <iostream>
#include "Scene.h"

Viewable::Viewable(Window* window,std::string imgpath,int x,int y,int w,int h) : imgPath(imgpath),clip{x,y,w,h},texture(std::move(window->createImgTexture(0xFF, 0xFF, 0xFF) ) )
{
    printf("%d\n",clip.w);

    if(this->imgPath.empty())
        throw OSError("no se setea el imgPath de Viewable");

    texture.loadFromFile(this->imgPath);

}

void Viewable::renderList(std::list<std::tuple<int,int>> lista,SDL_Rect* camera) {

    for (auto it = lista.begin(); it != lista.end(); it++) {
        texture.render(std::get<0>(*it)-camera->x, std::get<1>(*it)-camera->y,&clip);
    }
}

void Viewable::renderList(std::list<std::tuple<int,int,int>> lista,SDL_Rect* camera) {

    for (auto it = lista.begin(); it != lista.end(); it++) {
        int i = 0;
        while(std::get<2>(*it) - i * clip.w  > clip.w){
            texture.render(std::get<0>(*it) + clip.w * i-camera->x, std::get<1>(*it)-camera->y,&clip);
            i++;
        }
        SDL_Rect clipTemp = clip;
        clipTemp.w = std::get<2>(*it) - i * clip.w;
        texture.render(std::get<0>(*it)+ clip.w * i-camera->x, std::get<1>(*it)-camera->y,&clipTemp);
    }
}