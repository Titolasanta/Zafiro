//
// Created by tito on 07/09/18.
//

#ifndef TP_FASE1_TEST_PASTO_H
#define TP_FASE1_TEST_PASTO_H

#include "Scene.h"
#include "Viewable.h"

class Pasto : public Viewable{
public:
    //dibuja la lista de plataformas
    void render(Scene& scene);
    Pasto(Window* window);

};


#endif //TP_FASE1_TEST_PASTO_H