//
// Created by tito on 17/09/18.
//

#ifndef TP_FASE1_TEST_BULET_H
#define TP_FASE1_TEST_BULET_H


#include "Viewable.h"

class Bullet : public Viewable {
public:
    Bullet(Window *window);
    void render(Scene &scene,SDL_Rect* camera);
};


#endif //TP_FASE1_TEST_BULET_H
