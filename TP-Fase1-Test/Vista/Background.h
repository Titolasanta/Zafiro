//
// Created by tito on 17/09/18.
//

#ifndef TP_FASE1_TEST_FONDO_H
#define TP_FASE1_TEST_FONDO_H

#include "Window.h"
#include "Scene.h"

//The dimensions of the level
const int LEVEL_WIDTH = 3456;
const int LEVEL_HEIGHT = 245;

class Background  {
public:
    Background(Window&,int);
    void render(Scene&);

    SDL_Rect *getCamera();

    void setCamera(SDL_Rect *camera);

private:
    ImgTexture img1;
    ImgTexture img2;
    ImgTexture img3;
    //The camera area, area to be rendered
    SDL_Rect camera = { 0, 0, 800, 600 };
};


#endif //TP_FASE1_TEST_FONDO_H
