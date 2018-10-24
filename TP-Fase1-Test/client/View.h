//
// Created by tito on 07/09/18.
//

#ifndef TP_FASE1_TEST_VIEW_H
#define TP_FASE1_TEST_VIEW_H


#include "Window.h"
#include "SpriteHandler.h"
#include "SdlImgInit.h"
#include "SdlInit.h"
#include "PlataformaBlanda.h"
#include "Piedra.h"
#include "Background.h"
#include "Bullet.h"
#include "PlataformaDura.h"
#include "Ice.h"
#include "commonTextTexture.h"
#include "commonSdlTtfInit.h"

class View {

public:
    View(int SCREEN_WIDTH, int SCREEN_HEIGHT);
    void setId(int id);
    void changeLevel(Scene& scene);
    void render(Scene& scene);
    void moveBackground(int dir);
    void renderValidationScreen(std::string&,std::string&);
    void fullHouseMesage();
    void invalidLoginMesage();
    void conexionFail();
    void conexionDown();
    void waiting();
private:
    int id;
    SdlImgInit z;
    SdlInit x;
    SdlTtfInit y;
    Window window;
    SpriteHandler personajes;
    Background background;
//Scene& scene;
    Piedra piedra;
    Pasto pasto;
    PlataformaDura plataformaDura;
    Bullet bullet;
    Ice hielo;
    TextTexture txt;
    TextTexture insert1;
    TextTexture insert2;
    TextTexture usr;
    TextTexture pass;

    int level=1;
    SDL_Rect * camera = NULL;

};



#endif //TP_FASE1_TEST_VIEW_H
