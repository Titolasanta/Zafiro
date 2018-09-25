//
// Created by tito on 07/09/18.
//

#ifndef TP_FASE1_TEST_VIEWABLE_H

#define TP_FASE1_TEST_VIEWABLE_H


#include "ImgTexture.h"
#include "Window.h"
#include "Scene.h"

class Viewable {
public:
    Viewable(Window* window,std::string imgpath,int x,int y,int w,int h);
    void renderList(std::list<std::tuple<int,int>> list,SDL_Rect*);
    void renderList(std::list<std::tuple<int,int,int>> list,SDL_Rect* camera);
protected:
    std::string imgPath;
    const SDL_Rect clip;
    ImgTexture texture;
};
#endif //TP_FASE1_TEST_VIEWABLE_H
