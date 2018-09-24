//
// Created by tito on 07/09/18.
//

#ifndef TP_FASE1_TEST_VIEW_H
#define TP_FASE1_TEST_VIEW_H


#include "Window.h"
#include "Personajes.h"
#include "SdlImgInit.h"
#include "SdlInit.h"
#include "Pasto.h"
#include "Piedra.h"
#include "Background.h"

class View {

public:
    View(int SCREEN_WIDTH, int SCREEN_HEIGHT);

    void render(Scene& scene);

private:
    SdlImgInit z;
    SdlInit x;
    Window window;
    Personajes personajes;
    Background background;
//Scene& scene;
    Piedra piedra;
    Pasto pasto;
    SDL_Rect* camera = NULL;

};



#endif //TP_FASE1_TEST_VIEW_H
