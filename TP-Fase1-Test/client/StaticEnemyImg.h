//
// Created by tito on 07/11/18.
//

#ifndef TP_FASE1_TEST_STATICENEMYIMG_H
#define TP_FASE1_TEST_STATICENEMYIMG_H
#include "Window.h"
#include "Viewable.h"


class StaticEnemyImg : public Viewable {
public:
    StaticEnemyImg(Window* window);
    void render(Scene& scene,SDL_Rect *cam);
private:
    
};


#endif //TP_FASE1_TEST_STATICENEMYIMG_H
