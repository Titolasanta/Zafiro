//
// Created by tito on 07/09/18.
//

#include "Viewable.h"
#include "Window.h"
#include "Exception.h"
#include <list>
#include <tuple>
#include "Scene.h"

Viewable::Viewable(Window* window,std::string imgpath,int x,int y,int w,int h) : imgPath(imgpath),clip{x,y,w,h},texture(std::move(window->createImgTexture(0xFF, 0xFF, 0xFF) ) )
{
    printf("%d\n",clip.w);

    if(this->imgPath.empty())
        throw OSError("no se setea el imgPath de Viewable");

    texture.loadFromFile(this->imgPath);

}

void Viewable::renderList(std::list<std::tuple<int,int>> lista) {

    for (std::list< std::tuple<int,int>>::iterator it = lista.begin(); it != lista.end(); it++) {
        texture.render(std::get<0>(*it), std::get<1>(*it));
    }
}

void Viewable::renderList(std::list<std::tuple<int,int,int>> lista) {

    for (std::list< std::tuple<int,int,int>>::iterator it = lista.begin(); it != lista.end(); it++) {
        int i = 0;
        while(std::get<2>(*it) - i * clip.w  > clip.w){
            texture.render(std::get<0>(*it) + clip.w * i, std::get<1>(*it),&clip);
            i++;
        }
        SDL_Rect clipTemp = clip;
        clipTemp.w = std::get<2>(*it) - i * clip.w;
        texture.render(std::get<0>(*it)+ clip.w * i, std::get<1>(*it),&clipTemp);
    }
}