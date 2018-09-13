//
// Created by tito on 07/09/18.
//

#include "Viewable.h"
#include "Window.h"
#include "Exception.h"

Viewable::Viewable(Window* window,std::string imgpath) : imgPath(imgpath),texture(std::move(window->createImgTexture(0xFF, 0xFF, 0xFF) ) )
{
    if(this->imgPath.empty())
        throw OSError("no se setea el imgPath de Viewable");

    texture.loadFromFile(this->imgPath);

}

void Viewable::render(int x, int y) {
    texture.render(x,y);
}