//
// Created by tito on 07/09/18.
//
#ifndef PIEDRA_H
#define PIEDRA_H

#include "Viewable.h"

class Piedra : public Viewable{
public:
    Piedra(Window* window);
    void renderHalf(int,int);
    void render(Scene& scene);
    
};





#endif