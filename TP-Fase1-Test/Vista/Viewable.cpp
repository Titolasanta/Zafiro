//
// Created by tito on 07/09/18.
//

#include "Viewable.h"
#include "Window.h"
#include "Exception.h"
#include <list>
#include <tuple>
#include "Scene.h"

Viewable::Viewable(Window* window,std::string imgpath) : imgPath(imgpath),texture(std::move(window->createImgTexture(0xFF, 0xFF, 0xFF) ) )
{
    if(this->imgPath.empty())
        throw OSError("no se setea el imgPath de Viewable");

    texture.loadFromFile(this->imgPath);

}

void Viewable::renderList(std::list<std::tuple<int,int>> lista) {

    for (std::list< std::tuple<int,int>>::iterator it = lista.begin(); it != lista.end(); it++)
        texture.render( std::get<0>(*it), std::get<1>(*it) );

}