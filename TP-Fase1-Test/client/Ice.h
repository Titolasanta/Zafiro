//
// Created by tito on 25/09/18.
//

#ifndef TP_FASE1_TEST_HIELO_H
#define TP_FASE1_TEST_HIELO_H


#include <SDL_rect.h>
#include "Viewable.h"

class Ice : public Viewable {
public:
    Ice(Window* window);
    void render(Scene& scene,SDL_Rect* cam);
};


#endif //TP_FASE1_TEST_HIELO_H
