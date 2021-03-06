//
// Created by tito on 07/09/18.
//

#ifndef TP_FASE1_TEST_VIEW_H
#define TP_FASE1_TEST_VIEW_H


#include "Window.h"
#include "SpriteHandler.h"
#include "SdlInit.h"
#include "PlataformaBlanda.h"
#include "Piedra.h"
#include "Background.h"
#include "Bullet.h"
#include "PlataformaDura.h"
#include "Ice.h"
#include "commonTextTexture.h"
#include "commonSdlTtfInit.h"
#include "MovingEnemyImg.h"
#include "Sound.h"
#include "Weapons.h"

class View {

private:

    int id;
    int currentImage = 0;
    SdlInit x;
    SdlTtfInit y;
    Window window;
    SpriteHandler sprites;
    Background background;
    Piedra piedra;
    Pasto pasto;
    PlataformaDura plataformaDura;
    Bullet bullet;
    Ice hielo;
    TextTexture txt;
    ImgTexture immortal;
    TextTexture insert1;
    TextTexture insert2;
    TextTexture insert2bis;
    TextTexture usr;
    TextTexture pass;
    ImgTexture loginImages[4];
    TextTexture score;
    Sound sound;
    MovingEnemyImg staticEnemyImg;
    Weapons weapons;
    int level=1;
    SDL_Rect * camera = nullptr;
    int inLevelSummary = 0;

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
    void conexionFail2();
    void conexionDown();
    void waiting();
    void waiting_for_players();
    void levelSummary(Scene& scene);
    void endOfGameScreen();
    int isInLevelSummary();
    int getLevel();
    Sound& getSound();
    void setInLevelSummary(int ils) { inLevelSummary = ils; }

};

#endif //TP_FASE1_TEST_VIEW_H
