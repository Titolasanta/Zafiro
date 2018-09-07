//
// Created by tito on 07/09/18.
//

#ifndef TP_FASE1_TEST_VIEW_H
#define TP_FASE1_TEST_VIEW_H


#include "Window.h"
#include "Personajes.h"
#include "SdlImgInit.h"
#include "SdlInit.h"

class View {

public:
    View(int SCREEN_WIDTH, int SCREEN_HEIGHT,Scene scene);

    void render();

private:
    SdlImgInit z;
    SdlInit x;
    Window window;
    Personajes personajes;
    Scene& scene;
};


#endif //TP_FASE1_TEST_VIEW_H
