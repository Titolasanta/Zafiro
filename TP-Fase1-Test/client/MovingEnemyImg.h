//
// Created by tito on 07/11/18.
//

#ifndef TP_FASE1_TEST_STATICENEMYIMG_H
#define TP_FASE1_TEST_STATICENEMYIMG_H
#include "Window.h"
#include "Viewable.h"


class MovingEnemyImg {
public:
    MovingEnemyImg(Window* window);
    void render(Scene& scene,SDL_Rect *cam);
private:
    ImgTexture texture;
    SDL_Rect mobileRect[7];
    
};


#endif //TP_FASE1_TEST_STATICENEMYIMG_H
