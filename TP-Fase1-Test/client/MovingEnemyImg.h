//
// Created by tito on 07/11/18.
//

#ifndef TP_FASE1_TEST_STATICENEMYIMG_H
#define TP_FASE1_TEST_STATICENEMYIMG_H
#include "Window.h"
#include "Viewable.h"

class MovingEnemyImg {

private:
    ImgTexture texture;
    SDL_Rect mobileRect[7];

public:
    explicit MovingEnemyImg(Window* window);
    void render(Scene& scene,SDL_Rect *cam);

};

#endif //TP_FASE1_TEST_STATICENEMYIMG_H
