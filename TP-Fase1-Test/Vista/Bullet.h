//
// Created by tito on 17/09/18.
//

#ifndef TP_FASE1_TEST_BULET_H
#define TP_FASE1_TEST_BULET_H


#include "Viewable.h"

class Bullet : public Viewable {
    Bullet(Window window);
    void render(Scene scene);
};


#endif //TP_FASE1_TEST_BULET_H
