//
// Created by tito on 25/09/18.
//

#ifndef TP_FASE1_TEST_PLATAFORMADURA_H
#define TP_FASE1_TEST_PLATAFORMADURA_H

#include "../common/Scene.h"
#include "Window.h"
#include "Viewable.h"

class PlataformaDura : public Viewable{

public:
    void render(Scene& scene,SDL_Rect* camera);
    explicit PlataformaDura(Window* window);
};

#endif //TP_FASE1_TEST_PLATAFORMADURA_H
