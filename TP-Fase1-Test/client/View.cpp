//
// Created by tito on 07/09/18.
//

#include <string>
#include <zconf.h>
#include "View.h"
#include "SdlInit.h"
#include "SdlImgInit.h"
#include "SpriteHandler.h"
#include "../common/pugixml.hpp"
#include "../common/xml.h"
#include "../common/Logger.h"
#include <iostream>
extern Logger* gplogger;
extern pugi::xml_document *gXML_doc[2];

View::View(int SCREEN_WIDTH, int SCREEN_HEIGHT, int id)
: window("juego",SCREEN_WIDTH,SCREEN_HEIGHT),
personajes(&window),piedra(&window),plataformaDura(&window),hielo(&window),
pasto(&window),bullet(&window),background(window,1), id(id),txt(std::move(window.createTextTexture())),
pass(std::move(window.createTextTexture())),usr(std::move(window.createTextTexture()))
,insert1(std::move(window.createTextTexture())),insert2(std::move(window.createTextTexture()))
{
   // window.setRenderDrawColor(0x10  ,0x10,0xFF,0x120);
    std::string msg("Clave:");
    pass.loadFromRenderedText(msg);

    msg = "Usuario:";
    usr.loadFromRenderedText(msg);

    msg = "Ingrese sus datos";
    insert1.loadFromRenderedText(msg);

    msg = "esc para resetear los datos ingresados";
    insert2.loadFromRenderedText(msg);

    std::string windowName("juego");
    gplogger->log(3,"Se crea un View");

}

void View::render(Scene& scene) {

    if(level != scene.getLevel())
        changeLevel();

    if(level == 2) {
        moveBackground(scene.getVelocityY(id));
        if (scene.getPositionY(id) == 200 && scene.getPositionX(id) == 200) background.setScrollingOffset(-200);
    }else {
        moveBackground(scene.getVelocityX(id));
        if (scene.getPositionY(id) == 200 && scene.getPositionX(id) == 200) background.setScrollingOffset(0);
    }
    camera = scene.getCamera();

    window.redererClear();

    //background.render(scene);



    background.render(scene,*camera, background.getScrollingOffset(),level);


    if(level == 1)
        piedra.render(scene,camera);

    hielo.render(scene,camera);

    pasto.render(scene,camera);
    plataformaDura.render(scene,camera);
    bullet.render(scene,camera);
    personajes.render(scene,camera->x, camera->y);
    window.updateRenderer();

    //Center the camera over the player



}

void View::changeLevel() {
    ++level;
    background.changeLevel(level);
}

void View::moveBackground(int dir) {
    int newOffset= background.getScrollingOffset();
    if(dir > 0) --newOffset;
    if(dir < 0) ++newOffset;

    if (newOffset > 0) newOffset = 0;
    //if (newOffset < -3000) newOffset = -100;


    background.setScrollingOffset(newOffset);
}


void View::renderValidationScreen(std::string& Uinserted,std::string& Pinserted) {

    window.createRectangle(0,1000,0,800);

    insert1.render(100,70);
    insert2.render(100,100);

    usr.render(100,150);

    if(!Uinserted.empty()) {
        txt.loadFromRenderedText(Uinserted);
        txt.render(100, 180);
    }
    pass.render(100,250);
    if(!Pinserted.empty()) {
        txt.loadFromRenderedText(Pinserted);
        txt.render(100, 280);
    }
    window.updateRenderer();
}