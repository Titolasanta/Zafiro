//
// Created by tito on 07/09/18.
//

#include "Viewable.h"
#include "Window.h"
#include "../common/Exception.h"
#include <list>
#include <tuple>
#include <iostream>
#include "../common/Scene.h"

#define ENEMYID -1

Viewable::Viewable(Window* window,std::string imgpath,int x,int y,int w,int h) : imgPath(std::move(imgpath)),clip{x,y,w,h},texture(std::move(window->createImgTexture(0xFF, 0xFF, 0xFF) ) )
{

    if(this->imgPath.empty())
        throw OSError("no se setea el imgPath de Viewable");

    texture.loadFromFile(this->imgPath);

}

Viewable::Viewable(Window* window,std::string imgpath) : imgPath(std::move(imgpath)),texture(std::move(window->createImgTexture(0xFF, 0xFF, 0xFF) ) )
{

    if(this->imgPath.empty())
        throw OSError("no se setea el imgPath de Viewable");

    texture.loadFromFile(this->imgPath);

}

void Viewable::renderBulletList(std::list<std::tuple<int,int,int>> lista,SDL_Rect* camera) {
    for (auto it = lista.begin(); it != lista.end(); it++) {
        int id = std::get<2>(*it);
        if (id == ENEMYID) setXYWH(14, 21, 10, 10);
        else setXYWH(14, 2,10,10);
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
void Viewable::renderList(std::list<Enemy> lista,SDL_Rect* camera) {
    for (auto it = lista.begin(); it != lista.end(); it++) {
        texture.render(it->getPosX() - camera->x, it->getPosY() - camera->y, &clip);
    }
}

void Viewable::setXYWH(int x, int y, int w, int h){
    const SDL_Rect newclip = {x, y, w, h};
    clip = newclip;
}