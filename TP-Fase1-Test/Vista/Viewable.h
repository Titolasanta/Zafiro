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
    Viewable(Window* window,std::string imgpath);
    void renderList(std::list<std::tuple<int,int>> list);
protected:
    std::string imgPath;
    ImgTexture texture;
};
#endif //TP_FASE1_TEST_VIEWABLE_H
