//
// Created by tito on 17/09/18.
//

#ifndef TP_FASE1_TEST_FONDO_H
#define TP_FASE1_TEST_FONDO_H

#include "Window.h"
#include "Scene.h"

class Background  {
public:
    Background(Window&,int);
    void render(Scene&,SDL_Rect&,int scrollingOffset,int);

    SDL_Rect *getCamera();

    void setCamera(SDL_Rect *camera);

    void changeLevel(int);

private:
    ImgTexture img1;
    ImgTexture img2;
    ImgTexture img3;
    int scrollingOffset=0;
    bool scrollVertical = false;
    int scrollingCatarata = -2900;
public:
    ImgTexture &getImg1();
    int getScrollingOffset();
    void setScrollingOffset(int scrollingOffset);

private:
    //The camera area, area to be rendered
    SDL_Rect camera = { 0, 0, 800, 600 };
};


#endif //TP_FASE1_TEST_FONDO_H
