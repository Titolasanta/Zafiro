//
// Created by tito on 05/09/18.
//

#ifndef TP_FASE1_TEST_PERSONAJES_H
#define TP_FASE1_TEST_PERSONAJES_H


#include "Window.h"
#include "Scene.h"
#include "SpriteRojo.h"

class Personajes {
public:
    explicit Personajes(Window* window);
    void render(Scene scene);

private:
    ImgTexture rojo;
    SpriteRojo rojoFrames;
    int frameActualRojo;

};


#endif //TP_FASE1_TEST_PERSONAJES_H
