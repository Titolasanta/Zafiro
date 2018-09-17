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
    void render(Scene&);
private:
    ImgTexture img1;
    ImgTexture img2;
    ImgTexture img3;

};


#endif //TP_FASE1_TEST_FONDO_H
