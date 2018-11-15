//
// Created by tito on 14/11/18.
//

#ifndef TP_FASE1_TEST_BOSSSPRITE_H
#define TP_FASE1_TEST_BOSSSPRITE_H


#include "ImgTexture.h"
#include "Window.h"
#include "../common/Scene.h"

class BossSprite {
public:

    explicit BossSprite(Window* window);
    void render(Scene&);
private:
    ImgTexture *spriteTexture[3];
    ImgTexture spriteTexture0;
    ImgTexture spriteTexture1;
    ImgTexture spriteTexture2;
    
    int currentFrame = 0;
};


#endif //TP_FASE1_TEST_BOSSSPRITE_H
