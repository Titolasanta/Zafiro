//
// Created by tito on 07/09/18.
//

#ifndef TP_FASE1_TEST_VIEWABLE_H

#define TP_FASE1_TEST_VIEWABLE_H


#include "ImgTexture.h"
#include "Window.h"
#include "../common/Scene.h"

class Viewable {
public:
    Viewable(Window* window,std::string imgpath,int x,int y,int w,int h);
    Viewable(Window* window,std::string imgpath);
    void renderBulletList(std::list<std::tuple<int,int,int>> list,SDL_Rect*);
    void renderList(std::list<std::tuple<int,int,int>> list,SDL_Rect* camera);
    void renderList(std::list<Enemy> lista,SDL_Rect* camera);
    void setXYWH(int, int, int, int);
protected:
    std::string imgPath;
    SDL_Rect clip;
    ImgTexture texture;
};
#endif //TP_FASE1_TEST_VIEWABLE_H
