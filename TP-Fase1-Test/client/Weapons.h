//
// Created by tito on 18/11/18.
//

#ifndef TP_FASE1_TEST_WEAPONS_H
#define TP_FASE1_TEST_WEAPONS_H


#include "Viewable.h"

class Weapons : public Viewable {
public:
    Weapons(Window *window);
    void render(Scene &scene,SDL_Rect* camera);
private:
    SDL_Rect rect1;
    SDL_Rect rect2;

};


#endif //TP_FASE1_TEST_WEAPONS_H
