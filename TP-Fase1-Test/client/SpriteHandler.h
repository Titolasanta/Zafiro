//
// Created by tito on 05/09/18.
//

#ifndef TP_FASE1_TEST_PERSONAJES_H
#define TP_FASE1_TEST_PERSONAJES_H


#include "Window.h"
#include "Sprite.h"
#include "../common/Scene.h"

class SpriteHandler {

public:
    explicit SpriteHandler(Window* window);
    void render(Scene &scene, int cameraX, int cameraY);

private:
    ImgTexture spriteTexture;
    Sprite spritePositionHandler;
    int currentFrame[4] = {0, 0, 0, 0};
};


#endif //TP_FASE1_TEST_PERSONAJES_H
