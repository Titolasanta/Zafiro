//
// Created by tito on 07/09/18.
//
#ifndef PIEDRA_H
#define PIEDRA_H

#include "Viewable.h"

class Piedra : public Viewable{

public:
    explicit Piedra(Window* window);
    void render(Scene& scene,SDL_Rect* camera);
    
};

#endif