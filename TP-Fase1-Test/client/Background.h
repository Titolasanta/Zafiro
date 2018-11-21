//
// Created by tito on 17/09/18.
//

#ifndef TP_FASE1_TEST_FONDO_H
#define TP_FASE1_TEST_FONDO_H

#include "Window.h"
#include "../common/Scene.h"

class Background  {

private:
    ImgTexture img1;
    ImgTexture img2;
    ImgTexture img3;
    int scrollingOffset=0;
    bool scrollVertical = false;
    int scrollingCatarata = -2900;
    SDL_Rect camera = { 0, 0, 800, 600 };

public:
    Background(Window&,int);
    void render(Scene&,SDL_Rect&,int scrollingOffset,int);
    void changeLevel(int);
    int getScrollingOffset();
    void setScrollingOffset(int scrollingOffset);

};


#endif //TP_FASE1_TEST_FONDO_H
